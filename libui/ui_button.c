/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_button.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:36:13 by injah             #+#    #+#             */
/*   Updated: 2026/01/08 13:42:42 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

static void		ui_button_update(t_widget *button)
{
	ui_set_cursor(button->core, button->core->mouse.hand);
}

static void		ui_button_render(t_widget *button)
{
	t_button_data	*data;
	int				padding = 10;

	data = (t_button_data *)button->data;
	SDL_RenderCopy(button->renderer, button->texture, NULL, &button->absolute);
	SDL_RenderCopy(button->renderer, data->label, NULL, &(SDL_Rect){button->absolute.x + padding, button->absolute.y + padding, button->rect.w - 2 * padding, button->rect.h - 2 * padding});
}

static void	ui_button_destroy(t_widget *button)
{
	SDL_DestroyTexture(button->texture);
}


static int	ui_button_add_child(t_widget *widget, t_widget *child)
{
	(void)child;
	if (widget->nb_child == UI_MAX_BUTTON_CHILDS)
	{
		printf("ui_window_add_child: Window has maximum child\n");
		return (UI_ERROR);
	}
	int	padding_x = widget->rect.w / 10; 
	int	padding_y = widget->rect.h / 10;
	child->rect.x = padding_x;
	child->rect.y = padding_y;
	child->rect.w = widget->rect.w - 2 * padding_x;
	child->rect.h = widget->rect.h - 2 * padding_y;
	widget->childs[widget->nb_child] = child;
	widget->nb_child++;
	return (UI_SUCCESS);
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
	button->render = ui_button_render;
	button->update = ui_button_update;
	button->destroy = ui_button_destroy;
	button->texture = ui_new_texture(parent->renderer, width, height, button->colors[button->state]);
	ui_button_set_label(button, "default label");
	return (button);
}