/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 05:59:16 by thchin            #+#    #+#             */
/*   Updated: 2017/06/15 06:08:10 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../includes/wolf3d.h"

int		npc_collision(t_env *env, double posx, double posy)
{
	int		i;
	double	tmpx;
	double	tmpy;
	double	dist;

	i = 0;
	while (i < NENEMY)
	{
		tmpx = posx - env->npc[i].sprite.text.x;
		tmpy = posy - env->npc[i].sprite.text.y;
		dist = sqrtf(tmpx * tmpx + tmpy * tmpy);
		if (env->npc[i].stance != DEAD && dist <= 0.3)
			return (1);
		i += 1;
	}
	return (0);
}

int		sprite_collision(t_env *env, double posx, double posy)
{
	int		i;
	double	tmpx;
	double	tmpy;
	double	dist;

	i = 0;
	while (i < NSPRITE)
	{
		tmpx = posx - env->sprite[i].text.x;
		tmpy = posy - env->sprite[i].text.y;
		dist = sqrtf(tmpx * tmpx + tmpy * tmpy);
		if (env->sprite[i].text.text != 10 && dist <= 0.5)
			return (1);
		i += 1;
	}
	if (1 == npc_collision(env, posx, posy))
		return (1);
	return (0);
}
