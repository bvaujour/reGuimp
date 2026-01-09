/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draws.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 11:27:20 by injah             #+#    #+#             */
/*   Updated: 2026/01/08 14:20:04 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

void	draw_rect_on_image(t_img img, int start_x, int start_y, int rect_width, int rect_height, unsigned int color)
{
	int		x;
	int		y;

	if (start_x < 0)
		start_x = 0;
	if (start_y < 0)
		start_y = 0;
	y = 0;
	while (start_y + y < img.height && y < rect_height)
	{
		x = 0;
		while (start_x + x < img.width && x < rect_width)
		{
			img.pixels[(start_y + y) * img.width + (start_x + x)] = color;
			x++;
		}
		y++;
	}
}

void	bucket_image(t_img img, int start_x, int start_y, unsigned color)
{
	unsigned int	target_color;
	t_vector2		*stack;
	int				top;
	t_vector2		current;

	if (start_x < 0 || start_x >= img.width || start_y < 0 || start_y >= img.height)
		return;
	target_color = img.pixels[start_y * img.width + start_x];
	if (target_color == color)
		return;
	stack = malloc((img.width * img.height) * sizeof(t_vector2));
	top = 0;
	stack[top++] = (t_vector2){start_x, start_y};
	while (top > 0)
	{
		current = stack[--top];
		if (current.x < 0 || current.x >= img.width || current.y < 0 || current.y >= img.height)
			continue ;
		if (img.pixels[current.y * img.width + current.x] != target_color || img.pixels[current.y * img.width + current.x] == color)
			continue ;
		img.pixels[current.y * img.width + current.x] = color;
		if (top < img.width * img.height)
			stack[top++] = (t_vector2){current.x + 1, current.y};
		if (top < img.width * img.height)
			stack[top++] = (t_vector2){current.x - 1, current.y};
		if (top < img.width * img.height)
			stack[top++] = (t_vector2){current.x, current.y + 1};
		if (top < img.width * img.height)
			stack[top++] = (t_vector2){current.x, current.y - 1};
	}
	free(stack);
}

void	copy_image_on_image(t_img src, t_img dst, int start_x, int start_y)
{
	int	x;
	int	y;
	
	if (start_x < 0)
		start_x = 0;
	if (start_y < 0)
		start_y = 0;
	y = 0;
	while (y < src.height && start_y + y < dst.height)
	{
		x = 0;
		while (x < src.width && start_x + x < dst.width)
		{
			dst.pixels[(start_y + y) * dst.width + (start_x + x)] = get_pixel(src, x, y);
			x++;
		}
		y++;
	}
}

