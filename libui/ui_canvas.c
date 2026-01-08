/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_canvas.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 10:15:42 by injah             #+#    #+#             */
/*   Updated: 2026/01/08 12:20:11 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

void		ui_canvas_render(t_widget *canvas)
{	
	t_canvas_data	*data;

	data = (t_canvas_data *)canvas->data;
	SDL_UpdateTexture(canvas->texture, NULL, data->surface->pixels, data->surface->pitch);
	SDL_RenderCopy(canvas->renderer, canvas->texture, NULL, &canvas->absolute);
}

void		ui_canvas_update(t_widget *canvas)
{
	(void)canvas;
}

void		ui_canvas_destroy(t_widget *canvas)
{
	t_canvas_data	*data;

	data = (t_canvas_data *)canvas->data;
	SDL_DestroyTexture(canvas->texture);
	SDL_FreeSurface(data->surface);
}

t_img	ui_canvas_get_img(t_widget *canvas)
{
	t_img			img;
	t_canvas_data	*data;
	
	data = (t_canvas_data *)canvas->data;
	img.height = canvas->rect.h;
	img.width = canvas->rect.w;
	img.pixels = data->surface->pixels;
	return (img);
}

t_widget	*ui_create_canvas(t_widget *parent, int x, int y, int width, int height)
{
	t_widget		*canvas;
	t_canvas_data	*data;

	if (parent == NULL)
		return (NULL);
	canvas = ui_new_widget((SDL_Rect){x, y, width, height}, CANVAS, UI_MAX_CANVAS_CHILDS);
	if (!canvas)
		return (NULL);
	if (ui_add_child(parent, canvas) != UI_SUCCESS)
		return (free(canvas), NULL);
	canvas->data = malloc(sizeof(t_canvas_data));
	if (!canvas->data)
		return (free(canvas), NULL);
	data = (t_canvas_data *)canvas->data;
	data->surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_ARGB8888);
	SDL_FillRect(data->surface, NULL, SDL_MapRGBA(data->surface->format, 255, 255, 255, 255));
	ui_set_widget_colors(canvas, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
	canvas->render = ui_canvas_render;
	canvas->update = ui_canvas_update;
	canvas->destroy = ui_canvas_destroy;
	canvas->texture = SDL_CreateTexture(canvas->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, canvas->rect.w, canvas->rect.h);
	return (canvas);
}