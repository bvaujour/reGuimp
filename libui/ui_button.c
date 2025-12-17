/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_button.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:36:13 by injah             #+#    #+#             */
/*   Updated: 2025/12/17 14:33:03 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"


static void		ui_button_update(t_widget *button)
{
	// button->on_click(button, button->core->mouse_infos.last_click, button->on_click_param);
	ui_widget_manage_state_and_click(button);
}

static void		ui_button_build(t_widget *button)
{
	// SDL_Color	color;
// 
	// color = button->colors[button->state];
	if (button->surface)
		SDL_FreeSurface(button->surface);
	if (button->texture)
		SDL_DestroyTexture(button->texture);
	button->surface = IMG_Load("disney.jpg");
	// SDL_FillRect(button->surface, NULL, SDL_MapRGBA(button->surface->format, color.r, color.g, color.b, color.a));
}

static void		ui_button_render(t_widget *button)
{
	// SDL_Color		color;
	// SDL_Rect		rect;
	t_core			*core;

	core = button->core;

	if (button->texture)
		SDL_DestroyTexture(button->texture);
	SDL_RenderSetClipRect(core->renderer, &button->rect);
	button->texture = SDL_CreateTextureFromSurface(core->renderer, button->surface);
	SDL_RenderCopy(core->renderer, button->texture, NULL, NULL);
	// color = button->colors[button->state];
	// SDL_SetRenderDrawColor(core->renderer, color.r, color.g, color.b, color.a);
	// SDL_RenderFillRect(core->renderer, &button->rect);
	// // rect = ui_draw_outline(button->surface, button->colors[UI_OUTLINE_COLOR], button->outline);
	// color = button->colors[UI_OUTLINE_COLOR];
	// SDL_SetRenderDrawColor(core->renderer, color.r, color.g, color.b, color.a);
	// SDL_RenderDrawRect(core->renderer, &button->rect);

	// SDL_FillRect(button->surface, &rect, SDL_MapRGBA(button->surface->format, color.r, color.g, color.b, color.a));

	// SDL_RenderCopyEx(core->renderer, button->texture, NULL, NULL, 90, NULL, SDL_FLIP_NONE);

	// SDL_BlitSurface(button->surface, NULL, button->parent->surface, &button->rect);

}

static void	ui_button_destroy(t_widget *button)
{
	SDL_FreeSurface(button->surface);
}

static void	ui_button_manage_cursor(t_widget *button)
{
	(void)button;
	ui_set_cursor(button->core, button->core->mouse.hand);
}


t_widget	*ui_create_button(t_core *core, int x, int y, int width, int height)
{
	t_widget		*button;
	t_button_data	*data;

	button = ui_init_widget(core, x, y, width, height);
	data = malloc(sizeof(t_button_data));
	*data = (t_button_data){0};
	button->data = data;
	button->outline = 2;
	button->colors[UI_OUTLINE_COLOR] = (SDL_Color){200, 20, 100, 100};
	button->colors[UI_NORMAL_COLOR] = (SDL_Color){255, 255, 255, 255};
	button->colors[UI_HOVERED_COLOR] = (SDL_Color){100, 100, 100, 255};
	button->colors[UI_CLICKED_COLOR] = (SDL_Color){150, 150, 150, 255};
	button->type = BUTTON;
	button->is_dragable = true;
	button->render = ui_button_render;
	button->update = ui_button_update;
	button->destroy = ui_button_destroy;
	button->build = ui_button_build;
	button->manage_cursor = ui_button_manage_cursor;
	ui_button_build(button);
	return (button);
}