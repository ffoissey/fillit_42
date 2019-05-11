/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_backtrack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 13:23:07 by ffoissey          #+#    #+#             */
/*   Updated: 2018/11/29 17:21:55 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static inline unsigned char	ft_is_ok(t_tet *tet, t_box b, t_state *state,
		const unsigned char pt)
{
	if (pt == 2)
	{
		if (b.l + b.loc_l < state->size && b.c + b.loc_c < state->size)
		{
			if (state->mx[b.loc_l + b.l][b.c + b.loc_c] != '.')
				return (FALSE);
		}
		else
			return (FALSE);
	}
	else
	{
		if (b.l + b.loc_l < state->size && b.c + b.loc_c < state->size)
		{
			if (pt == 1 && state->mx[b.loc_l + b.l][b.c + b.loc_c] == '.')
				state->mx[b.loc_l + b.l][b.c + b.loc_c] = tet->l;
			else if (!pt && state->mx[b.loc_l + b.l][b.c + b.loc_c] == tet->l)
				state->mx[b.loc_l + b.l][b.c + b.loc_c] = '.';
			else
				return (FALSE);
		}
		else
			return (FALSE);
	}
	return (TRUE);
}

static inline unsigned char	ft_check(t_tet *tet, t_box b, t_state *state,
		const unsigned char point)
{
	while (tet->p[b.loc_l][++b.loc_c] == '.')
		b.c--;
	if (b.c < 0)
		return (FALSE);
	while (b.loc_l < tet->l_max)
	{
		b.loc_c = -1;
		while (++b.loc_c < tet->c_max)
		{
			if (tet->p[b.loc_l][b.loc_c] == tet->l)
				if (!ft_is_ok(tet, b, state, point))
					return (FALSE);
		}
		b.loc_l++;
	}
	return (TRUE);
}

static inline unsigned char	ft_first_pow(const unsigned char size)
{
	unsigned char	i;

	i = 2;
	while (i * i < size)
		i++;
	return (i);
}

static unsigned char		ft_place_tets(unsigned char i, t_state *state,
		t_tet *tet)
{
	t_box box;

	box.loc_c = -1;
	box.loc_l = 0;
	if (i == state->index)
		return (TRUE);
	box.l = -1;
	while (++box.l <= state->size)
	{
		box.c = -1;
		while (++box.c <= state->size)
		{
			if (state->mx[box.l][box.c] == '.')
				if (ft_check(tet + i, box, state, 2))
				{
					ft_check(tet + i, box, state, 1);
					if (ft_place_tets(i + 1, state, tet))
						return (TRUE);
					ft_check(tet + i, box, state, 0);
				}
		}
	}
	return (FALSE);
}

void						ft_backtrack(t_tet *tet, t_state *state)
{
	state->size = ft_first_pow(state->index << 2);
	while (!ft_place_tets(0, state, tet))
		state->size++;
	ft_print_matrix(state);
}
