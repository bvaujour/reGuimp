/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:53:38 by bvaujour          #+#    #+#             */
/*   Updated: 2026/01/08 13:31:42 by injah            ###   ########.fr       */
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
	data.tool_window = ui_create_window(data.core, 0, 0, 800, 600);
	data.render_window = ui_create_window(data.core, 900, 0, 1000, 800);
	data.button = ui_create_button(data.tool_window, 50, 0, 100, 50);
	data.canvas = ui_create_image(data.render_window, 100, 100, 800, 600);
	ui_widget_bind_onclicked(data.button, on_widget_clicked, &data);
	ui_widget_bind_onclicked(data.canvas, on_widget_clicked, &data);
	ui_run(data.core);
	return (0);
}