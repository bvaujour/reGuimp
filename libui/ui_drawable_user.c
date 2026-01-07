/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_drawable_user.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 21:11:52 by injah             #+#    #+#             */
/*   Updated: 2026/01/07 13:21:56 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

void	ui_drawable_export_png(t_widget *drawable, const char *file)
{
	SDL_Surface		*surface;
	t_drawable_data	*data;

	data = (t_drawable_data *)drawable->data;
	surface = SDL_CreateRGBSurfaceWithFormat(0, drawable->rect.w,
			drawable->rect.h, 32, SDL_PIXELFORMAT_ARGB8888);
	SDL_SetRenderTarget(drawable->renderer, data->snapshot);
	SDL_RenderReadPixels(drawable->renderer, NULL, SDL_PIXELFORMAT_ARGB8888,
		surface->pixels, surface->pitch);
	SDL_SetRenderTarget(drawable->renderer, NULL);
	IMG_SavePNG(surface, file);
	SDL_FreeSurface(surface);
}

void	ui_drawable_export_jpeg(t_widget *drawable, const char *file,
		int quality)
{
	SDL_Surface		*surface;
	t_drawable_data	*data;

	data = (t_drawable_data *)drawable->data;
	SDL_SetRenderTarget(drawable->renderer, data->snapshot);
	surface = SDL_CreateRGBSurfaceWithFormat(0, drawable->rect.w,
			drawable->rect.h, 32, SDL_PIXELFORMAT_ARGB8888);
	SDL_SetRenderTarget(drawable->renderer, data->snapshot);
	SDL_RenderReadPixels(drawable->renderer, NULL, SDL_PIXELFORMAT_ARGB8888,
		surface->pixels, surface->pitch);
	SDL_SetRenderTarget(drawable->renderer, NULL);
	IMG_SaveJPG(surface, file, quality);
	SDL_FreeSurface(surface);
}

void	ui_drawable_premult_brush_alpha(SDL_Surface *surface)
{
	Uint8	*pixels;
	int		pitch;
	Uint32	*row;

	SDL_LockSurface(surface);
	pixels = (Uint8 *)surface->pixels;
	pitch = surface->pitch;
	for (int y = 0; y < surface->h; y++)
	{
		row = (Uint32 *)(pixels + y * pitch);
		for (int x = 0; x < surface->w; x++)
		{
			Uint8 r, g, b, a;
			SDL_GetRGBA(row[x], surface->format, &r, &g, &b, &a);
			r = (r * a) / 255;
			g = (g * a) / 255;
			b = (b * a) / 255;
			row[x] = SDL_MapRGBA(surface->format, r, g, b, a);
		}
	}
	SDL_UnlockSurface(surface);
}

void	ui_drawable_set_premult_mode(SDL_Texture *brush)
{
	SDL_BlendMode	premulBlend;

	premulBlend = SDL_ComposeCustomBlendMode(
			SDL_BLENDFACTOR_ONE,
			SDL_BLENDFACTOR_ONE_MINUS_SRC_ALPHA, 
			SDL_BLENDOPERATION_ADD,
   			SDL_BLENDFACTOR_ZERO,
    		SDL_BLENDFACTOR_ONE,
    		SDL_BLENDOPERATION_ADD);
	SDL_SetTextureBlendMode(brush, premulBlend);
}

void	ui_drawable_set_brush(t_widget *drawable, const char *path)
{
	t_drawable_data	*data;
	SDL_Surface		*surface;

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
	// ui_drawable_premult_brush_alpha(surface);
	data->brush = SDL_CreateTextureFromSurface(drawable->renderer, surface);
	if (!data->brush)
	{
		printf("failed load brush\n");
		return ;
	}
	// ui_drawable_set_premult_mode(data->brush);
	SDL_SetTextureBlendMode(data->brush, SDL_BLENDMODE_BLEND);
	SDL_SetTextureColorMod(data->brush, data->brush_color.r,
		data->brush_color.g, data->brush_color.b);
	SDL_SetTextureAlphaMod(data->brush, data->brush_color.a);
	SDL_FreeSurface(surface);
}

void	ui_drawable_set_brush_size(t_widget *drawable, int size)
{
	t_drawable_data	*data;

	data = (t_drawable_data *)drawable->data;
	data->brush_size = size;
	data->brush_rect.w = size;
	data->brush_rect.h = data->brush_ratio * size;
}

void	ui_drawable_set_brush_color(t_widget *drawable, char red, char green,
		char blue, char alpha)
{
	t_drawable_data	*data;

	data = (t_drawable_data *)drawable->data;
	SDL_SetTextureAlphaMod(data->brush, alpha);
	SDL_SetTextureColorMod(data->brush, red, green, blue);
	data->brush_color.r = red;
	data->brush_color.g = green;
	data->brush_color.b = blue;
	data->brush_color.a = alpha;
}
