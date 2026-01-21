/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_engine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:31:56 by injah             #+#    #+#             */
/*   Updated: 2026/01/21 11:46:13 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

void ui_destroy_widget(t_widget *widget)
{
	int	i;

	if (widget->childs)
	{
		i = 0;
		while (widget->childs[i])
		{
			ui_destroy_widget(widget->childs[i]);
			i++;
		}
		free(widget->childs);
	}
	if (widget->texture)
		SDL_DestroyTexture(widget->texture);
	if (widget->cursor)
		SDL_FreeCursor(widget->cursor);
	if (widget->destroy)
		widget->destroy(widget);
	free(widget->data);
	free(widget);
}

static void ui_render_widget(t_widget *widget)
{
	int	i;

	if (widget->is_visible == false)
		return ;
	SDL_RenderSetClipRect(widget->renderer, &widget->clip);
	widget->render(widget);
	SDL_RenderSetClipRect(widget->renderer, NULL);
	if (widget->childs)
	{
		i = 0;
		while (widget->childs[i])
		{
			ui_render_widget(widget->childs[i]);
			i++;
		}
	}
	SDL_RenderSetClipRect(widget->renderer, &widget->clip);
	if (widget->is_resizable)
	{
		SDL_SetRenderDrawColor(widget->renderer, 100, 100, 100, 255);
		SDL_RenderDrawRect(widget->renderer, &(SDL_Rect){widget->absolute.x + widget->absolute.w - 10, widget->absolute.y, 10, widget->absolute.h});
		SDL_RenderDrawRect(widget->renderer, &(SDL_Rect){widget->absolute.x, widget->absolute.y + widget->absolute.h - 10, widget->absolute.w, 10});
	}
	SDL_RenderSetClipRect(widget->renderer, NULL);
}

static void ui_find_hovered_widget(t_widget *widget)
{
	int	i;
	t_core	*core;

	core = widget->core;
	if (widget->is_visible == false)
		return ;
	if (SDL_PointInRect(&core->mouse.position, &widget->absolute))
	{
		core->hovered_widget = widget;
		if (widget->childs)
		{
			i = 0;
			while (widget->childs[i])
			{
				ui_find_hovered_widget(widget->childs[i]);
				i++;
			}
		}
	}
		
}



void	ui_build_widget(t_widget *widget)
{
	int	i;

	i = 0;
	if (widget->build)
		widget->build(widget);
	if (widget->childs)
		while (widget->childs[i])
		{
			ui_build_widget(widget->childs[i]);
			i++;
		}
}

void	ui_init_widget(t_widget *widget)
{
	int	i;

	widget->absolute = ui_get_absolute_rect(widget);
	widget->clip = ui_get_clip_rect(widget);
	ui_widget_change_state(widget, NORMAL);
	if (widget->childs)
	{
		i = 0;
		while (widget->childs[i])
		{
			ui_init_widget(widget->childs[i]);
			i++;
		}
	}
}

void	ui_global_build(t_core *core)
{
	int	i;

	i = 0;
	while (core->windows[i])
	{
		ui_init_widget(core->windows[i]);
		ui_build_widget(core->windows[i]);
		ui_render_widget(core->windows[i]);
		SDL_RenderPresent(core->windows[i]->renderer);
		i++;
	}
}

static void	ui_event_widget(t_widget *widget)
{
	int	i;

	i = 0;
	if (widget->is_visible == false)
		return ;
	if (widget->event)
		widget->event(widget);
	if (widget->childs)
		while (widget->childs[i])
		{
			ui_event_widget(widget->childs[i]);
			i++;
		}
}

static void	ui_global_update(t_core *core)
{
	int				i;
	t_window_data	*data;

	i = 0;
	while (core->windows[i])
	{
		data = core->windows[i]->data;
		if (SDL_GetWindowID(SDL_GetMouseFocus()) == data->id || core->event.window.windowID == data->id)
		{
			if (core->dragged_widget)
				ui_widget_drag(core->dragged_widget);
			if (core->resizing_widget)
				ui_widget_resize(core->resizing_widget);
			ui_init_widget(core->windows[i]);
			ui_find_hovered_widget(core->windows[i]);
			if (core->hovered_widget)
			{
				ui_set_cursor(core, core->hovered_widget->cursor);
				if (core->mouse.buttons[SDL_BUTTON_LEFT] == true)
				{
					core->focused_widget = core->hovered_widget;
					ui_widget_change_state(core->hovered_widget, CLICKED);
				}
				else
					ui_widget_change_state(core->hovered_widget, HOVERED);
				
			}
			ui_event_widget(core->windows[i]);
			if (core->focused_widget)
			{
				if (core->focused_widget->update)
					core->focused_widget->update(core->focused_widget);
				if (core->focused_widget->state == CLICKED)
				{
					ui_widget_call_onclicked(core->focused_widget);
					if (core->dragged_widget == NULL && core->resizing_widget == NULL)
					{
						if (core->focused_widget->is_resizable && core->event.type == SDL_MOUSEMOTION && !SDL_PointInRect(&core->mouse.position, &(SDL_Rect){core->focused_widget->absolute.x, core->focused_widget->absolute.y, core->focused_widget->absolute.w - 10, core->focused_widget->absolute.h - 10}))
							core->resizing_widget = core->focused_widget;
						else if (core->focused_widget->is_dragable && core->event.type == SDL_MOUSEMOTION)
							core->dragged_widget = core->focused_widget;
					}
				}
			}
			ui_render_widget(core->windows[i]);
			SDL_RenderPresent(core->windows[i]->renderer);
			break ;
		}
		i++;
	}
}

static void	ui_global_event(t_core *core)
{
	SDL_Point	new_mouse_position;
	if (SDL_WaitEvent(&core->event))
	{
		if (core->event.type == SDL_KEYDOWN && core->onkeypress != NULL)
		{
			core->onkeypress(core->event.key.keysym.sym, core->onkeypress_param);
		}
		else if (core->event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (core->onbuttondown)
				core->onbuttondown(core->event.button.button, core->onbuttondown_param);
			core->mouse.buttons[core->event.button.button] = true;
		}
		else if (core->event.type == SDL_MOUSEBUTTONUP)
		{
			if (core->onbuttonup)
				core->onbuttonup(core->event.button.button, core->onbuttondown_param);
			core->mouse.buttons[core->event.button.button] = false;
			if (core->event.button.button == SDL_BUTTON_LEFT)
			{
				core->dragged_widget = NULL;
				core->resizing_widget = NULL;
			}
		}
		SDL_GetMouseState(&new_mouse_position.x, &new_mouse_position.y);
		core->mouse.motion.x = new_mouse_position.x - core->mouse.position.x;
		core->mouse.motion.y = new_mouse_position.y - core->mouse.position.y;
		core->mouse.position = new_mouse_position;
	}
}

void	ui_run(t_core *core)
{
	core->is_running = true;
	ui_global_build(core);
	// SDL_StopTextInput();
	while (core->is_running)
	{
		ui_global_event(core);
		ui_global_update(core);
	}
	ui_destroy(core);

}