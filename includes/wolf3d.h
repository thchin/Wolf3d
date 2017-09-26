/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 03:55:07 by thchin            #+#    #+#             */
/*   Updated: 2017/06/02 09:17:17 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <SDL/SDL.h>
# include <SDL/SDL_ttf.h>
# include "../libft/libft.h"

# define WIDTH 1280
# define HEIGHT 720
# define TRUE 1
# define FALSE 0
# define NSPRITE 19
# define NENEMY 13
# define NTHREAD 4

typedef enum	e_stance
{
	MOVE,
	STAND,
	SHOT,
	HIT,
	DEAD,
}				t_stance;

typedef struct	s_text
{
	double		x;
	double		y;
	int			text;
}				t_text;

typedef struct	s_sprite
{
	t_text		text;
	double		spritex;
	double		spritey;
	double		invdet;
	double		transformx;
	double		transformy;
	int			screenx;
	int			height;
	int			width;
	int			drawstartx;
	int			drawendx;
	int			drawstarty;
	int			drawendy;
	int			textx;
	int			texty;
}				t_sprite;

typedef struct	t_npc
{
	t_sprite	sprite;
	t_stance	stance;
	int			anim;
	double		dirx;
	double		diry;
	int			life;
	int			hit;
	double		deathtimer;
	double		speed;
	double		angle;
}				t_npc;

typedef struct	s_floor
{
	double		wallx;
	double		wally;
	double		distwall;
	double		currentdist;
	double		weight;
	double		currentx;
	double		currenty;
	int			textx;
	int			texty;
	int			text;
}				t_floor;

typedef struct	s_map
{
	int			i;
	int			x;
	int			y;
	int			max_x;
	int			tmpx;
	int			tmpy;
	int			color;
	int			mapx;
	int			mapy;
	t_sprite	sprite;
}				t_map;

typedef struct	s_move
{
	double		move_speed;
	double		rot_speed;
	int			move_up;
	int			move_down;
	int			rot_right;
	int			rot_left;
	int			strafe_left;
	int			strafe_right;
}				t_move;

typedef struct	s_weapon
{
	int			fire;
	int			weapon;
	int			weaponx;
	int			weapony;
	int			bullet;
	int			anim;
	int			ammo[4];
	double		time;
	int			textx;
	int			texty;
	int			size;
	int			drawstartx;
	int			drawendx;
	int			drawstarty;
	int			drawendy;
}				t_weapon;

typedef struct	s_hud
{
	TTF_Font	*police;
	SDL_Surface	*ammo;
	SDL_Surface	*str_ammo;
	SDL_Surface	*life;
	SDL_Surface	*str_life;
	SDL_Surface	*percent;
	SDL_Surface	*str_fps;
	SDL_Surface	*fps;
	SDL_Color	c;
	int			size;
}				t_hud;

typedef struct	s_menu
{
	SDL_Surface	*menu;
	SDL_Surface	*new;
	SDL_Surface	*quit;
	SDL_Surface	*row;
	SDL_Surface	*resume;
}				t_menu;

typedef struct	s_env
{
	SDL_Surface	*screen;
	int			**map;
	int			mapwidth;
	int			mapheight;
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	double		camerax;
	double		rayposx;
	double		rayposy;
	double		raydirx;
	double		raydiry;
	double		mapx;
	double		mapy;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	double		walldist;
	double		stepx;
	double		stepy;
	int			hit;
	int			side;
	int			lineheight;
	int			drawstart;
	int			drawend;
	SDL_Surface	*text[14];
	int			textwidth;
	int			textheight;
	int			text_num;
	double		wallx;
	int			textx;
	t_floor		floor;
	t_move		move;
	t_weapon	weapon;
	t_hud		hud;
	t_menu		menu;
	double		time;
	double		old_time;
	double		frametime;
	double		accumtime;
	double		deathtimer;
	double		spritebuffer[HEIGHT];
	double		zbuffer[WIDTH];
	t_sprite	sprite[NSPRITE];
	int			spriteorder[NSPRITE];
	double		spritedist[NSPRITE];
	t_npc		npc[NENEMY];
	int			npcorder[NENEMY];
	double		npcdist[NENEMY];
	double		midwalldist;
	int			life;
	int			debug;
	int			hurt;
	int			hited;
	int			screen_menu;
	int			ingame;
	int			dead;
}				t_env;

typedef struct	s_env_th
{
	t_env		*env;
	int			i;
}				t_env_th;

t_env			*init_env(void);
void			init_texture(t_env *env);
int				clear_env(t_env *env);
int				get_map(t_env *env);
int				print_img(t_env *env);
int				key_hook(t_env *env, int *i);

void			init_game(t_env *env);

void			init_player(t_env *env);
void			init_move(t_move *move);
void			move_player(t_env *env, t_move move);

void			img_put_pixel(t_env *env, int x, int y, int color);
void			fill_img(t_env *env, int color);

void			init_dda(t_env *env, int x);
void			calcul_step(t_env *env);
void			dda(t_env *env);
void			calcul_walldist(t_env *env);
void			calcul_height(t_env *env);

void			calcul_textx(t_env *env);
void			draw_textline(t_env *env, int x);

void			floor_casting(t_env *env, t_floor f, int x);

void			init_sprite(t_env *env);
void			update_sprite(t_env *env);
void			set_sprite(t_env *env, t_sprite *sprite);
void			order_sprite(t_env *env);
void			sprite_casting(t_env *env, int x);
void			get_sprite_color(t_env *env, t_sprite sprite, int x, int y);

void			init_weapon(t_weapon *weapon);
void			print_weapon(t_env *env, t_weapon *w);
void			anim_weapon(t_weapon *w);
void			knife_cast(t_env *env, t_weapon *w);
void			bullet_cast(t_env *env, t_weapon *w);

void			anime_npc(t_env *env);
void			move_npc(t_env *env);
void			npc_ai(t_env *env, t_npc *npc, t_sprite *sprite);
void			in_sight(t_env *env, t_npc *npc, t_sprite *sprite);

void			init_npc(t_env *env);
void			order_npc(t_env *env);
void			update_npc(t_env *env);
void			npc_casting(t_env *env, int x);

void			init_hud(t_env *env, t_hud *hud);
void			print_hud(t_env *env);
void			get_font_color(t_env *env, SDL_Surface *texte, SDL_Rect pos);

void			print_hurt(t_env *env, int x, int y);

t_env			*copy_env(t_env *src);
void			get_midwalldist(t_env *env);
int				get_direction(double angle);
double			get_angle(t_env *env, t_npc npc);

void			update_time(t_env *env);

void			init_font_menu(t_env *env);
void			menu_event(SDL_Event event, t_env *env, int *i);
void			print_menu(t_env *env, int i);
void			clear_menu(t_menu menu);

void			print_dead(t_env *env, int *i);

#endif
