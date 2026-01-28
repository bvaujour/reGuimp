/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guimp.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 10:25:14 by injah             #+#    #+#             */
/*   Updated: 2026/01/28 17:42:30 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUIMP_H
# define GUIMP_H

# include "libui/libui.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>

enum	e_color
{
	RED,
	GREEN,
	BLUE,
	ALPHA,
	NUM_COLOR
};

enum	e_tool
{
	PENCIL,
	DRAW_RECT,
	DRAW_CIRCLE,
	DRAW_BRUSH,
	BUCKET,
	ERASER,
	NUM_TOOL
};

typedef struct	s_vector2
{
	int	x;
	int	y;
}				t_vector2;

typedef	struct	s_rgba
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}				t_rgba;

typedef struct	s_drawing
{
	bool		is_drawing;
	int			last_x;
	int			last_y;
	int			thickness;
	t_widget	*thickness_slider;
}				t_drawing;

typedef struct	s_data
{
	t_core			*core;
	t_widget		*button;
	int				screen_width;
	int				screen_height;
	t_widget		*tool_window;
	t_widget		*canvas;
	t_widget		*render_window;
	t_widget		*tool_buttons_box;
	t_widget 		*tool_color_box;
	t_widget		*tool_color_parameter_box;
	t_widget		*color_sliders[NUM_COLOR];
	t_widget		*tool_buttons[NUM_TOOL];
	t_widget		*tool_parameters_boxes[NUM_TOOL];
	t_widget		*tool_window_box;
	t_rgba			color;
	enum e_tool		active_tool;
	t_drawing		drawing;
	t_widget 		*text_box;
	t_widget 		*text;
	t_widget 		*tool_parameters_stacking_box;
	t_widget 		*size_box;
}				t_data;

void			draw_rect_on_image(t_img img, int start_x, int start_y, int width, int height, unsigned int color);
void 			bucket_image(t_img img, int start_x, int start_y, unsigned color);
t_rgba			unpack_color(unsigned int color);
unsigned int	pack_color(t_rgba color);
void			set_pixel(t_img img, int x, int y, unsigned int color);
unsigned int	get_pixel(t_img img, int x, int y);

void			draw_with_guimp(t_data *data, t_widget *canvas, int button, int x, int y);
void			draw_with_libui(t_data *data, t_widget *canvas, int button, int x, int y);
int				distance(int x1, int y1, int x2, int y2);
int				lerp(int a, int b, int step, int max);

void			build_tool_buttons(t_data *data);
void			on_widget_clicked(t_widget *widget, int button, int x, int y, void *param);
void			show_parameter(t_data *data, enum e_tool tool);
void			toggle_color_parameters_box(t_data *data);
#endif