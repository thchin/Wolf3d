/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 00:36:28 by thchin            #+#    #+#             */
/*   Updated: 2017/07/11 09:07:15 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../includes/wolf3d.h"

#define SPRITE env->npc[i].sprite
#define XRIGHT env->posx + env->planex * move.move_speed
#define YRIGHT env->posy + env->planey * move.move_speed
#define XLEFT env->posx - env->planex * move.move_speed
#define YLEFT env->posy - env->planey * move.move_speed
#define XUP env->posx + env->dirx * move.move_speed
#define YUP env->posy + env->diry * move.move_speed
#define XDOWN env->posx - env->dirx * move.move_speed
#define YDOWN env->posy - env->diry * move.move_speed

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
		if (0 >= env->map[(int)(env->posy)][(int)(XRIGHT)] &&
			0 == sprite_collision(env, XRIGHT, env->posy))
			env->posx += env->planex * move.move_speed;
		if (0 >= env->map[(int)(YRIGHT)][(int)(env->posx)] &&
			0 == sprite_collision(env, env->posx, YRIGHT))
			env->posy += env->planey * move.move_speed;
	}
	if (move.strafe_left == 1)
	{
		if (0 >= env->map[(int)(env->posy)][(int)(XLEFT)] &&
			0 == sprite_collision(env, XLEFT, env->posy))
			env->posx -= env->planex * move.move_speed;
		if (0 >= env->map[(int)(YLEFT)][(int)(env->posx)] &&
			0 == sprite_collision(env, env->posx, YLEFT))
			env->posy -= env->planey * move.move_speed;
	}
}

void	move_player(t_env *env, t_move move)
{
	if (move.move_up == 1)
	{
		if (0 >= env->map[(int)(env->posy)][(int)(XUP)] &&
			0 == sprite_collision(env, XUP, env->posy))
			env->posx += env->dirx * move.move_speed;
		if (0 >= env->map[(int)(YUP)][(int)(env->posx)] &&
			0 == sprite_collision(env, env->posx, YUP))
			env->posy += env->diry * move.move_speed;
	}
	if (move.move_down == 1)
	{
		if (0 >= env->map[(int)(env->posy)][(int)(XDOWN)] &&
			0 == sprite_collision(env, XDOWN, env->posy))
			env->posx -= env->dirx * move.move_speed;
		if (0 >= env->map[(int)(YDOWN)][(int)(env->posx)] &&
			0 == sprite_collision(env, env->posx, YDOWN))
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
