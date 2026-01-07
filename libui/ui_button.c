/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_button.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:36:13 by injah             #+#    #+#             */
/*   Updated: 2026/01/07 16:41:55 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

static void	ui_button_event(t_widget *widget, SDL_Event event)
{
	t_button_data	*data;

	if (event.type == SDL_MOUSEBUTTONUP)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			data = widget->data;
			if (data->onclicked)
				data->onclicked(widget, event.button.button, data->onclicked_param);
		}
	}
}

static void		ui_button_update(t_widget *widget)
{
	ui_set_cursor(widget->core, widget->core->mouse.hand);
	ui_button_event(widget, widget->core->event);
}

static void		ui_button_render(t_widget *widget)
{
	t_button_data	*data;
	int				padding = 10;

	data = (t_button_data *)widget->data;

	SDL_RenderSetClipRect(widget->renderer, &widget->parent->absolute);
	SDL_RenderCopy(widget->renderer, widget->texture, NULL, &widget->absolute);
	SDL_SetTextureColorMod(data->label, 255, 0, 0);
	SDL_RenderCopy(widget->renderer, data->label, NULL, &(SDL_Rect){widget->absolute.x + padding, widget->absolute.y + padding, widget->rect.w - 2 * padding, widget->rect.h - 2 * padding});
	ui_draw_outline(widget->renderer, widget->absolute, widget->outline, widget->outline_color);
	SDL_RenderSetClipRect(widget->renderer, NULL);
}

static void	ui_button_destroy(t_widget *widget)
{
	SDL_DestroyTexture(widget->texture);
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
	t_widget			*widget;
	t_button_data		*data;

	if (parent == NULL)
		return (NULL);
	widget = ui_new_widget((SDL_Rect){x, y, width, height}, BUTTON, UI_MAX_BUTTON_CHILDS);
	if (!widget)
		return (NULL);
	if (ui_add_child(parent, widget) != UI_SUCCESS)
		return (free(widget), NULL);
	widget->data = malloc(sizeof(t_button_data));
	if (!widget->data)
		return (free(widget), NULL);
	data = (t_button_data *)widget->data;
	*data = (t_button_data){0};
	ui_set_widget_colors(widget, 0xFF5F5F5F, 0xFF7F7F7F, 0xFF9F9F9F);
	widget->render = ui_button_render;
	widget->update = ui_button_update;
	widget->destroy = ui_button_destroy;
	widget->add_child = ui_button_add_child;
	widget->texture = ui_new_texture(parent->renderer, width, height, widget->colors[widget->state]);
	ui_button_set_label(widget, "default label");
	return (widget);
}