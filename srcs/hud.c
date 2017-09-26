/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 09:20:26 by thchin            #+#    #+#             */
/*   Updated: 2017/06/02 08:41:08 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL/SDL_ttf.h>
#include "../includes/wolf3d.h"

void	init_hud(t_env *env, t_hud *hud)
{
	char	*tmp;

	hud->size = 55;
	hud->c.r = 255;
	hud->c.g = 110;
	hud->c.b = 110;
	hud->police = TTF_OpenFont("resources/raslani.ttf", 50);
	hud->str_ammo = TTF_RenderText_Blended(hud->police, "ammo : ", hud->c);
	hud->str_life = TTF_RenderText_Blended(hud->police, "health : ", hud->c);
	hud->percent = TTF_RenderText_Blended(hud->police, "%", hud->c);
	hud->str_fps = TTF_RenderText_Blended(hud->police, "fps : ", hud->c);
	hud->ammo = NULL;
	hud->life = NULL;
	tmp = ft_itoa(env->frametime);
	hud->fps = TTF_RenderText_Blended(hud->police, tmp, hud->c);
	free(tmp);
}

void	get_font_color(t_env *env, SDL_Surface *texte, SDL_Rect pos)
{
	Uint8		*color;
	Uint8		*pixel;
	SDL_Rect	tmp;

	tmp = pos;
	while (pos.x - tmp.x < texte->w)
	{
		pos.y = tmp.y;
		while (pos.y - tmp.y < texte->h)
		{
			color = (Uint8 *)texte->pixels + (pos.y - tmp.y) * texte->pitch +
				(pos.x - tmp.x) * texte->format->BytesPerPixel;
			pixel = (Uint8 *)env->screen->pixels + pos.y * env->screen->pitch +
				pos.x * env->screen->format->BytesPerPixel;
			pixel[1] = (color[2] * (double)color[3] / 255) +
				pixel[1] * (1.0 - (double)color[3] / 255);
			pixel[2] = (color[1] * (double)color[3] / 255) +
				pixel[2] * (1.0 - (double)color[3] / 255);
			pixel[3] = (color[0] * (double)color[3] / 255) +
				pixel[3] * (1.0 - (double)color[3] / 255);
			pos.y += 1;
		}
		pos.x += 1;
	}
}

void	update_hud(t_env *env, t_hud *hud)
{
	char	*tmp;

	if (NULL != hud->ammo)
		SDL_FreeSurface(hud->ammo);
	if (NULL != hud->life)
		SDL_FreeSurface(hud->life);
	tmp = ft_itoa(env->weapon.ammo[env->weapon.weapon]);
	hud->ammo = TTF_RenderText_Blended(hud->police, tmp, hud->c);
	free(tmp);
	tmp = ft_itoa(env->life);
	hud->life = TTF_RenderText_Blended(hud->police, tmp, hud->c);
	free(tmp);
	if (env->accumtime >= 1000)
	{
		if (NULL != hud->fps)
			SDL_FreeSurface(hud->fps);
		tmp = ft_itoa(1.0 / env->frametime);
		hud->fps = TTF_RenderText_Blended(hud->police, tmp, hud->c);
		free(tmp);
		env->accumtime = 0;
	}
}

void	print_hud(t_env *env)
{
	SDL_Rect	pos;

	update_hud(env, &env->hud);
	pos.x = 0;
	pos.y = 0;
	get_font_color(env, env->hud.str_fps, pos);
	pos.x += env->hud.str_fps->w;
	get_font_color(env, env->hud.fps, pos);
	pos.x = WIDTH - 275;
	pos.y = HEIGHT - 65;
	get_font_color(env, env->hud.str_ammo, pos);
	pos.x += env->hud.str_ammo->w;
	get_font_color(env, env->hud.ammo, pos);
	pos.x = 0;
	get_font_color(env, env->hud.str_life, pos);
	pos.x += env->hud.str_life->w;
	get_font_color(env, env->hud.life, pos);
	pos.x += env->hud.life->w;
	get_font_color(env, env->hud.percent, pos);
}
