/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_box.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:09:13 by injah             #+#    #+#             */
/*   Updated: 2025/12/23 15:29:17 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"


void		ui_box_render(t_widget *box)
{
	SDL_RenderSetClipRect(box->renderer, &box->parent->absolute);
	ui_draw_background(box->renderer, box->background, box->absolute, box->colors[box->state]);
	ui_draw_outline(box->renderer, box->absolute, box->outline);
	SDL_RenderSetClipRect(box->renderer, NULL);
}

void		ui_box_update(t_widget *box)
{
	(void)box;
}

void		ui_box_destroy(t_widget *box)
{
	SDL_DestroyTexture(box->background);
}

static int	ui_box_add_child(t_widget *box, t_widget *child)
{
	(void)box;
	(void)child;
	if (box->nb_child == UI_MAX_BOX_CHILDS)
	{
		printf("ui_window_add_child: Window has maximum child\n");
		return (UI_ERROR);
	}
	box->childs[box->nb_child] = child;
	box->nb_child++;
	return (UI_SUCCESS);
}
t_widget	*ui_create_box(t_widget *parent, int x, int y, int width, int height)
{
	t_widget	*box;

	if (parent == NULL)
		return (NULL);
	box = ui_new_widget((SDL_Rect){x, y, width, height}, BOX, UI_MAX_BOX_CHILDS);
	if (!box)
		return (NULL);
	if (ui_add_child(parent, box) != UI_SUCCESS)
		return (free(box), NULL);
	ui_set_widget_colors(box, 0x7F5F5F5F, 0x7F5F5F5F, 0x7F5F5F5F, 0x7F5F5F5F);
	box->is_dragable = true;
	box->render = ui_box_render;
	box->update = ui_box_update;
	box->destroy = ui_box_destroy;
	box->add_child = ui_box_add_child;
	box->background = ui_new_texture(parent->renderer, width, height);
	return (box);
}