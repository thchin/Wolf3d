/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 09:44:43 by thchin            #+#    #+#             */
/*   Updated: 2017/06/01 01:07:37 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL/SDL.h>
#include "../includes/wolf3d.h"

void	update_time(t_env *env)
{
	double	frametime;
	int		i;

	env->old_time = env->time;
	env->time = SDL_GetTicks();
	env->accumtime += (env->time - env->old_time);
	env->frametime = (env->time - env->old_time) / 1000.0;
	env->weapon.time += (env->time - env->old_time);
	if (env->hurt == 1)
		env->deathtimer += (env->time - env->old_time);
	i = 0;
	while (i < NENEMY)
	{
		env->npc[i].deathtimer += (env->time - env->old_time);
		env->npc[i].speed = env->frametime / 2.0;
		i += 1;
	}
	env->move.move_speed = env->frametime * 2.0;
	env->move.rot_speed = env->frametime;
}
