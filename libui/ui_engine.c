/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_engine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:31:56 by injah             #+#    #+#             */
/*   Updated: 2026/01/12 17:16:25 by injah            ###   ########.fr       */
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
	if (widget->parent)
		SDL_RenderSetClipRect(widget->renderer, &widget->parent->absolute);
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
	if (widget == widget->core->focused_widget)
		ui_widget_outline(widget, (SDL_Color){127, 127, 127, 255});
	else
		ui_widget_outline(widget, (SDL_Color){0, 0, 0, 255});
	SDL_RenderSetClipRect(widget->renderer, NULL);
}

static void ui_update_widget(t_widget *widget)
{
	int	i;

	if (widget->is_visible == false)
		return ;
	ui_widget_manage_state(widget);
	if (widget->event)
		widget->event(widget);
	if (widget->childs && widget->state != NORMAL)
	{
		i = 0;
		while (widget->childs[i])
		{
			ui_update_widget(widget->childs[i]);
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

void	ui_clean_widget(t_widget *widget)
{
	int	i;

	if (widget->is_visible == false)
		return ;
	widget->absolute = ui_get_absolute_rect(widget);
	ui_widget_change_state(widget, NORMAL);
	if (widget->childs)
	{
		i = 0;
		while (widget->childs[i])
		{
			ui_clean_widget(widget->childs[i]);
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
		ui_build_widget(core->windows[i]);
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
		if (core->event.window.windowID == data->id || (SDL_GetWindowID(SDL_GetMouseFocus()) == data->id && core->event.type == SDL_DROPFILE))
		{
			ui_clean_widget(core->windows[i]);
			ui_update_widget(core->windows[i]);
			if (core->hovered_widget)
				ui_set_cursor(core, core->hovered_widget->cursor);
			if (core->focused_widget)
			{
				if (core->focused_widget->update)
					core->focused_widget->update(core->focused_widget);
				if (core->focused_widget->state == CLICKED)
					ui_widget_call_onclicked(core->focused_widget);
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
	while (core->is_running)
	{
		ui_global_event(core);
		ui_global_update(core);
	}
	ui_destroy(core);

}