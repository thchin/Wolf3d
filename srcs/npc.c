/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 08:53:08 by thchin            #+#    #+#             */
/*   Updated: 2017/07/12 04:33:48 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../includes/wolf3d.h"

#define SPRITE env->npc[i].sprite

void	init_npc_dda(t_sprite *sprite, t_dda *dda, double dirx, double diry)
{
	dda->rayposx = sprite->text.x;
	dda->rayposy = sprite->text.y;
	dda->raydirx = dirx;
	dda->raydiry = diry;
	dda->mapx = (int)dda->rayposx;
	dda->mapy = (int)dda->rayposy;
	dda->deltadistx = sqrtf(1 +
			(dda->raydiry * dda->raydiry) / (dda->raydirx * dda->raydirx));
	dda->deltadisty = sqrtf(1 +
			(dda->raydirx * dda->raydirx) / (dda->raydiry * dda->raydiry));
	dda->hit = 0;
}

void	in_sight(t_env *env, t_npc *npc, t_sprite *sprite)
{
	double	dirx;
	double	diry;
	t_dda	tmp;

	dirx = env->posx - sprite->text.x;
	diry = env->posy - sprite->text.y;
	norm_vec2f(&dirx, &diry);
	if (npc->angle >= 34 && npc->angle <= 156 && npc->stance != DEAD &&
			npc->stance != HIT)
	{
		init_npc_dda(sprite, &tmp, dirx, diry);
		calcul_step(&tmp);
		dda(env, &tmp);
		calcul_walldist(&tmp);
		if (sprite->dist > 0 && sprite->dist < tmp.walldist)
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
	if (sprite->dist > 0 && sprite->dist <= 1.5 &&
			npc->stance == MOVE)
		npc->stance = SHOT;
	else if (sprite->dist > 1.5 && npc->stance == SHOT)
		npc->stance = MOVE;
	if (sprite->dist > 0 && sprite->dist <= 1.5 &&
			npc->stance == SHOT && env->life > 0 &&
			env->deathtimer < 350 && env->hurt == 0 && npc->anim == 2)
	{
		env->life -= 10;
		env->hurt = 1;
	}
	else if (env->deathtimer >= 350)
	{
		env->deathtimer = 0;
		env->hurt = 0;
	}
}

void	update_npc(t_env *env)
{
	int	i;

	i = 0;
	order_npc(env);
	while (i < NENEMY)
	{
		get_textbox(env, &SPRITE);
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
		if (SPRITE.transformy > 0 && SPRITE.transformy < env->dda.walldist &&
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
