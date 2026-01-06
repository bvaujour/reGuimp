/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_box.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:09:13 by injah             #+#    #+#             */
/*   Updated: 2026/01/06 16:16:04 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"


void		ui_box_render(t_widget *widget)
{
	SDL_RenderSetClipRect(widget->renderer, &widget->parent->absolute);
	SDL_RenderCopy(widget->renderer, widget->texture, NULL, &widget->absolute);
	ui_draw_outline(widget->renderer, widget->absolute, widget->outline, widget->outline_color);
	SDL_RenderSetClipRect(widget->renderer, NULL);
}

void		ui_box_update(t_widget *widget)
{
	ui_set_cursor(widget->core, widget->core->mouse.arrow);
}

void		ui_box_destroy(t_widget *widget)
{
	SDL_DestroyTexture(widget->texture);
}

t_widget	*ui_create_box(t_widget *parent, int x, int y, int width, int height)
{
	t_widget	*widget;

	if (parent == NULL)
		return (NULL);
	widget = ui_new_widget((SDL_Rect){x, y, width, height}, BOX, UI_MAX_BOX_CHILDS);
	if (!widget)
		return (NULL);
	if (ui_add_child(parent, widget) != UI_SUCCESS)
		return (free(widget), NULL);
	ui_set_widget_colors(widget, 0x7F5F5F5F, 0x7F5F5F5F, 0x7F5F5F5F);
	widget->render = ui_box_render;
	widget->update = ui_box_update;
	widget->destroy = ui_box_destroy;
	widget->texture = ui_new_texture(parent->renderer, width, height, widget->colors[widget->state]);
	return (widget);
}