/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_button.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:36:13 by injah             #+#    #+#             */
/*   Updated: 2026/01/18 15:50:59 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

static void		ui_button_render(t_widget *button)
{
	SDL_Rect	render_rect;

	render_rect = ui_get_render_rect(button);
	SDL_RenderSetClipRect(button->renderer, &button->parent->absolute);
	SDL_RenderCopy(button->renderer, button->texture, NULL, &render_rect);
	if (button == button->core->focused_widget)
		ui_widget_outline(button, (SDL_Color){127, 127, 127, 255});
	else
		ui_widget_outline(button, (SDL_Color){0, 0, 0, 255});
	SDL_RenderSetClipRect(button->renderer, NULL);
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