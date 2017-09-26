/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 04:31:38 by thchin            #+#    #+#             */
/*   Updated: 2017/06/15 05:18:38 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	get_ceiling_color(t_env *env, t_floor f, int x, int y)
{
	SDL_Surface	*data;
	Uint8		*color;
	Uint8		*pixel;
	double		dist;

	data = env->text[6];
	color = (Uint8 *)data->pixels + f.texty * data->pitch +
			data->format->BytesPerPixel * f.textx;
	pixel = (Uint8 *)env->screen->pixels + (HEIGHT - y) *
		env->screen->pitch + x * env->screen->format->BytesPerPixel;
	pixel[1] = color[0];
	pixel[2] = color[1];
	pixel[3] = color[2];
	dist = 1.0 / f.currentdist;
	dist = dist > 1.0 ? 1.0 : dist;
	dist = dist < 0.0 ? 0.0 : dist;
	pixel[1] *= dist;
	pixel[2] *= dist;
	pixel[3] *= dist;
	if (env->hurt == 1)
		print_hurt(env, x, HEIGHT - y);
}

void	get_floor_color(t_env *env, t_floor f, int x, int y)
{
	SDL_Surface	*data;
	Uint8		*color;
	Uint8		*pixel;
	double		dist;

	data = env->text[f.text];
	color = (Uint8 *)data->pixels + f.texty * data->pitch +
			data->format->BytesPerPixel * f.textx;
	pixel = (Uint8 *)env->screen->pixels + y *
		env->screen->pitch + x * env->screen->format->BytesPerPixel;
	pixel[1] = color[0];
	pixel[2] = color[1];
	pixel[3] = color[2];
	pixel[1] = pixel[1] >> 1 & 8355711;
	pixel[2] = pixel[2] >> 1 & 8355711;
	pixel[3] = pixel[3] >> 1 & 8355711;
	dist = 1.0 / f.currentdist;
	dist = dist > 1.0 ? 1.0 : dist;
	dist = dist < 0.0 ? 0.0 : dist;
	pixel[1] *= dist;
	pixel[2] *= dist;
	pixel[3] *= dist;
	if (env->hurt == 1)
		print_hurt(env, x, y);
}

void	draw_floor(t_env *env, t_floor f, int x)
{
	int	y;

	if (env->drawend < 0)
		env->drawend = HEIGHT;
	y = env->drawend;
	while (y < HEIGHT)
	{
		f.currentdist = HEIGHT / (2.0 * y - HEIGHT);
		f.weight = (f.currentdist) / (f.distwall);
		f.currentx = f.weight * f.wallx + (1.0 - f.weight) * env->posx;
		f.currenty = f.weight * f.wally + (1.0 - f.weight) * env->posy;
		f.currentx = f.currentx > 23 ? 23 : f.currentx;
		f.currentx = f.currentx < 0 ? 0 : f.currentx;
		f.currenty = f.currenty > 23 ? 23 : f.currenty;
		f.currenty = f.currenty < 0 ? 0 : f.currenty;
		f.text = ft_abs(env->map[(int)f.currenty][(int)f.currentx]) - 1;
		f.text = f.text == -1 ? 3 : f.text;
		f.textx = (int)(f.currentx * 64) % 64;
		f.texty = (int)(f.currenty * 64) % 64;
		env->spritebuffer[y] = env->dda.walldist;
		env->spritebuffer[HEIGHT - y] = env->dda.walldist;
		get_floor_color(env, f, x, y);
		get_ceiling_color(env, f, x, y);
		y += 1;
	}
}

void	floor_casting(t_env *env, t_floor f, int x)
{
	if (env->dda.side == 0 && env->dda.raydirx > 0)
	{
		f.wallx = env->dda.mapx;
		f.wally = env->dda.mapy + env->wallx;
	}
	else if (env->dda.side == 0 && env->dda.raydirx < 0)
	{
		f.wallx = env->dda.mapx + 1.0;
		f.wally = env->dda.mapy + env->wallx;
	}
	else if (env->dda.side == 1 && env->dda.raydiry > 0)
	{
		f.wallx = env->dda.mapx + env->wallx;
		f.wally = env->dda.mapy;
	}
	else
	{
		f.wallx = env->dda.mapx + env->wallx;
		f.wally = env->dda.mapy + 1.0;
	}
	f.distwall = env->dda.walldist;
	draw_floor(env, f, x);
}
