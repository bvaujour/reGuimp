/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_slider.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:33:33 by injah             #+#    #+#             */
/*   Updated: 2026/01/18 15:51:37 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

void	ui_bind_slider_onvaluechanged(t_widget *slider, void (*f)(struct s_widget *, float, void *), void *param)
{
	t_slider_data	*data;

	if (slider->type != SLIDER)
		return ;
	data = (t_slider_data *)slider->data;
	data->onvaluechange = f;
	data->onvaluechange_param = param;
	f(slider, data->value, param);
}

void	ui_slider_render(t_widget *slider)
{
	t_slider_data	*data;
	SDL_Rect		render_rect;

	data = (t_slider_data *)slider->data;
	render_rect = ui_get_render_rect(slider);
	SDL_RenderSetClipRect(slider->renderer, &slider->parent->absolute);

	SDL_RenderCopy(slider->renderer, slider->texture, NULL, &render_rect); // le slider background
	SDL_SetRenderDrawColor(slider->renderer, data->fill_color.r, data->fill_color.g, data->fill_color.b, data->fill_color.a);
	SDL_RenderFillRect(slider->renderer, &(SDL_Rect){render_rect.x, render_rect.y, render_rect.w * data->value, render_rect.h}); // la partie du slider remplie
	if (slider == slider->core->focused_widget)
		ui_widget_outline(slider, (SDL_Color){127, 127, 127, 255});
	else
		ui_widget_outline(slider, (SDL_Color){0, 0, 0, 255});
	SDL_RenderSetClipRect(slider->renderer, NULL);
}

void	ui_slider_destroy(t_widget *slider)
{
	(void)slider;
}

void	ui_slider_update(t_widget *slider)
{
	t_slider_data	*data;
	t_core			*core;
	SDL_Point		click_relative;
	core = slider->core;
	if (slider->state == CLICKED)
	{
		data = (t_slider_data *)slider->data;
		click_relative.x = core->mouse.position.x - slider->absolute.x;
		data->value = (float)click_relative.x / (slider->absolute.w - 1);
		if (data->onvaluechange)
			data->onvaluechange(slider, data->value, data->onvaluechange_param);
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
	data->value = 0.5f;
	ui_set_widget_colors(slider, 0xFF000000, 0xFF000000, 0xFF000000);
	data->fill_color = (SDL_Color){100, 100, 100, 255};
	slider->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	slider->render = ui_slider_render;
	slider->update = ui_slider_update;
	slider->destroy = ui_slider_destroy;
	slider->texture = ui_new_texture(parent->renderer, width, height, slider->colors[slider->state]);
	return (slider);
}