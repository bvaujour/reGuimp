/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_slider.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:33:33 by injah             #+#    #+#             */
/*   Updated: 2025/12/29 01:04:48 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

void	ui_slider_render(t_widget *widget)
{
	t_slider_data	*data;

	data = (t_slider_data *)widget->data;

	SDL_RenderSetClipRect(widget->renderer, &widget->parent->absolute);
	SDL_RenderCopy(widget->renderer, widget->texture, NULL, &widget->absolute);
	ui_draw_outline(widget->renderer, widget->absolute, widget->outline, widget->outline_color);
	SDL_RenderFillRect(widget->renderer, &(SDL_Rect){widget->absolute.x, widget->absolute.y, widget->absolute.w * data->value, widget->absolute.h});
	SDL_RenderCopy(widget->renderer, data->slide_texture, NULL, &(SDL_Rect){widget->absolute.x + data->slide_position.x, widget->absolute.y, widget->absolute.w / data->slide_factor, widget->rect.h});
	SDL_RenderSetClipRect(widget->renderer, NULL);
}

void	ui_slider_destroy(t_widget *widget)
{
	t_slider_data	*data;
	data = (t_slider_data *)widget->data;

	if (widget->texture)
		SDL_DestroyTexture(widget->texture);
	if (data->slide_texture)
		SDL_DestroyTexture(data->slide_texture);
}

void	ui_slider_update(t_widget *widget)
{
	t_slider_data	*data;
	t_core			*core;
	float			value;


	core = widget->core;
	ui_set_cursor(core, core->mouse.hand);
	if (widget->state == CLICKED)
	{
		data = (t_slider_data *)widget->data;
		data->slide_position.x = core->mouse.position.x - widget->absolute.x;
		if (data->slide_position.x < 0)
			data->slide_position.x = 0;
		else if (data->slide_position.x >= widget->absolute.w - widget->absolute.w / data->slide_factor)
			data->slide_position.x = widget->absolute.w - widget->absolute.w / data->slide_factor;
		if (data->onvaluechange)
		{
			if (data->slide_position.x == 0)
				value = 0;
			else
				value = (float)data->slide_position.x / (widget->absolute.w - widget->absolute.w / data->slide_factor);
			data->onvaluechange(widget, value, data->onvaluechange_param);
			data->value = value;
		}
	}
}

t_widget	*ui_create_slider(t_widget *parent, int x, int y, int width, int height)
{
	t_widget			*widget;
	t_slider_data		*data;

	if (parent == NULL)
		return (NULL);
	widget = ui_new_widget((SDL_Rect){x, y, width, height}, SLIDER, UI_MAX_SLIDER_CHILDS);
	if (!widget)
		return (NULL);
	if (ui_add_child(parent, widget) != UI_SUCCESS)
		return (free(widget), NULL);
	widget->data = malloc(sizeof(t_slider_data));
	if (!widget->data)
		return (free(widget), NULL);
	data = (t_slider_data *)widget->data;
	*data = (t_slider_data){0};
	data->slide_factor = 20;
	ui_set_widget_colors(widget, 0xFFFF0000, 0xFF00FF00, 0xFF0000FF);
	data->fill_color = (SDL_Color){100, 100, 100, 100};
	data->slide_color = (SDL_Color){200, 200, 200, 100};
	widget->render = ui_slider_render;
	widget->update = ui_slider_update;
	widget->destroy = ui_slider_destroy;
	data->slide_texture = ui_new_texture(parent->renderer, width / data->slide_factor, height, data->slide_color);
	widget->texture = ui_new_texture(parent->renderer, width, height, widget->colors[widget->state]);
	return (widget);
}