/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:53:57 by bvaujour          #+#    #+#             */
/*   Updated: 2025/12/28 23:37:21 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	LIBUI_H
# define LIBUI_H

# define UIKEY_ESCAPE	27

typedef struct	s_core		t_core;
typedef struct	s_widget	t_widget;


t_core	*ui_init();

void		ui_run(t_core *core);
void		ui_quit(t_core *core);

//BUTTON
t_widget	*ui_create_button(t_widget *parent, int x, int y, int width, int height);


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





t_widget	*ui_create_drawable(t_widget *parent, int x, int y, int width, int height);
void		ui_drawable_export_jpeg(t_widget *edit_img, const char *file, int quality);
void		ui_drawable_export_png(t_widget *drawable, const char *file);
void		ui_drawable_set_brush(t_widget *drawable, const char *path);
void		ui_drawable_set_brush_size(t_widget *drawable, int size);
void		ui_drawable_set_brush_color(t_widget *drawable, char red, char green, char blue, char alpha);


t_widget	*ui_create_slider(t_widget *parent, int x, int y, int width, int height);

t_widget 	*ui_create_window(t_core *core, int x, int y, int width, int height);
t_widget	*ui_create_box(t_widget *parent, int x, int y, int width, int height);
t_widget	*ui_create_dragbox(t_widget *parent, int x, int y, int width, int height);


//BINDINGS
/*prototype should be:
void void	on_key_pressed(int key_pressed, void *param(cast to your type))*/
void		ui_bind_onkeypress(t_core *core, void (*f)(int, void *), void *param);
/*prototype should be:
void on_widget_clicked(t_widget *clicked_widget, int mouse_button_clicked, void *param(cast to your type))*/
void		ui_bind_button_onclicked(t_widget *button, void (*f)(struct s_widget *, int, void *), void *param);
/*prototype should be:
void on_slider_value_change(t_widget *changed_slider, float value, void *param(cast to your type))*/
void		ui_bind_slider_onvaluechange(t_widget *slider, void (*f)(struct s_widget *, float, void *), void *param);





#endif