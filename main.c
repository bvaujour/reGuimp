/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:53:38 by bvaujour          #+#    #+#             */
/*   Updated: 2026/01/20 16:24:46 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

#define DRAW_WITH_LIBUI	true

void	on_key_pressed(int key, void *param)
{
	t_data *data;

	data = (t_data *)param;
	if (key == UIKEY_ESCAPE)
		ui_quit(data->core);
	printf("key = %d\n", key);
}

void	on_mouse_button_up(int button, void *param)
{
	t_data *data;

	data = (t_data *)param;
	if (button == 1)
		data->drawing.is_drawing = false;
}

void	on_widget_clicked(t_widget *widget, int button, int x, int y, void *param)
{
	t_data *data;

	data = (t_data *)param;
	if (widget == data->canvas)
	{
		if (DRAW_WITH_LIBUI)
			draw_with_libui(data, data->canvas, button, x, y);
		else
			draw_with_guimp(data, data->canvas, button, x, y);
	}
	else if (widget == data->tool_buttons[PENCIL])
	{
		ui_set_widget_cursor(data->canvas, "assets/cursors/pencil0.png");
		data->active_tool = PENCIL;
		show_parameter(data, PENCIL);
	}
	else if (widget == data->tool_buttons[DRAW_RECT])
	{
		ui_set_widget_cursor(data->canvas, "assets/cursors/rectangle0.png");
		data->active_tool = DRAW_RECT;
		show_parameter(data, DRAW_RECT);
	}
	else if (widget == data->tool_buttons[DRAW_CIRCLE])
	{
		ui_set_widget_cursor(data->canvas, "assets/cursors/circle0.png");
		data->active_tool = DRAW_CIRCLE;
		show_parameter(data, DRAW_CIRCLE);
	}
	else if (widget == data->tool_buttons[DRAW_BRUSH])
	{
		ui_set_widget_cursor(data->canvas, "assets/cursors/brush0.png");
		data->active_tool = DRAW_BRUSH;
		show_parameter(data, DRAW_BRUSH);
	}
	else if (widget == data->tool_buttons[ERASER])
	{
		ui_set_widget_cursor(data->canvas, "assets/cursors/eraser0.png");
		data->active_tool = ERASER;
		show_parameter(data, ERASER);
	}
	else if (widget == data->tool_buttons[BUCKET])
	{
		ui_set_widget_cursor(data->canvas, "assets/cursors/bucket0.png");
		data->active_tool = BUCKET;
		show_parameter(data, BUCKET);
	}
	// else if (widget == data->button)
	// 	;
}

void	on_slider_change_value(t_widget *slider, float value, void *param)
{
	t_data *data;
	
	data = (t_data *)param;
	(void)data;
	(void)slider;
	data->drawing.thickness = value * 50;
	printf("slider value: %f\n", value);
}

void	on_text_validate(t_widget *text, const char *str, void *param)
{
	t_data *data;
	
	data = (t_data *)param;
	if (text == data->text)
		printf("text = %s\n", str);
}


int	main()
{
	t_data		data;

	data = (t_data){0};
	data.core = ui_init();
	data.color = (t_rgba){0, 0, 0, 255};
	data.drawing.thickness = 1;
	ui_bind_onkeypress(data.core, on_key_pressed, &data);
	ui_bind_onbuttondown(data.core, on_mouse_button_up, &data);
	data.tool_window = ui_create_window(data.core, 0, 0, 800, 600);
	data.tool_window_box = ui_create_box(data.tool_window, 20, 20, 760, 560);
	data.tool_buttons_box = ui_create_box(data.tool_window_box, 20, 20, 500, 150);
	// data.tool_color_box = ui_create_box(data.tool_window_box, 340, 20, 720, 150);
	data.tool_color_box = ui_create_button(data.tool_window_box, 380, 25, 50, 50);
	ui_set_widget_colors(data.tool_color_box, 0xFFFF0000, 0xFF00FF00, 0xFF0000FF);
	
	ui_set_box_behavior(data.tool_buttons_box, HORIZONTAL, 5, true, true);
	build_tool_buttons(&data);
	
	data.tool_parameters_boxes[PENCIL] = ui_create_box(data.tool_window_box, 20, 170, 720, 370);
	data.tool_parameters_boxes[DRAW_RECT] = ui_create_box(data.tool_window_box, 20, 170, 720, 370);
	data.tool_parameters_boxes[DRAW_CIRCLE] = ui_create_box(data.tool_window_box, 20, 170, 720, 370);
	data.tool_parameters_boxes[DRAW_BRUSH] = ui_create_box(data.tool_window_box, 20, 170, 720, 370);
	data.tool_parameters_boxes[BUCKET] = ui_create_box(data.tool_window_box, 20, 170, 720, 370);
	data.tool_parameters_boxes[ERASER] = ui_create_box(data.tool_window_box, 20, 170, 720, 370);

	
	data.button = ui_create_button(data.tool_parameters_boxes[PENCIL], 20, 20, 100, 50);
	ui_widget_bind_onclicked(data.button, on_widget_clicked, &data);

	data.drawing.thickness_slider = ui_create_slider(data.tool_parameters_boxes[PENCIL], 20, 90, 100, 20);
	ui_bind_slider_onvaluechanged(data.drawing.thickness_slider, on_slider_change_value, &data);

	data.render_window = ui_create_window(data.core, 900, 0, 1000, 800);
	data.canvas = ui_create_image(data.render_window, 100, 100, 800, 600);
	ui_widget_bind_onclicked(data.canvas, on_widget_clicked, &data);
	ui_set_widget_cursor(data.canvas, "assets/cursors/pencil0.png");
	data.active_tool = PENCIL;
	show_parameter(&data, PENCIL);

	t_widget *text;
	text = ui_create_text(data.button, 0, 0, 100, 50);
	(void)text;
	ui_text_set_text(text, "File");
	
	data.text_box = ui_create_box(data.tool_parameters_boxes[DRAW_RECT], 10, 10, 700, 50);
	ui_set_widget_colors(data.text_box, 0x7f000000, 0x7f000000, 0x7f000000);
	data.text = ui_create_text(data.text_box, 0, 0, 50, 50);
	ui_bind_text_onvalidate(data.text, on_text_validate, &data);
	ui_run(data.core);
	return (0);
}

	// PENCIL,
	// DRAW_RECT,
	// DRAW_CIRCLE,
	// DRAW_BRUSH,
	// BUCKET,
	// ERASER,