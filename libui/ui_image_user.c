/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_image_user.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 18:55:09 by injah             #+#    #+#             */
/*   Updated: 2026/01/11 15:49:42 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

t_img	ui_image_get_img(t_widget *image)
{
	t_img			img;
	t_image_data	*data;
	
	data = (t_image_data *)image->data;
	SDL_SetRenderTarget(image->renderer, image->texture);
	SDL_RenderReadPixels(image->renderer, NULL, SDL_PIXELFORMAT_ARGB8888, data->surface->pixels, data->surface->pitch);
	SDL_SetRenderTarget(image->renderer, NULL);
	img.width = image->rect.w;
	img.height = image->rect.h;
	img.pixels = data->surface->pixels;
	img.pitch = data->surface->pitch;
	return (img);
}

void	ui_image_set_img(t_widget *image, t_img img)
{
	SDL_UpdateTexture(image->texture, NULL, img.pixels, img.pitch);
}

void	ui_draw_rect(t_widget *image, int x, int y, int width, int height, unsigned int color)
{
	SDL_Color	c;

	c = ui_unpack_color(color);
	SDL_SetRenderDrawColor(image->renderer, c.r, c.g, c.b, c.a);
	SDL_SetRenderTarget(image->renderer, image->texture);
	SDL_RenderDrawRect(image->renderer, &(SDL_Rect){x, y, width, height});
	SDL_SetRenderTarget(image->renderer, NULL);
}

void ui_draw_filled_rect(t_widget *image, int x, int y, int width, int height, unsigned int color)
{
	SDL_Color	c;

	c = ui_unpack_color(color);
	SDL_SetRenderTarget(image->renderer, image->texture);
	SDL_SetRenderDrawColor(image->renderer, c.r, c.g, c.b, c.a);
	SDL_RenderFillRect(image->renderer, &(SDL_Rect){x, y, width, height});
	SDL_SetRenderTarget(image->renderer, NULL);
}


void	ui_draw_point(t_widget *image, int x, int y, unsigned int color)
{
	SDL_Color	c;

	c = ui_unpack_color(color);
	SDL_SetRenderDrawColor(image->renderer, c.r, c.g, c.b, c.a);
	SDL_SetRenderTarget(image->renderer, image->texture);
	SDL_RenderDrawPoint(image->renderer, x, y);
	SDL_SetRenderTarget(image->renderer, NULL);
}

void	ui_draw_line(t_widget *image, int x1, int y1, int x2, int y2, unsigned int color)
{
	SDL_Color	c;

	c = ui_unpack_color(color);
	SDL_SetRenderDrawColor(image->renderer, c.r, c.g, c.b, c.a);
	SDL_SetRenderTarget(image->renderer, image->texture);
	SDL_RenderDrawLine(image->renderer, x1, y1, x2, y2);
	SDL_SetRenderTarget(image->renderer, NULL);
}


void	ui_draw_circle(t_widget *image, int center_x, int center_y, int radius, unsigned int color)
{
	int x = (radius - 1);
	int y = 0;
	int tx = 1;
	int ty = 1;
	int error = tx - (radius * 2);
	SDL_Color	c;

	c = ui_unpack_color(color);
	SDL_SetRenderDrawColor(image->renderer, c.r, c.g, c.b, c.a);
	SDL_SetRenderTarget(image->renderer, image->texture);

	while (x >= y)
	{
		SDL_RenderDrawPoint(image->renderer, center_x + x, center_y - y);
		SDL_RenderDrawPoint(image->renderer, center_x + x, center_y + y);
		SDL_RenderDrawPoint(image->renderer, center_x - x, center_y - y);
		SDL_RenderDrawPoint(image->renderer, center_x - x, center_y + y);
		SDL_RenderDrawPoint(image->renderer, center_x + y, center_y - x);
		SDL_RenderDrawPoint(image->renderer, center_x + y, center_y + x);
		SDL_RenderDrawPoint(image->renderer, center_x - y, center_y - x);
		SDL_RenderDrawPoint(image->renderer, center_x - y, center_y + x);
		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}
		if (error > 0)
		{
			--x;
			tx += 2;
			error += tx - (radius * 2);
		}
	}
	SDL_SetRenderTarget(image->renderer, NULL);
}

void	ui_draw_filled_circle(t_widget *image, int center_x, int center_y, int radius, unsigned int color)
{
	int	x;
	int y;
	int sqr_radius;
	int	sqr_dy;
	SDL_Color	c;

	c = ui_unpack_color(color);
	SDL_SetRenderDrawColor(image->renderer, c.r, c.g, c.b, c.a);
	SDL_SetRenderTarget(image->renderer, image->texture);
	sqr_radius = radius * radius;
	y = center_y - radius;
	while (y < center_y + radius)
	{
		x = center_x - radius;
		sqr_dy = (center_y - y) * (center_y - y);
		while (x < center_x + radius)
		{
			if (sqr_dy + (center_x - x) * (center_x - x) <= sqr_radius)
				SDL_RenderDrawPoint(image->renderer, x, y);
			x++;
		}
		y++;
	}
	SDL_SetRenderTarget(image->renderer, NULL);
}


void	ui_bucket_image(t_widget *image, int start_x, int start_y, unsigned color)
{
	unsigned int	target_color;
	SDL_Point		*stack;
	int				top;
	int				stack_size;
	SDL_Point		current;
	t_img			img;

	img = ui_image_get_img(image);
	if (start_x < 0 || start_x >= img.width || start_y < 0 || start_y >= img.height)
		return;
	target_color = img.pixels[start_y * img.width + start_x];
	if (target_color == color)
		return;
	stack_size = (img.width * img.height) * 3;
	stack = malloc(stack_size * sizeof(SDL_Point));
	top = 0;
	stack[top++] = (SDL_Point){start_x, start_y};
	while (top > 0)
	{
		current = stack[--top];
		if (current.x < 0 || current.x >= img.width || current.y < 0 || current.y >= img.height)
			continue ;
		if (img.pixels[current.y * img.width + current.x] != target_color || img.pixels[current.y * img.width + current.x] == color)
			continue ;
		img.pixels[current.y * img.width + current.x] = color;
		if (top < stack_size)
			stack[top++] = (SDL_Point){current.x + 1, current.y};
		if (top < stack_size)
			stack[top++] = (SDL_Point){current.x - 1, current.y};
		if (top < stack_size)
			stack[top++] = (SDL_Point){current.x, current.y + 1};
		if (top < stack_size)
			stack[top++] = (SDL_Point){current.x, current.y - 1};
	}
	free(stack);
	ui_image_set_img(image, img);
}

void	ui_clear_image(t_widget *image, unsigned int color)
{
	SDL_Color	c;

	c = ui_unpack_color(color);
	SDL_SetRenderDrawColor(image->renderer, c.r, c.g, c.b, c.a);
	SDL_SetRenderTarget(image->renderer, image->texture);
	SDL_RenderClear(image->renderer);
	SDL_SetRenderTarget(image->renderer, NULL);
}

void ui_erase_image(t_widget *image, int x, int y)
{
	SDL_SetRenderTarget(image->renderer, image->texture);

	// Pas de blending → écriture directe
	SDL_SetRenderDrawBlendMode(image->renderer, SDL_BLENDMODE_NONE);

	// Transparent
	SDL_SetRenderDrawColor(image->renderer, 0, 0, 0, 0);

	SDL_RenderFillRect(image->renderer, &(SDL_Rect){x, y, 100, 100});

	SDL_SetRenderTarget(image->renderer, NULL);

	// Restaurer le mode normal
	SDL_SetRenderDrawBlendMode(image->renderer, SDL_BLENDMODE_BLEND);
}


