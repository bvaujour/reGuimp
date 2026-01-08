/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_slider.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:33:33 by injah             #+#    #+#             */
/*   Updated: 2026/01/08 11:54:56 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

void	ui_slider_render(t_widget *slider)
{
	t_slider_data	*data;

	data = (t_slider_data *)slider->data;

	// SDL_RenderSetClipRect(slider->renderer, &slider->parent->absolute);
	SDL_RenderCopy(slider->renderer, slider->texture, NULL, &slider->absolute); // le slider background
	SDL_RenderFillRect(slider->renderer, &(SDL_Rect){slider->absolute.x, slider->absolute.y, slider->absolute.w * data->value, slider->absolute.h}); // la partie du slider remplie
	int				padding = 10;
	SDL_RenderCopy(slider->renderer, data->label, NULL, &(SDL_Rect){slider->absolute.x + padding, slider->absolute.y + padding, slider->rect.w - 2 * padding, slider->rect.h - 2 * padding});

	SDL_RenderCopy(slider->renderer, data->slide_texture, NULL, &(SDL_Rect){slider->absolute.x + data->slide_position.x, slider->absolute.y, slider->absolute.w / data->slide_factor, slider->rect.h}); //render le slider
}

void	ui_slider_destroy(t_widget *slider)
{
	t_slider_data	*data;
	data = (t_slider_data *)slider->data;

	if (slider->texture)
		SDL_DestroyTexture(slider->texture);
	if (data->slide_texture)
		SDL_DestroyTexture(data->slide_texture);
	if (data->label)
		SDL_DestroyTexture(data->label);
}

void	ui_slider_update(t_widget *slider)
{
	t_slider_data	*data;
	t_core			*core;

	core = slider->core;
	ui_set_cursor(core, core->mouse.hand);
	if (slider->state == CLICKED)
	{
		data = (t_slider_data *)slider->data;
		data->slide_position.x = core->mouse.position.x - slider->absolute.x;
		if (data->slide_position.x < 0)
			data->slide_position.x = 0;
		else if (data->slide_position.x >= slider->absolute.w - slider->absolute.w / data->slide_factor)
			data->slide_position.x = slider->absolute.w - slider->absolute.w / data->slide_factor;
		if (data->onvaluechange)
		{
			if (data->slide_position.x == 0)
				data->value = 0;
			else
				data->value = (float)data->slide_position.x / (slider->absolute.w - slider->absolute.w / data->slide_factor);
			data->onvaluechange(slider, data->value, data->onvaluechange_param);
		}
	}
}

t_widget	*ui_create_slider(t_widget *parent, int x, int y, int width, int height)
{
	t_widget			*slider;
	t_slider_data		*data;

	if (parent == NULL)
		return (NULL);
	slider = ui_new_widget((SDL_Rect){x, y, width, height}, SLIDER, UI_MAX_SLIDER_CHILDS);
	if (!slider)
		return (NULL);
	if (ui_add_child(parent, slider) != UI_SUCCESS)
		return (free(slider), NULL);
	slider->data = malloc(sizeof(t_slider_data));
	if (!slider->data)
		return (free(slider), NULL);
	data = (t_slider_data *)slider->data;
	*data = (t_slider_data){0};
	data->slide_factor = 20;
	data->value = 0.5f;
	data->slide_position.x = width / 2 - width / data->slide_factor;
	ui_set_widget_colors(slider, 0xFFFF0000, 0xFF00FF00, 0xFF0000FF);
	data->fill_color = (SDL_Color){100, 100, 100, 255};
	data->slide_color = (SDL_Color){255, 255, 255, 255};
	slider->render = ui_slider_render;
	slider->update = ui_slider_update;
	slider->destroy = ui_slider_destroy;
	data->slide_texture = ui_new_texture(parent->renderer, width / data->slide_factor, height, data->slide_color);
	slider->texture = ui_new_texture(parent->renderer, width, height, slider->colors[slider->state]);
	ui_slider_set_label(slider, "default label");
	return (slider);
}