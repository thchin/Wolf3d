/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@12.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 03:03:51 by thchin            #+#    #+#             */
/*   Updated: 2017/06/02 09:12:55 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <math.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "../includes/wolf3d.h"

#define SPRITE env->sprite[env->spriteorder[i]]
#define KEY event.key.keysym.sym

void	*my_thread(void *arg)
{
	t_env_th	*env_th;
	t_env		*env;
	int			x;

	env_th = (t_env_th *)arg;
	env = copy_env(env_th->env);
	x = WIDTH * env_th->i / NTHREAD;
	while (x < WIDTH * (env_th->i + 1) / NTHREAD)
	{
		init_dda(env, x);
		calcul_step(env);
		dda(env);
		calcul_walldist(env);
		calcul_height(env);
		calcul_textx(env);
		draw_textline(env, x);
		floor_casting(env, env->floor, x);
		sprite_casting(env, x);
		npc_casting(env, x);
		x += 1;
	}
	free(env);
	pthread_exit(0);
}

void	create_thread(t_env *env)
{
	pthread_t		th[NTHREAD];
	t_env_th		env_th[NTHREAD];
	int				i;
	void			*ret;
	int				check;

	i = 0;
	while (i < NTHREAD)
	{
		env_th[i].i = i;
		env_th[i].env = env;
		check = pthread_create(&th[i], NULL, my_thread, &env_th[i]);
		i += 1;
	}
	i = 0;
	while (i < NTHREAD)
	{
		check = pthread_join(th[i], &ret);
		i += 1;
	}
}

int		print_img(t_env *env)
{
	static int	i = 0;

	key_hook(env, &i);
	if (0 == env->screen_menu)
		print_menu(env, i);
	else if (0 == env->life && 0 == env->dead)
		print_dead(env, &i);
	else if (1 == env->screen_menu && 0 == env->dead)
	{
		move_player(env, env->move);
		move_npc(env);
		update_sprite(env);
		update_npc(env);
		create_thread(env);
		get_midwalldist(env);
		print_weapon(env, &env->weapon);
		anime_npc(env);
		print_hud(env);
		update_time(env);
	}
	SDL_Flip(env->screen);
	return (0);
}
