/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 00:50:55 by thchin            #+#    #+#             */
/*   Updated: 2017/07/12 04:30:47 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../includes/wolf3d.h"

#define KEY event.key.keysym.sym

void	cheat_event(SDL_Event event, t_env *env)
{
	int	tmp;

	if (event.type == SDL_KEYDOWN)
	{
		if (KEY == SDLK_f)
		{
			tmp = 0;
			while (tmp < NSPRITE)
			{
				env->npc[tmp].stance = STAND;
				env->npc[tmp].life = 3;
				tmp += 1;
			}
		}
		if (KEY == SDLK_g)
			env->life = 100;
	}
}

void	weapon_event(SDL_Event event, t_inventory inv, t_weapon *weapon)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (KEY == SDLK_SPACE)
			weapon->fire = 1;
		if (KEY == SDLK_1)
			weapon->weapon = 0;
		if (KEY == SDLK_2)
			weapon->weapon = 1;
		if (KEY == SDLK_3 && 1 == inv.smg)
			weapon->weapon = 2;
		if (KEY == SDLK_4 && 1 == inv.machinegun)
			weapon->weapon = 3;
		if (KEY == SDLK_r)
		{
			if (weapon->weapon == 1)
				weapon->ammo[1] = 7;
			else if (weapon->weapon == 2)
				weapon->ammo[2] = 30;
			else if (weapon->weapon == 3)
				weapon->ammo[3] = 99;
		}
	}
	if (event.type == SDL_KEYUP)
		if (KEY == SDLK_SPACE)
			weapon->fire = 0;
}

void	move_end_event(SDL_Event event, t_move *move)
{
	if (event.type == SDL_KEYUP)
	{
		if (KEY == SDLK_w)
			move->move_up = 0;
		if (KEY == SDLK_s)
			move->move_down = 0;
		if (KEY == SDLK_a)
			move->rot_left = 0;
		if (KEY == SDLK_d)
			move->rot_right = 0;
		if (KEY == SDLK_q)
			move->strafe_left = 0;
		if (KEY == SDLK_e)
			move->strafe_right = 0;
		if (KEY == SDLK_LSHIFT)
			move->speed = 2;
	}
}

void	move_start_event(SDL_Event event, t_move *move)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (KEY == SDLK_w)
			move->move_up = 1;
		if (KEY == SDLK_s)
			move->move_down = 1;
		if (KEY == SDLK_a)
			move->rot_left = 1;
		if (KEY == SDLK_d)
			move->rot_right = 1;
		if (KEY == SDLK_q)
			move->strafe_left = 1;
		if (KEY == SDLK_e)
			move->strafe_right = 1;
		if (KEY == SDLK_LSHIFT)
			move->speed = 4;
	}
}

int		key_hook(t_env *env, int *i)
{
	SDL_Event	event;

	if (1 == SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			clear_env(env);
		if (0 == env->question)
			menu_event(event, env, i);
		else
			question_event(event, env, i);
		move_start_event(event, &env->move);
		move_end_event(event, &env->move);
		weapon_event(event, env->inv, &env->weapon);
		cheat_event(event, env);
		print_img(env);
	}
	return (0);
}
