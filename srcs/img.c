/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 01:21:24 by thchin            #+#    #+#             */
/*   Updated: 2017/03/14 09:51:12 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "../includes/wolf3d.h"

void	img_put_pixel(t_env *env, int x, int y, int color)
{
//	char			*data;
//	unsigned int	value;

	(void)env;
	(void)color;
	(void)x;
	(void)y;
//	data = env->data;
//	value = mlx_get_color_value(env->mlx, color);
//	if (0 < x && WIDTH > x && 0 < y && HEIGHT > y)
//		ft_memcpy(data + y * env->size_line + x * (env->bpp / 8), &value, 3);
}

void	fill_img(t_env *env, int color)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		img_put_pixel(env, x, y, color);
		x += 1;
		if (WIDTH <= x)
		{
			x = 0;
			y += 1;
		}
	}
}
