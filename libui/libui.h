/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:53:57 by bvaujour          #+#    #+#             */
/*   Updated: 2026/01/08 16:07:14 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	LIBUI_H
# define LIBUI_H

# define UIKEY_ESCAPE	27

typedef struct	s_core		    t_core;
typedef struct	s_widget	    t_widget;
typedef struct  s_properties    t_properties;
typedef struct	s_img
{
	unsigned int	*pixels;
	int				width;
	int				height;
}				t_img;

//CORE

t_core		*ui_init();
void		ui_run(t_core *core);
void		ui_quit(t_core *core);
/*prototype should be:
void on_slider_value_change(t_widget *changed_slider, float value, void *param(cast to your type))*/
void		ui_bind_slider_onvaluechanged(t_widget *slider, void (*f)(struct s_widget *, float, void *), void *param);

//BUTTON

t_widget	*ui_create_button(t_widget *parent, int x, int y, int width, int height);
void		ui_button_set_label(t_widget *button, char *label);

//WIDGET

void		ui_set_widget_position(t_widget *widget, int x, int y);
void		ui_set_widget_size(t_widget *widget, int width, int height);
void		ui_set_widget_position_and_size(t_widget *widget, int x, int y, int width, int height);
int			ui_set_widget_texture(t_widget *widget, const char *path);
void		ui_set_widget_colors(t_widget *widget, unsigned int normal, unsigned int hovered, unsigned int clicked);
void		ui_set_widget_visibility(t_widget *widget, int new_visibility);
int			ui_get_widget_visibility(t_widget *widget);
void		ui_toggle_widget_visibility(t_widget *widget);
void		ui_get_screen_size(int *screen_width, int *screen_height);


//TEXT

t_widget    *ui_create_textbox(t_widget *widget, t_properties *properties);

//WINDOW

t_widget 	*ui_create_window(t_core *core, int x, int y, int width, int height);

//BOX

t_widget	*ui_create_box(t_widget *parent, int x, int y, int width, int height);

//SLIDER

t_widget	*ui_create_slider(t_widget *parent, int x, int y, int width, int height);
void		ui_slider_set_label(t_widget *slider, char *label);
/*prototype should be:
void void	on_key_pressed(int key_pressed, void *param(cast to your type))*/
void		ui_bind_onkeypress(t_core *core, void (*f)(int, void *), void *param);

t_img		ui_image_get_img(t_widget *image);
t_widget	*ui_create_image(t_widget *parent, int x, int y, int width, int height);

/*prototype should be:
void	function(t_widget *widget, int button, int x, int y, void *param)*/
void	ui_widget_bind_onclicked(t_widget *widget, void (*f)(struct s_widget *, int, int, int, void *), void *param);;


#endif