/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_window.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 12:53:46 by injah             #+#    #+#             */
/*   Updated: 2026/01/12 14:39:24 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

static void	ui_window_event(t_widget *window)
{
	if (window->core->event.type == SDL_WINDOWEVENT)
	{
		if (window->core->event.window.event == SDL_WINDOWEVENT_RESIZED)
		{
			window->rect.w = window->core->event.window.data1;
			window->rect.h = window->core->event.window.data2;
		}
	}
}

static void		ui_window_render(t_widget *window)
{
	SDL_RenderCopy(window->renderer, window->texture, NULL, &window->absolute);
}

static void	ui_window_destroy(t_widget *window)
{
	t_window_data	*data;

	data = (t_window_data *)window->data;
	if (window->renderer)
		SDL_DestroyRenderer(window->renderer);
	if (data->window)
		SDL_DestroyWindow(data->window);
}

t_widget 	*ui_create_window(t_core *core, int x, int y, int width, int height)
{
	t_widget			*window;
	t_window_data		*data;

	if (core == NULL)
		return (NULL);
	window = ui_new_widget((SDL_Rect){0, 0, width, height}, WINDOW, UI_MAX_WINDOW_CHILDS);
	if (!window)
		return (NULL);
	window->data = malloc(sizeof(t_window_data));
	if (!window->data)
		return (free(window), NULL);
	data = (t_window_data *)window->data;
	*data = (t_window_data){0};
	window->core = core;
	ui_set_widget_colors(window, 0xFF444444, 0xFF444444, 0xFF444444);
	window->render = ui_window_render;
	window->destroy = ui_window_destroy;
	window->event = ui_window_event;
	window->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW); 
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
	data->id = SDL_GetWindowID(data->window);
	window->texture = ui_new_texture(window->renderer, width, height, window->colors[window->state]);
	if (ui_core_add_window(core, window) == -1)
	{
		printf("ui_create_window: ui_core_add_window failed\n");
		ui_window_destroy(window);
		return (NULL);
	}
	return (window);
}
