/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_window.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 12:53:46 by injah             #+#    #+#             */
/*   Updated: 2025/12/04 16:57:26 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

static int	ui_add_window(t_core *core, t_widget *window)
{
	int			i;
	t_widget	**ui_new_window_tab;

	if (core->widgets == NULL)
	{
		core->widgets = malloc(sizeof(t_widget *) * 2);
		core->widgets[0] = window;
		core->widgets[1] = NULL;
	}
	else
	{
		i = 0;
		while (core->widgets[i])
			i++;
		ui_new_window_tab = malloc(sizeof(t_widget *) * (i + 1));
		if (ui_new_window_tab == NULL)
			return (-1);
		i = 0;
		while (core->widgets[i])
		{
			ui_new_window_tab[i] = core->widgets[i];
			i++;
		}
		free(core->widgets);
		core->widgets = ui_new_window_tab;
	}
	return (0);
}

void		ui_window_render(t_widget *window)
{
	t_window_data	*data;
	
	data = (t_window_data *)window->widget_data;
	SDL_SetRenderDrawColor(data->renderer, 255, 0, 0, 0);
	SDL_RenderClear(data->renderer);
	SDL_RenderPresent(data->renderer);
}

t_widget	*ui_new_window(t_core *core, const char *title, int x, int y, int w, int h)
{
	t_widget		*widget;
	t_window_data	*window_data;

	widget = ui_new_widget(sizeof(t_window_data));
	if (widget == NULL)
		return (NULL);
	window_data = (t_window_data *)widget->widget_data;
	widget->destroy = ui_window_destroy;
	widget->render = ui_window_render;
	window_data->window = SDL_CreateWindow(title, x, y, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!window_data->window)
	{
        fprintf(stderr, "SDL_CreateWindow error: %s\n", SDL_GetError());
		free(widget);
		free(window_data);
        return (NULL);
    }
	window_data->renderer = SDL_CreateRenderer(window_data->window, -1, SDL_RENDERER_ACCELERATED);
    if (!window_data->renderer)
	{
        fprintf(stderr, "SDL_CreateRenderer error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window_data->window);
		free(widget);
		free(window_data);
        return (NULL);
    }
	ui_add_window(core, widget);
    return (widget);
}

void	ui_window_destroy(t_widget *window)
{
	t_window_data	*window_data;

	window_data = (t_window_data *)window->widget_data;
	SDL_DestroyRenderer(window_data->renderer);
	SDL_DestroyWindow(window_data->window);
	ui_destroy_widgets(window->childs);
	free(window_data);
	free(window);
}