/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 06:09:24 by thchin            #+#    #+#             */
/*   Updated: 2017/06/15 06:11:10 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	init_inv(t_env *env)
{
	env->inv.key = 0;
	env->inv.smg = 0;
	env->inv.machinegun = 0;
}

void	init_player(t_env *env)
{
	env->posx = 2;
	env->posy = 11.5;
	env->dirx = 1.0;
	env->diry = 0;
	env->planex = 0;
	env->planey = 0.66;
	env->hurt = 0;
}

void	update_inventory(t_env *env, t_type type)
{
	if (type == SMG)
		env->inv.smg = 1;
	else if (type == MACHINEGUN)
		env->inv.machinegun = 1;
	else if (type == FOOD)
	{
		env->life += 30;
		env->life = env->life > 100 ? 100 : env->life;
	}
	else if (type == HEALTH)
	{
		env->life += 50;
		env->life = env->life > 100 ? 100 : env->life;
	}
	else if (type == WELL)
		env->life = 100;
	else if (type == KEY)
		env->inv.key = 1;
}
