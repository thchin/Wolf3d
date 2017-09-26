/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 07:09:43 by thchin            #+#    #+#             */
/*   Updated: 2017/08/23 05:15:36 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL/SDL.h>
#include "../includes/wolf3d.h"

void	get_left_textbox(t_env *env, t_sprite *sprite)
{
	Uint8		*color;
	SDL_Rect	pos;
	int			stop;
	int			y;

	stop = 0;
	pos.x = sprite->textx;
	pos.y = sprite->texty;
	y = sprite->texty;
	while (stop == 0 && pos.x < sprite->textx + 64)
	{
		color = (Uint8 *)env->text[sprite->text.text]->pixels +
			y * env->text[sprite->text.text]->pitch +
			pos.x * env->text[sprite->text.text]->format->BytesPerPixel;
		if (color[0] != 152 || color[1] != 0 || color[2] != 136)
			stop = 1;
		y += 1;
		if (y >= sprite->texty + 64)
		{
			y = sprite->texty;
			pos.x += 1;
		}
	}
	sprite->textstartx = (double)(pos.x - sprite->textx) / 64;
}

void	get_right_textbox(t_env *env, t_sprite *sprite)
{
	Uint8		*color;
	SDL_Rect	pos;
	int			stop;
	int			x;

	pos.x = sprite->textx;
	pos.y = sprite->texty;
	x = sprite->textx;
	stop = 0;
	while (stop == 0 && pos.y < sprite->texty + 64)
	{
		color = (Uint8 *)env->text[sprite->text.text]->pixels +
			pos.y * env->text[sprite->text.text]->pitch +
			x * env->text[sprite->text.text]->format->BytesPerPixel;
		if (color[0] != 152 || color[1] != 0 || color[2] != 136)
			stop = 1;
		x += 1;
		if (x >= sprite->textx + 64)
		{
			x = sprite->textx;
			pos.y += 1;
		}
	}
	sprite->textstarty = (double)(pos.y - sprite->texty) / 64;
}

void	get_up_textbox(t_env *env, t_sprite *sprite)
{
	Uint8		*color;
	SDL_Rect	pos;
	int			stop;
	int			y;

	stop = 0;
	y = sprite->texty;
	pos.x = sprite->textx + 63;
	pos.y = sprite->texty + 63;
	while (stop == 0 && pos.x > sprite->textx)
	{
		color = (Uint8 *)env->text[sprite->text.text]->pixels +
			y * env->text[sprite->text.text]->pitch +
			pos.x * env->text[sprite->text.text]->format->BytesPerPixel;
		if (color[0] != 152 || color[1] != 0 || color[2] != 136)
			stop = 1;
		y += 1;
		if (y >= sprite->texty + 64)
		{
			y = sprite->texty;
			pos.x -= 1;
		}
	}
	sprite->textendx = (double)(pos.x - sprite->textx + 1) / 64;
}

void	get_down_textbox(t_env *env, t_sprite *sprite)
{
	Uint8		*color;
	SDL_Rect	pos;
	int			stop;
	int			x;

	stop = 0;
	x = sprite->textx;
	pos.x = sprite->textx + 63;
	pos.y = sprite->texty + 63;
	while (stop == 0 && pos.y < sprite->texty)
	{
		color = (Uint8 *)env->text[sprite->text.text]->pixels +
			pos.y * env->text[sprite->text.text]->pitch +
			x * env->text[sprite->text.text]->format->BytesPerPixel;
		if (color[0] != 152 || color[1] != 0 || color[2] != 136)
			stop = 1;
		x += 1;
		if (x >= sprite->textx + 64)
		{
			x = sprite->textx;
			pos.y -= 1;
		}
	}
	sprite->textendy = (double)(pos.y - sprite->texty + 1) / 64;
}

void	get_textbox(t_env *env, t_sprite *sprite)
{
	get_left_textbox(env, sprite);
	get_right_textbox(env, sprite);
	get_up_textbox(env, sprite);
	get_down_textbox(env, sprite);
}
