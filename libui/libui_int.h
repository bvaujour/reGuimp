/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_int.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 04:12:23 by injah             #+#    #+#             */
/*   Updated: 2025/12/17 13:45:05 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	LIBUI_INT_H
# define LIBUI_INT_H

# include <stdio.h>
# include "libui.h"
# include "libft.h"
# include <stdbool.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_image.h>
// # include "SDL_ttf/include/SDL2/SDL_ttf.h"
// # include "SDL_image/include/SDL2/SDL_image.h"

# define	UI_MOUSE_BUTTON_SUPPORTED		10
# define	UI_MAX_PATH_LENGTH				1024
# define	UI_THEME1_FONT					"libui/fonts/Roboto/Roboto_Condensed-Black.ttf"

# define	UI_MAX_CANVAS_CHILDS			30
# define	UI_MAX_BUTTON_CHILDS			0

typedef enum	e_widget_type
{
	CANVAS,
	BUTTON,
	DRAWABLE,
	SLIDER,
}				e_widget_type;

typedef enum	e_widget_state
{
	UI_NORMAL_STATE,
	UI_HOVERED_STATE,
	UI_CLICKED_STATE,
}				e_widget_state;

typedef enum	e_widget_colors
{
	UI_NORMAL_COLOR,
	UI_HOVERED_COLOR,
	UI_CLICKED_COLOR,
	UI_OUTLINE_COLOR,
	UI_NUM_OF_WIDGET_COLORS,
}				e_widget_colors;

typedef struct	s_mouse_infos
{
	SDL_Point	position;
	SDL_Point	motion;
	bool		mouse_buttons[UI_MOUSE_BUTTON_SUPPORTED];
	int			last_click;
	SDL_Cursor	*arrow;
	SDL_Cursor	*hand;
	SDL_Cursor	*crosshair;
	SDL_Cursor	*current_cursor;
}				t_mouse_infos;

typedef struct	s_user_binding
{
	void	(*function)();
	void	*param;
}				t_user_binding;

typedef struct	s_widget
{
	struct s_core		*core;
	struct s_widget		**childs;
	int					nb_childs;
	int					max_childs;
	struct s_widget		*parent;
	void				*data;
	e_widget_type		type;
	SDL_Rect			rect;
	SDL_Surface			*surface;
	SDL_Texture			*texture;
	e_widget_state		state;
	SDL_Color			colors[UI_NUM_OF_WIDGET_COLORS];
	int					outline;
	bool				is_dragable;
	void				(*build)(struct s_widget *widget);
	void				(*update)(struct s_widget *widget);
	void				(*render)(struct s_widget *widget);
	void				(*destroy)(struct s_widget *widget);
	void				(*manage_cursor)(struct s_widget *widget);

	void				(*onclick)(struct s_widget *, int, void *);
	void				*onclick_param;
}				t_widget;

typedef struct	s_drawable_data
{
	char		*brush_path;
	SDL_Cursor	*cursor;
	SDL_Surface	*brush;
	SDL_Color	brush_color;
	int			brush_size;
}				t_drawable_data;

typedef struct	s_canvas_data
{
	int	dummy;
}				t_canvas_data;

typedef struct	s_slider_data
{
	SDL_Rect		slide_cursor_rect;
	void			(*onvaluechange)(struct s_widget *, float, void *);
	void			*onvaluechange_param;
}				t_slider_data;

typedef struct	s_button_data
{
	int	dummy;
}				t_button_data;

typedef struct	s_core
{
	t_widget				*canvas;
	SDL_Renderer			*renderer;
	SDL_Window				*window;
	void					(*onkeypress)(int, void *);
	void					*onkeypress_param;
	t_mouse_infos			mouse;
	SDL_Event				event;
	t_widget				*dragged_widget;
	t_widget 				*focused_widget;
	bool					is_running;
}				t_core;

//ENGINE
void		ui_destroy(t_core *core);
void		ui_destroy_widget_and_childs(t_widget *widget);

t_widget 	*ui_create_canvas(t_core *core, int width, int height);
void		ui_set_cursor(t_core *core, SDL_Cursor *cursor);



//WIDGET
int			ui_widget_add_child(t_widget *parent, t_widget *child);

void		ui_widget_common_update(t_widget *widget);
void		ui_widget_clear(t_widget *widget);
void		ui_widget_manage_state_and_click(t_widget *widget);

t_widget	*ui_init_widget(t_core *core, int x, int y, int width, int height);

//UTILS
SDL_Color	ui_unpack_color(unsigned int color);
SDL_Point	ui_get_absolute_position(t_widget *widget);
bool		ui_point_in_widget(t_widget *widget, SDL_Point point);
SDL_Rect	ui_draw_outline(SDL_Surface *surface, SDL_Color color, int size);





#endif
