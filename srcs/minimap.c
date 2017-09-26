/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 05:55:18 by thchin            #+#    #+#             */
/*   Updated: 2017/06/24 06:35:39 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL/SDL.h>
#include "../includes/wolf3d.h"

void	draw_square(t_env *env, t_minimap m, int size)
{
	Uint8	*pixel;

	while (m.y < m.tmpy + size)
	{
		pixel = (Uint8 *)env->screen->pixels + m.y * env->screen->pitch +
				m.x * env->screen->format->BytesPerPixel;
		pixel[1] = (m.color.r * 0.7 + pixel[1] * (1.0 - 0.7));
		pixel[2] = (m.color.g * 0.7 + pixel[2] * (1.0 - 0.7));
		pixel[3] = (m.color.b * 0.7 + pixel[3] * (1.0 - 0.7));
		m.x += 1;
		if (m.x >= m.tmpx + size)
		{
			m.y += 1;
			m.x = m.tmpx;
		}
	}
}

void	draw_sprite_minimap(t_env *env, t_minimap m)
{
	m.i = 0;
	while (m.i < NSPRITE)
	{
		m.text = env->sprite[m.i].text;
		m.x = WIDTH - env->mapwidth * 10 + m.text.x * 10 - 1;
		m.y = m.text.y * 10 - 1;
		m.tmpx = m.x;
		m.tmpy = m.y;
		if (8 == m.text.text)
			m.color = (t_color){130, 130, 130};
		else if (9 == m.text.text)
			m.color = (t_color){255, 255, 255};
		else if (10 == m.text.text)
			m.color = (t_color){0, 200, 0};
		draw_square(env, m, 3);
		m.i += 1;
	}
}

void	draw_npc_minimap(t_env *env, t_minimap m)
{
	m.i = 0;
	while (m.i < NENEMY)
	{
		m.text = env->npc[m.i].sprite.text;
		m.x = WIDTH - env->mapwidth * 10 + m.text.x * 10 - 1;
		m.y = m.text.y * 10 - 1;
		m.tmpx = m.x;
		m.tmpy = m.y;
		m.color = (t_color){175, 100, 10};
		draw_square(env, m, 2);
		m.i += 1;
	}
}

void	draw_map(t_env *env, t_minimap m)
{
	m.mapx = 0;
	m.mapy = 0;
	m.x = WIDTH - env->mapwidth * 10;
	m.max_x = WIDTH - env->mapwidth * 10;
	m.y = 0;
	while (m.y < env->mapheight * 10)
	{
		m.tmpx = m.x;
		m.tmpy = m.y;
		m.color = get_color(env, m.mapx, m.mapy);
		draw_square(env, m, 10);
		m.x += 10;
		m.y = m.tmpy;
		m.mapx += 1;
		if (m.x >= WIDTH)
		{
			m.x = m.max_x;
			m.y = m.tmpy + 10;
			m.mapy += 1;
			m.mapx = 0;
		}
	}
}

void	draw_minimap(t_env *env)
{
	t_minimap	m;

	draw_map(env, m);
	m.x = WIDTH - env->mapwidth * 10 + env->posx * 10;
	m.y = env->posy * 10;
	m.tmpx = m.x;
	m.tmpy = m.y;
	m.color = (t_color){255, 0, 0};
	draw_square(env, m, 2);
	draw_sprite_minimap(env, m);
	draw_npc_minimap(env, m);
}
