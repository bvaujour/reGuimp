/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:35:55 by injah             #+#    #+#             */
/*   Updated: 2026/01/14 11:40:56 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

void	build_tool_buttons(t_data *data)
{
	data->tool_buttons[PENCIL] = ui_create_button(data->tool_buttons_box, 0, 0, 50, 50);
	data->tool_buttons[DRAW_RECT] = ui_create_button(data->tool_buttons_box, 0, 0, 50, 50);
	data->tool_buttons[DRAW_CIRCLE] = ui_create_button(data->tool_buttons_box, 0, 0, 50, 50);
	data->tool_buttons[DRAW_BRUSH] = ui_create_button(data->tool_buttons_box, 0, 0, 50, 50);
	data->tool_buttons[ERASER] = ui_create_button(data->tool_buttons_box, 0, 0, 50, 50);
	data->tool_buttons[BUCKET] = ui_create_button(data->tool_buttons_box, 0, 0, 50, 50);
	// data->tool_buttons[COLOR_FRONT] = ui_create_button(data->tool_color_box, 0, 0, 50, 50);
	// data->tool_buttons[COLOR_BACK] = ui_create_button(data->tool_color_box, 0, 0, 50, 50);

	ui_set_widget_texture(data->tool_buttons[PENCIL], "assets/icons/pencil0.png");
	ui_set_widget_texture(data->tool_buttons[DRAW_RECT], "assets/icons/rectangle0.png");
	ui_set_widget_texture(data->tool_buttons[DRAW_CIRCLE], "assets/icons/circle0.png");
	ui_set_widget_texture(data->tool_buttons[DRAW_BRUSH], "assets/icons/brush0.png");
	ui_set_widget_texture(data->tool_buttons[BUCKET], "assets/icons/bucket0.png");
	ui_set_widget_texture(data->tool_buttons[ERASER], "assets/icons/eraser0.png");

	ui_widget_bind_onclicked(data->tool_buttons[PENCIL], on_widget_clicked, data); 
	ui_widget_bind_onclicked(data->tool_buttons[DRAW_RECT], on_widget_clicked, data);
	ui_widget_bind_onclicked(data->tool_buttons[DRAW_CIRCLE], on_widget_clicked, data);
	ui_widget_bind_onclicked(data->tool_buttons[DRAW_BRUSH], on_widget_clicked, data);
	ui_widget_bind_onclicked(data->tool_buttons[ERASER], on_widget_clicked, data);
	ui_widget_bind_onclicked(data->tool_buttons[BUCKET], on_widget_clicked, data);
}