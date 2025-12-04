/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:53:38 by bvaujour          #+#    #+#             */
/*   Updated: 2025/11/19 14:59:18 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

int	main()
{
	t_data		data;

	data = (t_data){0};
	ui_init(&data.core);
	ui_new_window(&data.core, "lol", 0, 0, 800, 600);
	ui_run(&data.core);
	SDL_Init(SDL_INIT_VIDEO);
	// int img_flags;

	// img_flags = IMG_INIT_PNG | IMG_INIT_JPG;

	// if (TTF_Init() != 0)
	// {
	// 	fprintf(stderr, "TTF_Init error: %s\n", TTF_GetError());
	// 	return (2);
	// }
	// if ((IMG_Init(img_flags) & img_flags) != img_flags)
	// {
	// 	fprintf(stderr, "IMG_Init error: %s\n", IMG_GetError());
	// 	return (3);
	// }
	// SDL_Window *window;
	// SDL_Renderer *renderer;
	// window = SDL_CreateWindow("lol", 0, 0, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	// renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	// SDL_DestroyRenderer(renderer);
	// SDL_DestroyWindow(window);
	// TTF_Quit();
	// IMG_Quit();
	// SDL_Quit();
	
	return (0);
}
