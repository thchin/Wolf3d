/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 04:00:28 by thchin            #+#    #+#             */
/*   Updated: 2017/06/02 09:12:04 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <SDL/SDL_ttf.h>
#include "../includes/wolf3d.h"

void	init_player(t_env *env)
{
	env->posx = 2;
	env->posy = 11.5;
	env->dirx = 1.0;
	env->diry = 0;
	env->planex = 0;
	env->planey = 0.66;
	env->hited = 0;
}

void	init_move(t_move *move)
{
	move->move_speed = 0.1;
	move->rot_speed = 0.1;
	move->move_up = 0;
	move->move_down = 0;
	move->rot_left = 0;
	move->rot_right = 0;
	move->strafe_left = 0;
	move->strafe_right = 0;
}

void	init_sdl(t_env *env)
{
	if (0 != SDL_Init(SDL_INIT_EVERYTHING))
		clear_env(env);
	TTF_Init();
	env->screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE);
	if (NULL == env->screen)
		clear_env(env);
	SDL_WM_SetCaption("wolf3d", NULL);
}

void	init_game(t_env *env)
{
	init_player(env);
	init_sprite(env);
	init_npc(env);
	init_weapon(&env->weapon);
	init_move(&env->move);
	env->time = 0;
	env->old_time = 0;
	env->frametime = 1.0;
	env->accumtime = 0;
	env->deathtimer = 0;
	env->life = 50;
	env->debug = 0;
	env->screen_menu = 0;
	env->ingame = 0;
	env->dead = 0;
}

t_env	*init_env(void)
{
	t_env	*env;
	int		i;

	env = NULL;
	if (NULL == (env = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	init_sdl(env);
	init_texture(env);
	init_hud(env, &env->hud);
	init_font_menu(env);
	init_game(env);
	return (env);
}
