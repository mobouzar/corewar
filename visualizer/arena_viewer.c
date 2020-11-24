/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_viewer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouzar <mobouzar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 11:23:19 by mobouzar          #+#    #+#             */
/*   Updated: 2020/11/24 12:37:10 by mobouzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"
#include <stdio.h>

void		init_struct(t_visu *visu)
{
	visu->close = 1;
	visu->pause = 1;
	visu->key = 32;
	visu->last_live_color = BORDER_COLOR;
}

void		init_colors(t_visu *visu)
{
	(void)*visu;
	start_color();
	init_pair(PLAYER1, COLOR_RED, 0);
	init_pair(5, 0, COLOR_RED);

	init_pair(PLAYER2, COLOR_GREEN, 0);
	init_pair(6, 0, COLOR_GREEN);

	init_pair(PLAYER3, COLOR_BLUE, 0);
	init_pair(7, 0, COLOR_BLUE);

	init_pair(PLAYER4, COLOR_MAGENTA, 0);
	init_pair(8, 0, COLOR_MAGENTA);

	init_pair(BOARD_COLOR, 8, 0);
	init_pair(OUT_PROCE, 8, 8);

	init_pair(10, COLOR_WHITE, COLOR_WHITE);
}

void print_byte(const void *addr, t_visu *visu, int i, int j)
{
    const char	*str = "0123456789abcdef";
    char_t		*p;

    p = (char_t *)addr;
	mvwprintw(visu->arena, i, j, "%c", str[(p[0] / 16) % 16]);
	mvwprintw(visu->arena, i, j + 1, "%c", str[p[0] % 16]);
}

void	move_process(t_visu *visu, unsigned char *arena, t_process *p)
{
	int	color;

	color = 0;
	while (p)
	{
		// dprintf(2, "id => |%d|\n", g_coords[p->pc].id);
		if (g_coords[p->pc].id)
			color = g_coords[p->pc].id + 4;
		else
			color = OUT_PROCE;
		wattron(visu->arena, COLOR_PAIR(color));
		print_byte(&arena[p->pc], visu, g_coords[p->pc].y, g_coords[p->pc].x);
		wattroff(visu->arena, COLOR_PAIR(color));
		p = p->next;
	}
}

void	print_arena(t_corewar *war, t_visu *visu, int i, int j)
{
	int	index;
	int	bold;

	bold = 0;
	index = -1;
	while (++index < 4096)
	{
		if (index != 0 && !(index % 64) && (j = 3))
			i += 1;
		g_coords[index].y = i;
		g_coords[index].x = j;
		bold = 0;
		visu->color = BOARD_COLOR;
		if (g_coords[index].id)
			visu->color = g_coords[index].id;
		if (g_coords[index].alpha)
			bold = A_BOLD;
		wattron(visu->arena, bold);
		wattron(visu->arena, COLOR_PAIR(visu->color));
		print_byte(&war->arena[index], visu, i, j);
		wattroff(visu->arena, COLOR_PAIR(visu->color));
		wattroff(visu->arena, bold);
		j += 3;
	}
	move_process(visu, war->arena, war->all_process);
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

	wattron(visu->arena, COLOR_PAIR(visu->last_live_color));
	box(visu->arena, ACS_VLINE, ACS_HLINE);
	wborder(visu->arena, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wattroff(visu->arena, COLOR_PAIR(visu->last_live_color));

	wattron(visu->menu, COLOR_PAIR(visu->last_live_color));
	box(visu->menu, ACS_VLINE, ACS_HLINE);
	wborder(visu->menu, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wattroff(visu->menu, COLOR_PAIR(visu->last_live_color));

}

int		board(t_corewar *war, t_visu *visu)
{
	get_winner(war, visu);
	print_arena(war, visu, 2, 3);
	menu_handler(war, visu);
	pause_handler(visu);
	event_handler(visu);
	usleep(10000);
	return (0);
}
