/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_window.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 12:53:46 by injah             #+#    #+#             */
/*   Updated: 2025/12/19 23:46:42 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

static void	ui_window_event(t_widget *window, SDL_Event event)
{
	if (event.type == SDL_WINDOWEVENT)
	{
		if (event.window.event == SDL_WINDOWEVENT_RESIZED)
		{
			window->rect.w = event.window.data1;
			window->rect.h = event.window.data2;
			printf("w %d\n", window->rect.w);
		}
	}
}

static void		ui_window_update(t_widget *window)
{
	ui_window_event(window, window->core->event);
	ui_set_cursor(window->core, window->core->mouse.arrow);
}

static void		ui_window_render(t_widget *window)
{
	ui_draw_background(window->renderer, window->background, window->rect, window->colors[window->state]);
}

static void	ui_window_destroy(t_widget *window)
{
	t_window_data	*data;

	data = (t_window_data *)window->data;
	if (window->background)
		SDL_DestroyTexture(window->background);
	if (window->renderer)
		SDL_DestroyRenderer(window->renderer);
	if (data->window)
		SDL_DestroyWindow(data->window);
}

static int	ui_window_add_child(t_widget *window, t_widget *child)
{
	(void)child;
	if (window->nb_child == UI_MAX_WINDOW_CHILDS)
	{
		printf("ui_window_add_child: Window has maximum child\n");
		return (UI_ERROR);
	}
	window->childs[window->nb_child] = child;
	window->nb_child++;
	return (UI_SUCCESS);
}

t_widget 	*ui_create_window(t_core *core, int x, int y, int width, int height)
{
	t_widget		*window;
	t_window_data	*data;

	window = ui_new_widget(WINDOW, sizeof(t_window_data));
	if (window == NULL)
	{
		printf("ui_create_window: SDL_window failed\n");
		ui_window_destroy(window);
		return (NULL);
	}
	data = (t_window_data *)window->data;
	*data = (t_window_data){0};
	window->childs = ui_new_widget_tab(UI_MAX_WINDOW_CHILDS);
	if (window->childs == NULL)
	{
		ui_window_destroy(window);
		return (NULL);
	}
	window->core = core;
	ui_set_widget_colors(window, 0xFF444444, 0xFF444444, 0xFF444444, 0xFF444444);
	window->render = ui_window_render;
	window->update = ui_window_update;
	window->destroy = ui_window_destroy;
	window->add_child = ui_window_add_child;
	window->rect = (SDL_Rect){0, 0, width, height};
	data->window = SDL_CreateWindow("LIBUI", x, y, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (data->window == NULL)
	{
		printf("ui_create_window: SDL_window failed\n");
		ui_window_destroy(window);
		return (NULL);
	}
	window->renderer = SDL_CreateRenderer(data->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	if (window->renderer == NULL)
	{
		printf("ui_create_window: SDL_renderer failed\n");
		ui_window_destroy(window);
		return (NULL);
	}
	window->window_id = SDL_GetWindowID(data->window);
	window->background = ui_new_texture(window->renderer, width, height);
	if (ui_core_add_window(core, window) == -1)
	{
		printf("ui_create_window: ui_core_add_window failed\n");
		ui_window_destroy(window);
		return (NULL);
	}
	return (window);
}
