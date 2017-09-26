/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 06:08:21 by thchin            #+#    #+#             */
/*   Updated: 2017/06/15 05:12:55 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <SDL/SDL_image.h>
#include "../includes/wolf3d.h"

#define BLUESTONE "resources/bluestone.png"
#define COLORSTONE "resources/colorstone.png"
#define EAGLE "resources/eagle.png"
#define GREYSTONE "resources/greystone.png"
#define MOSSY "resources/mossy.png"
#define PURPLESTONE "resources/purplestone.png"
#define REDBRICK "resources/redbrick.png"
#define WOOD "resources/wood.png"
#define BARREL "resources/barrel.png"
#define PILLAR "resources/pillar.png"
#define GLIGHT "resources/greenlight.png"
#define GUN "resources/Weapons.png"
#define GUARD "resources/Guard.png"
#define HURT "resources/Hurt2.png"
#define OBJ "resources/Objects.png"

void	get_texture(t_env *env)
{
	if (NULL == (env->text[0] = IMG_Load(EAGLE)) ||
		NULL == (env->text[1] = IMG_Load(REDBRICK)) ||
		NULL == (env->text[2] = IMG_Load(PURPLESTONE)) ||
		NULL == (env->text[3] = IMG_Load(GREYSTONE)) ||
		NULL == (env->text[4] = IMG_Load(BLUESTONE)) ||
		NULL == (env->text[5] = IMG_Load(MOSSY)) ||
		NULL == (env->text[6] = IMG_Load(WOOD)) ||
		NULL == (env->text[7] = IMG_Load(COLORSTONE)) ||
		NULL == (env->text[8] = IMG_Load(BARREL)) ||
		NULL == (env->text[9] = IMG_Load(PILLAR)) ||
		NULL == (env->text[10] = IMG_Load(GLIGHT)) ||
		NULL == (env->text[11] = IMG_Load(GUN)) ||
		NULL == (env->text[12] = IMG_Load(GUARD)) ||
		NULL == (env->text[13] = IMG_Load(HURT)) ||
		NULL == (env->text[14] = IMG_Load(OBJ)))
		clear_env(env);
}

void	init_texture(t_env *env)
{
	int	i;

	i = 0;
	while (i < 13)
	{
		env->text[i] = NULL;
		i += 1;
	}
	get_texture(env);
}

void	get_text_color(t_env *env, int x, int y, int texty)
{
	SDL_Surface	*data;
	Uint8		*color;
	Uint8		*pixel;
	double		dist;

	dist = 1.0 / env->dda.walldist;
	dist = dist > 1.0 ? 1.0 : dist;
	dist = dist < 0.0 ? 0.0 : dist;
	data = env->text[env->text_num];
	color = (Uint8 *)data->pixels + texty * data->pitch +
			data->format->BytesPerPixel * env->textx;
	pixel = (Uint8 *)env->screen->pixels + y * env->screen->pitch + x *
			env->screen->format->BytesPerPixel;
	pixel[1] = color[0] * dist;
	pixel[2] = color[1] * dist;
	pixel[3] = color[2] * dist;
	if (env->dda.side == 1)
	{
		pixel[1] = (pixel[1] >> 1 & 8355711) * dist;
		pixel[2] = (pixel[2] >> 1 & 8355711) * dist;
		pixel[3] = (pixel[3] >> 1 & 8355711) * dist;
	}
	if (env->hurt == 1)
		print_hurt(env, x, y);
}

void	draw_textline(t_env *env, int x)
{
	int		y;
	int		d;
	int		texty;

	y = env->drawstart;
	while (y < env->drawend)
	{
		d = y * 256 - (HEIGHT - 1) * 128 + env->lineheight * 128;
		texty = ((d * 64) / env->lineheight) / 256;
		get_text_color(env, x, y, texty);
		env->spritebuffer[y] = env->dda.walldist;
		y += 1;
	}
}

void	calcul_textx(t_env *env, t_dda dda)
{
	env->text_num = env->map[(int)dda.mapy][(int)dda.mapx] - 1;
	if (dda.side == 0)
		env->wallx = dda.rayposy + dda.walldist * dda.raydiry;
	else
		env->wallx = dda.rayposx + dda.walldist * dda.raydirx;
	env->wallx -= floor(env->wallx);
	env->textx = (int)(env->wallx * (double)64);
	if (dda.side == 0 && dda.raydirx > 0)
		env->textx = 64 - env->textx - 1;
	if (dda.side == 1 && dda.raydiry < 0)
		env->textx = 64 - env->textx - 1;
}
