/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_int.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 04:12:23 by injah             #+#    #+#             */
/*   Updated: 2026/01/08 12:20:28 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	LIBUI_INT_H
# define LIBUI_INT_H

# include <stdio.h>
# include "libui.h"
# include "libft.h"
# include <stdbool.h>
# include <SDL2/SDL.h>
# include "SDL_ttf/include/SDL2/SDL_ttf.h"
# include "SDL_image/include/SDL2/SDL_image.h"
# include <math.h>

# define	UI_MAX_WINDOWS					5
# define	UI_MAX_WINDOW_CHILDS			20
# define	UI_MAX_CANVAS_CHILDS			0
# define	UI_MAX_DRAGBOX_CHILDS			1
# define	UI_MAX_BUTTON_CHILDS			1
# define	UI_MAX_BOX_CHILDS				10
# define	UI_MAX_DRAWABLE_CHILDS			0
# define	UI_MAX_SLIDER_CHILDS			0
# define	UI_ERROR						-1
# define	UI_SUCCESS						0

typedef enum	e_widget_type
{
	WINDOW,
	CANVAS,
	BUTTON,
	DRAWABLE,
	DRAGBOX,
	SLIDER,
	BOX,
}				e_widget_type;

typedef enum	e_widget_state
{
	HOVERED,
	NORMAL,
	CLICKED,
	NUM_STATE
}				e_widget_state;

typedef struct	s_mouse_infos
{
	SDL_Point	position;
	SDL_Point	motion;
	Uint32 		mouse_state;
	SDL_Cursor	*arrow;
	SDL_Cursor	*hand;
	SDL_Cursor	*crosshair;
	SDL_Cursor	*current_cursor;
}				t_mouse_infos;

typedef struct	s_image_data
{
	Uint32	*pixels;
	int		width;
	int		height;
}				t_image_data;


typedef struct	s_widget
{
	struct s_core		*core;
	SDL_Renderer		*renderer;
	struct s_widget		**childs;
	int					max_child;
	int					nb_child;
	struct s_widget		*parent;
	void				*data;
	e_widget_type		type;
	SDL_Rect			rect;
	SDL_Rect			absolute;
	SDL_Texture			*texture;
	e_widget_state		state;
	SDL_Color			colors[NUM_STATE];
	bool				is_visible;
	bool				is_dragable;
	void				(*event)(struct s_widget *widget, SDL_Event event);
	void				(*update)(struct s_widget *widget);
	void				(*render)(struct s_widget *widget);
	void				(*destroy)(struct s_widget *widget);
	void				(*build)(struct s_widget *widget);
	void				(*onclicked)(struct s_widget *, int, int, int, void *);
	void				*onclicked_param;
}				t_widget;

typedef struct	s_drawable_data
{
	SDL_Cursor	*cursor;
	SDL_Texture	*brush;
	SDL_Color	brush_color;
	SDL_Rect	brush_rect;
	float		brush_ratio;
	int			brush_size;
	SDL_Texture	*layer;
	SDL_Texture	*snapshot;
}				t_drawable_data;

typedef struct	s_canvas_data
{
	SDL_Surface	*surface;
}				t_canvas_data;

typedef struct	s_window_data
{
	SDL_Window		*window;
	unsigned int	id;
}				t_window_data;

typedef struct	s_slider_data
{
	SDL_Texture		*label;
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
	SDL_Texture	*label;
	void		(*onclicked)(struct s_widget *, int, void *);
	void		*onclicked_param;
}				t_button_data;


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
void 		ui_destroy_widget(t_widget *widget);

void		ui_set_cursor(t_core *core, SDL_Cursor *cursor);

int			ui_core_add_window(t_core *core, t_widget *window);


//WIDGET

SDL_Rect	ui_get_absolute_rect(t_widget *widget);
void		ui_widget_manage_state(t_widget *widget);
int			ui_add_child(t_widget *widget, t_widget *child);
t_widget 	**ui_new_widget_tab(int tab_len);
int			ui_add_child(t_widget *parent, t_widget *child);
void		ui_widget_event(t_widget *widget, SDL_Event event);

t_widget	*ui_new_widget(SDL_Rect rect, e_widget_type type, int max_child);
void		ui_widget_outline(t_widget *widget);
void		ui_widget_drag(t_widget *widget);


//UTILS
SDL_Color	ui_unpack_color(unsigned int color);



SDL_Texture	*ui_new_texture(SDL_Renderer *renderer, int width, int height, SDL_Color color_mod);



void 	ui_bucket_image(t_image_data img, int start_x, int start_y, Uint32 color);
void	 ui_draw_circle_on_image(t_image_data img, SDL_Point center, int radius, int thickness, Uint32 color);
void	ui_draw_disk_on_image(t_image_data img, SDL_Point center, int radius, Uint32 color);
void	ui_draw_rect_on_image(t_image_data img, SDL_Rect rect, Uint32 color);
void	ui_set_render_target_pixels(SDL_Renderer *renderer, SDL_Texture *texture, Uint32 *pixels);
int		ui_get_render_target_image_data(SDL_Renderer *renderer, SDL_Texture *texture, t_image_data *img);



#endif
