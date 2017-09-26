/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 04:48:14 by thchin            #+#    #+#             */
/*   Updated: 2017/08/23 04:49:41 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

#define SPRIT env->sprite[i]

t_text	get_sprite(int nb)
{
	static t_text	sprite[NSPRITE] =
	{	{3.0, 11.5, 10, DECOR},
		{6.5, 18.5, 10, DECOR},
		{11.5, 13.5, 10, DECOR},
		{11.5, 8.5, 10, DECOR},
		{18.5, 8.5, 10, DECOR},
		{20.5, 2.5, 10, DECOR},
		{20.5, 3.5, 10, DECOR},
		{20.5, 19.5, 10, DECOR},
		{6.5, 9.5, 9, DECOR},
		{6.5, 10.5, 9, DECOR},
		{6.5, 11.5, 9, DECOR},
		{3.5, 1.5, 8, DECOR},
		{8.5, 1.5, 8, DECOR},
		{8.0, 1.8, 8, DECOR},
		{7.8, 1.2, 8, DECOR},
		{21.5, 2.5, 8, DECOR},
		{14.5, 15.5, 8, DECOR},
		{14.0, 15.1, 8, DECOR},
		{13.5, 15.8, 8, DECOR},
	};

	return (sprite[nb]);
}

void	sort_sprite(t_env *env)
{
	int			i;
	int			j;
	t_sprite	tmp;

	i = 0;
	j = 1;
	while (i < NSPRITE)
	{
		if (j < NSPRITE && env->sprite[i].dist > env->sprite[j].dist)
		{
			tmp = env->sprite[i];
			env->sprite[i] = env->sprite[j];
			env->sprite[j] = tmp;
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
		env->sprite[i].dist = ((env->posx - SPRIT.text.x) *
				(env->posx - SPRIT.text.x) +
				(env->posy - SPRIT.text.y) * (env->posy - SPRIT.text.y));
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
		get_textbox(env, &env->sprite[i]);
		i += 1;
	}
}
