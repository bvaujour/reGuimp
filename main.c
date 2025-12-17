/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:53:38 by bvaujour          #+#    #+#             */
/*   Updated: 2025/12/17 13:56:07 by injah            ###   ########.fr       */
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
	if (key == 'e')
		ui_drawable_export_jpg(data->drawable, "any.jpg", 50);
	printf("key = %d\n", key);
}

void	on_button_clicked(t_widget *widget, int mouse_button_click, void *param)
{
	t_data *data;

	data = (t_data *)param;
	if (widget == data->button)
	{
		printf("button1 clicked\n");
	}
	else if (widget == data->button2)
	{
		printf("button2 clicked\n");
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
	ui_drawable_set_brush_color(data->drawable, data->color_values[RED], data->color_values[GREEN], data->color_values[BLUE], data->color_values[ALPHA]);
}

int	main()
{
	t_data		data;
	(void)data;
	data = (t_data){0};
	data.test = 2;
	data.core = ui_init(1280, 720);
	ui_bind_onkeypress(data.core, on_key_pressed, &data);

	data.button = ui_create_button(data.core, 10, 10, 100, 50);
	ui_bind_widget_onclick(data.button, on_button_clicked, &data);
	
	
	// data.button2 = ui_create_button(data.core, 10, 70, 100, 50);
	// ui_bind_widget_onclick(data.button2, on_button_clicked, &data);

	
	
	// data.drawable = ui_create_drawable(data.core, 300, 30, 500, 500);
	
	
	// data.color_slider[RED] = ui_create_slider(data.core, 10, 140, 200, 30);
	// ui_bind_slider_onvaluechange(data.color_slider[RED], on_slider_value_change, &data);
	// data.color_slider[GREEN] = ui_create_slider(data.core, 10, 180, 200, 30);
	// ui_bind_slider_onvaluechange(data.color_slider[GREEN], on_slider_value_change, &data);
	// data.color_slider[BLUE] = ui_create_slider(data.core, 10, 220, 200, 30);
	// ui_bind_slider_onvaluechange(data.color_slider[BLUE], on_slider_value_change, &data);
	// data.color_slider[ALPHA] = ui_create_slider(data.core, 10, 260, 200, 30);
	// ui_bind_slider_onvaluechange(data.color_slider[ALPHA], on_slider_value_change, &data);








	
	ui_run(data.core);
	
	return (0);
}
