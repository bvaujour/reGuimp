/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_widget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 16:12:45 by injah             #+#    #+#             */
/*   Updated: 2025/12/20 06:45:21 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"


static SDL_Rect	ui_get_absolute_rect(t_widget *widget)
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

void	ui_widget_common_update(t_widget *widget)
{
	t_core			*core;

	core = widget->core;
	widget->absolute = ui_get_absolute_rect(widget);
	if (widget->window_id == core->event.window.windowID && SDL_PointInRect(&core->mouse.position, &widget->absolute))
	{
		core->focused_widget = widget;
		if (core->mouse.mouse_buttons[SDL_BUTTON_LEFT])
			widget->state = CLICKED;
		else
		{
			if (core->mouse.mouse_buttons[SDL_BUTTON_LEFT] == false && widget->state == CLICKED)
				widget->state = RELEASED;
			else
				widget->state = HOVERED;
		}
	}
	else
		widget->state = NORMAL;
}

t_widget *ui_new_widget(e_widget_type type, size_t sizeof_data)
{
	t_widget		*widget;

	widget = malloc(sizeof(t_widget));
	if (widget == NULL)
		return (NULL);
	*widget = (t_widget){0};
	widget->data = malloc(sizeof_data);
	if (widget->data == NULL)
	{
		free(widget);
		return (NULL);
	}
	widget->type = type;
	widget->is_visible = true;
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

int	ui_add_child(t_widget *parent, t_widget *child)
{
	if (parent->add_child == NULL || parent->add_child(parent, child) == UI_ERROR)
	{
		printf("ui_add_child failed\n");
		return (UI_ERROR);
	}
	printf("Adding child\n");
	child->parent = parent;
	child->core = parent->core;
	child->renderer = parent->renderer;
	parent->childs[parent->nb_child] = child;
	parent->nb_child++;
	return (UI_SUCCESS);
}

void	ui_set_child_references(t_widget *parent, t_widget *child)
{
	child->parent = parent;
	child->core = parent->core;
	child->renderer = parent->renderer;
	child->window_id = parent->window_id;
}

void	ui_draw_outline(SDL_Renderer *renderer, SDL_Rect start_rect, int size)
{
	int			i;
	SDL_Rect	rect;

	i = 0;
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

void	ui_draw_background(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect rect, SDL_Color color)
{
	SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
	SDL_SetTextureAlphaMod(texture, color.a);
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}
