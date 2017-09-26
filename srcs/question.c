/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   question.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 01:07:36 by thchin            #+#    #+#             */
/*   Updated: 2017/06/09 01:15:40 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL/SDL.h>
#include "../includes/wolf3d.h"

#define KEY event.key.keysym.sym
#define MENU env->menu

void	question_enter_event(SDL_Event event, t_env *env, int *i)
{
	if (KEY == SDLK_RETURN)
	{
		if (0 == *i)
		{
			if (0 == env->newgame)
				clear_env(env);
			else if (1 == env->newgame)
			{
				init_game(env);
				env->screen_menu = 1;
				env->ingame = 1;
				env->newgame = 0;
			}
		}
		else if (1 == *i)
		{
			env->newgame = 0;
			env->question = 0;
			*i = 1;
		}
	}
}

void	question_event(SDL_Event event, t_env *env, int *i)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (KEY == SDLK_LEFT || KEY == SDLK_RIGHT)
		{
			if (0 == *i)
				*i = 1;
			else if (1 == *i)
				*i = 0;
		}
		question_enter_event(event, env, i);
	}
}

void	print_black_screen(t_env *env)
{
	SDL_Rect	pos;
	Uint8		*pixel;

	pos.x = 0;
	while (pos.x < WIDTH)
	{
		pos.y = 0;
		while (pos.y < HEIGHT)
		{
			pixel = (Uint8 *)env->screen->pixels + pos.y * env->screen->pitch +
				pos.x * env->screen->format->BytesPerPixel;
			pixel[1] = 0;
			pixel[2] = 0;
			pixel[3] = 0;
			pos.y += 1;
		}
		pos.x += 1;
	}
}

void	print_question(t_env *env, int *i)
{
	SDL_Rect	pos;

	print_black_screen(env);
	pos.x = WIDTH / 2 - MENU.warning->w / 2;
	pos.y = HEIGHT / 3;
	get_font_color(env, MENU.warning, pos);
	pos.x = WIDTH / 2 - MENU.question->w / 2;
	pos.y += env->hud.size + 5;
	get_font_color(env, MENU.question, pos);
	pos.x = WIDTH / 3 - MENU.yes->w / 2;
	pos.y = (HEIGHT / 3) * 2;
	get_font_color(env, MENU.yes, pos);
	pos.x = (WIDTH / 3) * 2 - MENU.no->w / 2;
	get_font_color(env, MENU.no, pos);
	if (0 == *i % 2)
		pos.x = WIDTH / 3 - MENU.yes->w / 2 - MENU.row->w;
	else
		pos.x = (WIDTH / 3) * 2 - MENU.no->w / 2 - MENU.row->w;
	get_font_color(env, MENU.row, pos);
}
