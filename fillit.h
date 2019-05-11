/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 13:13:11 by ffoissey          #+#    #+#             */
/*   Updated: 2018/11/29 17:24:31 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "libft.h"
# include <fcntl.h>
# define ERROR "error"
# define USAGE "usage: ./fillit source_file"

typedef struct		s_tet
{
	char			p[4][5];
	char			l;
	unsigned char	nb;
	unsigned char	spe;
	unsigned char	heigth;
	unsigned char	width;
	unsigned char	c_max;
	unsigned char	l_max;
}					t_tet;

typedef struct		s_state
{
	unsigned char	mx[104][104];
	unsigned char	index;
	unsigned char	size;
}					t_state;

typedef	struct		s_box
{
	int				loc_c;
	int				loc_l;
	int				c;
	int				l;
}					t_box;

typedef struct		s_line
{
	int				fd;
	char			*line;
}					t_line;

void				ft_collect_tets(t_tet *tet, t_line *l,
					unsigned char *index);
void				ft_exit(t_line *line);
void				ft_init_tet(t_tet *tet);
void				ft_area(t_tet *tet, unsigned char i);
void				ft_backtrack(t_tet *tet, t_state *state);
void				ft_print_matrix(t_state *state);

#endif
