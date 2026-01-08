/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_button_user.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 11:56:25 by injah             #+#    #+#             */
/*   Updated: 2026/01/08 12:52:37 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

void	ui_button_set_label(t_widget *button, char *label)
{
	SDL_Surface		*surface;
	t_button_data	*data;

	if (button->type != BUTTON)
		return ;
	data = (t_button_data *)button->data;
	surface = TTF_RenderText_Solid(button->core->font, label, (SDL_Color){255, 255, 255, 255});
	printf("text w = %d\ntext h = %d\n", surface->w, surface->h);
	data->label = SDL_CreateTextureFromSurface(button->renderer, surface);
	SDL_FreeSurface(surface);
}
