/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_drawable_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:55:47 by injah             #+#    #+#             */
/*   Updated: 2026/01/05 13:59:15 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

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