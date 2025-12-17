/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_canvas.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 12:53:46 by injah             #+#    #+#             */
/*   Updated: 2025/12/17 13:54:37 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

static void		ui_canvas_update(t_widget *canvas)
{
	ui_widget_common_update(canvas);
}

static void		ui_canvas_build(t_widget *canvas)
{
	if (canvas->texture != NULL)
		SDL_DestroyTexture(canvas->texture);
	if (canvas->surface != NULL)
		SDL_FreeSurface(canvas->surface);
	canvas->texture = SDL_CreateTexture(canvas->core->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, canvas->rect.w, canvas->rect.h);
	canvas->surface = SDL_CreateRGBSurfaceWithFormat(0, canvas->rect.w, canvas->rect.h, 32, SDL_PIXELFORMAT_ARGB8888);
}

static void		ui_canvas_render(t_widget *canvas)
{
	(void)canvas;
	// SDL_UpdateTexture(canvas->texture, NULL, canvas->surface->pixels, canvas->surface->pitch);
	// SDL_RenderCopy(canvas->core->renderer, canvas->texture, NULL, NULL);
	// SDL_RenderPresent(canvas->core->renderer);
}

static void	ui_canvas_destroy(t_widget *canvas)
{
	if (canvas->surface)
		SDL_FreeSurface(canvas->surface);
	if (canvas->texture)
		SDL_DestroyTexture(canvas->texture);
}

static void	ui_canvas_manage_cursor(t_widget *canvas)
{
	ui_set_cursor(canvas->core, canvas->core->mouse.arrow);
}

t_widget 	*ui_create_canvas(t_core *core, int width, int height)
{
	t_widget		*canvas;
	t_canvas_data	*data;

	canvas = malloc(sizeof(t_widget));
	*canvas = (t_widget){0};
	data = malloc(sizeof(t_canvas_data));
	*data = (t_canvas_data){0};
	canvas->data = data;
	canvas->core = core;
	canvas->max_childs = UI_MAX_CANVAS_CHILDS;
	canvas->childs = malloc(sizeof(t_widget *) * UI_MAX_CANVAS_CHILDS);
	canvas->colors[UI_NORMAL_COLOR] = (SDL_Color){127, 127, 127, 255};
	canvas->colors[UI_HOVERED_COLOR] = (SDL_Color){145, 127, 127, 255};
	canvas->colors[UI_CLICKED_COLOR] = (SDL_Color){188, 127, 127, 255};
	canvas->render = ui_canvas_render;
	canvas->update = ui_canvas_update;
	canvas->build = ui_canvas_build;
	canvas->destroy = ui_canvas_destroy;
	canvas->manage_cursor = ui_canvas_manage_cursor;
	canvas->rect.w = width;
	canvas->rect.h = height;
	canvas->type = CANVAS;
	canvas->texture = SDL_CreateTexture(core->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, canvas->rect.w, canvas->rect.h);
	canvas->surface = SDL_CreateRGBSurfaceWithFormat(0, canvas->rect.w, canvas->rect.h, 32, SDL_PIXELFORMAT_ARGB8888);
	return (canvas);
}
