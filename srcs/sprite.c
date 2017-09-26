/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 04:39:40 by thchin            #+#    #+#             */
/*   Updated: 2017/08/23 05:18:40 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

#define SPRITE env->sprite[i]

void	dark_sprite(Uint8 *pixel, t_sprite sprite)
{
	double	dist;

	if (sprite.text.text != 10)
	{
		dist = 1.0 / sprite.transformy;
		dist = dist > 1.0 ? 1.0 : dist;
		dist = dist < 0.0 ? 0.0 : dist;
		pixel[1] *= dist;
		pixel[2] *= dist;
		pixel[3] *= dist;
	}
}

void	get_sprite_color(t_env *env, t_sprite sprite, int x, int y)
{
	Uint8		*color;
	Uint8		*pixel;
	SDL_Rect	text;
	int			d;
	double		dist;

	text.x = (int)((256 * (x - (-sprite.width / 2 + sprite.screenx)) *
				64 / sprite.width) / 256) + sprite.textx;
	d = y * 256 - HEIGHT * 128 + sprite.height * 128;
	text.y = ((d * 64) / sprite.height) / 256 + sprite.texty;
	color = (Uint8 *)env->text[sprite.text.text]->pixels +
		text.y * env->text[sprite.text.text]->pitch +
		text.x * env->text[sprite.text.text]->format->BytesPerPixel;
	pixel = (Uint8 *)env->screen->pixels + y * env->screen->pitch +
		x * env->screen->format->BytesPerPixel;
	if (color[0] != 152 || color[1] != 0 || color[2] != 136)
	{
		pixel[1] = color[0];
		pixel[2] = color[1];
		pixel[3] = color[2];
		dark_sprite(pixel, sprite);
		env->spritebuffer[y] = sprite.transformy;
		if (env->hurt == 1)
			print_hurt(env, x, y);
	}
}

void	set_sprite(t_env *env, t_sprite *sprite)
{
	sprite->spritex = sprite->text.x - env->posx;
	sprite->spritey = sprite->text.y - env->posy;
	sprite->invdet = 1.0 / (env->planex * env->diry - env->dirx * env->planey);
	sprite->transformx = sprite->invdet *
		(env->diry * sprite->spritex - env->dirx * sprite->spritey);
	sprite->transformy = sprite->invdet *
		(-(env->planey) * sprite->spritex + env->planex * sprite->spritey);
	sprite->screenx = (int)((WIDTH / 2) *
			(1 + sprite->transformx / sprite->transformy));
	sprite->height = ft_abs((int)(HEIGHT / (sprite->transformy)));
	sprite->drawstarty = -sprite->height / 2 + HEIGHT / 2;
	sprite->drawendy = sprite->height / 2 + HEIGHT / 2;
	sprite->width = ft_abs((int)(HEIGHT / (sprite->transformy)));
	sprite->drawstartx = -sprite->width / 2 + sprite->screenx;
	sprite->drawendx = sprite->width / 2 + sprite->screenx;
	sprite->drawendx = sprite->drawstartx + sprite->width * sprite->textendx;
	sprite->drawendy = sprite->drawstarty + sprite->height * sprite->textendy;
	sprite->drawstarty += sprite->height * sprite->textstarty;
	sprite->drawstartx += sprite->width * sprite->textstartx;
	sprite->drawstarty = sprite->drawstarty < 0 ? 0 : sprite->drawstarty;
	sprite->drawendy = sprite->drawendy >= HEIGHT ?
						HEIGHT - 1 : sprite->drawendy;
	sprite->drawstartx = sprite->drawstartx < 0 ? 0 : sprite->drawstartx;
	sprite->drawendx = sprite->drawendx >= WIDTH ? WIDTH - 1 : sprite->drawendx;
}

void	update_sprite(t_env *env)
{
	int	i;

	i = 0;
	order_sprite(env);
	while (i < NSPRITE)
	{
		set_sprite(env, &env->sprite[i]);
		i += 1;
	}
}

void	sprite_casting(t_env *env, int x)
{
	int	i;
	int	y;

	i = 0;
	while (i < NSPRITE)
	{
		if (SPRITE.transformy > 0 && SPRITE.transformy < env->dda.walldist &&
				x >= SPRITE.drawstartx && x < SPRITE.drawendx &&
				SPRITE.text.text != 12)
		{
			y = SPRITE.drawstarty;
			while (y < SPRITE.drawendy)
			{
				if (SPRITE.transformy < env->spritebuffer[y])
					get_sprite_color(env, SPRITE, x, y);
				y += 1;
			}
		}
		i += 1;
	}
}
