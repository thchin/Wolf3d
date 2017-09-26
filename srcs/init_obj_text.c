/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj_text.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 05:42:22 by thchin            #+#    #+#             */
/*   Updated: 2017/06/15 05:45:03 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	init_health_obj(t_sprite *sprite)
{
	if (HEALTH == sprite->text.type)
	{
		sprite->textx = 65 * 2;
		sprite->texty = 65 * 5;
	}
	if (FOOD == sprite->text.type)
	{
		sprite->textx = 65;
		sprite->texty = 65 * 5;
	}
	if (WELL == sprite->text.type)
	{
		sprite->textx = 65 * 3;
		sprite->texty = 65 * 7;
	}
}

void	init_weapon_obj(t_sprite *sprite)
{
	if (SMG == sprite->text.type)
	{
		sprite->textx = 65 * 4;
		sprite->texty = 65 * 5;
	}
	if (MACHINEGUN == sprite->text.type)
	{
		sprite->textx = 0;
		sprite->texty = 65 * 6;
	}
}

void	init_key_obj(t_sprite *sprite)
{
	if (KEY == sprite->text.type)
	{
		sprite->textx = 65 * 2;
		sprite->texty = 65 * 4;
	}
}

void	init_obj_text(t_sprite *sprite)
{
	init_health_obj(sprite);
	init_weapon_obj(sprite);
	init_key_obj(sprite);
}
