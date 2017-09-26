/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 08:41:22 by thchin            #+#    #+#             */
/*   Updated: 2017/08/29 01:58:23 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "../includes/wolf3d.h"

#define MENU env->menu
#define HUD env->hud
#define WARNING "your progression will be lost"

void	init_font_menu(t_env *env)
{
	MENU.menu = IMG_Load("resources/Menu.png");
	MENU.resume = TTF_RenderText_Blended(HUD.police, "resume game", HUD.c);
	MENU.new = TTF_RenderText_Blended(HUD.police, "new game", HUD.c);
	MENU.quit = TTF_RenderText_Blended(HUD.police, "quit game", HUD.c);
	MENU.row = TTF_RenderText_Blended(HUD.police, "-> ", HUD.c);
	MENU.warning = TTF_RenderText_Blended(HUD.police, WARNING, HUD.c);
	MENU.question = TTF_RenderText_Blended(HUD.police, "are you sure ?", HUD.c);
	MENU.yes = TTF_RenderText_Blended(HUD.police, "yes", HUD.c);
	MENU.no = TTF_RenderText_Blended(HUD.police, "no", HUD.c);
}

void	clear_menu(t_menu menu)
{
	SDL_FreeSurface(menu.menu);
	SDL_FreeSurface(menu.resume);
	SDL_FreeSurface(menu.new);
	SDL_FreeSurface(menu.quit);
	SDL_FreeSurface(menu.row);
	SDL_FreeSurface(menu.warning);
	SDL_FreeSurface(menu.question);
	SDL_FreeSurface(menu.yes);
	SDL_FreeSurface(menu.no);
}

void	print_back_menu(t_env *env)
{
	SDL_Rect	pos;
	SDL_Rect	text;
	Uint8		*pixel;
	Uint8		*texture;

	pos.x = 0;
	while (pos.x < WIDTH)
	{
		text.x = (int)((double)pos.x / WIDTH * 320.0);
		pos.y = 0;
		while (pos.y < HEIGHT)
		{
			text.y = (int)((double)pos.y / HEIGHT * 200);
			texture = (Uint8 *)MENU.menu->pixels + text.y * MENU.menu->pitch +
				text.x * MENU.menu->format->BytesPerPixel;
			pixel = (Uint8 *)env->screen->pixels + pos.y * env->screen->pitch +
				pos.x * env->screen->format->BytesPerPixel;
			pixel[1] = texture[0];
			pixel[2] = texture[1];
			pixel[3] = texture[2];
			pos.y += 1;
		}
		pos.x += 1;
	}
}

void	print_row_menu(t_env *env, int i)
{
	SDL_Rect	pos;

	if (0 == i)
	{
		pos.x = WIDTH / 2 - MENU.new->w / 2 - MENU.row->w;
		pos.y = HEIGHT / 3;
	}
	else if (1 == i)
	{
		pos.x = WIDTH / 2 - MENU.resume->w / 2 - MENU.row->w;
		pos.y = HEIGHT / 3 + HEIGHT / 3 / 2;
	}
	else if (2 == i)
	{
		pos.x = WIDTH / 2 - MENU.quit->w / 2 - MENU.row->w;
		pos.y = (HEIGHT / 3) * 2;
	}
	get_font_color(env, MENU.row, pos);
}

void	print_menu(t_env *env, int i)
{
	SDL_Rect	pos;

	if (0 == env->question)
	{
		print_back_menu(env);
		pos.x = WIDTH / 2 - MENU.new->w / 2;
		pos.y = HEIGHT / 3;
		get_font_color(env, MENU.new, pos);
		pos.x = WIDTH / 2 - MENU.quit->w / 2;
		pos.y = (HEIGHT / 3) * 2;
		get_font_color(env, MENU.quit, pos);
		if (1 == env->ingame)
		{
			pos.x = WIDTH / 2 - MENU.resume->w / 2;
			pos.y = HEIGHT / 3 + HEIGHT / 3 / 2;
			get_font_color(env, MENU.resume, pos);
		}
		print_row_menu(env, i);
	}
	else
		print_question(env, &i);
}
