/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_widget_user.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 03:24:56 by injah             #+#    #+#             */
/*   Updated: 2025/12/29 01:07:54 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

void	ui_set_widget_position(t_widget *widget, int x, int y)
{
	widget->rect.x = x;
	widget->rect.y = y;
}

void	ui_set_widget_size(t_widget *widget, int width, int height)
{
	widget->rect.w = width;
	widget->rect.h = height;
}

void	ui_set_widget_position_and_size(t_widget *widget, int x, int y, int width, int height)
{
	ui_set_widget_position(widget, x, y);
	ui_set_widget_size(widget, width, height);
}

void	ui_set_widget_colors(t_widget *widget, unsigned int normal, unsigned int hovered, unsigned int clicked)
{
	if (widget == NULL)
	{
		printf("Error: ui_set_widget_colors used on null widget\n");
		return ;
	}
	widget->colors[NORMAL] = ui_unpack_color(normal);
	widget->colors[HOVERED] = ui_unpack_color(hovered);
	widget->colors[CLICKED] = ui_unpack_color(clicked);
}

int	ui_set_widget_texture(t_widget *widget, const char *path)
{
	SDL_Surface	*surface;
	SDL_Color	color;
	surface = IMG_Load(path);
	if (!surface)
	{
		printf("ui_set_widget_texture: failed open image.\n");
		return (-1);
	}
	if (widget->texture)
		SDL_DestroyTexture(widget->texture);
	widget->texture = SDL_CreateTextureFromSurface(widget->renderer, surface);
	color = widget->colors[widget->state];
	SDL_SetTextureColorMod(widget->texture, color.r, color.g, color.b);
	SDL_SetTextureAlphaMod(widget->texture, color.a);
	SDL_FreeSurface(surface);
	return (0);
}

void	ui_set_widget_visibility(t_widget *widget, int new_visibility)
{
	widget->is_visible = new_visibility;
}

int	ui_get_widget_visibility(t_widget *widget)
{
	return (widget->is_visible);
}

void	ui_toggle_widget_visibility(t_widget *widget)
{
	widget->is_visible = !widget->is_visible;
}

void	ui_get_screen_size(int *screen_width, int *screen_height)
{
	SDL_Rect	rect;

	SDL_GetDisplayUsableBounds(0, &rect);
	if (screen_width)
		*screen_width = rect.w;
	if (screen_height)
		*screen_height = rect.h;
}