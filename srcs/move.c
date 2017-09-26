/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 00:36:28 by thchin            #+#    #+#             */
/*   Updated: 2017/05/31 00:49:50 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../includes/wolf3d.h"

#define SPRITE env->npc[i].sprite

void	rotate_left(t_env *env, t_move move)
{
	double	tmp;

	if (move.rot_left == 1)
	{
		tmp = env->dirx;
		env->dirx = env->dirx * cos(-(move.rot_speed)) -
				env->diry * sin(-(move.rot_speed));
		env->diry = tmp * sin(-(move.rot_speed)) +
			env->diry * cos(-(move.rot_speed));
		tmp = env->planex;
		env->planex = env->planex * cos(-(move.rot_speed)) -
			env->planey * sin(-(move.rot_speed));
		env->planey = tmp * sin(-(move.rot_speed)) +
			env->planey * cos(-(move.rot_speed));
	}
}

void	rotate_right(t_env *env, t_move move)
{
	double	tmp;

	if (move.rot_right == 1)
	{
		tmp = env->dirx;
		env->dirx = env->dirx * cos(move.rot_speed) -
			env->diry * sin(move.rot_speed);
		env->diry = tmp * sin(move.rot_speed) +
			env->diry * cos(move.rot_speed);
		tmp = env->planex;
		env->planex = env->planex * cos(move.rot_speed) -
			env->planey * sin(move.rot_speed);
		env->planey = tmp * sin(move.rot_speed) +
			env->planey * cos(move.rot_speed);
	}
}

void	strafe_player(t_env *env, t_move move)
{
	if (move.strafe_right == 1)
	{
		if (0 >= env->map[(int)(env->posy)]
				[(int)(env->posx + env->planex * move.move_speed)])
			env->posx += env->planex * move.move_speed;
		if (0 >= env->map[(int)(env->posy + env->planey * move.move_speed)]
				[(int)(env->posx)])
			env->posy += env->planey * move.move_speed;
	}
	if (move.strafe_left == 1)
	{
		if (0 >= env->map[(int)(env->posy)]
				[(int)(env->posx - env->planex * move.move_speed)])
			env->posx -= env->planex * move.move_speed;
		if (0 >= env->map[(int)(env->posy - env->planey * move.move_speed)]
				[(int)(env->posx)])
			env->posy -= env->planey * move.move_speed;
	}
}

void	move_player(t_env *env, t_move move)
{
	if (move.move_up == 1)
	{
		if (0 >= env->map[(int)(env->posy)]
				[(int)(env->posx + env->dirx * move.move_speed)])
			env->posx += env->dirx * move.move_speed;
		if (0 >= env->map[(int)(env->posy + env->diry * move.move_speed)]
				[(int)(env->posx)])
			env->posy += env->diry * move.move_speed;
	}
	if (move.move_down == 1)
	{
		if (0 >= env->map[(int)(env->posy)]
				[(int)(env->posx - env->dirx * move.move_speed)])
			env->posx -= env->dirx * move.move_speed;
		if (0 >= env->map[(int)(env->posy - env->diry * move.move_speed)]
				[(int)(env->posx)])
			env->posy -= env->diry * move.move_speed;
	}
	rotate_left(env, move);
	rotate_right(env, move);
	strafe_player(env, move);
}

void	move_npc(t_env *env)
{
	int	i;

	i = 0;
	while (i < NENEMY)
	{
		if (env->npc[i].stance == MOVE)
		{
			if (0 >= env->map[(int)(SPRITE.text.y +
					env->npc[i].diry * env->npc[i].speed +
					0.5 * env->npc[i].diry)]
					[(int)(SPRITE.text.x +
					env->npc[i].dirx * env->npc[i].speed +
					0.5 * env->npc[i].dirx)])
			{
				SPRITE.text.x += env->npc[i].dirx * env->npc[i].speed;
				SPRITE.text.y += env->npc[i].diry * env->npc[i].speed;
			}
			else
			{
				env->npc[i].dirx = -env->npc[i].dirx;
				env->npc[i].diry = -env->npc[i].diry;
			}
		}
		i += 1;
	}
}
