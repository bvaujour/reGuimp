/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_window.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 12:53:46 by injah             #+#    #+#             */
/*   Updated: 2025/12/29 01:04:57 by injah            ###   ########.fr       */
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

static void		ui_window_update(t_widget *widget)
{
	ui_window_event(widget, widget->core->event);
	ui_set_cursor(widget->core, widget->core->mouse.arrow);
}

static void		ui_window_render(t_widget *widget)
{
	SDL_RenderCopy(widget->renderer, widget->texture, NULL, &widget->absolute);
	ui_draw_outline(widget->renderer, widget->absolute, widget->outline, widget->outline_color);
}

static void	ui_window_destroy(t_widget *widget)
{
	t_window_data	*data;

	data = (t_window_data *)widget->data;
	if (widget->texture)
		SDL_DestroyTexture(widget->texture);
	if (widget->renderer)
		SDL_DestroyRenderer(widget->renderer);
	if (data->window)
		SDL_DestroyWindow(data->window);
}

static int	ui_window_add_child(t_widget *widget, t_widget *child)
{
	(void)child;
	if (widget->nb_child == UI_MAX_WINDOW_CHILDS)
	{
		printf("ui_window_add_child: Window has maximum child\n");
		return (UI_ERROR);
	}
	widget->childs[widget->nb_child] = child;
	widget->nb_child++;
	return (UI_SUCCESS);
}

t_widget 	*ui_create_window(t_core *core, int x, int y, int width, int height)
{
	t_widget			*widget;
	t_window_data		*data;

	if (core == NULL)
		return (NULL);
	widget = ui_new_widget((SDL_Rect){0, 0, width, height}, WINDOW, UI_MAX_WINDOW_CHILDS);
	if (!widget)
		return (NULL);
	widget->data = malloc(sizeof(t_window_data));
	if (!widget->data)
		return (free(widget), NULL);
	data = (t_window_data *)widget->data;
	*data = (t_window_data){0};
	widget->core = core;
	ui_set_widget_colors(widget, 0xFF444444, 0xFF444444, 0xFF444444);
	widget->render = ui_window_render;
	widget->update = ui_window_update;
	widget->destroy = ui_window_destroy;
	widget->add_child = ui_window_add_child;
	data->window = SDL_CreateWindow("LIBUI", x, y, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (data->window == NULL)
	{
		printf("ui_create_window: SDL_window failed\n");
		ui_window_destroy(widget);
		return (NULL);
	}
	widget->renderer = SDL_CreateRenderer(data->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	if (widget->renderer == NULL)
	{
		printf("ui_create_window: SDL_renderer failed\n");
		ui_window_destroy(widget);
		return (NULL);
	}
	widget->window_id = SDL_GetWindowID(data->window);
	widget->texture = ui_new_texture(widget->renderer, width, height, widget->colors[widget->state]);
	if (ui_core_add_window(core, widget) == -1)
	{
		printf("ui_create_window: ui_core_add_window failed\n");
		ui_window_destroy(widget);
		return (NULL);
	}
	return (widget);
}
