/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_drawableable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 21:16:05 by injah             #+#    #+#             */
/*   Updated: 2025/12/15 03:39:13 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

void	ui_drawable_stroke(t_widget *drawable, int x, int y)
{
	t_drawable_data		*data;

	data = (t_drawable_data *)drawable->data;
	SDL_SetSurfaceBlendMode(data->brush, SDL_BLENDMODE_MUL);
	SDL_SetSurfaceColorMod(data->brush, data->brush_color.r, data->brush_color.g, data->brush_color.b);
	SDL_SetSurfaceAlphaMod(data->brush, data->brush_color.a);
	SDL_BlitScaled(data->brush, NULL, drawable->surface, &(SDL_Rect){x - data->brush_size / 2, y - data->brush_size / 2, data->brush_size, data->brush_size});
}

//quality: [0:100]
void	ui_drawable_export_jpg(t_widget *drawable, const char *file, int quality)
{
	IMG_SaveJPG(drawable->surface, file, quality);
}

void	ui_drawable_export_png(t_widget *drawable, const char *file)
{
	IMG_SavePNG(drawable->surface, file);
}

void		ui_drawable_build_brush(t_widget *drawable)
{
	SDL_Surface			*surface;
	t_drawable_data		*data;

	data = (t_drawable_data *)drawable->data;
	if (data->cursor)
		SDL_FreeCursor(data->cursor);
	surface = SDL_CreateRGBSurfaceWithFormat(0, data->brush_size, data->brush_size, 32, SDL_PIXELFORMAT_ARGB8888);
	ui_draw_outline(surface, (SDL_Color){0, 0, 0, 255}, 1);
	SDL_SetSurfaceColorMod(data->brush, data->brush_color.r, data->brush_color.g, data->brush_color.b);
	SDL_BlitScaled(data->brush, NULL, surface, NULL);
	data->cursor = SDL_CreateColorCursor(surface, data->brush_size / 2, data->brush_size / 2);
	SDL_FreeSurface(surface);
}

void		ui_drawable_set_brush(t_widget *drawable, const char *path)
{
	t_drawable_data		*data;

	data = (t_drawable_data *)drawable->data;
	if (data->brush)
		SDL_FreeSurface(data->brush);
	data->brush = IMG_Load(path);
	ui_drawable_build_brush(drawable);
}

void		ui_drawable_set_brush_size(t_widget *drawable, int size)
{
	t_drawable_data		*data;

	data = (t_drawable_data *)drawable->data;
	data->brush_size = size;
	ui_drawable_build_brush(drawable);
}

void		ui_drawable_set_brush_color(t_widget *drawable, char red, char green, char blue, char alpha)
{
	t_drawable_data		*data;

	data = (t_drawable_data *)drawable->data;
	data->brush_color.r = red;
	data->brush_color.g = green;
	data->brush_color.b = blue;
	data->brush_color.a = alpha;
	ui_drawable_build_brush(drawable);
}

static void	ui_drawable_render(t_widget *drawable)
{
	SDL_BlitSurface(drawable->surface, NULL, drawable->parent->surface, &drawable->rect);

}

static void	ui_drawable_update(t_widget *drawable)
{
	t_core		*core;

	core = drawable->core;
	ui_widget_manage_state_and_click(drawable);
	if (drawable->state == UI_CLICKED_STATE)
	{
		ui_drawable_stroke(drawable, core->mouse.position.x - drawable->rect.x, core->mouse.position.y - drawable->rect.y);
	}
}

static void	ui_drawable_manage_cursor(t_widget *drawable)
{
	(void)drawable;
	t_drawable_data		*data;

	data = (t_drawable_data *)drawable->data;
	ui_set_cursor(drawable->core, data->cursor);
}

static void	ui_drawable_destroy(t_widget *drawable)
{
	t_drawable_data		*data;

	data = (t_drawable_data *)drawable->data;
	if (data->cursor)
		SDL_FreeCursor(data->cursor);
	if (data->brush)
		SDL_FreeSurface(data->brush);
	SDL_FreeSurface(drawable->surface);
	free(data->brush_path);
}

static void	ui_drawable_build(t_widget *drawable)
{
	SDL_Color	color;
	SDL_Surface	*surface;
	t_drawable_data		*data;

	data = (t_drawable_data *)drawable->data;
	color = drawable->colors[drawable->state];
	surface = SDL_CreateRGBSurfaceWithFormat(0, drawable->rect.w, drawable->rect.h, 32, SDL_PIXELFORMAT_ARGB8888);
	if (!surface)
		return ;
	SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a));
	drawable->surface = surface;
	ui_drawable_set_brush(drawable, data->brush_path);

}

t_widget	*ui_create_drawable(t_core *core, int x, int y, int width, int height)
{
	t_widget			*drawable;
	t_drawable_data		*data;

	drawable = ui_init_widget(core, x, y, width, height);
	data = malloc(sizeof(t_drawable_data));
	*data = (t_drawable_data){0};
	drawable->data = data; 
	drawable->type = DRAWABLE;
	drawable->outline = 2;
	drawable->colors[UI_OUTLINE_COLOR] = (SDL_Color){0, 0, 0, 100};
	drawable->colors[UI_NORMAL_COLOR] = (SDL_Color){255, 255, 255, 255};
	drawable->colors[UI_HOVERED_COLOR] = (SDL_Color){100, 100, 100, 255};
	drawable->colors[UI_CLICKED_COLOR] = (SDL_Color){150, 150, 150, 255};
	data->brush_color = (SDL_Color){0, 0, 0, 255};
	data->brush_size = 20;
	drawable->render = ui_drawable_render;
	drawable->update = ui_drawable_update;
	drawable->destroy = ui_drawable_destroy;
	drawable->build = ui_drawable_build;
	drawable->manage_cursor = ui_drawable_manage_cursor;
	data->brush_path = ft_strdup("libui/assets/brushs/brush_base.png");
	ui_drawable_build(drawable);
	return (drawable);
}