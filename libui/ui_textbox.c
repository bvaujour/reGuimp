/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_textbox.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 13:58:22 by kipouliq          #+#    #+#             */
/*   Updated: 2026/01/07 17:44:25 by kipouliq         ###   ########.fr       */
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

void		ui_textbox_render(t_widget *widget)
{
	SDL_RenderSetClipRect(widget->renderer, &widget->parent->absolute);
	SDL_RenderCopy(widget->renderer, widget->texture, NULL, &widget->absolute);
	ui_draw_outline(widget->renderer, widget->absolute, widget->outline, widget->outline_color);
	SDL_RenderSetClipRect(widget->renderer, NULL);
}

void		ui_textbox_update(t_widget *widget)
{
	ui_set_cursor(widget->core, widget->core->mouse.crosshair);
	ui_widget_drag(widget, widget->core->event);
}

void		ui_textbox_destroy(t_widget *widget)
{
	SDL_DestroyTexture(widget->texture);
}

t_widget	*ui_create_textbox(t_widget *parent, int x, int y, int width, int height)
{
	t_widget	*widget;

	if (parent == NULL)
		return (NULL);
	widget = ui_new_widget((SDL_Rect){x, y, width, height}, TEXTBOX, UI_MAX_DRAGBOX_CHILDS);
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

void        ui_create_textbox(t_widget *drawable)
{
    t_widget *text_dragbox;

    text_dragbox = ui_create_dragbox(drawable, drawable->absolute.x / 2, drawable->absolute.y / 2, 200, 100);
    drawable->add_child(drawable, text_dragbox);
    printf("create dragbox!\n");
}

// void	ui_get_text_input(t_widget *widget)
// {
//     SDL_Surface *surface;
//     SDL_Texture *text;
//     TTF_Font    *font;

//     font = TTF_OpenFont("libui/assets/fonts/Roboto/Roboto-Black.ttf", 150);
//     surface = TTF_RenderText_Solid(widget->renderer, "coucou", (SDL_Color){255, 255, 255, 255});
//     // text = SDL_CreateTextureFromSurface(surface)
// }