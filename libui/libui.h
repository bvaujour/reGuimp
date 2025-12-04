/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:53:57 by bvaujour          #+#    #+#             */
/*   Updated: 2025/12/04 16:58:41 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	LIBUI_H
# define LIBUI_H

# include <stdio.h>
# include <stdbool.h>
# include "SDL/include/SDL2/SDL.h"
# include "SDL_ttf/include/SDL2/SDL_ttf.h"
# include "SDL_image/include/SDL2/SDL_image.h"

# define	UI_BLUE							(SDL_Color){0, 150, 200, 255}
# define	UI_LIGHT_GREY					(SDL_Color){150, 150, 150, 255}
# define	UI_DARK_GREY					(SDL_Color){70, 70, 70, 255}
# define	UI_BLACK 						(SDL_Color){0, 0, 0, 255}
# define	UI_WHITE 						(SDL_Color){255, 255, 255, 255}

# define	UI_THEME1_BOX_COLOR				(SDL_Color){60, 60, 60, 255}
# define	UI_THEME1_WINDOW_COLOR			(SDL_Color){90, 90, 90, 255}
# define	UI_THEME1_BUTTON_DEFAULT_COLOR	(SDL_Color){150, 150, 150, 255}
# define	UI_THEME1_BUTTON_HOVERED_COLOR	(SDL_Color){130, 130, 130, 255}
# define	UI_THEME1_BUTTON_CLICKED_COLOR	(SDL_Color){100, 100, 100, 255}
# define	UI_THEME1_FONT					"libui/fonts/Roboto/Roboto_Condensed-Black.ttf"

typedef struct	s_window_data
{
	SDL_Renderer	*renderer;
	SDL_Window		*window;
}				t_window_data;

typedef struct	s_widget
{
	struct s_widget		**childs;
	struct s_widget		*parent;
	void				*widget_data;
	void				(*build)(struct s_widget *widget);
	void				(*update)(struct s_widget *widget);
	void				(*render)(struct s_widget *widget);
	void				(*destroy)(struct s_widget *widget);
}				t_widget;

typedef struct	s_core
{
	t_widget	**widgets;
	bool		is_running;
}				t_core;

void		ui_destroy_widgets(t_widget **widgets);
t_widget	*ui_new_widget(size_t widget_data_alloc_size);


void		ui_window_destroy(t_widget *window);
int			ui_init(t_core *core);
void		ui_run(t_core *core);
t_widget	*ui_new_window(t_core *core, const char *title, int x, int y, int w, int h);
void		ui_event(t_core *core);



#endif