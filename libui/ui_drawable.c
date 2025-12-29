/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_drawable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 21:16:05 by injah             #+#    #+#             */
/*   Updated: 2025/12/29 01:04:40 by injah            ###   ########.fr       */
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
	ui_drawable_event(widget, core->event);

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


int	ui_get_render_target_image_data(SDL_Renderer *renderer, SDL_Texture *texture, t_image_data *img)
{
	SDL_QueryTexture(texture, NULL, NULL, &img->width, &img->height);
	img->pixels = malloc(sizeof(Uint32) * img->width * img->height);
	if (img->pixels == NULL)
		return (UI_ERROR);
	SDL_SetRenderTarget(renderer, texture);
	SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, img->pixels, img->width * sizeof(Uint32));
	SDL_SetRenderTarget(renderer, NULL);
	return (UI_SUCCESS);
}

void	ui_set_render_target_pixels(SDL_Renderer *renderer, SDL_Texture *texture, Uint32 *pixels)
{
	int			width;
	int			height;
	SDL_Texture *tmp;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	tmp = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
	SDL_UpdateTexture(tmp, NULL, pixels, width * sizeof(Uint32));
	SDL_SetRenderTarget(renderer, texture);
	SDL_RenderCopy(renderer, tmp, NULL, NULL);
	SDL_SetRenderTarget(renderer, NULL);
	SDL_DestroyTexture(tmp);
}

void	ui_draw_rect_on_image(t_image_data img, SDL_Rect rect, Uint32 color)
{
	int		x;
	int		y;

	if (rect.x < 0)
		rect.x = 0;
	if (rect.y < 0)
		rect.y = 0;
	y = rect.y;
	while (y < img.height && y < rect.h)
	{
		x = rect.x;
		while (x < img.width && x < rect.w)
		{
			img.pixels[y * img.width + x] = color;
			x++;
		}
		y++;
	}
}

void	ui_draw_disk_on_image(t_image_data img, SDL_Point center, int radius, Uint32 color)
{
	int	x;
	int	y;
	int	dx;
	int	dy;
	int	sqr_y;
	int	sqr_rad;

	sqr_rad = radius * radius;
	y = center.y - radius;
	if (y < 0)
		y = 0;
	while (y < center.y + radius && y < img.height)
	{
		x = center.x - radius;
		if (x < 0)
			x = 0;
		dy = y - center.y;
		sqr_y = dy * dy;
		while (x < center.x + radius && x < img.width)
		{
			dx = x - center.x;
			if (dx * dx + sqr_y <= sqr_rad)
				img.pixels[y * img.width + x] = color;
			x++;
		}
		y++;
	}
}

void ui_draw_circle_on_image(t_image_data img, SDL_Point center, int radius, int thickness, Uint32 color)
{
    int r_outer = radius;
    int r_inner = radius - thickness;

    if (r_inner < 0)
        r_inner = 0;

    int r_outer2 = r_outer * r_outer;
    int r_inner2 = r_inner * r_inner;

    int min_x = center.x - r_outer;
    int max_x = center.x + r_outer;
    int min_y = center.y - r_outer;
    int max_y = center.y + r_outer;

    if (min_x < 0) min_x = 0;
    if (min_y < 0) min_y = 0;
    if (max_x >= img.width)  max_x = img.width - 1;
    if (max_y >= img.height) max_y = img.height - 1;

    for (int y = min_y; y <= max_y; y++)
    {
        int dy = y - center.y;
        int dy2 = dy * dy;

        for (int x = min_x; x <= max_x; x++)
        {
            int dx = x - center.x;
            int d2 = dx * dx + dy2;

            if (d2 <= r_outer2 && d2 >= r_inner2)
                img.pixels[y * img.width + x] = color;
        }
    }
}


void ui_bucket_image(t_image_data img, int start_x, int start_y, Uint32 color)
{
	Uint32		target;
	SDL_Point	*stack;
	int			top;
	SDL_Point	current;

	if (start_x < 0 || start_x >= img.width || start_y < 0 || start_y >= img.height)
		return;
	target = img.pixels[start_y * img.width + start_x];
	if (target == color)
		return;
	stack = malloc(img.width * img.height * sizeof(SDL_Point));
	top = 0;
	stack[top++] = (SDL_Point){start_x, start_y};
	while (top > 0)
	{
		current = stack[--top];
		if (current.x < 0 || current.x >= img.width || current.y < 0 || current.y >= img.height)
			continue ;
		if (img.pixels[current.y * img.width + current.x] != target)
			continue ;
		img.pixels[current.y * img.width + current.x] = color;
		stack[top++] = (SDL_Point){current.x + 1, current.y};
		stack[top++] = (SDL_Point){current.x - 1, current.y};
		stack[top++] = (SDL_Point){current.x, current.y + 1};
		stack[top++] = (SDL_Point){current.x, current.y - 1};
	}
	free(stack);
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

	ui_get_render_target_image_data(widget->renderer, widget->texture, &img);
	// ui_draw_rect_on_image(img, (SDL_Rect){0, 0, 200, 200}, 0x7fFF0000);
	ui_draw_circle_on_image(img, (SDL_Point){300, 200}, 100, 1, 0x7fFF0000);
	ui_bucket_image(img, 500, 1, 0xFF00FF00);
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
	widget->destroy = ui_drawable_destroy;
	widget->texture = SDL_CreateTexture(widget->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, widget->rect.w, widget->rect.h);
	SDL_SetTextureBlendMode(widget->texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(widget->renderer, 255, 255, 255, 255);
	SDL_SetRenderTarget(widget->renderer, widget->texture);
	SDL_RenderDrawRect(widget->renderer, &(SDL_Rect){0, 0, 100, 100});
	SDL_RenderDrawLine(widget->renderer, 101, 201, 400, 400);
	SDL_SetRenderTarget(widget->renderer, NULL);
	ui_test(widget);
	ui_drawable_set_brush(widget, "libui/assets/brushs/brush_base.png");
	return (widget);
}