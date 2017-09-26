/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 03:17:34 by thchin            #+#    #+#             */
/*   Updated: 2017/05/13 07:06:50 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

#define SPRITE env->sprite[env->spriteorder[i]]
#define SCROSS 16

void	init_weapon(t_weapon *weapon)
{
	weapon->fire = 0;
	weapon->weapon = 0;
	weapon->weaponx = 0;
	weapon->weapony = 0;
	weapon->ammo[0] = 0;
	weapon->ammo[1] = 7;
	weapon->ammo[2] = 30;
	weapon->ammo[3] = 99;
	weapon->anim = 0;
	weapon->bullet = 1;
	weapon->time = 0;
	weapon->size = WIDTH / 3;
	weapon->drawstartx = WIDTH / 2.0 - weapon->size / 2.0;
	weapon->drawendx = WIDTH / 2.0 + weapon->size / 2.0;
	weapon->drawstarty = HEIGHT - weapon->size;
	weapon->drawendy = HEIGHT;
}

void	get_weapon_color(t_env *env, t_weapon w, int x, int y)
{
	Uint8	*color;
	Uint8	*pixel;

	color = (Uint8 *)env->text[11]->pixels +
		(w.texty + w.weapony) * env->text[11]->pitch +
		(w.textx + w.weaponx) * env->text[11]->format->BytesPerPixel;
	pixel = (Uint8 *)env->screen->pixels + y * env->screen->pitch +
		x * env->screen->format->BytesPerPixel;
	if (color[3] != 0)
	{
		pixel[1] = color[0];
		pixel[2] = color[1];
		pixel[3] = color[2];
	}
}

void	print_crosshair(t_env *env)
{
	int		x;
	int		y;
	Uint8	*pixel;

	x = 0;
	y = 0;
	while (x < SCROSS)
	{
		pixel = (Uint8 *)env->screen->pixels + HEIGHT / 2 * env->screen->pitch +
			(WIDTH / 2 - SCROSS / 2 + x) * env->screen->format->BytesPerPixel;
		pixel[1] = 255;
		pixel[2] = 255;
		pixel[3] = 255;
		x += 1;
	}
	while (y < SCROSS)
	{
		pixel = (Uint8 *)env->screen->pixels +
			(HEIGHT / 2 - SCROSS / 2 + y) * env->screen->pitch +
			WIDTH / 2 * env->screen->format->BytesPerPixel;
		pixel[1] = 255;
		pixel[2] = 255;
		pixel[3] = 255;
		y += 1;
	}
}

void	print_weapon(t_env *env, t_weapon *w)
{
	int			x;
	int			y;
	Uint8		*pixel;

	x = w->drawstartx;
	w->weapony = 64 * w->weapon + w->weapon;
	anim_weapon(w);
	w->weapon == 0 ? knife_cast(env, w) : bullet_cast(env, w);
	while (x < w->drawendx)
	{
		w->textx = (int)((double)(x - w->drawstartx) / w->size * 64.0);
		y = w->drawstarty;
		while (y < w->drawendy)
		{
			w->texty = (int)((double)(y - w->drawstarty) / w->size * 64.0);
			get_weapon_color(env, *w, x, y);
			y += 1;
		}
		x += 1;
	}
	print_crosshair(env);
}
