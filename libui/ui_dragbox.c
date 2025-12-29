/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_dragbox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:09:13 by injah             #+#    #+#             */
/*   Updated: 2025/12/19 22:13:34 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

static int		ui_check_widget_collision(t_widget *widget, SDL_Rect new_rect)
{
	t_widget	*parent;
	SDL_Rect	 intersection;

	int			i;

	i = 0;
	if (!widget->parent)
		return (false);
	parent = widget->parent;
	if (new_rect.x < 0)
		return (false);
	if (new_rect.y < 0)
		return (false);
	if (new_rect.x > parent->rect.w - new_rect.w)
		return (false);
	if (new_rect.y > parent->rect.h - new_rect.h)
		return (false);
	while (parent->childs[i])
	{
		if (parent->childs[i] != widget)
		{
			if (SDL_IntersectRect(&parent->childs[i]->rect, &new_rect, &intersection))
				return (false);
		}
		i++;
	}
	return (true);
}

static void	ui_widget_drag(t_widget *widget, SDL_Event event)
{
	SDL_Rect	new_rect;

	if (event.type == SDL_MOUSEMOTION)
	{
		if (widget->state == CLICKED)
		{
			widget->core->dragged_widget = widget;
			new_rect = widget->rect;
			new_rect.x += widget->core->mouse.motion.x;
			new_rect.y += widget->core->mouse.motion.y;
			if (ui_check_widget_collision(widget, new_rect))
				widget->rect = new_rect;
		}
	}
}

void		ui_dragbox_render(t_widget *widget)
{
	SDL_RenderSetClipRect(widget->renderer, &widget->parent->absolute);
	SDL_RenderCopy(widget->renderer, widget->texture, NULL, &widget->absolute);
	ui_draw_outline(widget->renderer, widget->absolute, widget->outline, widget->outline_color);
	SDL_RenderSetClipRect(widget->renderer, NULL);
}

void		ui_dragbox_update(t_widget *widget)
{
	ui_set_cursor(widget->core, widget->core->mouse.crosshair);
	ui_widget_drag(widget, widget->core->event);
}

void		ui_dragbox_destroy(t_widget *widget)
{
	SDL_DestroyTexture(widget->texture);
}

static int	ui_dragbox_add_child(t_widget *widget, t_widget *child)
{
	(void)widget;
	(void)child;
	if (widget->nb_child == UI_MAX_BOX_CHILDS)
	{
		printf("ui_window_add_child: Window has maximum child\n");
		return (UI_ERROR);
	}
	widget->rect.w = child->rect.w;
	widget->rect.h = child->rect.h;
	child->rect.x = widget->outline;
	child->rect.y = widget->outline;
	child->rect.w = widget->rect.w - 2 * widget->outline;
	child->rect.h = widget->rect.h - 2 * widget->outline;
	widget->childs[widget->nb_child] = child;
	widget->nb_child++;
	return (UI_SUCCESS);
}

t_widget	*ui_create_dragbox(t_widget *parent, int x, int y, int width, int height)
{
	t_widget	*widget;

	if (parent == NULL)
		return (NULL);
	widget = ui_new_widget((SDL_Rect){x, y, width, height}, DRAGBOX, UI_MAX_DRAGBOX_CHILDS);
	if (!widget)
		return (NULL);
	if (ui_add_child(parent, widget) != UI_SUCCESS)
		return (free(widget), NULL);
	ui_set_widget_colors(widget, 0x7F5F5F5F, 0x7F5F5F5F, 0x7F5F5F5F);
	widget->outline = 25;
	widget->render = ui_dragbox_render;
	widget->update = ui_dragbox_update;
	widget->destroy = ui_dragbox_destroy;
	widget->add_child = ui_dragbox_add_child;
	widget->texture = ui_new_texture(parent->renderer, width, height, widget->colors[widget->state]);
	return (widget);
}