/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_drawable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 21:16:05 by injah             #+#    #+#             */
/*   Updated: 2026/01/05 15:55:35 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

static void	ui_drawable_render_brush_at_mouse(t_widget *widget)
{
	t_drawable_data	*data;

	data = (t_drawable_data *)widget->data;
	data->brush_rect.x = widget->core->mouse.position.x - data->brush_rect.w / 2;
	data->brush_rect.y = widget->core->mouse.position.y - data->brush_rect.h / 2;
	SDL_RenderCopy(widget->renderer, data->brush, NULL, &data->brush_rect);
	// printf("brush posx: %d\nbrush posy: %d\nbrush ratio: %f\nbrush_width: %d\nbrush height:%d\n", data->brush_rect.x, data->brush_rect.y, data->brush_ratio, data->brush_rect.w, data->brush_rect.h);
}

static void	ui_drawable_render(t_widget *widget)
{
	SDL_RenderSetClipRect(widget->renderer, &widget->parent->absolute);
	SDL_RenderCopy(widget->renderer, widget->texture, NULL, &widget->absolute);
	ui_draw_outline(widget->renderer, widget->absolute, widget->outline, widget->outline_color);
	if (widget->state == HOVERED || widget->state == CLICKED)
		ui_drawable_render_brush_at_mouse(widget);
	SDL_RenderSetClipRect(widget->renderer, NULL);
}

static void	ui_drawable_event(t_widget *widget, SDL_Event event)
{
	(void)widget;
	if (event.type == SDL_DROPFILE)
	{
		printf("DRAWBLE_EVENT\n");
		SDL_Surface *surface = IMG_Load(event.drop.file);
		if (surface)
		{
			SDL_Texture *tmp = SDL_CreateTextureFromSurface(widget->renderer, surface);

			SDL_SetRenderTarget(widget->renderer, widget->texture);
			SDL_RenderCopy(widget->renderer, tmp, NULL, NULL);
			SDL_SetRenderTarget(widget->renderer, NULL);

			SDL_DestroyTexture(tmp);
			SDL_FreeSurface(surface);

			printf ("%s\n", event.drop.file);
		}
	}
}


static void	ui_drawable_update(t_widget *widget)
{
	t_drawable_data	*data;
	t_core			*core;

	core = widget->core;

	if (widget->state == CLICKED)
	{
		data = (t_drawable_data *)widget->data;
		data->brush_rect.x = core->mouse.position.x - widget->absolute.x - data->brush_rect.w / 2;
		data->brush_rect.y = core->mouse.position.y - widget->absolute.y - data->brush_rect.h / 2;
		SDL_SetRenderTarget(widget->renderer, widget->texture);
		SDL_RenderCopy(widget->renderer, data->brush, NULL, &data->brush_rect);
		SDL_SetRenderTarget(widget->renderer, NULL);
	}
}

static void	ui_drawable_destroy(t_widget *widget)
{
	(void)widget;

	t_drawable_data		*data;

	data = (t_drawable_data *)widget->data;
	if (data->cursor)
		SDL_FreeCursor(data->cursor);
	if (data->brush)
		SDL_DestroyTexture(data->brush);
	if (widget->texture)
		SDL_DestroyTexture(widget->texture);
}


// void ui_bucket_image(t_image_data img, int x, int y, Uint32 color)
// {
//     if (x < 0 || x >= img.width || y < 0 || y >= img.height)
//         return;

//     Uint32 target = img.pixels[y * img.width + x];

//     if (target == color)
//         return;

//     ui_flood_fill_image(img, x, y, target, color);
// }

void	ui_test(t_widget *widget)
{
	t_image_data	img;

	SDL_SetRenderDrawColor(widget->renderer, 255, 255, 255, 255);
	SDL_SetRenderTarget(widget->renderer, widget->texture);
	SDL_RenderDrawRect(widget->renderer, &(SDL_Rect){200, 200, 300, 300});
	SDL_RenderDrawLine(widget->renderer, 101, 201, 400, 400);
	SDL_SetRenderTarget(widget->renderer, NULL);

	ui_get_render_target_image_data(widget->renderer, widget->texture, &img);
	ui_draw_rect_on_image(img, (SDL_Rect){0, 0, 200, 200}, 0x7fFF0000);
	ui_draw_circle_on_image(img, (SDL_Point){300, 200}, 100, 1, 0x7fFF0000);
	ui_bucket_image(img, 300, 200, 0xFF00FF00);
	ui_set_render_target_pixels(widget->renderer, widget->texture, img.pixels);
	free(img.pixels);
}

t_widget	*ui_create_drawable(t_widget *parent, int x, int y, int width, int height)
{
	t_widget			*widget;
	t_drawable_data		*data;

	if (parent == NULL)
		return (NULL);
	widget = ui_new_widget((SDL_Rect){x, y, width, height}, DRAWABLE, UI_MAX_DRAWABLE_CHILDS);
	if (!widget)
		return (NULL);
	if (ui_add_child(parent, widget) != UI_SUCCESS)
		return (free(widget), NULL);
	widget->data = malloc(sizeof(t_drawable_data));
	if (!widget->data)
		return (free(widget), NULL);
	ui_set_widget_colors(widget, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
	data = (t_drawable_data *)widget->data;
	*data = (t_drawable_data){0};
	data->brush_size = 25;
	data->brush_color = (SDL_Color){255, 255, 255, 255};
	widget->render = ui_drawable_render;
	widget->update = ui_drawable_update;
	widget->event = ui_drawable_event;
	widget->destroy = ui_drawable_destroy;
	widget->texture = SDL_CreateTexture(widget->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, widget->rect.w, widget->rect.h);
	SDL_SetTextureBlendMode(widget->texture, SDL_BLENDMODE_BLEND);
	ui_test(widget);
	ui_drawable_set_brush(widget, "libui/assets/brushs/brush_base.png");
	return (widget);
}