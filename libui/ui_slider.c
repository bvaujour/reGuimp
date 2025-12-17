/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_slider.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:33:33 by injah             #+#    #+#             */
/*   Updated: 2025/12/17 06:36:19 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

void	ui_slider_render(t_widget *slider)
{
	SDL_Color		color;
	t_slider_data	*data;
	SDL_Rect		after_outilne;

	data = (t_slider_data *)slider->data;
	color = slider->colors[slider->state];
	after_outilne = ui_draw_outline(slider->surface, slider->colors[UI_OUTLINE_COLOR], 3);
	SDL_FillRect(slider->surface, &after_outilne, SDL_MapRGBA(slider->surface->format, color.r, color.g, color.b, color.a));
	SDL_FillRect(slider->surface, &data->slide_cursor_rect, SDL_MapRGBA(slider->surface->format, 100, 100, 100, 255));
	SDL_BlitSurface(slider->surface, NULL, slider->parent->surface, &slider->rect);
}

void	ui_slider_destroy(t_widget *slider)
{
	(void)slider;

	SDL_FreeSurface(slider->surface);
}

void	ui_slider_build(t_widget *slider)
{
	SDL_Color	color;

	color = slider->colors[slider->state];
	if (slider->surface)
		SDL_FreeSurface(slider->surface);
	slider->surface = SDL_CreateRGBSurfaceWithFormat(0, slider->rect.w, slider->rect.h, 32, SDL_PIXELFORMAT_ARGB8888);
	SDL_FillRect(slider->surface, NULL, SDL_MapRGBA(slider->surface->format, color.r, color.g, color.b, color.a));
}

void	ui_slider_update(t_widget *slider)
{
	t_slider_data	*data;
	t_core			*core;
	float			value;

	ui_widget_manage_state_and_click(slider);
	if (slider->state == UI_CLICKED_STATE)
	{
		core = slider->core;
		
		data = (t_slider_data *)slider->data;
		data->slide_cursor_rect.x = core->mouse.position.x - slider->rect.x;
		printf("slider cursor pos: %d\n", data->slide_cursor_rect.x);
		if (data->slide_cursor_rect.x < 0)
			data->slide_cursor_rect.x = 0;
		else if (data->slide_cursor_rect.x >= slider->surface->w - data->slide_cursor_rect.w)
			data->slide_cursor_rect.x = slider->surface->w - data->slide_cursor_rect.w;
		if (data->onvaluechange)
		{
			if (data->slide_cursor_rect.x == 0)
				value = 0;
			else
				value = (float)data->slide_cursor_rect.x / (slider->surface->w - data->slide_cursor_rect.w);
			data->onvaluechange(slider, value, data->onvaluechange_param);
		}
	}
}

void	ui_slider_manage_cursor(t_widget *slider)
{
	ui_set_cursor(slider->core, slider->core->mouse.hand);
}

t_widget	*ui_create_slider(t_core *core, int x, int y, int width, int height)
{
	t_widget		*slider;
	t_slider_data	*data;

	slider = ui_init_widget(core, x, y, width, height);
	data = malloc(sizeof(t_slider_data));
	*data = (t_slider_data){0};
	slider->data = data;
	data->slide_cursor_rect = (SDL_Rect){0, 0, 10, 50};
	slider->outline = 2;
	slider->colors[UI_OUTLINE_COLOR] = (SDL_Color){0, 0, 0, 100};
	slider->colors[UI_NORMAL_COLOR] = (SDL_Color){255, 255, 255, 255};
	slider->colors[UI_HOVERED_COLOR] = (SDL_Color){100, 100, 100, 255};
	slider->colors[UI_CLICKED_COLOR] = (SDL_Color){150, 150, 150, 255};
	slider->type = SLIDER;
	slider->render = ui_slider_render;
	slider->update = ui_slider_update;
	slider->destroy = ui_slider_destroy;
	slider->build = ui_slider_build;
	slider->manage_cursor = ui_slider_manage_cursor;
	ui_slider_build(slider);
	return (slider);
}