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

void		ui_dragbox_render(t_widget *dragbox)
{
	SDL_RenderSetClipRect(dragbox->renderer, &dragbox->parent->absolute);
	
	ui_draw_background(dragbox->renderer, dragbox->background, dragbox->absolute, dragbox->colors[dragbox->state]);
	ui_draw_outline(dragbox->renderer, dragbox->absolute, dragbox->outline);
	SDL_RenderSetClipRect(dragbox->renderer, NULL);
}

void		ui_dragbox_update(t_widget *dragbox)
{
	ui_set_cursor(dragbox->core, dragbox->core->mouse.crosshair);
	ui_widget_drag(dragbox, dragbox->core->event);
}

void		ui_dragbox_destroy(t_widget *dragbox)
{
	SDL_DestroyTexture(dragbox->background);
}

static int	ui_dragbox_add_child(t_widget *dragbox, t_widget *child)
{
	(void)dragbox;
	(void)child;
	if (dragbox->nb_child == UI_MAX_BOX_CHILDS)
	{
		printf("ui_window_add_child: Window has maximum child\n");
		return (UI_ERROR);
	}
	dragbox->rect.w = child->rect.w;
	dragbox->rect.h = child->rect.h;
	child->rect.x = dragbox->outline;
	child->rect.y = dragbox->outline;
	child->rect.w = dragbox->rect.w - 2 * dragbox->outline;
	child->rect.h = dragbox->rect.h - 2 * dragbox->outline;
	dragbox->childs[dragbox->nb_child] = child;
	dragbox->nb_child++;
	return (UI_SUCCESS);
}
t_widget	*ui_create_dragbox(t_widget *parent, int x, int y, int width, int height)
{
	t_widget		*dragbox;

	if (parent == NULL || parent->add_child == NULL)
		return (NULL);
	dragbox = ui_new_widget(BUTTON, sizeof(t_dragbox_data));
	if (!dragbox)
		return (NULL);
	dragbox->childs = ui_new_widget_tab(UI_MAX_DRAGBOX_CHILDS);
	if (!dragbox->childs)
	{
		ui_dragbox_destroy(dragbox);
		return (NULL);
	}
	dragbox->rect = (SDL_Rect){x, y, width, height};
	ui_set_widget_colors(dragbox, 0x7F5F5F5F, 0x7F5F5F5F, 0x7F5F5F5F, 0x7F5F5F5F);
	dragbox->outline = 25;
	dragbox->render = ui_dragbox_render;
	dragbox->update = ui_dragbox_update;
	dragbox->destroy = ui_dragbox_destroy;
	dragbox->add_child = ui_dragbox_add_child;
	ui_set_child_references(parent, dragbox);
	dragbox->background = ui_new_texture(parent->renderer, width, height);
	if (parent->add_child == NULL || parent->add_child(parent, dragbox) == UI_ERROR)
	{
		printf("ui_create_dragbox: FAILED ADD CHILD\n");
		ui_dragbox_destroy(dragbox);
		return (NULL);
	}
	return (dragbox);
}