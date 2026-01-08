/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:53:38 by bvaujour          #+#    #+#             */
/*   Updated: 2026/01/08 12:29:01 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"


void	on_key_pressed(int key, void *param)
{
	t_data *data;

	data = (t_data *)param;
	if (key == UIKEY_ESCAPE)
		ui_quit(data->core);
	// if (key == 'e')
	// 	ui_drawable_export_jpg(data->drawable, "any.jpg", 50);
	printf("key = %d\n", key);
}

// void	on_button_clicked(t_widget *widget, int mouse_button_click, void *param)
// {
// 	t_data *data;
	
// 	data = (t_data *)param;
// 	if (widget == data->button)
// 	{
// 		ui_drawable_export_png(data->drawable, "lol.png");
// 		printf("button1 clicked\n");
// 	}
// 	else if (widget == data->button2)
// 	{
// 		printf("button2 clicked\n");
// 		ui_toggle_widget_visibility(data->box);
// 	}
// 	// static int size = 20;
// 	// if (clicked_widget == data->button)
// 	// {
// 	// 	ui_drawable_set_brush_size(data->drawable, size);
// 	// 	size++;
// 	// }
// 	// data->test++;
// 	printf("main button = %d\n", mouse_button_click);
// }

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
}

void	on_widget_clicked(t_widget *widget, int button, int x, int y, void *param)
{
	t_data *data;
	t_img	img;
	data = (t_data *)param;
	if (widget == data->canvas)
	{
		img = ui_canvas_get_img(data->canvas);
		if (data->tool == DRAW_RECT && button == 1)
			draw_rect_on_image(img, x, y, 100, 100, 0xFFFF0000);
	}
}


int	main()
{
	t_data		data;

	data = (t_data){0};
	data.core = ui_init();
	ui_bind_onkeypress(data.core, on_key_pressed, &data);
	data.render_window = ui_create_window(data.core, 0, 0, 800, 600);
	data.canvas = ui_create_canvas(data.render_window, 0, 0, 800, 600);
	ui_widget_bind_onclicked(data.canvas, on_widget_clicked, &data);
	ui_run(data.core);
	return (0);
}