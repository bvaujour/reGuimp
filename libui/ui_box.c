/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_box.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:09:13 by injah             #+#    #+#             */
/*   Updated: 2026/01/12 18:31:25 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

void	ui_box_render(t_widget *box)
{
	SDL_RenderCopy(box->renderer, box->texture, NULL, &box->absolute);
}

void	ui_place_childs_vertical(t_widget *box, int space, bool wrap, bool size_to_content)
{
	int			i;
	SDL_Rect	measures;

	i = 0;
	measures.x = space;
	measures.y = space;
	measures.w = 0;
	measures.h = 0;
	while (box->childs[i])
	{
		if (wrap && measures.y + box->childs[i]->rect.h + space > box->rect.h)
		{
			measures.x = measures.w;
			measures.y = space;
		}
		box->childs[i]->rect.x = measures.x;
		box->childs[i]->rect.y = measures.y;
		measures.y += box->childs[i]->rect.h + space;
		if (size_to_content && measures.y > box->rect.h)
			box->rect.h = measures.y;
		if (measures.y > measures.h)
			measures.h = measures.y;
		if (measures.x + box->childs[i]->rect.w + space > measures.w)
			measures.w = measures.x + box->childs[i]->rect.w + space;
		i++;
	}
	if (size_to_content)
	{
		box->rect.w = measures.w;
		box->rect.h = measures.h;
	}
}

void	ui_place_childs_horizontal(t_widget *box, int space, bool wrap, bool size_to_content)
{
	int			i;
	SDL_Rect	measures;

	i = 0;
	measures.x = space;
	measures.y = space;
	measures.w = 0;
	measures.h = 0;
	while (box->childs[i])
	{
		if (wrap && measures.x + box->childs[i]->rect.w + space > box->rect.w)
		{
			measures.y = measures.h;
			measures.x = space;
		}
		box->childs[i]->rect.x = measures.x;
		box->childs[i]->rect.y = measures.y;
		measures.x += box->childs[i]->rect.w + space;
		if (size_to_content && measures.x > box->rect.w)
			box->rect.w = measures.x;
		if (measures.x > measures.w)
			measures.w = measures.x;
		if (measures.y + box->childs[i]->rect.h + space > measures.h)
			measures.h = measures.y + box->childs[i]->rect.h + space;
		i++;
	}
	if (size_to_content)
	{
		box->rect.w = measures.w;
		box->rect.h = measures.h;
	}
}
void	ui_box_build(t_widget *box)
{
	t_box_data	*data;

	data = (t_box_data *)box->data;
	if (data->flow_direction == VERTICAL)
		ui_place_childs_vertical(box, data->space_between_childs, data->wrap, data->size_to_content);
	else if (data->flow_direction == HORIZONTAL)
		ui_place_childs_horizontal(box, data->space_between_childs, data->wrap, data->size_to_content);
}

void	ui_set_box_behavior(t_widget *box, enum direction flow_direction, int space_between_childs, bool wrap_childs, bool size_to_content)
{
	t_box_data	*data;

	if (box->type != BOX)
		return ;
	data = (t_box_data *)box->data;
	data->flow_direction = flow_direction;
	data->size_to_content = size_to_content;
	data->space_between_childs = space_between_childs;
	data->wrap = wrap_childs;
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
	*data = (t_box_data){0};
	ui_set_widget_colors(box, 0x7F5F5F5F, 0x7F5F5F5F, 0x7F5F5F5F);
	box->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	box->is_dragable = true;
	box->render = ui_box_render;
	box->build = ui_box_build;
	box->texture = ui_new_texture(parent->renderer, width, height, box->colors[box->state]);
	data->flow_direction = DEFAULT;
	return (box);
}