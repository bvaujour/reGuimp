/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:23:08 by injah             #+#    #+#             */
/*   Updated: 2025/12/04 16:56:48 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

int	ui_init(t_core *core)
{
	int img_flags;
	
	img_flags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "SDL_Init error: %s\n", SDL_GetError());
        return (1);
    }
	if (TTF_Init() != 0)
	{
		fprintf(stderr, "TTF_Init error: %s\n", TTF_GetError());
		return (2);
	}
	if ((IMG_Init(img_flags) & img_flags) != img_flags)
	{
		fprintf(stderr, "IMG_Init error: %s\n", IMG_GetError());
		return (3);
	}
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	core->widgets = NULL;
	return (0);
}

static void	ui_update(t_core *core)
{
	int	i;

	i = 0;
	while (core->widgets[i])
	{
		if (core->widgets[i]->update)
			core->widgets[i]->update(core->widgets[i]);
		i++;
	}
}

static void	ui_render(t_core *core)
{
	int	i;

	i = 0;
	while (core->widgets[i])
	{
		if (core->widgets[i]->render)
			core->widgets[i]->render(core->widgets[i]);
		i++;
	}
}

static void	ui_destroy(t_core *core)
{
	ui_destroy_widgets(core->widgets);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

void	ui_run(t_core *core)
{
	core->is_running = true;
	while (core->is_running)
	{
		ui_event(core);
		ui_update(core);
		ui_render(core);
	}
	ui_destroy(core);
}