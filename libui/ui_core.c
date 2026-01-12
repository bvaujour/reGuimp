/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:23:08 by injah             #+#    #+#             */
/*   Updated: 2026/01/12 14:28:24 by injah            ###   ########.fr       */
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
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	core->font = TTF_OpenFont("libui/assets/fonts/Roboto/Roboto-Black.ttf", 150);
	if (!core->font)
		printf("font not open\n");
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
	int	i;

	i = 0;
	while (core->windows[i])
	{
		ui_destroy_widget(core->windows[i]);
		i++;
	}
	free(core->windows);
	TTF_CloseFont(core->font);
	free(core);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

void	ui_bind_onkeypress(t_core *core, void (*f)(int, void *), void *param)
{
	core->onkeypress = f;
	core->onkeypress_param = param;
}

void	ui_bind_onbuttondown(t_core *core, void (*f)(int, void *), void *param)
{
	core->onbuttondown = f;
	core->onbuttondown_param = param;
}

void	ui_bind_onbuttonup(t_core *core, void (*f)(int, void *), void *param)
{
	core->onbuttonup = f;
	core->onbuttonup_param = param;
}
