/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_viewer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 11:23:19 by mobouzar          #+#    #+#             */
/*   Updated: 2020/10/31 11:23:26 by mobouzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"
#include <stdio.h>

static void		init_colors(void)
{
	start_color();
	init_pair(1, 7, 7);
	init_pair(2, 8, 0);
	init_pair(3, COLOR_GREEN, COLOR_GREEN);
}

static void print_byte(const void *addr, t_visu *visu, int i, int j)
{
    const char *str = "0123456789abcdef";
    char_t *p;

    p = (char_t *)addr;
	wattron(visu->bwin, COLOR_PAIR(GRAY));
	mvwprintw(visu->bwin, i, j, "%c", str[(p[0] / 16) % 16]);
	mvwprintw(visu->bwin, i, j + 1, "%c ", str[p[0] % 16]);
	wattroff(visu->bwin, COLOR_PAIR(GRAY));
}

 void	print_arena(t_corewar *war, t_visu *visu, int i, int j)
{
	int	index;

	index = -1;
	while (++index < 4096)
	{
		if (index != 0 && !(index % 64))
        {
			i += 1;
			j = 3;
		}
		// dprintf(open("/dev/ttys001", O_WRONLY), "key before => |%c|\n", visu->key);
		if (visu->key != ' ')
        {
			// dprintf(open("/dev/ttys002", O_WRONLY), "key after => |%c|\n", visu->key);
			print_byte(&war->arena[index], visu, i, j);
		}
		j += 3;
	}
}

int		board(t_corewar *war)
{
	t_visu	*visu;
	int		listener;
	// (void )*war;

	listener = 0;
	visu = (t_visu *)ft_memalloc(sizeof(t_visu));
	initscr();
	curs_set(FALSE);
	noecho();
	init_colors();
	visu->bwin = subwin(stdscr, 68, 197 , 0, 0);
	visu->mwin = subwin(stdscr, 68, 55, 0, 196);

	wattron(visu->bwin, COLOR_PAIR(WHITE));
	wborder(visu->bwin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wattroff(visu->bwin, COLOR_PAIR(WHITE));

	wattron(visu->mwin, COLOR_PAIR(WHITE));
	wborder(visu->mwin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wattroff(visu->mwin, COLOR_PAIR(WHITE));

	print_arena(war, visu, 2, 3);
	mvwprintw(visu->mwin, 2, 4, "*** PAUSED ***");
	while ((visu->key = getch()))
	{
		if (visu->key == 27)
			break ;
		event_handler(visu, listener++);
		usleep(100000);
		mvwprintw(visu->mwin, 4, 4, "Cycle : %d", war->cycle);
		// if (war->cycle > 0)
		wrefresh(visu->mwin);
	}
	endwin();
	return (0);
}
