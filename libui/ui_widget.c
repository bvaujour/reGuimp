/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_widget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:28:16 by injah             #+#    #+#             */
/*   Updated: 2025/11/18 16:31:28 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	ui_destroy_widgets(t_widget **widgets)
{
	int	i;

	i = 0;
	if (widgets == NULL)
		return ;
	while (widgets[i])
	{
		if (widgets[i]->destroy)
			widgets[i]->destroy(widgets[i]);
		i++;
	}
	free(widgets);
}

static void	ui_init_widget(t_widget *widget)
{
	widget->build = NULL;
	widget->childs = NULL;
	widget->destroy = NULL;
	widget->parent = NULL;
	widget->update = NULL;
	widget->render = NULL;
	widget->widget_data = NULL;
}

t_widget	*ui_new_widget(size_t widget_data_alloc_size)
{
	t_widget		*widget;

	widget = malloc(sizeof(t_widget));
	if (widget == NULL)
		return (NULL);
	ui_init_widget(widget);
	widget->widget_data = malloc(widget_data_alloc_size);
	if (widget->widget_data == NULL)
	{
		free(widget);
		return (NULL);
	}
	return (widget);
}