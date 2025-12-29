/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_drawable_user.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 21:11:52 by injah             #+#    #+#             */
/*   Updated: 2025/12/28 14:07:04 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

void	ui_drawable_export_png(t_widget *drawable, const char *file)
{
	SDL_Surface	*surface;

	surface = SDL_CreateRGBSurfaceWithFormat(0, drawable->rect.w, drawable->rect.h, 32, SDL_PIXELFORMAT_ARGB8888);

	SDL_SetRenderTarget(drawable->renderer, drawable->texture);

	SDL_RenderReadPixels(drawable->renderer, NULL, SDL_PIXELFORMAT_ARGB8888, surface->pixels, surface->pitch);

	SDL_SetRenderTarget(drawable->renderer, NULL);
	IMG_SavePNG(surface, file);
	SDL_FreeSurface(surface);
}

void	ui_drawable_export_jpeg(t_widget *drawable, const char *file, int quality)
{
	SDL_Surface	*surface;

	surface = SDL_CreateRGBSurfaceWithFormat(0, drawable->rect.w, drawable->rect.h, 32, SDL_PIXELFORMAT_ARGB8888);

	SDL_SetRenderTarget(drawable->renderer, drawable->texture);

	SDL_RenderReadPixels(drawable->renderer, NULL, SDL_PIXELFORMAT_ARGB8888, surface->pixels, surface->pitch);

	SDL_SetRenderTarget(drawable->renderer, NULL);
	IMG_SaveJPG(surface, file, quality);
	SDL_FreeSurface(surface);
}

void	ui_drawable_set_brush(t_widget *drawable, const char *path)
{
	t_drawable_data		*data;
	SDL_Surface 		*surface;

	data = (t_drawable_data *)drawable->data;
	surface = IMG_Load(path);
	if (!surface)
	{
		printf("failed load brush\n");
		return ;
	}
	data->brush_ratio = (float)surface->h / surface->w;
	data->brush_rect.w = data->brush_size;
	data->brush_rect.h = data->brush_ratio * data->brush_size;
	if (data->brush)
		SDL_DestroyTexture(data->brush);
	data->brush = SDL_CreateTextureFromSurface(drawable->renderer, surface);
	if (!data->brush)
	{
		printf("failed load brush\n");
		return ;
	}
	SDL_SetTextureBlendMode(data->brush, SDL_BLENDMODE_BLEND);
	SDL_SetTextureColorMod(data->brush, data->brush_color.r, data->brush_color.g, data->brush_color.b);
	SDL_SetTextureAlphaMod(data->brush, data->brush_color.a);
	SDL_FreeSurface(surface);
}

void	ui_drawable_set_brush_size(t_widget *drawable, int size)
{
	t_drawable_data		*data;

	data = (t_drawable_data *)drawable->data;
	data->brush_size = size;
	data->brush_rect.w = size;
	data->brush_rect.h = data->brush_ratio * size;
}

void	ui_drawable_set_brush_color(t_widget *drawable, char red, char green, char blue, char alpha)
{
	t_drawable_data		*data;

	data = (t_drawable_data *)drawable->data;
	SDL_SetTextureAlphaMod(data->brush, alpha);
	SDL_SetTextureColorMod(data->brush, red, green, blue);
	data->brush_color.r = red;
	data->brush_color.g = green;
	data->brush_color.b = blue;
	data->brush_color.a = alpha;
}
