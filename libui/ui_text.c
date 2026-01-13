/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_text.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:04:56 by bvaujour          #+#    #+#             */
/*   Updated: 2026/01/13 19:21:24 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

static void		ui_text_render(t_widget *text)
{
	t_text_data			*data;
	data = (t_text_data *)text->data;

	SDL_RenderCopy(text->renderer, text->texture, NULL, &text->absolute);
	// SDL_RenderCopy(text->renderer, data->text, NULL, &(SDL_Rect){text->absolute.x, text->absolute.y, data->width, data->height});
}

static void	ui_text_destroy(t_widget *text)
{
	(void)text;
}

void	ui_text_fill_parent(t_widget *text)
{
	TTF_Font			 *font;
	SDL_Surface			*surface;
	int	i;
	int	w, h;
	i = 0;
	while (1)
	{
		font = TTF_OpenFont("libui/assets/fonts/Roboto/Roboto-Black.ttf", i);
		TTF_SizeUTF8(font, "F", &w, &h);
		printf("size w = %d\nsize h = %d\n", w, h);
		TTF_CloseFont(font);
		if (w > text->parent->rect.w || h > text->parent->rect.h)
			break ;
		i++;
	}
	if (i == 0)
		i = 1;
	font = TTF_OpenFont("libui/assets/fonts/Roboto/Roboto-Black.ttf", i);
	surface = TTF_RenderText_Blended(font, "File", (SDL_Color){255, 255, 255, 255});
	if (text->texture)
		SDL_DestroyTexture(text->texture);
	text->texture = SDL_CreateTextureFromSurface(text->renderer, surface);
	text->rect.w = surface->w;
	text->rect.h = surface->h;
	text->rect.x = text->parent->rect.w / 2 - text->rect.w / 2;
	text->rect.y = text->parent->rect.h / 2 - text->rect.h / 2;
	TTF_CloseFont(font);
	SDL_FreeSurface(surface);
	
}

static void	ui_text_build(t_widget *text)
{
	// SDL_Surface			*surface;
	// t_text_data			*data;

	// TTF_Font *font = TTF_OpenFont("libui/assets/fonts/Roboto/Roboto-Black.ttf", 30);
	// surface = TTF_RenderText_Blended_Wrapped(font, "File looooooooooooooooooooooooool", (SDL_Color){255, 255, 255, 255}, text->rect.w);
	// data = (t_text_data *)text->data;
	// if (text->texture)
	// 	SDL_DestroyTexture(text->texture);
	// text->texture = SDL_CreateTextureFromSurface(text->renderer, surface);
	// text->rect.w = surface->w;
	// text->rect.h = surface->h;
	// text->rect.x = text->parent->rect.w / 2 - text->rect.w / 2;
	// text->rect.y = text->parent->rect.h / 2 - text->rect.h / 2;
	// TTF_CloseFont(font);
	// SDL_FreeSurface(surface);
	ui_text_fill_parent(text);
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
	text->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	text->render = ui_text_render;
	text->destroy = ui_text_destroy;
	text->build = ui_text_build;
	text->texture = ui_new_texture(parent->renderer, width, height, text->colors[text->state]);
	return (text);
}