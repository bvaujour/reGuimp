/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_box.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:09:13 by injah             #+#    #+#             */
/*   Updated: 2026/01/07 02:54:32 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

static void	ui_box_event(t_widget *box, SDL_Event event)
{
	if (event.type == SDL_MOUSEMOTION && box->state == CLICKED)
			box->core->dragged_widget = box;
}

void	ui_box_render(t_widget *box)
{
	SDL_RenderCopy(box->renderer, box->texture, NULL, &box->absolute);
}

void	ui_box_update(t_widget *box)
{
	ui_set_cursor(box->core, box->core->mouse.arrow);
}

void	ui_box_destroy(t_widget *box)
{
	SDL_DestroyTexture(box->texture);
}

void	ui_box_build(t_widget *box)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (box->childs[i])
	{
		if (box->childs[i]->rect.w > box->rect.w)
			box->childs[i]->rect.w = box->rect.w;
		box->childs[i]->rect.x = 0;
		box->childs[i]->rect.y = y;
		y += box->childs[i]->rect.h;
		i++;
	}
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
	ui_set_widget_colors(box, 0x7F5F5F5F, 0x7F5F5F5F, 0x7F5F5F5F);
	box->is_dragable = true;
	box->render = ui_box_render;
	box->update = ui_box_update;
	box->destroy = ui_box_destroy;
	box->build = ui_box_build;
	box->event = ui_box_event;
	box->texture = ui_new_texture(parent->renderer, width, height, box->colors[box->state]);
	return (box);
}