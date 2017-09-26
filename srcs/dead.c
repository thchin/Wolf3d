/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 08:44:58 by thchin            #+#    #+#             */
/*   Updated: 2017/06/02 09:12:13 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "../includes/wolf3d.h"

void	grey_screen(t_env *env)
{
	int		x;
	int		y;
	Uint8	sum;
	Uint8	*pixel;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			pixel = (Uint8 *)env->screen->pixels + y * env->screen->pitch +
				x * env->screen->format->BytesPerPixel;
			sum = (pixel[1] + pixel[2] + pixel[3]) / 3;
			pixel[1] = sum;
			pixel[2] = sum;
			pixel[3] = sum;
			y += 1;
		}
		x += 1;
	}
}

void	print_dead(t_env *env, int *i)
{
	SDL_Surface	*dead;
	SDL_Rect	pos;

	grey_screen(env);
	dead = TTF_RenderText_Blended(env->hud.police, "WASTED", env->hud.c);
	pos.x = WIDTH / 2 - dead->w / 2;
	pos.y = HEIGHT / 3 - HEIGHT / 3 / 2;
	get_font_color(env, dead, pos);
	SDL_FreeSurface(dead);
	env->dead = 1;
	env->ingame = 0;
	*i = 0;
}
