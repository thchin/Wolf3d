/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hurt.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 11:58:44 by thchin            #+#    #+#             */
/*   Updated: 2017/05/31 01:07:46 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	print_hurt(t_env *env, int x, int y)
{
	int		textx;
	int		texty;
	int		size;
	Uint8	*color;
	Uint8	*pixel;

	size = 420;
	textx = (int)((double)x / WIDTH * size);
	texty = (int)((double)y / HEIGHT * size);
	color = (Uint8 *)env->text[13]->pixels +
		texty * env->text[13]->pitch +
		textx * env->text[13]->format->BytesPerPixel;
	pixel = (Uint8 *)env->screen->pixels + y * env->screen->pitch +
		x * env->screen->format->BytesPerPixel;
	pixel[1] = (color[0] * (double)color[3] / 255) +
				pixel[1] * (1.0 - (double)color[3] / 255);
	pixel[2] = (color[1] * (double)color[3] / 255) +
				pixel[2] * (1.0 - (double)color[3] / 255);
	pixel[3] = (color[2] * (double)color[3] / 255) +
				pixel[3] * (1.0 - (double)color[3] / 255);
}
