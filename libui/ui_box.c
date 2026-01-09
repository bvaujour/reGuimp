/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_box.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:09:13 by injah             #+#    #+#             */
/*   Updated: 2026/01/08 17:31:38 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

void	ui_box_render(t_widget *box)
{
	SDL_RenderCopy(box->renderer, box->texture, NULL, &box->absolute);
}

void	ui_box_update(t_widget *box)
{
	ui_set_cursor(box->core, box->core->mouse.arrow);
	if (box->state == CLICKED)
		ui_widget_call_onclicked(box);
}

void	ui_box_destroy(t_widget *box)
{
	SDL_DestroyTexture(box->texture);
}

void	ui_place_childs_vertical(t_widget *box, int space, bool wrap)
{
	int	i;
	int	max_w;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = space;
	max_w = 0;
	while (box->childs[i])
	{
		if (wrap && y + box->childs[i]->rect.h > box->rect.h)
		{
			x += max_w + space;
			max_w = 0;
			y = space;
		}
		box->childs[i]->rect.x = space + x;
		box->childs[i]->rect.y = y;
		y += box->childs[i]->rect.h + space;
		if (box->childs[i]->rect.w > max_w)
			max_w = box->childs[i]->rect.w;
		i++;
	}
}

void	ui_place_childs_horizontal(t_widget *box, int space, bool wrap)
{
	int	i;
	int	max_h;
	int	x;
	int	y;

	i = 0;
	y = 0;
	x = space;
	max_h = 0;
	while (box->childs[i])
	{
		if (wrap && x + box->childs[i]->rect.w > box->rect.w)
		{
			y += max_h + space;
			max_h = 0;
			x = space;
		}
		box->childs[i]->rect.y = space + y;
		box->childs[i]->rect.x = x;
		x += box->childs[i]->rect.w + space;
		if (box->childs[i]->rect.h > max_h)
			max_h = box->childs[i]->rect.h;
		i++;
	}
}
void	ui_box_build(t_widget *box)
{
	t_box_data	*data;

	data = (t_box_data *)box->data;
	if (data->flow_direction == VERTICAL)
		ui_place_childs_vertical(box, data->space_between_childs, true);
	else
		ui_place_childs_horizontal(box, data->space_between_childs, true);
}

t_widget	*ui_create_box(t_widget *parent, int x, int y, int width, int height)
{
	t_widget	*box;
	t_box_data	*data;

	if (parent == NULL)
		return (NULL);
	box = ui_new_widget((SDL_Rect){x, y, width, height}, BOX, UI_MAX_BOX_CHILDS);
	if (!box)
		return (NULL);
	if (ui_add_child(parent, box) != UI_SUCCESS)
		return (free(box), NULL);
	box->data = malloc(sizeof(t_box_data));
	if (!box->data)
		return (free(box), NULL);
	data = (t_box_data *)box->data;
	ui_set_widget_colors(box, 0x7F5F5F5F, 0x7F5F5F5F, 0x7F5F5F5F);
	box->is_dragable = true;
	box->render = ui_box_render;
	box->update = ui_box_update;
	box->destroy = ui_box_destroy;
	box->build = ui_box_build;
	box->texture = ui_new_texture(parent->renderer, width, height, box->colors[box->state]);
	data->space_between_childs = 10;
	return (box);
}