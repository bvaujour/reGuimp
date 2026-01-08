/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:53:38 by bvaujour          #+#    #+#             */
/*   Updated: 2026/01/08 14:24:04 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

void	on_key_pressed(int key, void *param)
{
	t_data *data;

	data = (t_data *)param;
	if (key == UIKEY_ESCAPE)
		ui_quit(data->core);
	printf("key = %d\n", key);
}
void	on_widget_clicked(t_widget *widget, int button, int x, int y, void *param)
{
	t_data *data;
	t_img	img;
	data = (t_data *)param;
	if (widget == data->canvas)
	{
		img = ui_image_get_img(data->canvas);
		if (data->tool == DRAW_RECT && button == 1)
			draw_rect_on_image(img, x, y, 100, 100, pack_color(data->color));
		if (data->tool == BUCKET && button == 1)
			bucket_image(img, x, y, pack_color(data->color));
	}
	if (widget == data->button)
	{
		printf("button clicked\n");
		if (data->tool == DRAW_RECT)
		{
			data->tool = BUCKET;
		}
		else if (data->tool == BUCKET)
		{
			data->tool = DRAW_RECT;
		}
	}
}


int	main()
{
	t_data		data;

	data = (t_data){0};
	data.core = ui_init();
	data.color = (t_rgba){255, 0, 0, 255};
	ui_bind_onkeypress(data.core, on_key_pressed, &data);

	// data.tool_window = ui_create_window(data.core, 0, 0, data.screen_width / 4, data.screen_height);
	// data.render_window = ui_create_window(data.core, data.screen_width / 4, 0,  2 * data.screen_width / 4, data.screen_height);

	// data.dragbox = ui_create_dragbox(data.tool_window, 0, 0, 300, 500);
	// data.box = ui_create_box(data.dragbox, 50, 50, 300, 500);

	// // data.button2 = ui_create_button(data.tool_window, 0, 0, 30, 30);
	// data.color_slider[RED] = ui_create_slider(data.box, 10, 140, 200, 30);
	// data.color_slider[GREEN] = ui_create_slider(data.box, 10, 180, 200, 30);
	// data.color_slider[BLUE] = ui_create_slider(data.box, 10, 220, 200, 30);
	// data.color_slider[ALPHA] = ui_create_slider(data.box, 10, 260, 200, 30);
	// data.drawable = ui_create_drawable(data.render_window, 0, 0, 800, 600);
	// data.button = ui_create_button(data.tool_window, 10, 10, 500, 100);
	// data.text_button = ui_create_button(data.tool_window, 10, 10, 200, 100);
	// ui_bind_button_onclicked(data.text_button, on_button_clicked, &data);
	// ui_set_widget_texture(data.tool_window, "libui/assets/backgrounds/dark-blue-paint-minimal-background.jpg");

	// // ui_set_widget_position_and_size(data.button2, 0, 10, 100, 30);
	// // ui_bind_button_onclicked(data.button2, on_button_clicked, &data);
	
	
	// ui_bind_slider_onvaluechanged(data.color_slider[RED], on_slider_value_change, &data);
	// ui_bind_slider_onvaluechanged(data.color_slider[GREEN], on_slider_value_change, &data);
	// ui_bind_slider_onvaluechanged(data.color_slider[BLUE], on_slider_value_change, &data);
	// ui_bind_slider_onvaluechanged(data.color_slider[ALPHA], on_slider_value_change, &data);
	
	

	// ui_run(data.core);
	
	
	data.tool_window = ui_create_window(data.core, 0, 0, 800, 600);
	data.render_window = ui_create_window(data.core, 900, 0, 1000, 800);
	data.button = ui_create_button(data.tool_window, 50, 0, 100, 50);
	data.canvas = ui_create_image(data.render_window, 100, 100, 800, 600);
	
	// t_widget *box = ui_create_box(data.canvas, 0, 0, 100, 100);
// 
	// (void) box;

	ui_widget_bind_onclicked(data.button, on_widget_clicked, &data);
	ui_widget_bind_onclicked(data.canvas, on_widget_clicked, &data);
	ui_run(data.core);
	return (0);
}