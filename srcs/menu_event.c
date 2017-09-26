/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 09:16:13 by thchin            #+#    #+#             */
/*   Updated: 2017/06/02 09:17:50 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL/SDL.h>
#include "../includes/wolf3d.h"

#define KEY event.key.keysym.sym

void	move_menu_event(SDL_Event event, t_env *env, int *i)
{
	if (KEY == SDLK_DOWN)
	{
		if (0 == *i)
			*i = (1 == env->ingame) ? 1 : 2;
		else if (1 == *i)
			*i = 2;
		else if (2 == *i)
			*i = 0;
	}
	if (KEY == SDLK_UP)
	{
		if (0 == *i)
			*i = 2;
		else if (1 == *i)
			*i = 0;
		else if (2 == *i)
			*i = (1 == env->ingame) ? 1 : 0;
	}
}

void	menu_event(SDL_Event event, t_env *env, int *i)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (KEY == SDLK_ESCAPE)
		{
			if (env->screen_menu == 0)
				clear_env(env);
			env->screen_menu = 0;
			if (env->life > 0)
				*i = 1;
		}
		if (KEY == SDLK_RETURN)
		{
			if (0 == *i)
			{
				init_game(env);
				env->screen_menu = 1;
				env->ingame = 1;
			}
			else if (1 == *i)
				env->screen_menu = 1;
			else if (2 == *i)
				clear_env(env);
		}
		move_menu_event(event, env, i);
	}
}
