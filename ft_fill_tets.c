/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_tets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 13:22:27 by ffoissey          #+#    #+#             */
/*   Updated: 2018/11/29 17:47:56 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	ft_replace_tet(t_tet *tet, unsigned char i)
{
	unsigned char line;
	unsigned char col;

	line = 0;
	while (line < 4)
	{
		col = 0;
		while (col < 4)
		{
			if (tet[i].p[line][col] == tet[i].l)
			{
				tet[i].p[line - tet[i].heigth][col - tet[i].width] = tet[i].l;
				tet[i].p[line][col] = '.';
			}
			col++;
		}
		line++;
	}
}

static void	ft_justify_tet(t_tet *tet, unsigned char i)
{
	unsigned char	line;
	unsigned char	col;

	line = 0;
	while (line < 4)
	{
		col = 0;
		while (col < 4)
		{
			if (tet[i].p[line][col] == tet[i].l)
			{
				if (tet[i].width > col)
					tet[i].width = col;
				if (tet[i].heigth > line)
					tet[i].heigth = line;
			}
			col++;
		}
		line++;
	}
	if (tet[i].heigth != 0 || tet[i].width != 0)
		ft_replace_tet(tet, i);
	tet[i].heigth = 4 - tet[i].heigth;
	tet[i].width = 4 - tet[i].width;
	ft_area(tet, i);
}

static int	ft_second_check(t_tet *tet, unsigned char i,
			unsigned char c, unsigned char l)
{
	if (l == 3 && tet[i].nb != 4)
		return (FALSE);
	while (c < 4)
	{
		if (c < 2 && tet[i].p[l][c] == tet[i].l && tet[i].p[l][c + 1] == '.')
			if (!c && (tet[i].p[l][c + 2] == tet[i].l
				|| tet[i].p[l][c + 3] == tet[i].l))
				return (FALSE);
		if (l > 0 && tet[i].p[l - 1][c] == tet[i].l
				&& tet[i].p[l][c] == tet[i].l)
			tet[i].spe = 0;
		c++;
	}
	if (tet[i].spe)
		return (FALSE);
	return (TRUE);
}

static void	ft_cp_into_tet(t_tet *tet, unsigned char i,
			unsigned char l, t_line *line)
{
	unsigned char	c;

	c = 0;
	while ((line->line)[c])
	{
		if ((line->line)[c] == '.')
			tet[i].p[l][c] = (line->line)[c];
		else if ((line->line)[c] == '#')
		{
			tet[i].p[l][c] = tet[i].l;
			tet[i].nb++;
			if (l > 0 && tet[i].nb > 1 && ((!c && tet[i].p[l - 1][c] == '.')
				|| (tet[i].p[l - 1][c] == '.' && tet[i].p[l][c - 1] == '.')))
				(tet[i].nb >= 2) ? (tet[i].spe = 1) : ft_exit(line);
		}
		else
			ft_exit(line);
		c++;
	}
	tet[i].p[l][c] = '\0';
	if (!ft_second_check(tet, i, 0, l))
		ft_exit(line);
}

void		ft_collect_tets(t_tet *tet, t_line *l,
			unsigned char *index)
{
	int				ret;
	unsigned char	i;
	unsigned char	line_tet;

	i = 1;
	line_tet = 0;
	while ((ret = get_next_line(l->fd, &(l->line))) == 1)
	{
		if (i++ % 5 == 0)
			(l->line && *(l->line)) ? ft_exit(l) : (line_tet = 0);
		else if (*index >= 26 || !(l->line) || ft_strlen(l->line) != 4)
			ft_exit(l);
		else
			ft_cp_into_tet(tet, *index, line_tet++, l);
		if (line_tet == 4)
		{
			ft_justify_tet(tet, *index);
			(*index)++;
		}
		ft_strdel(&l->line);
	}
	ft_strdel(&l->line);
	if (ret == -1 || !*index || i % *index || i % 5)
		ft_exit(NULL);
}
