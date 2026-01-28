/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_widget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 16:12:45 by injah             #+#    #+#             */
/*   Updated: 2026/01/21 11:40:37 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

SDL_Rect	ui_get_absolute_rect(t_widget *widget)
{
	SDL_Rect	absolute;

	absolute = widget->absolute;
	if (widget->parent == NULL)
		return ((SDL_Rect){widget->relative.x, widget->relative.y, widget->absolute.w, widget->absolute.h});
	absolute.x = widget->parent->absolute.x + widget->relative.x;
	absolute.y = widget->parent->absolute.y + widget->relative.y;
	return (absolute);
}

SDL_Rect ui_get_clip_rect(t_widget *widget)
{
	SDL_Rect clip;

	clip = (SDL_Rect){widget->absolute.x, widget->absolute.y, widget->absolute.w, widget->absolute.h};
	if (widget->parent == NULL)
		return (clip);
	if (!SDL_IntersectRect(&clip, &widget->parent->clip, &clip))
		return (SDL_Rect){0, 0, 0, 0};
	return (clip);
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
	if (SDL_PointInRect(&core->mouse.position, &(SDL_Rect){widget->absolute.x, widget->absolute.y, widget->absolute.w, widget->absolute.h}))
	{
		if (core->mouse.buttons[SDL_BUTTON_LEFT] == true)
		{
			ui_widget_change_state(widget, CLICKED);
			widget->core->focused_widget = widget;
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
	widget->relative.x = rect.x;
	widget->relative.y = rect.y;
	widget->absolute = rect;
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
	SDL_RenderDrawRect(widget->renderer, &(SDL_Rect){widget->absolute.x, widget->absolute.y, widget->absolute.w, widget->absolute.h});
}

void		ui_widget_drag(t_widget *widget)
{
	if (widget->parent == NULL)
		return ;
	widget->relative.x += widget->core->mouse.motion.x;
	widget->relative.y += widget->core->mouse.motion.y;
}

void		ui_widget_resize(t_widget *widget)
{
	if (widget->core->mouse.position.y - widget->core->mouse.motion.y > widget->absolute.y + widget->absolute.h - 10)
		widget->absolute.h += widget->core->mouse.motion.y;

	if (widget->core->mouse.position.x - widget->core->mouse.motion.x > widget->absolute.x + widget->absolute.w - 10)
		widget->absolute.w += widget->core->mouse.motion.x;

	ui_build_widget(widget);
}


void		ui_widget_call_onclicked(t_widget *widget)
{
	SDL_Point	relative_mouse_position;

	relative_mouse_position.y = widget->core->mouse.position.y - widget->relative.y;
	relative_mouse_position.x = widget->core->mouse.position.x - widget->relative.x;
	if (widget->onclicked)
		widget->onclicked(widget, SDL_BUTTON_LEFT, relative_mouse_position.x, relative_mouse_position.y, widget->onclicked_param);
}

