/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_box.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:09:13 by injah             #+#    #+#             */
/*   Updated: 2025/12/29 01:04:06 by injah            ###   ########.fr       */
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

static int	ui_box_add_child(t_widget *widget, t_widget *child)
{
	(void)widget;
	(void)child;
	if (widget->nb_child == UI_MAX_BOX_CHILDS)
	{
		printf("ui_window_add_child: Window has maximum child\n");
		return (UI_ERROR);
	}
	widget->childs[widget->nb_child] = child;
	widget->nb_child++;
	return (UI_SUCCESS);
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
	widget->add_child = ui_box_add_child;
	widget->texture = ui_new_texture(parent->renderer, width, height, widget->colors[widget->state]);
	return (widget);
}