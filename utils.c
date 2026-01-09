/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 13:02:42 by injah             #+#    #+#             */
/*   Updated: 2026/01/08 14:07:11 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

t_rgba	unpack_color(unsigned int color)
{
	t_rgba	unpacked_color;

	unpacked_color.a = (color >> 24) & 0xFF;
	unpacked_color.r = (color >> 16) & 0xFF;
	unpacked_color.g = (color >> 8) & 0xFF;
	unpacked_color.b = color & 0xFF;
	return (unpacked_color);
}

unsigned int pack_color(t_rgba color)
{
	unsigned int	packed_color;

	packed_color = color.a << 24 | color.r << 16 | color.g << 8 | color.b;
	return (packed_color);
}

void	set_pixel(t_img img, int x, int y, unsigned int color)
{
	img.pixels[img.width * y + x] = color;
}

unsigned int	get_pixel(t_img img, int x, int y)
{
	return (img.pixels[img.width * y + x]);
}