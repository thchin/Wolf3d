/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 04:02:33 by thchin            #+#    #+#             */
/*   Updated: 2017/06/02 09:14:06 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <SDL/SDL_ttf.h>
#include "../includes/wolf3d.h"

void	clear_text(t_env *env)
{
	int	i;

	i = 0;
	while (i < 14)
	{
		if (NULL != env->text[i])
			SDL_FreeSurface(env->text[i]);
		i += 1;
	}
	SDL_FreeSurface(env->screen);
}

void	clear_map(t_env *env)
{
	int	i;

	if (NULL != env->map)
	{
		i = 0;
		while (i < env->mapheight && NULL != env->map[i])
		{
			free(env->map[i]);
			i += 1;
		}
		free(env->map);
	}
}

void	clear_hud(t_hud hud)
{
	TTF_CloseFont(hud.police);
	SDL_FreeSurface(hud.ammo);
	SDL_FreeSurface(hud.str_ammo);
	SDL_FreeSurface(hud.life);
	SDL_FreeSurface(hud.str_life);
	SDL_FreeSurface(hud.percent);
	SDL_FreeSurface(hud.str_fps);
	SDL_FreeSurface(hud.fps);
}

void	clear_sdl(void)
{
	TTF_Quit();
	SDL_Quit();
}

int		clear_env(t_env *env)
{
	clear_map(env);
	clear_hud(env->hud);
	clear_sdl();
	clear_menu(env->menu);
	free(env);
	exit(0);
}
