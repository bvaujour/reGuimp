/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_button.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:36:13 by injah             #+#    #+#             */
/*   Updated: 2026/01/15 19:10:08 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

static void		ui_button_render(t_widget *button)
{
	SDL_RenderCopy(button->renderer, button->texture, NULL, &button->absolute);
}

static void	ui_button_destroy(t_widget *button)
{
	(void)button;
}

t_widget	*ui_create_button(t_widget *parent, int x, int y, int width, int height)
{
	t_widget			*button;
	t_button_data		*data;

	if (parent == NULL)
		return (NULL);
	button = ui_new_widget((SDL_Rect){x, y, width, height}, BUTTON, UI_MAX_BUTTON_CHILDS);
	if (!button)
		return (NULL);
	if (ui_add_child(parent, button) != UI_SUCCESS)
		return (free(button), NULL);
	button->data = malloc(sizeof(t_button_data));
	if (!button->data)
		return (free(button), NULL);
	data = (t_button_data *)button->data;
	*data = (t_button_data){0};
	ui_set_widget_colors(button, 0xFF5F5F5F, 0xFF7F7F7F, 0xFF9F9F9F);
	button->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	button->render = ui_button_render;
	button->destroy = ui_button_destroy;
	button->texture = ui_new_texture(parent->renderer, width, height, button->colors[button->state]);
	return (button);
}