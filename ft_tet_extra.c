/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tet_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 13:13:03 by ffoissey          #+#    #+#             */
/*   Updated: 2018/11/29 16:19:15 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	ft_init_tet(t_tet *tet)
{
	unsigned char	i;
	unsigned char	j;
	unsigned char	k;

	i = 0;
	while (i < 26)
	{
		j = 0;
		while (j < 4)
		{
			k = 0;
			while (k < 4)
				tet[i].p[j][k++] = '.';
			tet[i].p[j++][k] = '\0';
		}
		tet[i].spe = 0;
		tet[i].nb = 0;
		tet[i].l = 'A' + i;
		tet[i].heigth = 4;
		tet[i].width = 4;
		tet[i].l_max = 0;
		tet[i].c_max = 0;
		i++;
	}
}

void	ft_area(t_tet *tet, unsigned char i)
{
	short	l;
	short	c;
	short	c_max;
	short	l_max;

	l = -1;
	c_max = 1;
	l_max = 1;
	while (++l < 4)
	{
		c = -1;
		while (++c < 4)
		{
			if (tet[i].p[l][c] != '.')
			{
				if ((c + 1) > c_max)
					c_max = c + 1;
				if ((l + 1) > l_max)
					l_max = l + 1;
			}
		}
	}
	tet[i].c_max = c_max;
	tet[i].l_max = l_max;
}
