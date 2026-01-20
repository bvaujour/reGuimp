/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 13:02:42 by injah             #+#    #+#             */
/*   Updated: 2026/01/20 21:15:05 by xacharle         ###   ########.fr       */
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

int	lerp(int a, int b, int step, int max)
{
	return (a + (b - a) * step / max);
}

int	distance(int x1, int y1, int x2, int y2)
{
	int	dist;
	int	delta_x;
	int	delta_y;
	
	delta_x = x1 - x2;
	delta_y = y1 - y2;
	dist = sqrt(delta_x * delta_x + delta_y * delta_y);
	return (dist);
}

void	show_parameter(t_data *data, enum e_tool tool)
{
	int	i;

	i = 0;
	while (i < NUM_TOOL)
	{
		ui_set_widget_visibility(data->tool_parameters_boxes[i], false);
		i++;
	}
	ui_set_widget_visibility(data->tool_parameters_boxes[tool], true);
}

void	toggle_color_parameters_box(t_data *data)
{
	ui_toggle_widget_visibility(data->tool_color_parameter_box);
	// ui_set_widget_visibility(data->color_sliders[i], true);
	// i++;
}