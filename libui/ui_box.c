/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_box.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:09:13 by injah             #+#    #+#             */
/*   Updated: 2026/01/21 12:23:09 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

void	ui_box_render(t_widget *box)
{
	SDL_RenderCopy(box->renderer, box->texture, NULL, &box->absolute);
	if (box == box->core->focused_widget)
		ui_widget_outline(box, (SDL_Color){127, 127, 127, 255});
	else
		ui_widget_outline(box, (SDL_Color){0, 0, 0, 255});
}

void	ui_build_vertical_wrap_box(t_widget *box, int space)
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
		if (measures.y + box->childs[i]->absolute.h + space > box->absolute.h - 10)
		{
			measures.x = measures.w;
			measures.y = space;
		}
		box->childs[i]->relative.x = measures.x;
		box->childs[i]->relative.y = measures.y;
		measures.y += box->childs[i]->absolute.h + space;
		if (measures.y > box->absolute.h)
			box->absolute.h = measures.y;
		if (measures.y > measures.h)
			measures.h = measures.y;
		if (measures.x + box->childs[i]->absolute.w + space > measures.w)
			measures.w = measures.x + box->childs[i]->absolute.w + space;
		i++;
	}
}

void	ui_build_horizontal_wrap_box(t_widget *box, int space)
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
		if (measures.x + box->childs[i]->absolute.w + space > box->absolute.w - 10)
		{
			measures.y = measures.h;
			measures.x = space;
		}
		box->childs[i]->relative.x = measures.x;
		box->childs[i]->relative.y = measures.y;
		measures.x += box->childs[i]->absolute.w + space;
		if (measures.x > box->absolute.w)
			box->absolute.w = measures.x;
		if (measures.x > measures.w)
			measures.w = measures.x;
		if (measures.y + box->childs[i]->absolute.h + space > measures.h)
			measures.h = measures.y + box->childs[i]->absolute.h + space;
		i++;
	}
}

void	ui_build_vertical_box(t_widget *box)
{
	SDL_Rect	child_rect;
	int			i;

	child_rect.w = box->absolute.w - 10;
	child_rect.h = (box->absolute.h - 10) / box->nb_child;
	i = 0;
	while (box->childs[i])
	{
		box->childs[i]->absolute.w = child_rect.w;
		box->childs[i]->absolute.h = child_rect.h;
		box->childs[i]->relative.x = 0;
		box->childs[i]->relative.y = child_rect.h * i;
		i++;
	}
}

void	ui_build_horizontal_box(t_widget *box)
{
	SDL_Rect	child_rect;
	int			i;

	child_rect.w = (box->absolute.w - 10) / box->nb_child;
	child_rect.h = box->absolute.h - 10;
	i = 0;
	while (box->childs[i])
	{
		box->childs[i]->absolute.w = child_rect.w;
		box->childs[i]->absolute.h = child_rect.h;
		box->childs[i]->relative.x = child_rect.w * i;
		box->childs[i]->relative.y = 0;
		i++;
	}
}

void	ui_build_stacking_box(t_widget *box)
{
	int			i;

	i = 0;
	while (box->childs[i])
	{
		box->childs[i]->relative.x = 0;
		box->childs[i]->relative.y = 0;
		box->childs[i]->absolute.w = box->absolute.w - 10;
		box->childs[i]->absolute.h = box->absolute.h - 10;
		i++;
	}
}
void	ui_box_build(t_widget *box)
{
	t_box_data	*data;

	data = (t_box_data *)box->data;
	if (data->mode == STACKING_CHILDS)
		ui_build_stacking_box(box);
	else if (data->flow_direction == VERTICAL && data->mode == EVEN_CHILDS)
		ui_build_vertical_box(box);
	else if (data->flow_direction == HORIZONTAL && data->mode == EVEN_CHILDS)
		ui_build_horizontal_box(box);
	if (data->flow_direction == VERTICAL && data->mode == WRAP_CHILDS)
		ui_build_vertical_wrap_box(box, 5);	
	else if (data->flow_direction == HORIZONTAL && data->mode == WRAP_CHILDS)
		ui_build_horizontal_wrap_box(box, 5);
}

void	ui_set_box_behavior(t_widget *box, e_direction flow_direction, e_box_mode mode)
{
	t_box_data	*data;

	if (box->type != BOX)
		return ;
	data = (t_box_data *)box->data;
	data->flow_direction = flow_direction;
	data->mode = mode;
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
	box->render = ui_box_render;
	box->build = ui_box_build;
	box->texture = ui_new_texture(parent->renderer, width, height, box->colors[box->state]);
	data->flow_direction = DEFAULT;
	return (box);
}