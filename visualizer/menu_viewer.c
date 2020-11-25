/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_viewer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouzar <mobouzar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 11:22:18 by mobouzar          #+#    #+#             */
/*   Updated: 2020/11/25 14:07:51 by mobouzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

void	pause_handler(t_visu *visu)
{
	wattron(visu->menu, A_BOLD);
	if (visu->pause == 1)
	{
		mvwprintw(visu->menu, 2, 4, "*** PAUSED ***");
		wrefresh(visu->menu);
		while (1)
		{
			visu->key = event_listenner();
			if (visu->key == 27)
				visu->close = 1;
			if (visu->key == 32 || visu->close == 1 || visu->key == 's')
			{
				if (visu->key == 's')
					nodelay(stdscr, FALSE);
				else if (visu->key == 32)
					nodelay(stdscr, TRUE);
				visu->pause = 0;
				break ;
			}
		}
		mvwprintw(visu->menu, 2, 4, "*** RUNNING ***");
	}
	wattroff(visu->menu, A_BOLD);
}

void	event_handler(t_visu *visu)
{
	visu->key = event_listenner();
	if (visu->key > 0)
	{
		if (visu->key == 32)
		{
			nodelay(stdscr, TRUE);
			pause_handler(visu);
			visu->pause = 1;
		}
		else if (visu->key == 27)
			visu->close = 1;
		else if (visu->key == 43)
			visu->cycle_speed += 100;
		else if (visu->key == 45)
			visu->cycle_speed -= 100;
		else if (visu->key == 's')
		{
			nodelay(stdscr, FALSE);
			visu->step = 1;
		}
	}
}

void	menu_handler(t_corewar *war, t_visu *visu)
{
	wattron(visu->menu, A_BOLD);
	mvwprintw(visu->menu, 4, 4, "Cycles/second limit : ");
	mvwprintw(visu->menu, 4, 26, "%d", visu->cycle_speed);
	mvwprintw(visu->menu, 7, 4, "Cycle : %d", war->cycle);
	mvwprintw(visu->menu, 9, 4, "Processes : %d", war->nbr_process);
	mvwprintw(visu->menu, 11, 4, "CYCLE_TO_DIE : %d", war->cycle_to_die);
	mvwprintw(visu->menu, 13, 4, "CYCLE_DELTA : %d", CYCLE_DELTA);
	mvwprintw(visu->menu, 15, 4, "NBR_LIVE : %d", NBR_LIVE);
	mvwprintw(visu->menu, 17, 4, "MAX_CHECKS : %d", MAX_CHECKS);
	player1_handler(visu, war);
	player2_handler(visu, war);
	player3_handler(visu, war);
	player4_handler(visu, war);
	mvwprintw(visu->menu, 37, 18, "THE WINNER'S BOX");
	mvwprintw(visu->menu, 40, 4, "The winner is: ");
	wrefresh(visu->menu);
	wattroff(visu->menu, A_BOLD);
}
