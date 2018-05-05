/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoptere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 18:24:23 by asoptere          #+#    #+#             */
/*   Updated: 2018/02/07 18:46:26 by asoptere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int	main(int argc, char **argv)
{
	int		fd;
	t_piece	**pieces;
	int		count;

	count = 0;
	if (argc == 2)
	{
		pieces = (t_piece**)malloc(sizeof(t_piece*) * 26);
		fd = open(*(argv + 1), O_RDONLY);
		if (check_file(fd, pieces, &count, 0))
		{
			*(pieces + count) = 0;
			close(fd);
			if (check_newline(argv[1], count))
				generate(pieces, count);
			else
				ft_putstr("error\n");
		}
		else
			ft_putstr("error\n");
	}
	else
		write(1, "usage: [map]\n", 13);
	return (0);
}
