/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_drawable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 21:16:05 by injah             #+#    #+#             */
/*   Updated: 2026/01/08 11:54:44 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

static void	ui_drawable_render_brush_at_mouse(t_widget *drawable)
{
	t_drawable_data	*data;

	data = (t_drawable_data *)drawable->data;
	data->brush_rect.x = drawable->core->mouse.position.x - data->brush_rect.w / 2;
	data->brush_rect.y = drawable->core->mouse.position.y - data->brush_rect.h / 2;
	SDL_RenderCopy(drawable->renderer, data->brush, NULL, &data->brush_rect);
	// printf("brush posx: %d\nbrush posy: %d\nbrush ratio: %f\nbrush_width: %d\nbrush height:%d\n", data->brush_rect.x, data->brush_rect.y, data->brush_ratio, data->brush_rect.w, data->brush_rect.h);
}

static void	ui_drawable_render(t_widget *drawable)
{
	t_drawable_data	*data;
	data = (t_drawable_data *)drawable->data;

	// SDL_RenderSetClipRect(drawable->renderer, &drawable->parent->absolute);
	SDL_RenderCopy(drawable->renderer, drawable->texture, NULL, &drawable->absolute);
	SDL_RenderCopy(drawable->renderer, data->layer, NULL, &drawable->absolute);
	if (drawable->state == HOVERED || drawable->state == CLICKED)
		ui_drawable_render_brush_at_mouse(drawable);
}

static void	ui_drawable_snapshot(t_widget *drawable)
{
	t_drawable_data	*data;

	data = (t_drawable_data *)drawable->data;
	SDL_SetRenderTarget(drawable->renderer, data->snapshot);
	SDL_RenderCopy(drawable->renderer, drawable->texture, NULL, NULL);
	SDL_RenderCopy(drawable->renderer, data->layer, NULL, NULL);
	SDL_SetRenderTarget(drawable->renderer, NULL);
}

static void	ui_drawable_event(t_widget *drawable, SDL_Event event)
{
	(void)drawable;
	// t_drawable_data	*data;
	// data = (t_drawable_data *)drawable->data;

	if (event.type == SDL_DROPFILE)
	{
		printf("DRAWBLE_EVENT\n");
		SDL_Surface *surface = IMG_Load(event.drop.file);
		if (surface)
		{
			SDL_Texture *tmp = SDL_CreateTextureFromSurface(drawable->renderer, surface);

			SDL_SetRenderTarget(drawable->renderer, drawable->texture);
			SDL_RenderCopy(drawable->renderer, tmp, NULL, NULL);
			SDL_SetRenderTarget(drawable->renderer, NULL);

			SDL_DestroyTexture(tmp);
			SDL_FreeSurface(surface);

			printf ("%s\n", event.drop.file);
		}
	}
	if (event.type == SDL_MOUSEBUTTONUP)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			ui_drawable_snapshot(drawable);
		}
	}
}

void	ui_drawable_draw_brush(t_widget *drawable)
{
	t_drawable_data	*data;
	t_core			*core;

	core = drawable->core;
	data = (t_drawable_data *)drawable->data;
	data->brush_rect.x = core->mouse.position.x - drawable->absolute.x - data->brush_rect.w / 2;
	data->brush_rect.y = core->mouse.position.y - drawable->absolute.y - data->brush_rect.h / 2;
	SDL_SetRenderTarget(drawable->renderer, data->layer);
	SDL_RenderCopy(drawable->renderer, data->brush, NULL, &data->brush_rect);
	SDL_SetRenderTarget(drawable->renderer, NULL);
}

void	ui_drawable_erase(t_widget *drawable)
{
	t_drawable_data	*data;
	t_core			*core;

	core = drawable->core;
	data = (t_drawable_data *)drawable->data;
	SDL_SetTextureBlendMode(data->brush, SDL_BLENDMODE_NONE);
	SDL_SetTextureAlphaMod(data->brush, 0);
	data->brush_rect.x = core->mouse.position.x - drawable->absolute.x - data->brush_rect.w / 2;
	data->brush_rect.y = core->mouse.position.y - drawable->absolute.y - data->brush_rect.h / 2;
	SDL_SetRenderTarget(drawable->renderer, data->layer);
	SDL_RenderCopy(drawable->renderer, data->brush, NULL, &data->brush_rect);
	SDL_SetRenderTarget(drawable->renderer, NULL);
}

static void	ui_drawable_update(t_widget *drawable)
{
	if (drawable->state == CLICKED)
	{
		ui_drawable_draw_brush(drawable);
		// ui_drawable_erase(drawable);
	}
}

static void	ui_drawable_destroy(t_widget *drawable)
{
	t_drawable_data		*data;

	data = (t_drawable_data *)drawable->data;
	if (data->cursor)
		SDL_FreeCursor(data->cursor);
	if (data->brush)
		SDL_DestroyTexture(data->brush);
	if (drawable->texture)
		SDL_DestroyTexture(drawable->texture);
	if (data->layer)
		SDL_DestroyTexture(data->layer);
	if (data->snapshot)
		SDL_DestroyTexture(data->snapshot);
}

void	ui_test(t_widget *drawable)
{
	t_image_data	img;
	t_drawable_data	*data;
	data = (t_drawable_data *)drawable->data;

	SDL_SetRenderDrawColor(drawable->renderer, 0, 255, 255, 255);
	SDL_SetRenderTarget(drawable->renderer, data->layer);
	SDL_RenderDrawRect(drawable->renderer, &(SDL_Rect){250, 250, 300, 300});
	SDL_RenderDrawLine(drawable->renderer, 101, 201, 400, 400);
	SDL_SetRenderTarget(drawable->renderer, NULL);

	ui_get_render_target_image_data(drawable->renderer, data->layer, &img);
	ui_draw_rect_on_image(img, (SDL_Rect){0, 0, 200, 200}, 0x7fFF0000);
	ui_draw_circle_on_image(img, (SDL_Point){300, 200}, 100, 1, 0x7fFF0000);
	ui_bucket_image(img, 300, 200, 0xFF00FF00);
	ui_set_render_target_pixels(drawable->renderer, data->layer, img.pixels);
	free(img.pixels);
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
	ui_set_widget_colors(drawable, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
	data = (t_drawable_data *)drawable->data;
	*data = (t_drawable_data){0};
	data->brush_size = 25;
	data->brush_color = (SDL_Color){255, 255, 255, 255};
	drawable->render = ui_drawable_render;
	drawable->update = ui_drawable_update;
	drawable->event = ui_drawable_event;
	drawable->destroy = ui_drawable_destroy;
	drawable->texture = SDL_CreateTexture(drawable->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, drawable->rect.w, drawable->rect.h);
	data->layer = SDL_CreateTexture(drawable->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, drawable->rect.w, drawable->rect.h);
	data->snapshot = SDL_CreateTexture(drawable->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, drawable->rect.w, drawable->rect.h);
	SDL_SetRenderDrawColor(drawable->renderer, 0, 0, 0, 255);
	SDL_SetRenderTarget(drawable->renderer, drawable->texture);
	SDL_RenderFillRect(drawable->renderer, NULL);
	SDL_SetRenderTarget(drawable->renderer, NULL);
	SDL_SetTextureBlendMode(drawable->texture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(data->layer, SDL_BLENDMODE_BLEND);
	ui_test(drawable);
	ui_drawable_set_brush(drawable, "libui/assets/brushs/brush_base.png");
	return (drawable);
}