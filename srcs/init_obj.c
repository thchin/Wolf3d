/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 02:04:10 by thchin            #+#    #+#             */
/*   Updated: 2017/07/11 09:16:48 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

#define OBJ env->obj[i]
#define SPRITE env->obj[i].sprite

t_text	get_obj(int nb)
{
	static t_text	obj[NOBJ] =
	{	{3.5, 18.5, 14, SMG},
		{22.5, 7.5, 14, MACHINEGUN},
		{21.5, 22.5, 14, WELL},
		{22.5, 9.5, 14, KEY},
		{7.5, 21.5, 14, HEALTH},
		{8.5, 21.5, 14, FOOD},
	};

	return (obj[nb]);
}

void	sort_obj(t_env *env)
{
	int		i;
	int		j;
	t_obj	tmp;

	i = 0;
	j = 1;
	while (i < NOBJ)
	{
		if (j < NOBJ && env->obj[i].sprite.dist > env->obj[j].sprite.dist)
		{
			tmp = env->obj[i];
			env->obj[i] = env->obj[j];
			env->obj[j] = tmp;
		}
		j += 1;
		if (j >= NOBJ)
		{
			i += 1;
			j = i + 1;
		}
	}
}

void	order_obj(t_env *env)
{
	int	i;

	i = 0;
	while (i < NOBJ)
	{
		SPRITE.dist = (env->posx - SPRITE.text.x) *
				(env->posx - SPRITE.text.x) +
				(env->posy - SPRITE.text.y) * (env->posy - SPRITE.text.y);
		i += 1;
	}
	sort_obj(env);
}

void	init_obj(t_env *env)
{
	int	i;

	i = 0;
	while (i < NOBJ)
	{
		SPRITE.text = get_obj(i);
		OBJ.active = 1;
		init_obj_text(&SPRITE);
		get_textbox(env, &SPRITE);
		i += 1;
	}
}
