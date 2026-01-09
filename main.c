/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:53:38 by bvaujour          #+#    #+#             */
/*   Updated: 2026/01/08 18:00:51 by injah            ###   ########.fr       */
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
	printf("widget clicked\n");
	if (widget == data->canvas)
	{
		img = ui_image_get_img(data->canvas);
		if (data->active_tool == DRAW_RECT && button == 1)
			draw_rect_on_image(img, x - 50, y - 50, 100, 100, pack_color(data->color));
		if (data->active_tool == BUCKET && button == 1)
			bucket_image(img, x, y, pack_color(data->color));
	}
	else if (widget == data->tool_buttons[PENCIL])
		data->active_tool = PENCIL;
	else if (widget == data->tool_buttons[DRAW_RECT])
		data->active_tool = DRAW_RECT;
	else if (widget == data->tool_buttons[DRAW_CIRCLE])
		data->active_tool = DRAW_CIRCLE;
	else if (widget == data->tool_buttons[DRAW_BRUSH])
		data->active_tool = DRAW_BRUSH;
	else if (widget == data->tool_buttons[ERASER])
		data->active_tool = ERASER;
	else if (widget == data->tool_buttons[BUCKET])
		data->active_tool = BUCKET;
}


int	main()
{
	t_data		data;

	data = (t_data){0};
	data.core = ui_init();
	data.color = (t_rgba){255, 0, 0, 255};
	ui_bind_onkeypress(data.core, on_key_pressed, &data);
	data.tool_window = ui_create_window(data.core, 0, 0, 800, 600);
	data.tool_box = ui_create_box(data.tool_window, 20, 100, 600, 200);
	data.tool_buttons[PENCIL] = ui_create_button(data.tool_box, 0, 0, 30, 30);
	data.tool_buttons[DRAW_RECT] = ui_create_button(data.tool_box, 0, 0, 30, 30);
	data.tool_buttons[DRAW_CIRCLE] = ui_create_button(data.tool_box, 0, 0, 30, 30);
	data.tool_buttons[DRAW_BRUSH] = ui_create_button(data.tool_box, 0, 0, 30, 30);
	data.tool_buttons[ERASER] = ui_create_button(data.tool_box, 0, 0, 30, 30);
	data.tool_buttons[BUCKET] = ui_create_button(data.tool_box, 0, 0, 30, 30);
	ui_set_widget_texture(data.tool_buttons[PENCIL], "assets/icons/pencil0.png");
	ui_set_widget_texture(data.tool_buttons[DRAW_RECT], "assets/icons/rectangle0.png");
	ui_set_widget_texture(data.tool_buttons[DRAW_CIRCLE], "assets/icons/circle0.png");
	ui_set_widget_texture(data.tool_buttons[DRAW_BRUSH], "assets/icons/brush0.png");
	ui_set_widget_texture(data.tool_buttons[BUCKET], "assets/icons/bucket0.png");
	ui_set_widget_texture(data.tool_buttons[ERASER], "assets/icons/eraser0.png");

	ui_widget_bind_onclicked(data.tool_buttons[PENCIL], on_widget_clicked, &data);
	ui_widget_bind_onclicked(data.tool_buttons[DRAW_RECT], on_widget_clicked, &data);
	ui_widget_bind_onclicked(data.tool_buttons[DRAW_CIRCLE], on_widget_clicked, &data);
	ui_widget_bind_onclicked(data.tool_buttons[DRAW_BRUSH], on_widget_clicked, &data);
	ui_widget_bind_onclicked(data.tool_buttons[ERASER], on_widget_clicked, &data);
	ui_widget_bind_onclicked(data.tool_buttons[BUCKET], on_widget_clicked, &data);

	data.render_window = ui_create_window(data.core, 900, 0, 1000, 800);
	data.canvas = ui_create_image(data.render_window, 100, 100, 800, 600);
	draw_rect_on_image(ui_image_get_img(data.canvas), 0, 10, 100, 100, 0xFF553322);

	ui_widget_bind_onclicked(data.canvas, on_widget_clicked, &data);
	ui_run(data.core);
	return (0);
}