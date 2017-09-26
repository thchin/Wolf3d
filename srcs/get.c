/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 01:51:25 by thchin            #+#    #+#             */
/*   Updated: 2017/05/10 06:03:33 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "../includes/wolf3d.h"

void	clear_tab(char **tab)
{
	int	i;

	i = 0;
	while (NULL != tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i += 1;
	}
	free(tab);
	tab = NULL;
}

void	get_map_size(t_env *env, char *line)
{
	int	i;

	env->mapwidth = ft_atoi(line);
	i = 0;
	while (line[i] != ' ')
		i += 1;
	i += 1;
	env->mapheight = ft_atoi(&line[i]);
	env->map = NULL;
	if (NULL == (env->map = (int **)malloc(sizeof(int *) * env->mapheight)))
		clear_env(env);
	i = 0;
	while (i < env->mapheight)
	{
		env->map[i] = NULL;
		if (NULL == (env->map[i] = (int *)malloc(sizeof(int) * env->mapwidth)))
			clear_env(env);
		i += 1;
	}
}

void	get_map_line(t_env *env, char *line)
{
	static int	i = 0;
	int			j;
	char		**tab;

	j = 0;
	tab = ft_strsplit(line, ' ');
	while (j < env->mapwidth)
	{
		env->map[i][j] = ft_atoi(tab[j]);
		j += 1;
	}
	clear_tab(tab);
	i += 1;
}

int		get_map(t_env *env)
{
	int		fd;
	char	*line;

	if (0 > (fd = open("map1", O_RDONLY)))
		return (FALSE);
	if (0 >= get_next_line(fd, &line))
	{
		close(fd);
		return (FALSE);
	}
	get_map_size(env, line);
	free(line);
	while (0 < get_next_line(fd, &line))
	{
		get_map_line(env, line);
		free(line);
	}
	return (TRUE);
}
