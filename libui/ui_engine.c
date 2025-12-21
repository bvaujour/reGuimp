/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_engine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:31:56 by injah             #+#    #+#             */
/*   Updated: 2025/12/20 07:08:37 by injah            ###   ########.fr       */
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

void	ui_update_widgets(t_widget **widgets)
{
	int	i;

	if (widgets == NULL)
		return ;
	i = 0;
	while (widgets[i])
	{
		if (widgets[i]->is_visible)
		{
			ui_widget_common_update(widgets[i]);
			ui_update_widgets(widgets[i]->childs);
		}
		i++;
	}
}

void	ui_render_widgets(t_widget **widgets)
{
	int	i;

	if (widgets == NULL)
		return ;
	i = 0;
	while (widgets[i])
	{
		if (widgets[i]->is_visible)
		{
			if (widgets[i]->render)
				widgets[i]->render(widgets[i]);
			ui_render_widgets(widgets[i]->childs);
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

static void	ui_render_present(t_widget **windows)
{
	int	i;

	i = 0;
	while (windows[i])
	{
		SDL_RenderPresent(windows[i]->renderer);
		i++;
	}
}

void	ui_run(t_core *core)
{
	core->is_running = true;

	while (core->is_running)
	{
		core->focused_widget = NULL;
		ui_event(core);
		if (core->event.window.event != SDL_WINDOWEVENT_FOCUS_LOST)
		{
			ui_update_widgets(core->windows);
			if (core->focused_widget && core->focused_widget->update)
				core->focused_widget->update(core->focused_widget);
			ui_render_widgets(core->windows);
			ui_render_present(core->windows);
		}
	}
	ui_destroy(core);

}