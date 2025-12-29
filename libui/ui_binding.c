/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_binding.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 22:39:51 by injah             #+#    #+#             */
/*   Updated: 2025/12/28 23:36:07 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui_int.h"

void	ui_bind_onkeypress(t_core *core, void (*f)(int, void *), void *param)
{
	core->onkeypress = f;
	core->onkeypress_param = param;
}

void	ui_bind_button_onclicked(t_widget *button, void (*f)(struct s_widget *, int, void *), void *param)
{
	t_button_data	*data;
	if (button == NULL)
	{
		printf("Error: ui_bind_button_onclicked used on null widget\n");
		return ;
	}
	if (button->type != BUTTON)
		printf("Error: ui_bind_button_onclicked used on wrong widget\n");
	data = button->data;
	data->onclicked = f;
	data->onclicked_param = param;
}

void	ui_bind_slider_onvaluechange(t_widget *slider, void (*f)(struct s_widget *, float, void *), void *param)
{
	t_slider_data	*data;

	if (slider->type != SLIDER)
		return ;
	data = (t_slider_data *)slider->data;
	data->onvaluechange = f;
	data->onvaluechange_param = param;
}