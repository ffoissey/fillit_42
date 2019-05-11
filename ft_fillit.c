/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fillit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 13:19:02 by ffoissey          #+#    #+#             */
/*   Updated: 2018/11/29 17:35:53 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void		ft_exit(t_line *line)
{
	if (line)
	{
		ft_strdel(&(line->line));
		while ((get_next_line(line->fd, &line->line)) == 1)
			ft_strdel(&(line->line));
		ft_strdel(&(line->line));
	}
	ft_putendl(ERROR);
	exit(2);
}

void		ft_print_matrix(t_state *state)
{
	unsigned char	l;

	l = 0;
	while (l < state->size)
	{
		write(1, state->mx[l++], state->size);
		write(1, "\n", 1);
	}
}

static void	ft_set_matrix(t_state *state)
{
	unsigned char	l;
	unsigned char	c;

	l = 0;
	while (l < 104)
	{
		c = 0;
		while (c < 104)
			state->mx[l][c++] = '.';
		l++;
	}
}

int			main(int ac, char **av)
{
	t_line			line;
	t_tet			tet[26];
	t_state			state;
	unsigned char	index;

	line.fd = 0;
	index = 0;
	line.line = NULL;
	state.size = 0;
	ft_init_tet(tet);
	if (ac != 2)
	{
		ft_putendl(USAGE);
		return (1);
	}
	if ((line.fd = open(av[1], O_RDONLY)) == -1)
		ft_exit(NULL);
	ft_collect_tets(tet, &line, &index);
	close(line.fd);
	ft_set_matrix(&state);
	state.index = index;
	ft_backtrack(tet, &state);
	return (0);
}
