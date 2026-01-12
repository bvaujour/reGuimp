/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draws_with_libui.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 02:17:57 by injah             #+#    #+#             */
/*   Updated: 2026/01/12 17:30:30 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

// void	pencil(t_data *data, t_widget *canvas, int x, int y)
// {
// 	int	i;
// 	int	j;
// 	int	half_thickness;

// 	half_thickness = data->drawing.thickness / 2;
// 	if (data->drawing.is_drawing == false)
// 	{
// 		ui_draw_filled_rect(canvas, x - half_thickness, y - half_thickness, data->drawing.thickness, data->drawing.thickness, pack_color(data->color));
// 		data->drawing.is_drawing = true;
// 	}
// 	else
// 	{
// 		j = -half_thickness;
// 		while (j < half_thickness)
// 		{
// 			i = -half_thickness;
// 			while (i < half_thickness)
// 			{
// 				ui_draw_line(canvas, data->drawing.last_x + i, data->drawing.last_y + j, x + i, y + j, pack_color(data->color));
// 				i++;
// 			}
// 			j++;
// 		}
// 	}
// 	data->drawing.last_x = x;
// 	data->drawing.last_y = y;
// }

// void	pencil(t_data *data, t_widget *canvas, int x, int y)
// {
// 	int	i;
// 	int	half_thickness;
// 	int	dist;

// 	half_thickness = data->drawing.thickness / 2;
// 	if (half_thickness < 1)
// 		half_thickness = 1;
// 	if (data->drawing.is_drawing == false)
// 	{
// 		ui_draw_filled_circle(canvas, x - half_thickness, y - half_thickness, half_thickness, pack_color(data->color));
// 		data->drawing.is_drawing = true;
// 	}
// 	else
// 	{
// 		dist = distance(data->drawing.last_x, data->drawing.last_y, x, y);
// 		if (dist < half_thickness)
// 			return ;
// 		i = 0;
// 		while (i < dist)
// 		{
// 			ui_draw_filled_circle(canvas, lerp(data->drawing.last_x, x, i, dist) - half_thickness, lerp(data->drawing.last_y, y, i, dist) - half_thickness, half_thickness, pack_color(data->color));
// 			i += half_thickness;
// 		}
// 	}
// 	data->drawing.last_x = x;
// 	data->drawing.last_y = y;
// }

void	pencil(t_data *data, t_widget *canvas, int x, int y)
{
	int	i;
	int	half_thickness;
	int	dist;

	half_thickness = data->drawing.thickness / 2;
	if (half_thickness < 1)
		half_thickness = 1;
	if (data->drawing.is_drawing == false)
	{
		ui_draw_filled_rect(canvas, x - half_thickness, y - half_thickness, data->drawing.thickness, data->drawing.thickness, pack_color(data->color));
		data->drawing.is_drawing = true;
	}
	else
	{
		dist = distance(data->drawing.last_x, data->drawing.last_y, x, y);
		if (dist < half_thickness)
			return ;
		i = 0;
		while (i < dist)
		{
			ui_draw_filled_rect(canvas, lerp(data->drawing.last_x, x, i, dist) - half_thickness, lerp(data->drawing.last_y, y, i, dist) - half_thickness, data->drawing.thickness, data->drawing.thickness, pack_color(data->color));
			i += half_thickness;
		}
	}
	data->drawing.last_x = x;
	data->drawing.last_y = y;
}


void	draw_with_libui(t_data *data, t_widget *canvas, int button, int x, int y)
{
	if (button == 1)
	{
		if (data->active_tool == DRAW_RECT)
			ui_draw_rect(canvas, x - 50, y - 50, 100, 100, pack_color(data->color));
		else if (data->active_tool == BUCKET)
			ui_bucket_image(canvas, x, y, pack_color(data->color));
		else if (data->active_tool == PENCIL)
			pencil(data, canvas, x, y);
		else if (data->active_tool == DRAW_CIRCLE)
			ui_draw_circle(canvas, x, y, 10, pack_color(data->color));
		else if (data->active_tool == ERASER)
			ui_erase_image(canvas, x, y);
	}
}

