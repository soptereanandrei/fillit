/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoptere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 18:23:48 by asoptere          #+#    #+#             */
/*   Updated: 2018/02/09 13:22:53 by asoptere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

int			check_newline(char *file, int count)
{
	int		fd;
	int		i;
	char	buf[21];
	int		bt;

	fd = open(file, O_RDONLY);
	i = 0;
	while (i < count - 1)
	{
		bt = read(fd, buf, 21);
		i++;
	}
	bt = read(fd, buf, 21);
	if (bt == 20)
		return (1);
	return (0);
}

static	int	check_square(char **tab)
{
	int	i;
	int	j;
	int	blocks;

	i = 0;
	blocks = 0;
	while (*(tab + i))
	{
		j = 0;
		while (*(*(tab + i) + j))
		{
			if (*(*(tab + i) + j) != '.' && *(*(tab + i) + j) != '#')
				return (0);
			if (*(*(tab + i) + j) == '#')
				if (++blocks > 4)
					return (0);
			j++;
		}
		if (j != 4)
			return (0);
		i++;
	}
	if (i != 4 || blocks != 4)
		return (0);
	return (1);
}

int			check_file(int fd, t_piece **pieces, int *count, int ok)
{
	char	buf[22];
	char	**tab;
	int		bt;

	while ((bt = read(fd, buf, 21)))
	{
		if (bt == -1)
			return (0);
		if (buf[0] != '.' && buf[0] != '#')
			return (0);
		buf[20] = '\0';
		tab = ft_strsplit(buf, '\n');
		if (check_square(tab))
			*(pieces + *count) = to_piece(tab, *count, &bt);
		else
			return (0);
		free(tab);
		(*count)++;
		ft_bzero(buf, 22);
		if (!bt)
			return (0);
		ok = 1;
	}
	return (ok);
}
