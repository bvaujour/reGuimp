/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_image.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 10:15:42 by injah             #+#    #+#             */
/*   Updated: 2026/01/12 15:56:43 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"


void		ui_image_event(t_widget *image)
{
	SDL_Surface	*surface;
	SDL_Texture	*texture;
	if (image->core->event.type == SDL_DROPFILE)
	{
		surface = IMG_Load(image->core->event.drop.file);
		if (surface)
		{
			texture = SDL_CreateTextureFromSurface(image->renderer, surface);
			if (texture)
			{
				SDL_SetRenderTarget(image->renderer, image->texture);
				SDL_RenderCopy(image->renderer, texture, NULL, NULL);
				SDL_SetRenderTarget(image->renderer, NULL);
				SDL_DestroyTexture(texture);
			}
			SDL_FreeSurface(surface);
		}
	}
}
void		ui_image_render(t_widget *image)
{
	SDL_RenderCopy(image->renderer, image->texture, NULL, &image->absolute);
}

void		ui_image_destroy(t_widget *image)
{
	t_image_data	*data;

	data = (t_image_data *)image->data;
	SDL_FreeSurface(data->surface);
}

t_widget	*ui_create_image(t_widget *parent, int x, int y, int width, int height)
{
	t_widget		*image;
	t_image_data	*data;

	if (parent == NULL)
		return (NULL);
	image = ui_new_widget((SDL_Rect){x, y, width, height}, IMAGE, UI_MAX_IMAGE_CHILDS);
	if (!image)
		return (NULL);
	if (ui_add_child(parent, image) != UI_SUCCESS)
		return (free(image), NULL);
	image->data = malloc(sizeof(t_image_data));
	if (!image->data)
		return (free(image), NULL);
	data = (t_image_data *)image->data;
	data->surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_ARGB8888);
	SDL_FillRect(data->surface, NULL, SDL_MapRGBA(data->surface->format, 255, 255, 255, 255));
	ui_set_widget_colors(image, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
	image->render = ui_image_render;
	image->destroy = ui_image_destroy;
	image->event = ui_image_event;
	image->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW); 
	image->texture = SDL_CreateTexture(image->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, image->rect.w, image->rect.h);
	SDL_SetTextureBlendMode(image->texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawBlendMode(image->renderer, SDL_BLENDMODE_BLEND);
	// ui_clear_image(image, 0x00000000);
	return (image);
}