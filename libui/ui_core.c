/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:23:08 by injah             #+#    #+#             */
/*   Updated: 2025/12/17 13:40:58 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

t_core	*ui_init(int width, int height)
{
	int 	img_flags;
	t_core	*core;

	core = malloc(sizeof(t_core));
	if (core == NULL)
		return (NULL);
	*core = (t_core){0};
	img_flags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (SDL_Init(SDL_INIT_VIDEO) != 0 || TTF_Init() != 0 || (IMG_Init(img_flags) & img_flags) != img_flags)
		return (ui_destroy(core), NULL);
	core->window = SDL_CreateWindow("LIBUI", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (!core->window)
		return (ui_destroy(core), NULL);
	core->renderer = SDL_CreateRenderer(core->window, -1, SDL_RENDERER_ACCELERATED);
	if (!core->renderer)
		return (ui_destroy(core), NULL);
	core->canvas = ui_create_canvas(core, width, height);
	core->mouse.arrow = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	core->mouse.hand = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	core->mouse.crosshair = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	return (core);
}

void	ui_quit(t_core *core)
{
	core->is_running = false;
}

void	ui_set_cursor(t_core *core, SDL_Cursor *cursor)
{
	if (cursor != core->mouse.current_cursor)
	{
		SDL_SetCursor(cursor);
		core->mouse.current_cursor = cursor;
	}
}

void	ui_destroy(t_core *core)
{
	ui_destroy_widget_and_childs(core->canvas);
	SDL_FreeCursor(core->mouse.arrow);
	SDL_FreeCursor(core->mouse.hand);
	SDL_FreeCursor(core->mouse.crosshair);
	SDL_DestroyRenderer(core->renderer);
	SDL_DestroyWindow(core->window);
	free(core);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}
