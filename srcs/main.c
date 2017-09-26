/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 03:52:12 by thchin            #+#    #+#             */
/*   Updated: 2017/08/29 02:16:34 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int	main(int ac, char **av)
{
	t_env	*env;

	(void)ac;
	(void)av;
	if (NULL == (env = init_env()))
		return (0);
	if (FALSE == get_map(env))
		return (0);
	while (1)
		print_img(env);
	return (1);
}
