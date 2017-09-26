/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 09:39:22 by thchin            #+#    #+#             */
/*   Updated: 2017/05/31 01:09:18 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	copy_player(t_env *env, t_env *src)
{
	env->map = src->map;
	env->posx = src->posx;
	env->posy = src->posy;
	env->dirx = src->dirx;
	env->diry = src->diry;
	env->planex = src->planex;
	env->planey = src->planey;
}

void	copy_npc(t_env *env, t_env *src)
{
	int	i;

	i = 0;
	while (i < NSPRITE)
	{
		env->sprite[i] = src->sprite[i];
		env->spriteorder[i] = src->spriteorder[i];
		i += 1;
	}
	i = 0;
	while (i < NENEMY)
	{
		env->npc[i] = src->npc[i];
		env->npcorder[i] = src->npcorder[i];
		i += 1;
	}
}

t_env	*copy_env(t_env *src)
{
	t_env		*env;
	int			i;

	env = (t_env *)malloc(sizeof(t_env));
	copy_player(env, src);
	i = 0;
	while (i < 14)
	{
		env->text[i] = src->text[i];
		i += 1;
	}
	env->screen = src->screen;
	env->move = src->move;
	env->weapon = src->weapon;
	env->deathtimer = src->deathtimer;
	env->hurt = src->hurt;
	copy_npc(env, src);
	return (env);
}
