/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_engine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:31:56 by injah             #+#    #+#             */
/*   Updated: 2026/01/08 17:14:19 by kipouliq         ###   ########.fr       */
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
	SDL_RenderSetClipRect(widget->renderer, &widget->absolute);
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
		ui_widget_outline(widget);
	SDL_RenderSetClipRect(widget->renderer, NULL);
}

static void ui_update_widget(t_widget *widget)
{
	int	i;

	if (widget->is_visible == false)
		return ;
	widget->absolute = ui_get_absolute_rect(widget);
	ui_widget_manage_state(widget);
	ui_widget_event(widget, widget->core->event);
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
			ui_update_widget(core->windows[i]);
			if (core->focused_widget)
			{
				core->focused_widget->update(core->focused_widget);
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
	core->mouse.mouse_state = SDL_GetMouseState(NULL, NULL);
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
			core->mouse.position.x =  core->event.motion.x;
			core->mouse.position.y = core->event.motion.y;
		}
		else if (core->event.type == SDL_MOUSEBUTTONUP)
		{
			if (core->event.button.button == SDL_BUTTON_LEFT)
				core->dragged_widget = NULL;
		}
	}
}

void	ui_run(t_core *core)
{
	core->is_running = true;
	ui_global_build(core);
	printf("sizeof uint32: %ld\nsizeof unsigned: %ld\n", sizeof(Uint32), sizeof(unsigned int));
	while (core->is_running)
	{
		ui_global_event(core);
		ui_global_update(core);
	}
	ui_destroy(core);

}