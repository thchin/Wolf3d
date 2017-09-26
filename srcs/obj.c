/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 01:31:33 by thchin            #+#    #+#             */
/*   Updated: 2017/07/11 09:33:58 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

#define OBJ env->obj[i]
#define SPRITE env->obj[i].sprite
#define TEXT env->obj[i].sprite.text

void	hit_obj(t_env *env)
{
	int	i;

	i = 0;
	while (i < NOBJ)
	{
		if (1 == OBJ.active && (int)env->posx == (int)TEXT.x &&
			(int)env->posy == (int)TEXT.y)
		{
			update_inventory(env, TEXT.type);
			OBJ.active = 0;
			if (WELL == TEXT.type)
				SPRITE.textx = 65 * 4;
		}
		i += 1;
	}
}

void	update_obj(t_env *env)
{
	int	i;

	i = 0;
	order_obj(env);
	while (i < NOBJ)
	{
		set_sprite(env, &SPRITE);
		i += 1;
	}
}

void	obj_casting(t_env *env, int x)
{
	int	i;
	int	y;

	i = 0;
	while (i < NOBJ)
	{
		if ((1 == OBJ.active || (0 == OBJ.active && WELL == TEXT.type)) &&
			SPRITE.transformy > 0 && SPRITE.transformy < env->dda.walldist &&
			x >= SPRITE.drawstartx && x < SPRITE.drawendx)
		{
			y = SPRITE.drawstarty;
			while (y < SPRITE.drawendy)
			{
				if (SPRITE.transformy < env->spritebuffer[y])
					get_sprite_color(env, SPRITE, x, y);
				y += 1;
			}
		}
		i += 1;
	}
}
