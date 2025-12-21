/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_int.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 04:12:23 by injah             #+#    #+#             */
/*   Updated: 2025/12/20 06:56:45 by injah            ###   ########.fr       */
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
# define	UI_MAX_WINDOWS					5

# define	UI_MAX_WINDOW_CHILDS			20
# define	UI_MAX_DRAGBOX_CHILDS			1
# define	UI_MAX_BUTTON_CHILDS			1
# define	UI_MAX_BOX_CHILDS				10
# define	UI_ERROR						-1
# define	UI_SUCCESS						0

typedef enum	e_widget_type
{
	WINDOW,
	BUTTON,
	DRAWABLE,
	SLIDER,
	BOX,
}				e_widget_type;

typedef enum	e_widget_state
{
	NORMAL,
	HOVERED,
	CLICKED,
	RELEASED,
	NUM_STATE
}				e_widget_state;

typedef struct	s_mouse_infos
{
	SDL_Point	position;
	SDL_Point	motion;
	bool		mouse_buttons[UI_MOUSE_BUTTON_SUPPORTED];
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
	unsigned int		window_id;
	SDL_Renderer		*renderer;
	struct s_widget		**childs;
	int					nb_child;
	struct s_widget		*parent;
	void				*data;
	e_widget_type		type;
	SDL_Rect			rect;
	SDL_Rect			absolute;
	SDL_Texture			*background;
	e_widget_state		state;
	SDL_Color			colors[NUM_STATE];
	int					outline;
	bool				is_visible;
	bool				is_dragable;
	void				(*update)(struct s_widget *widget);
	void				(*render)(struct s_widget *widget);
	void				(*destroy)(struct s_widget *widget);
	int					(*add_child)(struct s_widget *parent, struct s_widget *child);

	void				(*onclick)(struct s_widget *, int, void *);
	void				*onclick_param;
}				t_widget;

typedef struct	s_drawable_data
{
	char		*brush_path;
	SDL_Cursor	*cursor;
	SDL_Texture	*brush;
	SDL_Color	brush_color;
	SDL_Rect	brush_rect;
	float		brush_ratio;
	int			brush_size;
}				t_drawable_data;

typedef struct	s_window_data
{
	SDL_Window		*window;
	int				id;
}				t_window_data;

typedef struct	s_slider_data
{
	SDL_Point		slide_position;
	SDL_Texture		*slide_texture;
	SDL_Color		slide_color;
	SDL_Color		fill_color;
	float			value;
	int				slide_factor;
	void			(*onvaluechange)(struct s_widget *, float, void *);
	void			*onvaluechange_param;
}				t_slider_data;

typedef struct	s_button_data
{
	SDL_Texture	*text_texture;
}				t_button_data;

typedef struct	s_box_data
{
	int	dummy;
}				t_box_data;

typedef struct	s_dragbox_data
{
	int	dummy;
}				t_dragbox_data;



typedef struct	s_core
{
	t_widget				**windows;
	TTF_Font				*font;
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
void		ui_destroy_widgets(t_widget **widgets);

void		ui_set_cursor(t_core *core, SDL_Cursor *cursor);

int			ui_core_add_window(t_core *core, t_widget *window);


//WIDGET
void		ui_set_child_references(t_widget *parent, t_widget *child);


void		ui_widget_common_update(t_widget *widget);

t_widget 	**ui_new_widget_tab(int tab_len);
int			ui_add_child(t_widget *parent, t_widget *child);

t_widget	 *ui_new_widget(e_widget_type type, size_t sizeof_data);

//UTILS
SDL_Color	ui_unpack_color(unsigned int color);
void		ui_draw_outline(SDL_Renderer *renderer, SDL_Rect start_rect, int size);
void		ui_draw_background(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect rect, SDL_Color color);


SDL_Texture	*ui_new_texture(SDL_Renderer *renderer, int width, int height);





#endif
