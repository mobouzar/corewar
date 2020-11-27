/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouzar <mobouzar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 10:06:05 by mobouzar          #+#    #+#             */
/*   Updated: 2020/11/28 00:33:12 by mobouzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

int		event_listenner(void)
{
	int	key;

	if ((key = getch()) == -1)
		return (0);
	return (key);
}

void	init_colors(void)
{
	start_color();
	init_pair(PLAYER1, COLOR_RED, 0);
	init_pair(5, 0, COLOR_RED);
	init_pair(PLAYER2, COLOR_GREEN, 0);
	init_pair(6, 0, COLOR_GREEN);
	init_pair(PLAYER3, COLOR_BLUE, 0);
	init_pair(7, 0, COLOR_BLUE);
	init_pair(PLAYER4, COLOR_MAGENTA, 0);
	init_pair(8, 0, COLOR_MAGENTA);
	init_pair(9, 8, 0);
	init_pair(OUT_PROCE, 8, 8);
	init_pair(10, COLOR_WHITE, COLOR_WHITE);
}

void	print_byte(const void *addr, t_visu *visu, int i, int j)
{
	const char	*str = "0123456789abcdef";
	uint8_t		*p;

	p = (uint8_t *)addr;
	mvwprintw(visu->arena, i, j, "%c", str[(p[0] / 16) % 16]);
	mvwprintw(visu->arena, i, j + 1, "%c", str[p[0] % 16]);
}

void	get_winner_color(t_corewar *war, t_visu *visu)
{
	int	last_live;
	int	i;

	i = 0;
	last_live = 0;
	visu->win = BORDER_COLOR;
	while (i < 4)
	{
		if (last_live < war->players[i].last_cycle_to_live)
		{
			last_live = war->players[i].last_cycle_to_live;
			visu->win = i + 5;
		}
		i++;
	}
	border_maker(visu);
}

void	print_winner(t_corewar *war, t_visu *visu)
{
	char *msg;

	msg = ft_nstrjoin(3, "say congrats",\
		war->players[visu->win - 5].data_file->prog_name, "&");
	if (visu->win - 5 >= 0 && visu->win - 5 < 4)
	{
		wattron(visu->menu, A_BOLD);
		wattron(visu->menu, COLOR_PAIR(visu->win - 4));
		mvwprintw(visu->menu, 40, 20, "%s",\
			war->players[visu->win - 5].data_file->prog_name);
		wattroff(visu->menu, COLOR_PAIR(visu->win - 4));
		mvwprintw(visu->menu, 42, 4,\
			"********* Press q to finish. *********");
		wattroff(visu->menu, A_BOLD);
	}
	wrefresh(visu->menu);
	if (!visu->close)
		system(msg);
	ft_strdel(&msg);
	if (!visu->close)
	{
		while (1)
			if (event_listenner() == 'q')
				break ;
	}
}
