/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_size_box.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:09:13 by injah             #+#    #+#             */
/*   Updated: 2026/01/20 09:21:37 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

void	ui_size_box_render(t_widget *size_box)
{
	SDL_SetRenderDrawColor(size_box->renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(size_box->renderer, &(SDL_Rect){size_box->absolute.x + size_box->absolute.w - 15, size_box->absolute.y, 15, size_box->absolute.h - 15});
	SDL_RenderDrawRect(size_box->renderer, &(SDL_Rect){size_box->absolute.x, size_box->absolute.y + size_box->absolute.h - 15, size_box->absolute.w - 15, 15});
}

void	ui_size_box_build(t_widget *size_box)
{
	if (size_box->nb_child)
	{
		size_box->childs[0]->relative.x = 0;
		size_box->childs[0]->relative.y = 0;
		size_box->absolute.w = size_box->childs[0]->absolute.w + 15;
		size_box->absolute.h = size_box->childs[0]->absolute.h + 15;
	}
}

t_widget	*ui_create_size_box(t_widget *parent, int x, int y, int width, int height)
{
	t_widget	*size_box;
	t_size_box_data	*data;

	if (parent == NULL)
		return (NULL);
	size_box = ui_new_widget((SDL_Rect){x, y, width, height}, SIZE_BOX, UI_MAX_SIZE_BOX_CHILDS);
	if (!size_box)
		return (NULL);
	if (ui_add_child(parent, size_box) != UI_SUCCESS)
		return (free(size_box), NULL);
	size_box->data = malloc(sizeof(t_size_box_data));
	if (!size_box->data)
		return (free(size_box), NULL);
	data = (t_size_box_data *)size_box->data;
	*data = (t_size_box_data){0};
	ui_set_widget_colors(size_box, 0x7F5F5F5F, 0x7F5F5F5F, 0x7F5F5F5F);
	size_box->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	size_box->render = ui_size_box_render;
	size_box->build = ui_size_box_build;
	size_box->texture = ui_new_texture(parent->renderer, width, height, size_box->colors[size_box->state]);
	return (size_box);
}