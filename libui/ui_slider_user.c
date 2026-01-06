/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_slider_user.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 11:58:57 by injah             #+#    #+#             */
/*   Updated: 2026/01/06 12:10:12 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

void	ui_bind_slider_onvaluechanged(t_widget *slider, void (*f)(struct s_widget *, float, void *), void *param)
{
	t_slider_data	*data;

	if (slider->type != SLIDER)
		return ;
	data = (t_slider_data *)slider->data;
	data->onvaluechange = f;
	data->onvaluechange_param = param;
	f(slider, data->value, param);
}

void	ui_slider_set_label(t_widget *slider, char *label)
{
	SDL_Surface		*surface;
	t_slider_data	*data;

	if (slider->type != SLIDER)
		return ;
	data = (t_slider_data *)slider->data;
	surface = TTF_RenderText_Solid(slider->core->font, label, (SDL_Color){255, 255, 255, 255});
	data->label = SDL_CreateTextureFromSurface(slider->renderer, surface);
	SDL_FreeSurface(surface);
}

