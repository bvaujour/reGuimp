/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 17:57:41 by injah             #+#    #+#             */
/*   Updated: 2025/12/17 06:34:48 by injah            ###   ########.fr       */
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

SDL_Point	ui_get_absolute_position(t_widget *widget)
{
	t_widget 	*reference;
	SDL_Point	position;

	position.x = widget->rect.x;
	position.y = widget->rect.y;
	reference = widget->parent;
	while (reference != NULL)
	{
		position.x += reference->rect.x;
		position.y += reference->rect.y;
		reference = reference->parent;
	}
	return (position);
}

bool	ui_point_in_widget(t_widget *widget, SDL_Point point)
{
	SDL_Point	absolute_pos;
	SDL_Rect	absolute_rect;

	absolute_pos = ui_get_absolute_position(widget);
	absolute_rect.x = absolute_pos.x;
	absolute_rect.y = absolute_pos.y;
	absolute_rect.w = widget->rect.w;
	absolute_rect.h = widget->rect.h;
	if (SDL_PointInRect(&point, &absolute_rect))
		return (true);
	return (false);
}

SDL_Rect	ui_draw_outline(SDL_Surface *surface, SDL_Color color, int size)
{
	SDL_Rect	rect;

	rect.x = size;
	rect.y = size;
	rect.w = surface->w - 2 * size;
	rect.h = surface->h - 2 * size;
	SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a));
	SDL_FillRect(surface, &rect, SDL_MapRGBA(surface->format, 0, 0, 0, 0));
	return (rect);
}