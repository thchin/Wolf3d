/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 05:40:53 by thchin            #+#    #+#             */
/*   Updated: 2017/05/15 14:31:36 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	weapon_timer(t_weapon *w)
{
	w->time = 0;
	if (w->fire == 1 && w->anim == 0)
		w->anim = 1;
	else if (w->fire == 1 && w->anim == 1)
	{
		if (w->weapon > 0)
			w->ammo[w->weapon] -= 1;
		w->anim = 2;
	}
	else if (w->fire == 1 && w->anim == 2)
	{
		if (w->weapon == 3)
		{
			w->bullet = 1;
			w->ammo[w->weapon] -= 1;
		}
		w->bullet = 1;
		w->anim = 1;
	}
	else if (w->fire == 0 && w->anim > 0)
		w->anim = 0;
}

void	anim_weapon(t_weapon *w)
{
	if (w->ammo[w->weapon] <= 0 && w->weapon > 0)
		w->fire = 0;
	if (w->fire == 1 && (w->ammo[w->weapon] > 0 || w->weapon == 0))
	{
		if (w->fire == 1 && w->anim == 0)
			w->weaponx = 65 * 1;
		else if (w->fire == 1 && w->anim == 1)
			w->weaponx = 65 * 2;
		else if (w->fire == 1 && w->anim == 2)
			w->weaponx = 65 * 3;
	}
	else if (w->fire == 0 && w->anim > 0)
		w->weaponx = 65 * 4;
	else if (w->fire == 0 || w->ammo[w->weapon] <= 0)
	{
		w->bullet = 1;
		w->weaponx = 0;
	}
	if (w->time > 200)
		weapon_timer(w);
}
