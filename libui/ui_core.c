/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:23:08 by injah             #+#    #+#             */
/*   Updated: 2025/12/20 06:21:59 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

t_core	*ui_init()
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
	core->windows = ui_new_widget_tab(UI_MAX_WINDOWS);
	if (!core->windows)
	{
		free (core);
		return (NULL);
	}
	// SDL_SYSTEM_CURSOR_SIZEALL
	core->mouse.arrow = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	core->mouse.hand = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	core->mouse.crosshair = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	core->font = TTF_OpenFont("libui/assets/fonts/Roboto/Roboto-Black.ttf", 150);
	if (!core->font)
		printf("font not open\n");
	printf("sizeof(SDL_Rect) = %zu\n", sizeof(SDL_Rect));
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
	SDL_FreeCursor(core->mouse.arrow);
	SDL_FreeCursor(core->mouse.hand);
	SDL_FreeCursor(core->mouse.crosshair);
	TTF_CloseFont(core->font);
	ui_destroy_widgets(core->windows);
	free(core);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}
