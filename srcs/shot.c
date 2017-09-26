/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 04:39:02 by thchin            #+#    #+#             */
/*   Updated: 2017/06/01 05:30:32 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

#define NPC env->npc[env->npcorder[i]]
#define STEXT sprite.text.text
#define SCROSS 16
#define X WIDTH / 2 - SCROSS / 2 + s.x

void	get_midwalldist(t_env *env)
{
	init_dda(env, WIDTH / 2);
	calcul_step(env);
	dda(env);
	calcul_walldist(env);
}

int		check_pixel_perfect(t_env *env, t_sprite sprite)
{
	SDL_Rect	s;
	SDL_Rect	text;
	int			d;
	Uint8		*color;

	s.x = 0;
	while (s.x < SCROSS)
	{
		text.x = (int)((256 * (X - (-sprite.width / 2 + sprite.screenx)) *
						64 / sprite.width) / 256) + sprite.textx;
		s.y = sprite.drawstarty;
		while (s.y < sprite.drawendy)
		{
			d = s.y * 256 - HEIGHT * 128 + sprite.height * 128;
			text.y = ((d * 64) / sprite.height) / 256 + sprite.texty;
			color = (Uint8 *)env->text[STEXT]->pixels +
				text.y * env->text[STEXT]->pitch +
				text.x * env->text[STEXT]->format->BytesPerPixel;
			if (color[0] != 152 && color[1] != 0 && color[2] != 136)
				return (1);
			s.y += 1;
		}
		s.x += 1;
	}
	return (0);
}

int		check_range(t_sprite sprite, double max_dist)
{
	if (sprite.transformy > 0 && sprite.transformy < max_dist &&
		WIDTH / 2 >= sprite.drawstartx && WIDTH / 2 < sprite.drawendx)
		return (1);
	return (0);
}

void	knife_cast(t_env *env, t_weapon *w)
{
	int	i;

	if (w->weapon == 0 && w->fire == 1 && w->bullet == 1 &&
		w->anim == 1)
	{
		i = 0;
		while (w->bullet == 1 && i < NENEMY)
		{
			if (1 == check_range(NPC.sprite, 1.0) &&
				NPC.stance != DEAD && NPC.sprite.text.text == 12 &&
				1 == check_pixel_perfect(env, NPC.sprite))
			{
				NPC.life = 0;
				NPC.stance = DEAD;
				NPC.anim = 0;
				w->bullet = 0;
			}
			i += 1;
		}
	}
}

void	bullet_cast(t_env *env, t_weapon *w)
{
	int	i;

	if (w->weapon > 0 && w->fire == 1 && w->bullet == 1 &&
		(w->anim == 2 || (w->anim == 1 && w->weapon == 3)))
	{
		i = 0;
		while (w->bullet == 1 && i < NENEMY)
		{
			if (1 == check_range(NPC.sprite, env->walldist) &&
				NPC.stance != DEAD && NPC.sprite.text.text == 12 &&
				1 == check_pixel_perfect(env, NPC.sprite))
			{
				NPC.life -= 1;
				NPC.stance = HIT;
				if (NPC.life <= 0)
				{
					NPC.stance = DEAD;
					NPC.anim = 0;
				}
				w->bullet = 0;
			}
			i += 1;
		}
	}
}
