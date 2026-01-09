/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_textbox.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 13:58:22 by kipouliq          #+#    #+#             */
/*   Updated: 2026/01/09 16:45:54 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

static void	ui_textbox_event(t_widget *box, SDL_Event event)
{
	if (event.type == SDL_MOUSEMOTION && box->state == CLICKED)
	{
		box->core->dragged_widget = box->parent;
	}
}

void	ui_print_textbox(t_widget *canvas)
{
	t_widget 		*textbox;
	t_image_data	*canvas_data;
	t_textbox_data 	*textbox_data = NULL;
	
	textbox = ui_search_child_by_type(canvas, TEXTBOX);
	if (textbox)
	{
		textbox_data = (t_textbox_data *)textbox->data;
		canvas_data = (t_image_data *)canvas->data;
		if (!textbox_data || !canvas_data)
			return ;
		printf("%d\n", textbox->type);
		printf("%d\n", SDL_BlitSurface(textbox_data->text_surface, NULL, canvas_data->surface, NULL));
		printf("%s\n", SDL_GetError());
		// SDL_DestroyTexture(data->text_texture);
		// data->text_texture = NULL;
	}
}

void	ui_textbox_render(t_widget *widget)
{
	t_textbox_data *data;

	SDL_RenderCopy(widget->renderer, widget->texture, NULL, &widget->absolute);
	data = (t_textbox_data *)widget->data;
	if (!data)
		return ;
	if (data->text_texture)
		SDL_RenderCopy(widget->renderer, data->text_texture, NULL, &widget->absolute);
}

void	ui_textbox_set_text(t_widget *widget)
{
	TTF_Font		*font;
	t_textbox_data  *data;

	data = (t_textbox_data *)widget->data;
	font = TTF_OpenFont("libui/assets/fonts/Roboto/Roboto-Black.ttf", 26);
	if (!font)
	{
		ft_dprintf(2, "Error: failed to open font because : %s\n", SDL_GetError());
		return ; 
	}
	// surface = TTF_RenderText_Blended(font, data->text_content, (SDL_Color){255, 255, 255, 255});
	
	data->text_surface = TTF_RenderText_Blended(font, "coucou", (SDL_Color){0, 0, 0, 255});
	data->text_texture = SDL_CreateTextureFromSurface(widget->renderer, data->text_surface);
}

void	ui_textbox_update(t_widget *widget)
{
	ui_set_cursor(widget->core, widget->core->mouse.arrow);
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
	widget->data = malloc(sizeof(t_textbox_data));
	if (!widget->data)
		return (free(widget), NULL);
	if (ui_add_child(parent, widget) != UI_SUCCESS)
		return (free(widget), NULL);
	ui_set_widget_colors(widget, 0x5000FFFF, 0x5000FFFF, 0x5000FFFF);
	// widget->outline = 25;
	widget->render = ui_textbox_render;
	widget->update = ui_textbox_update;
	widget->destroy = ui_textbox_destroy;
	widget->texture = ui_new_texture(parent->renderer, width, height,
		widget->colors[widget->state]);
	widget->event = ui_textbox_event;
	widget->is_dragable = true;
	widget->parent = parent;
	printf("%d %d %d %d\n", x, y, width, height);
	ui_textbox_set_text(widget);
	return (widget);
}

t_widget   *ui_create_textbox(t_widget *parent)
{
	t_widget	*textbox;

	if (!parent)
		return (NULL);
	textbox = ui_create_widget_textbox(parent, parent->rect.x, parent->rect.y,
				parent->rect.w, parent->rect.h);
	if (!textbox)
		return (NULL);
	// ui_add_child(parent, textbox);
	printf("created textbox!\n");
	return (textbox);
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