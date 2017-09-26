/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_npc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 06:17:25 by thchin            #+#    #+#             */
/*   Updated: 2017/05/31 01:01:34 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../includes/wolf3d.h"

#define NPC env->npc[i]
#define SPRITE npc->sprite

void	anime_death(t_env *env, t_npc *npc)
{
	SPRITE.textx = 0;
	SPRITE.texty = 65 * 5;
	if (npc->anim == 0)
		npc->anim = (npc->deathtimer >= 350) ? 1 : 0;
	else if (npc->anim == 1)
	{
		SPRITE.textx = 65;
		npc->anim = (npc->deathtimer >= 350) ? 2 : 1;
	}
	else if (npc->anim == 2)
	{
		SPRITE.textx = 65 * 2;
		npc->anim = (npc->deathtimer >= 350) ? 3 : 2;
	}
	else if (npc->anim == 3)
	{
		SPRITE.textx = 65 * 3;
		npc->anim = (npc->deathtimer >= 350) ? 4 : 3;
	}
	else if (npc->anim == 4)
		SPRITE.textx = 65 * 4;
}

void	anime_move(t_env *env, t_npc *npc, double angle)
{
	SPRITE.texty = 0;
	SPRITE.textx = get_direction(angle);
	if (npc->anim == 0)
		npc->anim = (npc->deathtimer >= 350) ? 1 : 0;
	else if (npc->anim == 1)
	{
		SPRITE.texty = 65;
		npc->anim = (npc->deathtimer >= 350) ? 2 : 1;
	}
	else if (npc->anim == 2)
	{
		SPRITE.texty = 65 * 2;
		npc->anim = (npc->deathtimer >= 350) ? 3 : 2;
	}
	else if (npc->anim == 3)
	{
		SPRITE.texty = 65 * 3;
		npc->anim = (npc->deathtimer >= 350) ? 4 : 3;
	}
	else if (npc->anim == 4)
	{
		SPRITE.texty = 65 * 4;
		npc->anim = (npc->deathtimer >= 350) ? 1 : 4;
	}
}

void	anime_shot(t_env *env, t_npc *npc)
{
	double	dirx;
	double	diry;

	dirx = env->posx - SPRITE.text.x;
	diry = env->posy - SPRITE.text.y;
	SPRITE.textx = 0;
	SPRITE.texty = 65 * 6;
	npc->dirx = dirx;
	npc->diry = diry;
	npc->anim = npc->anim > 2 ? 0 : npc->anim;
	if (npc->anim == 0)
		npc->anim = (npc->deathtimer >= 350) ? 1 : 0;
	else if (npc->anim == 1)
	{
		SPRITE.textx = 65;
		npc->anim = (npc->deathtimer >= 350) ? 2 : 1;
	}
	else if (npc->anim == 2)
	{
		SPRITE.textx = 65 * 2;
		npc->anim = (npc->deathtimer >= 350) ? 1 : 2;
	}
}

void	anime_hit(t_env *env, t_npc *npc)
{
	double	dirx;
	double	diry;

	dirx = env->posx - SPRITE.text.x;
	diry = env->posy - SPRITE.text.y;
	SPRITE.textx = 65 * 7;
	SPRITE.texty = 65 * 5;
	npc->dirx = dirx;
	npc->diry = diry;
	if (npc->deathtimer >= 350)
	{
		if (npc->stance == HIT)
			npc->stance = MOVE;
	}
}

void	anime_npc(t_env *env)
{
	int	i;

	i = 0;
	while (i < NENEMY)
	{
		if (NPC.stance == HIT)
			anime_hit(env, &NPC);
		else if (NPC.stance == DEAD)
			anime_death(env, &NPC);
		else if (NPC.stance == MOVE)
			anime_move(env, &NPC, NPC.angle);
		else if (NPC.stance == STAND)
		{
			NPC.sprite.textx = get_direction(NPC.angle);
			NPC.sprite.texty = 0;
		}
		else if (NPC.stance == SHOT)
			anime_shot(env, &NPC);
		npc_ai(env, &NPC, &NPC.sprite);
		if (NPC.deathtimer >= 350)
			NPC.deathtimer = 0;
		i += 1;
	}
}
