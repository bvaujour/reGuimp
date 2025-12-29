/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 17:57:41 by injah             #+#    #+#             */
/*   Updated: 2025/12/29 00:53:11 by injah            ###   ########.fr       */
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
	SDL_SetTextureColorMod(texture, color_mod.r, color_mod.g, color_mod.b);
	SDL_SetTextureAlphaMod(texture, color_mod.a);
	SDL_FreeSurface(surface);
	return (texture);
}