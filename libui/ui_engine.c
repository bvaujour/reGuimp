/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_engine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:31:56 by injah             #+#    #+#             */
/*   Updated: 2025/12/29 00:36:25 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"


// void	ui_destroy_widget_and_childs(t_widget *widget)
// {
// 	int	i;

// 	i = 0;
// 	while (i < widget->nb_childs)
// 	{
// 		ui_destroy_widget_and_childs(widget->childs[i]);
// 		i++;
// 	}
// 	if (widget->destroy)
// 		widget->destroy(widget);
// 	free(widget->childs);
// 	free(widget->data);
// 	free(widget);
// }

// // trouve le focused widget
// static void	ui_update_widget_and_childs(t_widget *widget)
// {
// 	int	i;

// 	i = 0;
// 	ui_widget_common_update(widget);
// 	while (i < widget->nb_childs)
// 	{
// 		ui_update_widget_and_childs(widget->childs[i]);
// 		i++;
// 	}
// }

// static void	ui_render_widget_and_childs(t_widget *widget)
// {
// 	int	i;

// 	i = 0;
// 	if (widget->render)
// 		widget->render(widget);
// 	while (i < widget->nb_childs)
// 	{
// 		ui_render_widget_and_childs(widget->childs[i]);
// 		i++;
// 	}
	
// }

void	ui_destroy_widgets(t_widget **widgets)
{
	int	i;

	if (widgets == NULL)
		return ;
	i = 0;
	while (widgets[i])
	{
		ui_destroy_widgets(widgets[i]->childs);
		if (widgets[i]->destroy)
			widgets[i]->destroy(widgets[i]);
		free(widgets[i]->data);
		free(widgets[i]);
		i++;
	}
	free(widgets);
}

// void	ui_update_widgets(t_widget **widgets)
// {
// 	int	i;

// 	if (widgets == NULL)
// 		return ;
// 	i = 0;
// 	while (widgets[i])
// 	{
// 		if (widgets[i]->is_visible)
// 		{
// 			ui_widget_manage_state(widgets[i]);
// 			if (widgets[i]->state != NORMAL)
// 			{
// 				widgets[i]->core->focused_widget = widgets[i];
// 				ui_update_widgets(widgets[i]->childs);
// 			}
// 		}
// 		i++;
// 	}
// }

// void	ui_render_widgets(t_widget **widgets)
// {
// 	int	i;

// 	if (widgets == NULL)
// 		return ;
// 	i = 0;
// 	while (widgets[i])
// 	{
// 		if (widgets[i]->is_visible)
// 		{
// 			widgets[i]->render(widgets[i]);
// 			ui_render_widgets(widgets[i]->childs);
// 		}
// 		i++;
// 	}
// }

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

static void	ui_update_core(t_core *core)
{
	int				i;
	t_window_data	*data;

	i = 0;
	while (core->windows[i])
	{
		data = core->windows[i]->data;
		if (core->event.window.windowID == SDL_GetWindowID(data->window))
		{
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
		if (core->event.window.event != SDL_WINDOWEVENT_FOCUS_LOST)
			ui_update_core(core);
	}
	ui_destroy(core);

}