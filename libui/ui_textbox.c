/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_textbox.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 13:58:22 by kipouliq          #+#    #+#             */
/*   Updated: 2026/01/08 13:35:46 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

void	ui_textbox_render(t_widget *widget)
{
	SDL_RenderSetClipRect(widget->renderer, &widget->parent->absolute);
	SDL_RenderCopy(widget->renderer, widget->texture, NULL, &widget->absolute);
	ui_draw_outline(widget->renderer, widget->absolute, widget->outline,
		widget->outline_color);
	SDL_RenderSetClipRect(widget->renderer, NULL);
}

void	ui_textbox_update(t_widget *widget)
{
	(void) widget;
	// ui_set_cursor(widget->core, widget->core->mouse.crosshair);
	// ui_widget_drag(widget, widget->core->event);
}

void	ui_textbox_destroy(t_widget *widget)
{
	SDL_DestroyTexture(widget->texture);
}

t_widget	*ui_create_widget_textbox(t_widget *parent, int x, int y, int width,
		int height)
{
	t_widget	*widget;

	if (parent == NULL)
		return (NULL);
	widget = ui_new_widget((SDL_Rect){x, y, width, height}, TEXTBOX,
			UI_MAX_TEXTBOX_CHILDS);
	if (!widget)
		return (NULL);
	if (ui_add_child(parent, widget) != UI_SUCCESS)
		return (free(widget), NULL);
	ui_set_widget_colors(widget, 0x7F5F5F5F, 0x7F5F5F5F, 0x7F5F5F5F);
	widget->outline = 25;
	widget->render = ui_textbox_render;
	widget->update = ui_textbox_update;
	widget->destroy = ui_textbox_destroy;
	widget->texture = ui_new_texture(parent->renderer, width, height,
			widget->colors[widget->state]);
	return (widget);
}

void	ui_create_textbox(t_widget *widget, t_properties *properties)
{
	t_widget	*text_dragbox;

	if (!widget)
		return ;
	if (properties)
	{
		text_dragbox = ui_create_widget_textbox(widget, properties->x, properties->y,
				properties->w, properties->h);
	}
	else
		text_dragbox = ui_create_widget_textbox(widget, widget->rect.x, widget->rect.y,
				widget->rect.w, widget->rect.h);
	widget->add_child(widget, text_dragbox);
	printf("create dragbox!\n");
}

// void	ui_get_text_input(t_widget *widget)
// {
//     SDL_Surface *surface;
//     SDL_Texture *text;
//     TTF_Font    *font;

//     font = TTF_OpenFont("libui/assets/fonts/Roboto/Roboto-Black.ttf", 150);
//     surface = TTF_RenderText_Solid(widget->renderer, "coucou",
		// (SDL_Color){255, 255, 255, 255});
		//     // text = SDL_CreateTextureFromSurface(surface)
		// }