/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_npc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 14:07:22 by thchin            #+#    #+#             */
/*   Updated: 2017/05/31 01:10:23 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

#define NPC env->npc[i]

t_text	get_npc(int nb)
{
	static t_text	npc[NENEMY] =
	{	{18.5, 1.5, 12},
		{21.5, 1.5, 12},
		{21.5, 2.5, 12},
		{21.5, 3.5, 12},
		{21.5, 4.5, 12},
		{20.5, 1.5, 12},
		{20.5, 2.5, 12},
		{20.5, 3.5, 12},
		{20.5, 4.5, 12},
		{19.5, 1.5, 12},
		{19.5, 2.5, 12},
		{19.5, 3.5, 12},
		{19.5, 4.5, 12},
	};

	return (npc[nb]);
}

void	sort_npc(t_env *env)
{
	int		i;
	int		j;
	int		tmp;
	double	tmpf;

	i = 0;
	j = 1;
	while (i < NENEMY)
	{
		if (env->npcdist[i] > env->npcdist[j])
		{
			tmp = env->npcorder[i];
			env->npcorder[i] = env->npcorder[j];
			env->npcorder[j] = tmp;
			tmpf = env->npcdist[i];
			env->npcdist[i] = env->npcdist[j];
			env->npcdist[j] = tmpf;
		}
		j += 1;
		if (j >= NENEMY)
		{
			i += 1;
			j = i + 1;
		}
	}
}

void	order_npc(t_env *env)
{
	int	i;

	i = 0;
	while (i < NENEMY)
	{
		env->npcorder[i] = i;
		env->npcdist[i] = ((env->posx - NPC.sprite.text.x) *
				(env->posx - NPC.sprite.text.x) +
				(env->posy - NPC.sprite.text.y) *
				(env->posy - NPC.sprite.text.y));
		i += 1;
	}
	sort_npc(env);
}

void	init_npc(t_env *env)
{
	int	i;

	i = 0;
	while (i < NENEMY)
	{
		env->npc[i].sprite.text = get_npc(i);
		env->npc[i].sprite.textx = 0;
		env->npc[i].sprite.texty = 0;
		env->npc[i].stance = STAND;
		env->npc[i].anim = 0;
		env->npc[i].dirx = 0;
		env->npc[i].diry = -1;
		env->npc[i].life = 3;
		env->npc[i].hit = 0;
		env->npc[i].speed = 0.1;
		i += 1;
	}
}
