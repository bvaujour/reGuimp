/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_slider.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:33:33 by injah             #+#    #+#             */
/*   Updated: 2025/12/20 06:50:15 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

void	ui_slider_render(t_widget *slider)
{
	t_slider_data	*data;

	data = (t_slider_data *)slider->data;

	SDL_RenderSetClipRect(slider->renderer, &slider->parent->absolute);
	ui_draw_background(slider->renderer, slider->background, slider->absolute, slider->colors[slider->state]);
	SDL_SetTextureColorMod(slider->background, data->fill_color.r, data->fill_color.g, data->fill_color.b);
	SDL_RenderCopy(slider->renderer, slider->background, NULL, &(SDL_Rect){slider->absolute.x, slider->absolute.y, slider->absolute.w * data->value, slider->absolute.h});
	SDL_SetTextureColorMod(data->slide_texture, data->slide_color.r, data->slide_color.g, data->slide_color.b);
	SDL_RenderCopy(slider->renderer, data->slide_texture, NULL, &(SDL_Rect){slider->absolute.x + data->slide_position.x, slider->absolute.y, slider->absolute.w / data->slide_factor, slider->rect.h});
	ui_draw_outline(slider->renderer, slider->absolute, slider->outline);
	SDL_RenderSetClipRect(slider->renderer, NULL);
}

void	ui_slider_destroy(t_widget *slider)
{
	t_slider_data	*data;
	data = (t_slider_data *)slider->data;

	if (slider->background)
		SDL_DestroyTexture(slider->background);
	if (data->slide_texture)
		SDL_DestroyTexture(data->slide_texture);
}

void	ui_slider_update(t_widget *slider)
{
	t_slider_data	*data;
	t_core			*core;
	float			value;


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
				value = 0;
			else
				value = (float)data->slide_position.x / (slider->absolute.w - slider->absolute.w / data->slide_factor);
			data->onvaluechange(slider, value, data->onvaluechange_param);
			data->value = value;
		}
	}
}

t_widget	*ui_create_slider(t_widget *parent, int x, int y, int width, int height)
{
	t_widget		*slider;
	t_slider_data	*data;
	
	slider = ui_new_widget(SLIDER, sizeof(t_slider_data));
	if (!slider)
	{
		ui_slider_destroy(slider);
		return (NULL);
	}
	data = (t_slider_data *)slider->data;
	*data = (t_slider_data){0};
	slider->rect = (SDL_Rect){x, y, width, height};
	slider->outline = 2;
	data->slide_factor = 20;
	ui_set_widget_colors(slider, 0xFF7F7F7F, 0xFF7F7F7F, 0xFF9F9F9F, 0xFF9F9F9F);
	data->fill_color = (SDL_Color){100, 100, 100, 100};
	slider->render = ui_slider_render;
	slider->update = ui_slider_update;
	slider->destroy = ui_slider_destroy;
	ui_set_child_references(parent, slider);
	if (!parent->add_child || parent->add_child(parent, slider) == UI_ERROR)
	{
		printf("ui_create_slider: FAILED ADD CHILD\n");
		ui_slider_destroy(slider);
		return (NULL);
	}
	data->slide_texture = ui_new_texture(parent->renderer, width / data->slide_factor, height);
	slider->background = ui_new_texture(parent->renderer, width, height);
	return (slider);
}