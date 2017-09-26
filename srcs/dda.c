/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 01:24:28 by thchin            #+#    #+#             */
/*   Updated: 2017/06/15 05:08:01 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../includes/wolf3d.h"

void	init_player_dda(t_env *env, t_dda *dda, int x)
{
	double	camerax;

	camerax = 2.0 * x / (double)(WIDTH) - 1;
	dda->rayposx = env->posx;
	dda->rayposy = env->posy;
	dda->raydirx = env->dirx + env->planex * camerax;
	dda->raydiry = env->diry + env->planey * camerax;
	dda->mapx = (int)dda->rayposx;
	dda->mapy = (int)dda->rayposy;
	dda->deltadistx = sqrt(1 +
			(dda->raydiry * dda->raydiry) / (dda->raydirx * dda->raydirx));
	dda->deltadisty = sqrt(1 +
			(dda->raydirx * dda->raydirx) / (dda->raydiry * dda->raydiry));
	dda->hit = 0;
}

void	calcul_step(t_dda *dda)
{
	if (dda->raydirx < 0)
	{
		dda->stepx = -1;
		dda->sidedistx = (dda->rayposx - dda->mapx) * dda->deltadistx;
	}
	else
	{
		dda->stepx = 1;
		dda->sidedistx = (dda->mapx + 1.0 - dda->rayposx) * dda->deltadistx;
	}
	if (dda->raydiry < 0)
	{
		dda->stepy = -1;
		dda->sidedisty = (dda->rayposy - dda->mapy) * dda->deltadisty;
	}
	else
	{
		dda->stepy = 1;
		dda->sidedisty = (dda->mapy + 1.0 - dda->rayposy) * dda->deltadisty;
	}
}

void	dda(t_env *env, t_dda *dda)
{
	while (dda->hit == 0)
	{
		if (dda->sidedistx < dda->sidedisty)
		{
			dda->sidedistx += dda->deltadistx;
			dda->mapx += dda->stepx;
			dda->side = 0;
		}
		else
		{
			dda->sidedisty += dda->deltadisty;
			dda->mapy += dda->stepy;
			dda->side = 1;
		}
		if (env->map[(int)dda->mapy][(int)dda->mapx] > 0)
			dda->hit = 1;
	}
}

void	calcul_walldist(t_dda *dda)
{
	if (dda->side == 0)
		dda->walldist = (dda->mapx - dda->rayposx + (1 - dda->stepx) / 2) /
			dda->raydirx;
	else
		dda->walldist = (dda->mapy - dda->rayposy + (1 - dda->stepy) / 2) /
			dda->raydiry;
}

void	calcul_height(t_env *env, t_dda dda)
{
	env->lineheight = (int)(HEIGHT / (dda.walldist));
	env->drawstart = -(env->lineheight) / 2 + HEIGHT / 2;
	if (env->drawstart < 0)
		env->drawstart = 0;
	env->drawend = env->lineheight / 2 + HEIGHT / 2;
	if (env->drawend >= HEIGHT)
		env->drawend = HEIGHT - 1;
}
