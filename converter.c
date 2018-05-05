/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conveter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoptere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 18:35:35 by asoptere          #+#    #+#             */
/*   Updated: 2018/02/07 14:15:04 by asoptere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#define ABS(x)  ( (x<0) ? -(x) : (x) )

void		max_min(t_piece *pc)
{
	int		k;

	pc->i_min = 0;
	pc->i_max = 0;
	pc->j_min = 0;
	pc->j_max = 0;
	k = 1;
	while (k < 4)
	{
		if (pc->conf[k].i > pc->i_max)
			pc->i_max = pc->conf[k].i;
		if (pc->conf[k].i < pc->i_min)
			pc->i_min = pc->conf[k].i;
		if (pc->conf[k].j > pc->j_max)
			pc->j_max = pc->conf[k].j;
		if (pc->conf[k].j < pc->j_min)
			pc->j_min = pc->conf[k].j;
		k++;
	}
	reset_start_position(pc);
}

void		set_first(char **tab, t_piece *pc, unsigned int *i, unsigned int *j)
{
	while (tab[*i][*j] != '#')
		if (tab[*i][*j] == '\0')
		{
			*j = 0;
			(*i)++;
		}
		else
			(*j)++;
	pc->conf[0].i = *i;
	pc->conf[0].j = (*j)++;
}

void		set_rest(char **tab, t_piece *pc, unsigned int i, unsigned int j)
{
	int		cnt;

	cnt = 1;
	while (i < 4)
	{
		while (j < 4)
		{
			if (tab[i][j] == '#')
			{
				pc->conf[cnt].i = i - pc->conf[0].i;
				pc->conf[cnt].j = j - pc->conf[0].j;
				cnt++;
			}
			j++;
		}
		j = 0;
		i++;
	}
	pc->conf[0].i = 0;
	pc->conf[0].j = 0;
}

int			check_links(t_piece *pc)
{
	unsigned int i;
	unsigned int j;
	unsigned int ok;

	i = 0;
	j = 0;
	ok = 1;
	while (i < 3)
	{
		j = i + 1;
		while (j < 4)
		{
			if (ABS(pc->conf[j].i - pc->conf[i].i)
					+ ABS(pc->conf[j].j - pc->conf[i].j) == 1)
				ok++;
			j++;
		}
		i++;
	}
	return (ok >= 4);
}

t_piece		*to_piece(char **tab, unsigned int index, int *ok)
{
	t_piece			*new;
	unsigned int	i;
	unsigned int	j;

	new = (t_piece*)malloc(sizeof(t_piece));
	new->letter = 'A' + index;
	i = 0;
	j = 0;
	set_first(tab, new, &i, &j);
	set_rest(tab, new, i, j);
	max_min(new);
	new->used = 0;
	if (!(check_links(new)))
		*ok = 0;
	return (new);
}
