/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_widget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 16:12:45 by injah             #+#    #+#             */
/*   Updated: 2026/01/13 15:54:19 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

SDL_Rect	ui_get_absolute_rect(t_widget *widget)
{
	t_widget 	*reference;
	SDL_Point	position;

	position.x = widget->rect.x;
	position.y = widget->rect.y;
	reference = widget->parent;
	while (reference != NULL)
	{
		position.x += reference->rect.x;
		position.y += reference->rect.y;
		reference = reference->parent;
	}
	return ((SDL_Rect){position.x, position.y, widget->rect.w, widget->rect.h});
}

void	ui_widget_change_state(t_widget *widget, e_widget_state new_state)
{
	SDL_Color	color;

	if (widget->state != new_state)
	{
		widget->state = new_state;
		color = widget->colors[new_state];
		SDL_SetTextureColorMod(widget->texture, color.r, color.g, color.b);
		SDL_SetTextureAlphaMod(widget->texture, color.a);
	}
}

void	ui_widget_manage_state(t_widget *widget)
{
	t_core			*core;

	core = widget->core;
	if (SDL_PointInRect(&core->mouse.position, &widget->absolute))
	{
		if (core->mouse.buttons[SDL_BUTTON_LEFT] == true)
		{
			ui_widget_change_state(widget, CLICKED);
			widget->core->focused_widget = widget;
			if (widget->is_dragable && (core->mouse.position.x == widget->absolute.x || core->mouse.position.y == widget->absolute.y || core->mouse.position.x == widget->absolute.x + widget->absolute.w - 1 ||  core->mouse.position.y == widget->absolute.y + widget->absolute.h - 1))
				widget->core->dragged_widget = widget;
		}
		else
		{
			ui_widget_change_state(widget, HOVERED);
			widget->core->hovered_widget = widget;
		}
	}
	else
		ui_widget_change_state(widget, NORMAL);
}

t_widget *ui_new_widget(SDL_Rect rect, e_widget_type type, int max_child)
{
	t_widget		*widget;

	widget = malloc(sizeof(t_widget));
	if (widget == NULL)
		return (NULL);
	*widget = (t_widget){0};
	if (max_child)
	{
		widget->childs = ui_new_widget_tab(max_child);
		if (widget->childs == NULL)
			return (free(widget), NULL);
	}
	widget->max_child = max_child;
	widget->rect = rect;
	widget->type = type;
	widget->is_visible = true;
	return (widget);
}

int	ui_add_child(t_widget *widget, t_widget *child)
{
	if (widget->nb_child == widget->max_child)
	{
		printf("ui_add_child: Widget has maximum child\n");
		return (UI_ERROR);
	}
	widget->childs[widget->nb_child] = child;
	widget->nb_child++;
	child->parent = widget;
	child->core = widget->core;
	child->renderer = widget->renderer;
	return (UI_SUCCESS);
}

t_widget 	**ui_new_widget_tab(int tab_len)
{
	t_widget	**childs;
	int			i;

	i = 0;
	childs = malloc(sizeof(t_widget *) * (tab_len + 1));
	if (childs == NULL)
	{
		printf("ui_new_widget_tab failed\n");
		return (NULL);
	}
	while (i <= tab_len)
	{
		childs[i] = NULL;
		i++;
	}
	return (childs);
}

int	ui_core_add_window(t_core *core, t_widget *window)
{
	int	i;

	i = 0;
	while (i < UI_MAX_WINDOWS)
	{
		if (core->windows[i] == NULL)
		{
			core->windows[i] = window;
			window->parent = NULL;
			window->core = core;
			return (0);
		}
		i++;
	}
	return (-1);
}

void	ui_widget_outline(t_widget *widget, SDL_Color color)
{
	SDL_SetRenderDrawColor(widget->renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawRect(widget->renderer, &widget->absolute);
}

void		ui_widget_drag(t_widget *widget)
{
	SDL_Rect	intersection;
	SDL_Rect	new_rect;
	int			i;


	i = 0;
	if (widget ->parent == NULL)
		return ;
	new_rect = widget->rect;
	new_rect.x = widget->core->mouse.position.x - widget->parent->absolute.x;
	new_rect.y = widget->core->mouse.position.y - widget->parent->absolute.y;
	if (new_rect.x < 0 || new_rect.y < 0 || new_rect.x > widget->parent->rect.w - new_rect.w || new_rect.y > widget->parent->rect.h - new_rect.h)
		return ;
	while (widget->parent->childs[i])
	{
		if (widget->parent->childs[i]->is_visible && widget->parent->childs[i] != widget)
		{
			if (SDL_IntersectRect(&widget->parent->childs[i]->rect, &new_rect, &intersection))
				return ;
		}
		i++;
	}
	widget->rect = new_rect;
}


void		ui_widget_call_onclicked(t_widget *widget)
{
	SDL_Point	relative_mouse_position;

	relative_mouse_position.x = widget->core->mouse.position.x - widget->rect.x;
	relative_mouse_position.y = widget->core->mouse.position.y - widget->rect.y;
	if (widget->onclicked)
		widget->onclicked(widget, SDL_BUTTON_LEFT, relative_mouse_position.x, relative_mouse_position.y, widget->onclicked_param);
}

