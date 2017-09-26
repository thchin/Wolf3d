/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 08:53:08 by thchin            #+#    #+#             */
/*   Updated: 2017/05/31 00:46:25 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../includes/wolf3d.h"

#define SPRITE env->npc[env->npcorder[i]].sprite

void	in_sight(t_env *env, t_npc *npc, t_sprite *sprite)
{
	double	tmp;
	double	dirx;
	double	diry;

	dirx = env->posx - sprite->text.x;
	diry = env->posy - sprite->text.y;
	tmp = 1.0 / sqrtf(dirx * dirx + diry * diry);
	dirx *= tmp;
	diry *= tmp;
	if (npc->angle >= 34 && npc->angle <= 156 && npc->stance != DEAD &&
		npc->stance != HIT)
	{
		if (sprite->transformy > 0 && sprite->transformy < env->walldist)
		{
			npc->stance = MOVE;
			npc->dirx = dirx;
			npc->diry = diry;
		}
		else
			npc->stance = STAND;
	}
	else if (npc->stance != DEAD && npc->stance != HIT)
		npc->stance = STAND;
}

void	npc_ai(t_env *env, t_npc *npc, t_sprite *sprite)
{
	in_sight(env, npc, &npc->sprite);
	if (sprite->transformy > 0 && sprite->transformy <= 1.5 &&
		npc->stance == MOVE)
		npc->stance = SHOT;
	else if (sprite->transformy > 1.5 && npc->stance == SHOT)
		npc->stance = MOVE;
	if (sprite->transformy > 0 && sprite->transformy <= 1.5 &&
		npc->stance == SHOT && env->life > 0 &&
		env->deathtimer < 350 && env->hited == 0 && npc->anim == 2)
	{
		env->life -= 10;
		env->hurt = 1;
		env->hited = 1;
	}
	else if (env->deathtimer >= 350)
	{
		env->deathtimer = 0;
		env->hurt = 0;
		env->hited = 0;
	}
}

void	update_npc(t_env *env)
{
	int	i;

	i = 0;
	order_npc(env);
	while (i < NENEMY)
	{
		set_sprite(env, &SPRITE);
		env->npc[i].angle = get_angle(env, env->npc[i]);
		i += 1;
	}
}

void	npc_casting(t_env *env, int x)
{
	int	i;
	int	y;

	i = 0;
	while (i < NENEMY)
	{
		if (SPRITE.transformy > 0 && SPRITE.transformy < env->walldist &&
				x >= SPRITE.drawstartx && x < SPRITE.drawendx)
		{
			y = SPRITE.drawstarty;
			while (y < SPRITE.drawendy)
			{
				if (SPRITE.transformy < env->spritebuffer[y])
					get_sprite_color(env, SPRITE, x, y);
				y += 1;
			}
		}
		i += 1;
	}
}
