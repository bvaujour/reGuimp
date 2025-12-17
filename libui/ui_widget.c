/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_widget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 16:12:45 by injah             #+#    #+#             */
/*   Updated: 2025/12/17 05:18:05 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

int	ui_widget_add_child(t_widget *parent, t_widget *child)
{
	if (child == parent)
		return (0);
	child->parent = parent;
	child->core = parent->core;
	parent->childs[parent->nb_childs] = child;
	parent->nb_childs++;
	return (0);
}

void	ui_widget_common_update(t_widget *widget)
{
	t_core			*core;

	core = widget->core;
	if (ui_point_in_widget(widget, core->mouse.position))
		core->focused_widget = widget;
	else
		widget->state = UI_NORMAL_STATE;
}

void	ui_widget_clear(t_widget *widget)
{
	SDL_Color	color;

	color = widget->colors[widget->state];
	SDL_FillRect(widget->surface, NULL, SDL_MapRGBA(widget->surface->format, color.r, color.g, color.b, color.a));
}

void	ui_widget_manage_state_and_click(t_widget *widget)
{
	t_core	*core;
	
	core = widget->core;
	if (core->mouse.mouse_buttons[SDL_BUTTON_LEFT] == true)
		widget->state = UI_CLICKED_STATE;
	else
	{
		if (widget->state == UI_CLICKED_STATE)
		{
			if (widget->onclick)
				widget->onclick(widget, widget->core->mouse.last_click, widget->onclick_param);
		}
		widget->state = UI_HOVERED_STATE;
	}
}

t_widget	*ui_init_widget(t_core *core, int x, int y, int width, int height)
{
	t_widget *widget;

	widget = malloc(sizeof(t_widget));
	if (!widget)
		return (NULL);
	*widget = (t_widget){0};
	widget->core = core;
	widget->rect.x = x;
	widget->rect.y = y;
	widget->rect.w = width;
	widget->rect.h = height;
	ui_widget_add_child(core->canvas, widget);
	return (widget);
}
