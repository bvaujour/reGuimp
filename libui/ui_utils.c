/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 17:57:41 by injah             #+#    #+#             */
/*   Updated: 2026/01/18 14:57:23 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

SDL_Color	ui_unpack_color(unsigned int color)
{
	SDL_Color	argb_color;

	argb_color.a = (color >> 24) & 0xFF;
	argb_color.r = (color >> 16) & 0xFF;
	argb_color.g = (color >> 8) & 0xFF;
	argb_color.b = color & 0xFF;
	return (argb_color);
}

SDL_Texture	*ui_new_texture(SDL_Renderer *renderer, int width, int height, SDL_Color color_mod)
{
	SDL_Texture		*texture;
	SDL_Surface		*surface;

	surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_ARGB8888);
	SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 255, 255, 255, 255));
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureColorMod(texture, color_mod.r, color_mod.g, color_mod.b);
	SDL_SetTextureAlphaMod(texture, color_mod.a);
	SDL_FreeSurface(surface);
	return (texture);
}

TTF_Font	*ui_open_font_match_size(const char *font_path, const char *text, int width, int height)
{
	TTF_Font	*font;
	int			i;
	int			current_width;
	int			current_height;

	i = 0;
	while (1)
	{
		font = TTF_OpenFont(font_path, i);
		TTF_SizeUTF8(font, text, &current_width, &current_height);
		TTF_CloseFont(font);
		if (current_width > width || current_height > height)
			break ;
		i++;
	}
	if (i == 0)
		i = 1;
	font = TTF_OpenFont(font_path, i - 1);
	return (font);
}

TTF_Font	*ui_open_font_match_height(const char *font_path, const char *text, int height)
{
	TTF_Font	*font;
	int			i;
	int			current_width;
	int			current_height;

	i = 0;
	while (1)
	{
		font = TTF_OpenFont(font_path, i);
		TTF_SizeUTF8(font, text, &current_width, &current_height);
		TTF_CloseFont(font);
		if (current_height > height)
			break ;
		i++;
	}
	if (i == 0)
		i = 1;
	font = TTF_OpenFont(font_path, i - 1);
	return (font);
}
