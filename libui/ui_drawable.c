/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_drawableable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 21:16:05 by injah             #+#    #+#             */
/*   Updated: 2025/12/15 03:39:13 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

void	ui_drawable_export_png(t_widget *drawable, const char *file)
{
	SDL_Surface	*surface;

	surface = SDL_CreateRGBSurfaceWithFormat(0, drawable->rect.w, drawable->rect.h, 32, SDL_PIXELFORMAT_ARGB8888);

	SDL_SetRenderTarget(drawable->renderer, drawable->background);

	SDL_RenderReadPixels(drawable->renderer, NULL, SDL_PIXELFORMAT_ARGB8888, surface->pixels, surface->pitch);

	SDL_SetRenderTarget(drawable->renderer, NULL);
	IMG_SavePNG(surface, file);
	SDL_FreeSurface(surface);
}

void		ui_drawable_set_brush(t_widget *drawable, const char *path)
{
	t_drawable_data		*data;
	// SDL_Surface		*loaded_img;
	SDL_Surface 		*surface;
	data = (t_drawable_data *)drawable->data;
	if (data->brush)
		SDL_DestroyTexture(data->brush);
	surface = IMG_Load(path);
	//surface = SDL_ConvertSurfaceFormat(loaded_img, SDL_PIXELFORMAT_ARGB8888, 0);
	// SDL_FreeSurface(loaded_img);
	if (!surface)
		printf("failed load brush\n");
	data->brush_ratio = (float)surface->h / surface->w;
	data->brush_rect.w = data->brush_size;
	data->brush_rect.h = data->brush_ratio * data->brush_size;
	data->brush = SDL_CreateTextureFromSurface(drawable->renderer, surface);
	if (!data->brush)
		printf("failed load brush\n");
	SDL_SetTextureBlendMode(data->brush, SDL_BLENDMODE_BLEND);
	SDL_FreeSurface(surface);
}

void		ui_drawable_set_brush_size(t_widget *drawable, int size)
{
	t_drawable_data		*data;

	data = (t_drawable_data *)drawable->data;
	data->brush_size = size;
	data->brush_rect.w = size;
	data->brush_rect.h = data->brush_ratio * size;
}

void		ui_drawable_set_brush_color(t_widget *drawable, char red, char green, char blue, char alpha)
{
	t_drawable_data		*data;

	data = (t_drawable_data *)drawable->data;
	data->brush_color.r = red;
	data->brush_color.g = green;
	data->brush_color.b = blue;
	data->brush_color.a = alpha;
}

static void	ui_drawable_render(t_widget *drawable)
{
	SDL_Color		color;
	t_drawable_data	*data;

	data = (t_drawable_data *)drawable->data;
	SDL_RenderSetClipRect(drawable->renderer, &drawable->parent->absolute);
	SDL_RenderCopy(drawable->renderer, drawable->background, NULL, &drawable->absolute);

	if (drawable->state == HOVERED || drawable->state == CLICKED)
	{
		data->brush_rect.x = drawable->core->mouse.position.x - data->brush_rect.w / 2;
		data->brush_rect.y = drawable->core->mouse.position.y - data->brush_rect.h / 2;
		// printf("brush posx: %d\nbrush posy: %d\nbrush ratio: %f\nbrush_width: %d\nbrush height:%d\n", data->brush_rect.x, data->brush_rect.y, data->brush_ratio, data->brush_rect.w, data->brush_rect.h);
		color = data->brush_color;
		SDL_SetTextureColorMod(data->brush, color.r, color.g, color.b);
		SDL_RenderCopy(drawable->renderer, data->brush, NULL, &data->brush_rect);
	}
	SDL_RenderSetClipRect(drawable->renderer, NULL);
}

static void	ui_drawable_event(t_widget *drawable, SDL_Event event)
{
	(void)drawable;
	if (event.type == SDL_DROPFILE)
	{
	printf ("HELLO\n");

		SDL_Surface *surface = IMG_Load(event.drop.file);
		if (surface)
		{
			SDL_Texture *tmp = SDL_CreateTextureFromSurface(drawable->renderer, surface);

			SDL_SetRenderTarget(drawable->renderer, drawable->background);
			SDL_RenderCopy(drawable->renderer, tmp, NULL, NULL);
			SDL_SetRenderTarget(drawable->renderer, NULL);

			SDL_DestroyTexture(tmp);
			SDL_FreeSurface(surface);

			printf ("%s\n", event.drop.file);
		}
	}
}

static void	ui_drawable_update(t_widget *drawable)
{
	t_drawable_data	*data;
	t_core			*core;

	core = drawable->core;
	ui_drawable_event(drawable, core->event);

	if (drawable->state == CLICKED)
	{
		data = (t_drawable_data *)drawable->data;
		SDL_SetTextureAlphaMod(data->brush, data->brush_color.a);
		SDL_SetTextureColorMod(data->brush, data->brush_color.r, data->brush_color.g, data->brush_color.b);
		data->brush_rect.x = core->mouse.position.x - drawable->absolute.x - data->brush_rect.w / 2;
		data->brush_rect.y = core->mouse.position.y - drawable->absolute.y - data->brush_rect.h / 2;
		SDL_SetRenderTarget(drawable->renderer, drawable->background);
		SDL_RenderCopy(drawable->renderer, data->brush, NULL, &data->brush_rect);
		SDL_SetRenderTarget(drawable->renderer, NULL);
	}
}

static void	ui_drawable_destroy(t_widget *drawable)
{
	(void)drawable;

	t_drawable_data		*data;

	data = (t_drawable_data *)drawable->data;
	if (data->cursor)
		SDL_FreeCursor(data->cursor);
	if (data->brush)
		SDL_DestroyTexture(data->brush);
	if (drawable->background)
		SDL_DestroyTexture(drawable->background);
	free(data->brush_path);
}

static void	ui_drawable_build(t_widget *drawable)
{
	drawable->background = SDL_CreateTexture(drawable->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, drawable->rect.w, drawable->rect.h);
	SDL_SetRenderTarget(drawable->renderer, drawable->background);
	SDL_SetRenderDrawColor(drawable->renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(drawable->renderer, NULL);
	SDL_SetRenderTarget(drawable->renderer, NULL);
}

t_widget	*ui_create_drawable(t_widget *parent, int x, int y, int width, int height)
{
	t_widget			*drawable;
	t_drawable_data		*data;

	if (parent == NULL)
		return (NULL);
	drawable = ui_new_widget((SDL_Rect){x, y, width, height}, DRAWABLE, UI_MAX_DRAWABLE_CHILDS);
	if (!drawable)
		return (NULL);
	if (ui_add_child(parent, drawable) != UI_SUCCESS)
		return (free(drawable), NULL);
	drawable->data = malloc(sizeof(t_drawable_data));
	if (!drawable->data)
		return (free(drawable), NULL);
	data = (t_drawable_data *)drawable->data;
	*data = (t_drawable_data){0};
	data->brush_size = 25;
	data->brush_color = (SDL_Color){255, 255, 255, 255};
	drawable->render = ui_drawable_render;
	drawable->update = ui_drawable_update;
	drawable->destroy = ui_drawable_destroy;
	data->brush_path = ft_strdup("libui/assets/brushs/brush_base.png");
	ui_drawable_build(drawable);
	ui_drawable_set_brush(drawable, data->brush_path);
	return (drawable);
}