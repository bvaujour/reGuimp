/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guimp.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 10:25:14 by injah             #+#    #+#             */
/*   Updated: 2026/01/07 17:04:11 by kipouliq         ###   ########.fr       */
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

typedef struct	s_data
{
	t_core			*core;
	int				screen_width;
	int				screen_height;
	int				test;
	t_widget		*tool_window;
	t_widget		*render_window;
	t_widget		*drawable;
	t_widget		*button;
	t_widget		*button2;
	t_widget		*text_button;
	t_widget		*box;
	t_widget		*dragbox;
	t_widget		*color_slider[NUM_COLOR];
	unsigned char	color_values[NUM_COLOR];
}				t_data;


#endif