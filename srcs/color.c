/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 07:27:11 by thchin            #+#    #+#             */
/*   Updated: 2017/04/21 01:52:11 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int		rgb_to_hex(t_env *env, t_rgb rgb)
{
	int	c;
	int	r;
	int	g;
	int	b;

	(void)env;
//	if (1 == env->endian)
//	{
		r = rgb.r;
		g = rgb.g << 8;
		b = rgb.b << 16;
//	}
//	else
//	{
//		b = rgb.b;
//		g = rgb.g << 8;
//		r = rgb.r << 16;
//	}
	c = r | g;
	c = c | b;
	return (c);
}

t_rgb	set_color(t_rgb c, int r, int g, int b)
{
	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}

t_rgb	get_color(t_env *env)
{
	if (1 == env->map[env->mapy][env->mapx])
		env->color = set_color(env->color, 255, 0, 0);
	else if (2 == env->map[env->mapy][env->mapx])
		env->color = set_color(env->color, 0, 255, 0);
	else if (3 == env->map[env->mapy][env->mapx])
		env->color = set_color(env->color, 0, 0, 255);
	else if (4 == env->map[env->mapy][env->mapx])
		env->color = set_color(env->color, 140, 140, 0);
	else if (5 == env->map[env->mapy][env->mapx])
		env->color = set_color(env->color, 0, 140, 140);
	else if (6 == env->map[env->mapy][env->mapx])
		env->color = set_color(env->color, 140, 140, 140);
	else if (7 == env->map[env->mapy][env->mapx])
		env->color = set_color(env->color, 17, 254, 0);
	else if (8 == env->map[env->mapy][env->mapx])
		env->color = set_color(env->color, 10, 10, 167);
	else
		env->color = set_color(env->color, 255, 255, 255);
	if (env->side == 1)
	{
		env->color.r /= 2;
		env->color.g /= 2;
		env->color.b /= 2;
	}
	return (env->color);
}

void	draw_verline(t_env *env, int x, int color)
{
	while (env->drawstart < env->drawend)
	{
		img_put_pixel(env, x, env->drawstart, color);
		env->drawstart += 1;
	}
}
