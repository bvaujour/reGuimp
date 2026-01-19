/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_engine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:31:56 by injah             #+#    #+#             */
/*   Updated: 2026/01/19 12:26:14 by injah            ###   ########.fr       */
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
	widget->render(widget);
	if (widget->childs)
	{
		i = 0;
		while (widget->childs[i])
		{
			ui_render_widget(widget->childs[i]);
			i++;
		}
	}
	SDL_RenderSetClipRect(widget->renderer, NULL);
}

static void ui_update_widget_state(t_widget *widget)
{
	int	i;

	if (widget->is_visible == false)
		return ;
	ui_widget_manage_state(widget);
	if (widget->childs && widget->state != NORMAL)
	{
		i = 0;
		while (widget->childs[i])
		{
			ui_update_widget_state(widget->childs[i]);
			i++;
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
		ui_update_widget_state(core->windows[i]);
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
			ui_init_widget(core->windows[i]);
			ui_update_widget_state(core->windows[i]);
			ui_event_widget(core->windows[i]);
			if (core->hovered_widget)
				ui_set_cursor(core, core->hovered_widget->cursor);
			if (core->focused_widget)
			{
				if (core->focused_widget->update)
					core->focused_widget->update(core->focused_widget);
				if (core->focused_widget->state == CLICKED)
				{
					ui_widget_call_onclicked(core->focused_widget);
					if (core->dragged_widget == NULL && core->focused_widget->is_dragable && core->event.type == SDL_MOUSEMOTION)
					{
						core->dragged_widget = core->focused_widget;
						core->dragged_widget->drag_offset.x = core->mouse.position.x - core->dragged_widget->absolute.x;
						core->dragged_widget->drag_offset.y = core->mouse.position.y - core->dragged_widget->absolute.y;
					}
				}
				if (core->dragged_widget)
					ui_widget_drag(core->dragged_widget);
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
				core->dragged_widget = NULL;
		}
		SDL_GetMouseState(&core->mouse.position.x, &core->mouse.position.y);
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