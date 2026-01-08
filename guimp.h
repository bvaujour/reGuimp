/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guimp.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 10:25:14 by injah             #+#    #+#             */
/*   Updated: 2026/01/08 12:26:42 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUIMP_H
# define GUIMP_H

# include "libui/libui.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

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
	DRAW_RECT,
	DRAW_CIRCLE,
	DRAW_BRUSH,
	BUCKET,
	ERRASE,
};

typedef struct	s_data
{
	t_core			*core;
	int				screen_width;
	int				screen_height;
	t_widget		*tool_window;
	t_widget		*canvas;
	t_widget		*render_window;
	t_widget		*button;
	t_widget		*box;
	t_widget		*color_slider[NUM_COLOR];
	unsigned char	color_values[NUM_COLOR];
	enum e_tool		tool;
}				t_data;

void	draw_rect_on_image(t_img img, int start_x, int start_y, int width, int height, unsigned int color);

#endif