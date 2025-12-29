/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:53:38 by bvaujour          #+#    #+#             */
/*   Updated: 2025/12/29 00:41:50 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"


void	on_key_pressed(int key, void *param)
{
	t_data *data;

	data = (t_data *)param;
	if (key == UIKEY_ESCAPE)
		ui_quit(data->core);
	if (key == 'a')
		printf("test = %d\n", data->test);
	// if (key == 'e')
	// 	ui_drawable_export_jpg(data->drawable, "any.jpg", 50);
	printf("key = %d\n", key);
}

void	on_button_clicked(t_widget *widget, int mouse_button_click, void *param)
{
	t_data *data;
	
	data = (t_data *)param;
	if (widget == data->button)
	{
		ui_drawable_export_png(data->drawable, "lol.png");
		printf("button1 clicked\n");
	}
	else if (widget == data->button2)
	{
		printf("button2 clicked\n");
		ui_toggle_widget_visibility(data->box);
	}
	// static int size = 20;
	// if (clicked_widget == data->button)
	// {
	// 	ui_drawable_set_brush_size(data->drawable, size);
	// 	size++;
	// }
	// data->test++;
	printf("main button = %d\n", mouse_button_click);
}

void	on_slider_value_change(t_widget *slider, float value, void *param)
{
	t_data *data;

	data = (t_data *)param;
	if (slider == data->color_slider[RED])
	{
		data->color_values[RED] = value * 255;
	}
	else if (slider == data->color_slider[GREEN])
	{
		data->color_values[GREEN] = value * 255;
	}
	else if (slider == data->color_slider[BLUE])
	{
		data->color_values[BLUE] = value * 255;
	}
	else if (slider == data->color_slider[ALPHA])
	{
		data->color_values[ALPHA] = value * 255;
	}
	printf("%f\n", value);
	ui_drawable_set_brush_color(data->drawable, data->color_values[RED], data->color_values[GREEN], data->color_values[BLUE], data->color_values[ALPHA]);
}

int	main()
{
	t_data		data;
	(void)data;
	data = (t_data){0};
	data.test = 2;
	data.core = ui_init();
	ui_get_screen_size(&data.screen_width, &data.screen_height);
	ui_bind_onkeypress(data.core, on_key_pressed, &data);

	data.tool_window = ui_create_window(data.core, 0, 0, data.screen_width / 4, data.screen_height);
	data.render_window = ui_create_window(data.core, data.screen_width / 4, 0,  3 * data.screen_width / 4, data.screen_height);

	data.dragbox = ui_create_dragbox(data.tool_window, 0, 0, 300, 500);
	data.box = ui_create_box(data.dragbox, 50, 50, 300, 500);

	data.button = ui_create_button(data.box, 10, 10, 500, 100);
	// data.button2 = ui_create_button(data.tool_window, 0, 0, 30, 30);
	data.color_slider[RED] = ui_create_slider(data.box, 10, 140, 200, 30);
	data.color_slider[GREEN] = ui_create_slider(data.box, 10, 180, 200, 30);
	data.color_slider[BLUE] = ui_create_slider(data.box, 10, 220, 200, 30);
	data.color_slider[ALPHA] = ui_create_slider(data.box, 10, 260, 200, 30);
	data.drawable = ui_create_drawable(data.render_window, 0, 0, 800, 600);
	
	ui_bind_button_onclicked(data.button, on_button_clicked, &data);
	ui_set_widget_texture(data.tool_window, "libui/assets/backgrounds/dark-blue-paint-minimal-background.jpg");
	
	// ui_set_widget_position_and_size(data.button2, 0, 10, 100, 30);
	// ui_bind_button_onclicked(data.button2, on_button_clicked, &data);

	
	
	
	ui_bind_slider_onvaluechange(data.color_slider[RED], on_slider_value_change, &data);
	ui_bind_slider_onvaluechange(data.color_slider[GREEN], on_slider_value_change, &data);
	ui_bind_slider_onvaluechange(data.color_slider[BLUE], on_slider_value_change, &data);
	ui_bind_slider_onvaluechange(data.color_slider[ALPHA], on_slider_value_change, &data);







	
	ui_run(data.core);
	
	return (0);
}
