/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_widget_user.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 03:24:56 by injah             #+#    #+#             */
/*   Updated: 2025/12/17 05:09:57 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

void	ui_set_widget_position(t_widget *widget, int x, int y)
{
	widget->rect.x = x;
	widget->rect.y = y;
}

void	ui_set_widget_size(t_widget *widget, int width, int height)
{
	widget->rect.w = width;
	widget->rect.h = height;
	if (widget->build)
		widget->build(widget);
	else
		printf("ui_set_widget_size: widget has no build\n");
}

void	ui_set_widget_position_and_size(t_widget *widget, int x, int y, int width, int height)
{
	ui_set_widget_position(widget, x, y);
	ui_set_widget_size(widget, width, height);
}

void	ui_set_widget_colors(t_widget *widget, unsigned int normal, unsigned int hovered, unsigned int clicked)
{
	if (widget == NULL)
	{
		printf("Error: ui_set_widget_colors used on null widget\n");
		return ;
	}
	widget->colors[UI_NORMAL_COLOR] = ui_unpack_color(normal);
	widget->colors[UI_HOVERED_COLOR] = ui_unpack_color(hovered);
	widget->colors[UI_CLICKED_COLOR] = ui_unpack_color(clicked);
}