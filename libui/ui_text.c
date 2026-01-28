/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_text.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:04:56 by bvaujour          #+#    #+#             */
/*   Updated: 2026/01/19 17:35:56 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

static void		ui_text_render(t_widget *text)
{
	// SDL_RenderSetClipRect(text->renderer, &text->clip);
	SDL_RenderCopy(text->renderer, text->texture, NULL, &text->absolute);
	// SDL_RenderSetClipRect(text->renderer, NULL);
}

static void		ui_text_event(t_widget *text)
{	
	t_text_data			*data;
	int					i;
	
	data = (t_text_data *)text->data;
	if (text == text->core->focused_widget)
	{
		SDL_StartTextInput();
		if (text->core->event.type == SDL_TEXTINPUT)
		{
			if (data->text_index < UI_MAX_TEXT_SIZE)
			{
				i = 0;
				while (text->core->event.text.text[i] && data->text_index < UI_MAX_TEXT_SIZE)
					data->text[data->text_index++] = text->core->event.text.text[i++];
				data->text[data->text_index] = '\0';
				text->build(text);
				printf("%s\n", data->text);
			}
		}
		if (text->core->event.type == SDL_KEYDOWN)
		{
			if (text->core->event.key.keysym.sym == SDLK_BACKSPACE && data->text_index > 0)
			{
				data->text_index--;
				data->text[data->text_index] = '\0';
				text->build(text);
			}
			if (text->core->event.key.keysym.sym == SDLK_RETURN || text->core->event.key.keysym.sym == SDLK_RETURN2)
			{
				if (data->onvalidate)
					data->onvalidate(text, data->text, data->onvalidate_param);
			}
		}
	}
	else
		SDL_StopTextInput();
}

void	ui_bind_text_onvalidate(t_widget *text, void (*f)(t_widget *text, const char *str, void *param), void *param)
{
	t_text_data	*data;

	if (text->type != TEXT)
		return ;
	data = (t_text_data *)text->data;
	data->onvalidate = f;
	data->onvalidate_param = param;
}

static void	ui_text_destroy(t_widget *text)
{
	(void)text;
}

void	ui_text_set_text(t_widget *text, const char *str)
{
	t_text_data			*data;
	int	i;

	i = 0;
	data = (t_text_data *)text->data;
	while (str[i] && data->text_index < UI_MAX_TEXT_SIZE)
		data->text[data->text_index++] = str[i++];
	data->text[data->text_index] = '\0';
	text->build(text);
}



static void	ui_text_build(t_widget *text)
{
	t_text_data			*data;
	TTF_Font			*font;
	SDL_Surface			*surface;

	data = (t_text_data *)text->data;
	if (ft_strlen(data->text) == 0)
	{
		if (text->texture)
			SDL_DestroyTexture(text->texture);
		text->texture = ui_new_texture(text->renderer, text->absolute.w, text->absolute.h, text->colors[text->state]);
		return ;
	}
	if (data->mode == FILL)
		font = ui_open_font_match_size(text->core->font_file, data->text, text->parent->absolute.w, text->parent->absolute.h);
	else
		font = TTF_OpenFont(text->core->font_file, 25);
	if (!font)
	{
		printf("font invalid\n");
		return ;
	}
	if (data->mode == WRAP)
		surface = TTF_RenderText_Blended_Wrapped(font, data->text, data->text_color, text->parent->absolute.w);
	else
		surface = TTF_RenderText_Blended(font, data->text, data->text_color);
	if (!surface)
	{
			printf("surface invalid\n");
			return (TTF_CloseFont(font));
	}
	if (text->texture)
		SDL_DestroyTexture(text->texture);
	text->texture = SDL_CreateTextureFromSurface(text->renderer, surface);
	if (!text->texture)
	{
		printf("texture invalid\n");
		SDL_FreeSurface(surface);
		return (TTF_CloseFont(font));
	}
	text->absolute.w = surface->w;
	text->absolute.h = surface->h;
	if (data->mode == CENTERED || data->mode == FILL)
	{
		text->relative.x = text->parent->absolute.w / 2 - text->absolute.w / 2;
		text->relative.y = text->parent->absolute.h / 2 - text->absolute.h / 2;
	}
	else if (data->mode == SINGLE_LINE)
	{
		if (text->absolute.w > text->parent->absolute.w)
			text->relative.x = text->parent->absolute.w - text->absolute.w;
		else
			text->relative.x = 0;
	}
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
	printf("build success\n");
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
	text->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	text->render = ui_text_render;
	text->destroy = ui_text_destroy;
	text->build = ui_text_build;
	text->event = ui_text_event;
	// text->update = ui_text_update;
	
	data->mode = WRAP;
	return (text);
}