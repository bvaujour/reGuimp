/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_text.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:04:56 by bvaujour          #+#    #+#             */
/*   Updated: 2026/01/15 19:21:06 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

static void		ui_text_render(t_widget *text)
{


	SDL_RenderCopy(text->renderer, text->texture, NULL, &text->absolute);
}

static void	ui_text_destroy(t_widget *text)
{
	t_text_data			*data;

	data = (t_text_data *)text->data;
	free(data->text);
}

static void	ui_text_build(t_widget *text)
{
	t_text_data			*data;
	TTF_Font			*font;
	SDL_Surface			*surface;

	data = (t_text_data *)text->data;
	font = ui_open_font_match_size(text->core->font_file, data->text, text->parent->rect.w, text->parent->rect.h);
	surface = TTF_RenderText_Blended(font, data->text, data->text_color);
	if (text->texture)
		SDL_DestroyTexture(text->texture);
	text->texture = SDL_CreateTextureFromSurface(text->renderer, surface);
	text->rect.w = surface->w;
	text->rect.h = surface->h;
	text->rect.x = text->parent->rect.w / 2 - text->rect.w / 2;
	text->rect.y = text->parent->rect.h / 2 - text->rect.h / 2;
	SDL_FreeSurface(surface);
}



t_widget	*ui_create_text(t_widget *parent, int x, int y, int width, int height)
{
	t_widget			*text;
	t_text_data			*data;

	if (parent == NULL)
		return (NULL);
	text = ui_new_widget((SDL_Rect){x, y, width, height}, TEXT, UI_MAX_TEXT_CHILDS);
	if (!text)
		return (NULL);
	if (ui_add_child(parent, text) != UI_SUCCESS)
		return (free(text), NULL);
	text->data = malloc(sizeof(t_text_data));
	if (!text->data)
		return (free(text), NULL);
	data = (t_text_data *)text->data;
	*data = (t_text_data){0};
	ui_set_widget_colors(text, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
	data->text_color = (SDL_Color){255, 255, 255, 255};
	text->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	text->render = ui_text_render;
	text->destroy = ui_text_destroy;
	text->build = ui_text_build;
	data->text = ft_strdup("hello world!!");
	return (text);
}