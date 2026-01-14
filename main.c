/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:53:38 by bvaujour          #+#    #+#             */
/*   Updated: 2026/01/14 11:41:33 by xacharle         ###   ########.fr       */
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
		set_parameter_tool_visibility(data, PENCIL);
	}
	else if (widget == data->tool_buttons[DRAW_RECT])
	{
		ui_set_widget_cursor(data->canvas, "assets/cursors/rectangle0.png");
		data->active_tool = DRAW_RECT;
		set_parameter_tool_visibility(data, DRAW_RECT);
	}
	else if (widget == data->tool_buttons[DRAW_CIRCLE])
	{
		ui_set_widget_cursor(data->canvas, "assets/cursors/circle0.png");
		data->active_tool = DRAW_CIRCLE;
		set_parameter_tool_visibility(data, DRAW_CIRCLE);
	}
	else if (widget == data->tool_buttons[DRAW_BRUSH])
	{
		ui_set_widget_cursor(data->canvas, "assets/cursors/brush0.png");
		data->active_tool = DRAW_BRUSH;
		set_parameter_tool_visibility(data, DRAW_BRUSH);
	}
	else if (widget == data->tool_buttons[ERASER])
	{
		ui_set_widget_cursor(data->canvas, "assets/cursors/eraser0.png");
		data->active_tool = ERASER;
		set_parameter_tool_visibility(data, ERASER);
	}
	else if (widget == data->tool_buttons[BUCKET])
	{
		ui_set_widget_cursor(data->canvas, "assets/cursors/bucket0.png");
		data->active_tool = BUCKET;
		set_parameter_tool_visibility(data, BUCKET);
	}
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
	data.tool_buttons_box = ui_create_box(data.tool_window_box, 20, 20, 720, 150);
	ui_set_box_behavior(data.tool_buttons_box, HORIZONTAL, 5, false, true);
	// ui_set_box_behavior(data.tool_color_box, HORIZONTAL, 5, false, true);
	build_tool_buttons(&data);
	
	data.tool_parameters_boxes[PENCIL] = ui_create_box(data.tool_window_box, 20, 170, 720, 370); // pourquoi parents sonts data.tool_window_box et non tool_buttons_box ? Comment ca peut etre aligné alors que y = 170 ?
	data.tool_parameters_boxes[DRAW_RECT] = ui_create_box(data.tool_window_box, 20, 170, 720, 370);
	data.tool_parameters_boxes[DRAW_CIRCLE] = ui_create_box(data.tool_window_box, 20, 170, 720, 370);
	data.tool_parameters_boxes[DRAW_BRUSH] = ui_create_box(data.tool_window_box, 20, 170, 720, 370);
	data.tool_parameters_boxes[BUCKET] = ui_create_box(data.tool_window_box, 20, 170, 720, 370);
	data.tool_parameters_boxes[ERASER] = ui_create_box(data.tool_window_box, 20, 170, 720, 370);
	// data.tool_parameters_boxes[COLOR_FRONT] = ui_create_box(data.tool_window_box, 20, 170, 720, 370);
	// data.tool_parameters_boxes[COLOR_BACK] = ui_create_box(data.tool_window_box, 20, 170, 720, 370);


	data.button = ui_create_button(data.tool_parameters_boxes[PENCIL], 20, 20, 100, 50);
	data.render_window = ui_create_window(data.core, 900, 0, 1000, 800);
	data.canvas = ui_create_image(data.render_window, 100, 100, 800, 600);
	ui_widget_bind_onclicked(data.canvas, on_widget_clicked, &data);
	ui_set_widget_cursor(data.canvas, "assets/cursors/pencil0.png");
	data.active_tool = PENCIL;
	set_parameter_tool_visibility(&data, PENCIL);
	ui_run(data.core);
	return (0);
}

	// PENCIL,
	// DRAW_RECT,
	// DRAW_CIRCLE,
	// DRAW_BRUSH,
	// BUCKET,
	// ERASER,