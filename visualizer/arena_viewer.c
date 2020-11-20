/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_viewer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouzar <mobouzar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 11:23:19 by mobouzar          #+#    #+#             */
/*   Updated: 2020/11/19 15:03:26 by mobouzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"
#include <stdio.h>

void		init_struct(t_visu *visu)
{
	visu->close = 1;
	visu->pause = 1;
	visu->key = 32;
	visu->color_a = 8;
	visu->color_s = 0;
}

void		init_colors(t_visu *visu)
{
	start_color();
	init_pair(0, COLOR_BLACK, COLOR_RED);
	init_pair(1, 8, COLOR_WHITE);
	init_pair(2, visu->color_a, visu->color_s);
	init_pair(4, 15, 15);
	init_pair(3, COLOR_GREEN, COLOR_GREEN);

	// init_pair(1, 2, COLOR_BLACK);
    // init_pair(2, COLOR_BLACK, 2);
    // init_pair(3, 10, COLOR_BLACK);
    // init_pair(4, 21, COLOR_BLACK);
    // init_pair(5, COLOR_BLACK, 21);
    // init_pair(6, 33, COLOR_BLACK);
    // init_pair(7, 88, COLOR_BLACK);
    // init_pair(8, COLOR_BLACK, 88);
    // init_pair(9, 160, COLOR_BLACK);
    // init_pair(10, 129, COLOR_BLACK);
    // init_pair(11, COLOR_BLACK, 129);
    // init_pair(12, 201, COLOR_BLACK);
    // init_pair(13, COLOR_BLACK, 244);
    // init_pair(17, 244, COLOR_BLACK);
    // init_pair(14, COLOR_BLACK, 247);
    // init_pair(15, COLOR_BLACK, 255);
    // init_pair(16, COLOR_BLACK, COLOR_BLACK);
    // init_pair(20, 255, COLOR_BLACK);
}

static void print_byte(const void *addr, t_visu *visu, int i, int j)
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
		wattron(visu->arena, A_BOLD);
		print_byte(&war->arena[p[0]], visu, p[1], p[2]);
		wattroff(visu->arena, A_BOLD);
	}
}

void	print_arena(t_corewar *war, t_visu *visu, int i, int j)
{
	int	index;
	int	process;

	index = -1;
	process = 3;
	while (++index < 4096 || process <= visu->cursor)
	{
		if (index != 0 && !(index % 64) && (j = 3))
			i += 1;
		wattron(visu->arena, COLOR_PAIR(GRAY));
		print_byte(&war->arena[index], visu, i, j);
		wattroff(visu->arena, COLOR_PAIR(GRAY));
		move_process(visu, war, (int []){index, i, j, process});
		j += 3;
		process++;
		wrefresh(visu->arena);
	}
}

void	border_maker(t_visu *visu)
{
	initscr();
	nodelay(stdscr, TRUE);
	curs_set(FALSE);
	noecho();
	init_struct(visu);
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
	print_arena(war, visu, 2, 3);
	menu_handler(war, visu);
	pause_handler(visu);
	event_handler(visu);
	return (0);
}
