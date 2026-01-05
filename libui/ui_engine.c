/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_engine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:31:56 by injah             #+#    #+#             */
/*   Updated: 2026/01/05 15:48:36 by injah            ###   ########.fr       */
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
}

static void ui_update_widget(t_widget *widget)
{
	int	i;

	if (widget->is_visible == false)
		return ;
	widget->absolute = ui_get_absolute_rect(widget);
	ui_widget_manage_state(widget);
	if (widget->event)
		widget->event(widget, widget->core->event);
	if (widget->childs)
	{
		i = 0;
		while (widget->childs[i])
		{
			ui_update_widget(widget->childs[i]);
			i++;
		}
	}
}

static void	ui_update(t_core *core)
{
	int				i;
	t_window_data	*data;

	i = 0;
	while (core->windows[i])
	{
		data = core->windows[i]->data;
		if (SDL_GetWindowID(SDL_GetMouseFocus()) == SDL_GetWindowID(data->window))
		{
			// printf("update window %d\n", SDL_GetWindowID(data->window));
			ui_update_widget(core->windows[i]);
			if (core->focused_widget)
				core->focused_widget->update(core->focused_widget);
			ui_render_widget(core->windows[i]);
			SDL_RenderPresent(core->windows[i]->renderer);
			break ;
		}
		i++;
	}
}

static void	ui_event(t_core *core)
{
	if (SDL_WaitEvent(&core->event))
	{
		if (core->event.type == SDL_KEYDOWN && core->onkeypress != NULL)
		{
			core->onkeypress(core->event.key.keysym.sym, core->onkeypress_param);
		}
		
		else if (core->event.type == SDL_MOUSEMOTION)
		{
			core->mouse.motion.x = core->event.motion.x - core->mouse.position.x;
			core->mouse.motion.y = core->event.motion.y - core->mouse.position.y;
			core->mouse.position.x = core->event.motion.x;
			core->mouse.position.y = core->event.motion.y;
			// printf("%d\n", core->mouse.motion.x);
			// printf("%d\n", core->mouse.motion.y);
		}
		else if (core->event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (core->event.button.button < UI_MOUSE_BUTTON_SUPPORTED)
				core->mouse.mouse_buttons[core->event.button.button] = true;
		}
		else if (core->event.type == SDL_MOUSEBUTTONUP)
		{
			core->dragged_widget = NULL;
			if (core->event.button.button < UI_MOUSE_BUTTON_SUPPORTED)
				core->mouse.mouse_buttons[core->event.button.button] = false;
		}
		else if (core->event.type == SDL_DROPFILE)
		{
			printf("file droped on window %d\n", core->event.window.windowID);
		}
		printf("window ID %d\n", core->event.window.windowID);

		// if (core->event.type == SDL_MOUSEMOTION || core->event.type == SDL_DROPFILE || core->event.type == SDL_MOUSEBUTTONDOWN)
		// printf("id : %d, enum: %d\n", core->event.window.windowID, core->event.type);
	}
}

void	ui_run(t_core *core)
{
	core->is_running = true;
	while (core->is_running)
	{
		ui_event(core);
		ui_update(core);
	}
	ui_destroy(core);

}