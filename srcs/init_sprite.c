/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 04:48:14 by thchin            #+#    #+#             */
/*   Updated: 2017/05/31 01:08:40 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

#define SPRITE env->sprite[i]

t_text	get_sprite(int nb)
{
	static t_text	sprite[NSPRITE] =
	{	{3.0, 11.5, 10},
		{6.5, 18.5, 10},
		{11.5, 13.5, 10},
		{11.5, 8.5, 10},
		{18.5, 8.5, 10},
		{20.5, 2.5, 10},
		{20.5, 3.5, 10},
		{20.5, 19.5, 10},
		{6.5, 9.5, 9},
		{6.5, 10.5, 9},
		{6.5, 11.5, 9},
		{3.5, 1.5, 8},
		{8.5, 1.5, 8},
		{8.0, 1.8, 8},
		{7.8, 1.2, 8},
		{21.5, 2.5, 8},
		{14.5, 15.5, 8},
		{14.0, 15.1, 8},
		{13.5, 15.8, 8},
	};

	return (sprite[nb]);
}

void	sort_sprite(t_env *env)
{
	int		i;
	int		j;
	int		tmp;
	double	tmpf;

	i = 0;
	j = 1;
	while (i < NSPRITE)
	{
		if (env->spritedist[i] > env->spritedist[j])
		{
			tmp = env->spriteorder[i];
			env->spriteorder[i] = env->spriteorder[j];
			env->spriteorder[j] = tmp;
			tmpf = env->spritedist[i];
			env->spritedist[i] = env->spritedist[j];
			env->spritedist[j] = tmpf;
		}
		j += 1;
		if (j >= NSPRITE)
		{
			i += 1;
			j = i + 1;
		}
	}
}

void	order_sprite(t_env *env)
{
	int	i;

	i = 0;
	while (i < NSPRITE)
	{
		env->spriteorder[i] = i;
		env->spritedist[i] = ((env->posx - SPRITE.text.x) *
				(env->posx - SPRITE.text.x) +
				(env->posy - SPRITE.text.y) * (env->posy - SPRITE.text.y));
		i += 1;
	}
	sort_sprite(env);
}

void	init_sprite(t_env *env)
{
	int	i;

	i = 0;
	while (i < NSPRITE)
	{
		env->sprite[i].text = get_sprite(i);
		env->sprite[i].textx = 0;
		env->sprite[i].texty = 0;
		i += 1;
	}
}
