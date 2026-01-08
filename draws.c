/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draws.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 11:27:20 by injah             #+#    #+#             */
/*   Updated: 2026/01/08 12:26:34 by injah            ###   ########.fr       */
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

