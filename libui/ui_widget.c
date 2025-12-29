/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_widget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 16:12:45 by injah             #+#    #+#             */
/*   Updated: 2025/12/29 01:03:12 by injah            ###   ########.fr       */
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
		widget->core->focused_widget = widget;
		if (core->mouse.mouse_buttons[SDL_BUTTON_LEFT])
			ui_widget_change_state(widget, CLICKED);
		else
			ui_widget_change_state(widget, HOVERED);
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
	widget->rect = rect;
	widget->type = type;
	widget->is_visible = true;
	widget->outline = 2;
	return (widget);
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

void	ui_draw_outline(SDL_Renderer *renderer, SDL_Rect start_rect, int size, SDL_Color color)
{
	int			i;
	SDL_Rect	rect;

	i = 0;
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	while (i < size)
	{
		rect.x = start_rect.x + i;
		rect.y = start_rect.y + i;
		rect.w = start_rect.w - 2 * i;
		rect.h = start_rect.h - 2 * i;
		SDL_RenderDrawRect(renderer, &rect);
		i++;
	}
}
int	ui_add_child(t_widget *parent, t_widget *child)
{
	child->parent = parent;
	child->core = parent->core;
	child->renderer = parent->renderer;
	child->window_id = parent->window_id;
	if (parent->add_child == NULL)
		return (ft_dprintf(2, "ui_add_child: parent widget does not have add child function\n"), UI_ERROR);
	if (parent->add_child(parent, child) == UI_ERROR)
		return (ft_dprintf(2, "ui_add_child: parent widget can't add this child\n"), UI_ERROR);
	return (UI_SUCCESS);	
}
