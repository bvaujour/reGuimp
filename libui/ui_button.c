/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_button.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:36:13 by injah             #+#    #+#             */
/*   Updated: 2025/12/20 06:47:04 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

static void	ui_button_event(t_widget *button, SDL_Event event)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_SPACE)
			button->state = CLICKED;
	}
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
			button->state = CLICKED;
	}
	if (event.type == SDL_MOUSEBUTTONUP)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			if (button->onclick)
				button->onclick(button, event.button.button, button->onclick_param);
		}
	}
}

static void		ui_button_update(t_widget *button)
{
	printf("button update\n");
	ui_button_event(button, button->core->event);
	ui_set_cursor(button->core, button->core->mouse.hand);
}

static void		ui_button_render(t_widget *button)
{
	t_button_data	*data;
	int				text_offset = 10;

	data = (t_button_data *)button->data;

	SDL_RenderSetClipRect(button->renderer, &button->parent->absolute);
	ui_draw_background(button->renderer, button->background, button->absolute, button->colors[button->state]);
	SDL_SetTextureColorMod(data->text_texture, 255, 0, 0);
	SDL_RenderCopy(button->renderer, data->text_texture, NULL, &(SDL_Rect){button->absolute.x + text_offset, button->absolute.y + text_offset, button->rect.w - 2 * text_offset, button->rect.h - 2 * text_offset});
	ui_draw_outline(button->renderer, button->absolute, button->outline);
	SDL_RenderSetClipRect(button->renderer, NULL);


}

static void	ui_button_destroy(t_widget *button)
{
	SDL_DestroyTexture(button->background);
}


static int	ui_button_add_child(t_widget *button, t_widget *child)
{
	(void)child;
	if (button->nb_child == UI_MAX_BUTTON_CHILDS)
	{
		printf("ui_window_add_child: Window has maximum child\n");
		return (UI_ERROR);
	}
	int	padding_x = button->rect.w / 10; 
	int	padding_y = button->rect.h / 10;
	child->rect.x = padding_x;
	child->rect.y = padding_y;
	child->rect.w = button->rect.w - 2 * padding_x;
	child->rect.h = button->rect.h - 2 * padding_y;
	button->childs[button->nb_child] = child;
	button->nb_child++;
	return (UI_SUCCESS);
}

void	ui_button_build_label(t_widget *button)
{
	SDL_Surface		*surface;
	t_button_data	*data;

	data = (t_button_data *)button->data;
	surface = TTF_RenderText_Solid(button->core->font, "button", (SDL_Color){255, 255, 255, 255});
	data->text_texture = SDL_CreateTextureFromSurface(button->renderer, surface);
	SDL_FreeSurface(surface);
}

t_widget	*ui_create_button(t_widget *parent, int x, int y, int width, int height)
{
	t_widget		*button;
	t_button_data	*data;

	if (parent == NULL || parent->add_child == NULL)
		return (NULL);
	button = ui_new_widget(BUTTON, sizeof(t_button_data));
	if (!button)
		return (NULL);
	button->childs = ui_new_widget_tab(UI_MAX_BUTTON_CHILDS);
	if (!button->childs)
	{
		ui_button_destroy(button);
		return (NULL);
	}
	data = (t_button_data *)button->data;
	*data = (t_button_data){0};
	button->rect = (SDL_Rect){x, y, width, height};
	ui_set_widget_colors(button, 0xFF5F5F5F, 0xFF7F7F7F, 0xFF9F9F9F, 0xFFBFBFBF);
	button->outline = 2;
	button->render = ui_button_render;
	button->update = ui_button_update;
	button->destroy = ui_button_destroy;
	button->add_child = ui_button_add_child;
	ui_set_child_references(parent, button);
	button->background = ui_new_texture(parent->renderer, width, height);
	ui_button_build_label(button);
	if (parent->add_child == NULL || parent->add_child(parent, button) == UI_ERROR)
	{
		printf("ui_create_button: FAILED ADD CHILD\n");
		ui_button_destroy(button);
		return (NULL);
	}
	return (button);
}