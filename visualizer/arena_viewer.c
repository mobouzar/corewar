/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_viewer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouzar <mobouzar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 11:23:19 by mobouzar          #+#    #+#             */
/*   Updated: 2020/11/20 17:24:52 by mobouzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"
#include <stdio.h>

void		init_struct(t_visu *visu)
{
	visu->close = 1;
	visu->pause = 1;
	visu->key = 32;
	visu->color = GREEN;
}

void		init_colors(t_visu *visu)
{
	// (void)*visu;
	start_color();
	init_pair(0, visu->color_a, visu->color_b);
	init_pair(1, 8, COLOR_WHITE);
	init_pair(2, 8, 0);
	init_pair(4, 15, 15);
	init_pair(3, COLOR_GREEN, COLOR_GREEN);
}

void print_byte(const void *addr, t_visu *visu, int i, int j)
{
    const char	*str = "0123456789abcdef";
    char_t		*p;

    p = (char_t *)addr;
	mvwprintw(visu->arena, i, j, "%c", str[(p[0] / 16) % 16]);
	mvwprintw(visu->arena, i, j + 1, "%c ", str[p[0] % 16]);
}

void	move_process(t_visu *visu, t_corewar *war, int *p)
{
	if (p[0] == visu->cursor)
	{
		wattron(visu->arena, COLOR_PAIR(PROCE_COLOR));
		print_byte(&war->arena[p[0]], visu, p[1], p[2]);
		wattroff(visu->arena, COLOR_PAIR(PROCE_COLOR));
	}
}

void	print_arena(t_corewar *war, t_visu *visu, int i, int j)
{
	int	index;

	index = -1;
	while (++index < 4096)
	{
		if (index != 0 && !(index % 64) && (j = 3))
			i += 1;
		visu->coords[index].y = i;
		visu->coords[index].x = j;
		wattron(visu->arena, COLOR_PAIR(GRAY));
		print_byte(&war->arena[index], visu, i, j);
		wattroff(visu->arena, COLOR_PAIR(GRAY));
		move_process(visu, war, (int []){index, i, j});
		j += 3;
	}
	wrefresh(visu->arena);
}

void	border_maker(t_visu *visu)
{
	initscr();
	nodelay(stdscr, TRUE);
	curs_set(FALSE);
	noecho();
	init_colors(visu);
	visu->arena = subwin(stdscr, 68, 197 , 0, 0);
	visu->menu = subwin(stdscr, 68, 55, 0, 196);

	wattron(visu->arena, COLOR_PAIR(WHITE));
	box(visu->arena, ACS_VLINE, ACS_HLINE);
	wborder(visu->arena, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wattroff(visu->arena, COLOR_PAIR(WHITE));

	wattron(visu->menu, COLOR_PAIR(WHITE));
	box(visu->menu, ACS_VLINE, ACS_HLINE);
	wborder(visu->menu, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wattroff(visu->menu, COLOR_PAIR(WHITE));

}

int		board(t_corewar *war, t_visu *visu)
{
	dprintf(2, "pc<%d> y<%d> x<%d>\n", visu->cursor, visu->coords[visu->cursor].y, visu->coords[visu->cursor].x);
	// move_process(visu, war, (int []){visu->cursor, visu->coords[visu->cursor].y, visu->coords[visu->cursor].x});
	menu_handler(war, visu);
	pause_handler(visu);
	event_handler(visu);
	return (0);
}
