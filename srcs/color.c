/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 06:35:21 by thchin            #+#    #+#             */
/*   Updated: 2017/06/24 06:35:37 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

t_color	get_color(t_env *env, int x, int y)
{
	if (1 == env->map[y][x])
		return ((t_color){152, 0, 0});
	if (2 == env->map[y][x])
		return ((t_color){255, 0, 0});
	if (3 == env->map[y][x])
		return ((t_color){101, 0, 101});
	if (4 == env->map[y][x])
		return ((t_color){155, 155, 155});
	if (5 == env->map[y][x])
		return ((t_color){0, 0, 255});
	if (6 == env->map[y][x])
		return ((t_color){204, 204, 0});
	if (7 == env->map[y][x])
		return ((t_color){96, 64, 38});
	if (8 == env->map[y][x])
		return ((t_color){143, 121, 103});
	return ((t_color){0, 0, 0});
}
