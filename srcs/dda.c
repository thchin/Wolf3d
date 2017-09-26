/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 01:24:28 by thchin            #+#    #+#             */
/*   Updated: 2017/05/13 06:59:13 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../includes/wolf3d.h"

void	init_dda(t_env *env, int x)
{
	env->camerax = 2 * x / (double)(WIDTH) - 1;
	env->rayposx = env->posx;
	env->rayposy = env->posy;
	env->raydirx = env->dirx + env->planex * env->camerax;
	env->raydiry = env->diry + env->planey * env->camerax;
	env->mapx = (int)env->rayposx;
	env->mapy = (int)env->rayposy;
	env->deltadistx = sqrt(1 +
			(env->raydiry * env->raydiry) / (env->raydirx * env->raydirx));
	env->deltadisty = sqrt(1 +
			(env->raydirx * env->raydirx) / (env->raydiry * env->raydiry));
	env->hit = 0;
}

void	calcul_step(t_env *env)
{
	if (env->raydirx < 0)
	{
		env->stepx = -1;
		env->sidedistx = (env->rayposx - env->mapx) * env->deltadistx;
	}
	else
	{
		env->stepx = 1;
		env->sidedistx = (env->mapx + 1.0 - env->rayposx) * env->deltadistx;
	}
	if (env->raydiry < 0)
	{
		env->stepy = -1;
		env->sidedisty = (env->rayposy - env->mapy) * env->deltadisty;
	}
	else
	{
		env->stepy = 1;
		env->sidedisty = (env->mapy + 1.0 - env->rayposy) * env->deltadisty;
	}
}

void	dda(t_env *env)
{
	double	tmpx;
	double	tmpy;

	while (env->hit == 0)
	{
		if (env->sidedistx < env->sidedisty)
		{
			env->sidedistx += env->deltadistx;
			env->mapx += env->stepx;
			env->side = 0;
		}
		else
		{
			env->sidedisty += env->deltadisty;
			env->mapy += env->stepy;
			env->side = 1;
		}
		if (env->map[(int)env->mapy][(int)env->mapx] > 0)
			env->hit = 1;
	}
}

void	calcul_walldist(t_env *env)
{
	if (env->side == 0)
	{
		env->walldist = (env->mapx - env->rayposx + (1 - env->stepx) / 2) /
			env->raydirx;
	}
	else
		env->walldist = (env->mapy - env->rayposy + (1 - env->stepy) / 2) /
			env->raydiry;
}

void	calcul_height(t_env *env)
{
	env->lineheight = (int)(HEIGHT / (env->walldist));
	env->drawstart = -(env->lineheight) / 2 + HEIGHT / 2;
	if (env->drawstart < 0)
		env->drawstart = 0;
	env->drawend = env->lineheight / 2 + HEIGHT / 2;
	if (env->drawend >= HEIGHT)
		env->drawend = HEIGHT - 1;
}
