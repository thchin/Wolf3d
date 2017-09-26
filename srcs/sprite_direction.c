/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_direction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 08:52:03 by thchin            #+#    #+#             */
/*   Updated: 2017/06/15 05:39:37 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../includes/wolf3d.h"

void	norm_vec2f(double *x, double *y)
{
	double	tmp;

	tmp = 1.0 / sqrtf(*x * *x + *y * *y);
	*x *= tmp;
	*y *= tmp;
}

double	get_angle(t_env *env, t_npc npc)
{
	double		angle;
	double		dirx;
	double		diry;

	dirx = env->posx - npc.sprite.text.x;
	diry = env->posy - npc.sprite.text.y;
	norm_vec2f(&dirx, &diry);
	angle = atan2(diry, dirx) - atan2(npc.diry, npc.dirx);
	angle += M_PI / 2;
	angle = (angle > M_PI * 2) ? angle - M_PI * 2 : angle;
	angle = (angle < 0) ? angle + M_PI * 2 : angle;
	angle *= 180 / M_PI;
	return (angle);
}

int		get_direction(double angle)
{
	if (angle > 337.5 || angle <= 22.5)
		return (65 * 2);
	if (angle > 22.5 && angle <= 67.5)
		return (65 * 1);
	if (angle > 67.5 && angle <= 112.5)
		return (0);
	if (angle > 112.5 && angle <= 157.5)
		return (65 * 7);
	if (angle > 157.5 && angle <= 202.5)
		return (65 * 6);
	if (angle > 202.5 && angle <= 247.5)
		return (65 * 5);
	if (angle > 247.5 && angle <= 292.5)
		return (65 * 4);
	if (angle > 292.5 && angle <= 337.5)
		return (65 * 3);
	return (0);
}
