/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_engine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:31:56 by injah             #+#    #+#             */
/*   Updated: 2025/12/17 13:54:17 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"


void	ui_destroy_widget_and_childs(t_widget *widget)
{
	int	i;

	i = 0;
	while (i < widget->nb_childs)
	{
		ui_destroy_widget_and_childs(widget->childs[i]);
		i++;
	}
	if (widget->destroy)
		widget->destroy(widget);
	free(widget->childs);
	free(widget->data);
	free(widget);
}

// trouve le focused widget
static void	ui_update_widget_and_childs(t_widget *widget)
{
	int	i;

	i = 0;
	ui_widget_common_update(widget);
	while (i < widget->nb_childs)
	{
		ui_update_widget_and_childs(widget->childs[i]);
		i++;
	}
}

static void	ui_render_widget_and_childs(t_widget *widget)
{
	int	i;

	i = 0;
	while (i < widget->nb_childs)
	{
		ui_render_widget_and_childs(widget->childs[i]);
		i++;
	}
	if (widget->render)
		widget->render(widget);
}

static void	ui_event(t_core *core)
{
	if (SDL_WaitEvent(&core->event))
	{
		if (core->event.type == SDL_KEYDOWN && core->onkeypress != NULL)
			core->onkeypress(core->event.key.keysym.sym, core->onkeypress_param);
		if (core->event.type == SDL_QUIT)
		{
			core->is_running = false;
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
			if (core->event.button.button >= UI_MOUSE_BUTTON_SUPPORTED)
				return ;
			core->mouse.mouse_buttons[core->event.button.button] = true;
			core->mouse.last_click = core->event.button.button;
			// printf("button down: %d\n", core->event.button.button);
		}
		else if (core->event.type == SDL_MOUSEBUTTONUP)
		{
			if (core->event.button.button >= UI_MOUSE_BUTTON_SUPPORTED)
				return ;
			core->mouse.mouse_buttons[core->event.button.button] = false;

			// printf("button up: %d\n", core->event.button.button);
		}
		else if (core->event.type == SDL_WINDOWEVENT)
		{
			
			// printf("window core->event\n");
		}
	}
}

void	ui_run(t_core *core)
{
	core->is_running = true;

	while (core->is_running)
	{
		ui_event(core);
		ui_update_widget_and_childs(core->canvas);
		if (core->focused_widget->update)
			core->focused_widget->update(core->focused_widget);
		if (core->focused_widget->manage_cursor)
			core->focused_widget->manage_cursor(core->focused_widget);
		ui_widget_clear(core->canvas);
		ui_render_widget_and_childs(core->canvas);
		SDL_RenderPresent(core->renderer);

	}
	ui_destroy(core);

}