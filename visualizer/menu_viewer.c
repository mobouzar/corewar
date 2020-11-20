/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_viewer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouzar <mobouzar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 11:22:18 by mobouzar          #+#    #+#             */
/*   Updated: 2020/11/20 17:50:15 by mobouzar         ###   ########.fr       */
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

void		pause_handler(t_visu *visu)
{
	wattron(visu->menu, A_BOLD);
	if (!(visu->pause % 2 == 0))
	{
		mvwprintw(visu->menu, 2, 4, "*** PAUSED ***");
		wrefresh(visu->menu);
		while (1)
		{
			if (event_listenner() == 32)
			{
				visu->pause++;
				break ;
			}
		}
		mvwprintw(visu->menu, 2, 4, "*** RUNNING ***");
	}
	wattroff(visu->menu, A_BOLD);
}

void		event_handler(t_visu *visu)
{
	visu->key = event_listenner();
	if (visu->key > 0)
	{
		if (visu->key == 32 && (visu->pause++))
			pause_handler(visu);
		else if (visu->key == 'a')
			visu->color_a++;
		else if (visu->key == 's')
			visu->color_b++;
		else if (visu->key == 'z')
			visu->color_a--;
		else if (visu->key == 'x')
			visu->color_b--;
		// else if (visu->key == 43)
		// 	visu->sleep += 300;
		// else if (visu->key == 45 && visu->sleep > 0)
		// 	visu->sleep -= 10;
		// dprintf(open("/dev/ttys003", O_WRONLY), "default |%d|\n", visu->sleep);
		// else if (visu->key == 27)
		// 	visu->close = 0;
		init_colors(visu);
		// dprintf(2, "colora |%d| colors |%d|\n", visu)
	}
	// usleep(10);
}

void	player1_handler(t_visu *visu, t_corewar *war)
{
	mvwprintw(visu->menu, 20, 4, "Playser -1 : ");
	mvwprintw(visu->menu, 20, 17, "%s", war->players[0].name);
	mvwprintw(visu->menu, 21, 6, "Last live");
	mvwprintw(visu->menu, 21, 30, ": %d", 1);
	mvwprintw(visu->menu, 22, 6, "Lives in current period : %d", 1);
}

void	player2_handler(t_visu *visu, t_corewar *war)
{
	mvwprintw(visu->menu, 24, 4, "Playser -2 : ");
	mvwprintw(visu->menu, 24, 17, "%s", war->players[1].name);
	mvwprintw(visu->menu, 25, 6, "Last live");
	mvwprintw(visu->menu, 25, 30, ": %d", 1);
	mvwprintw(visu->menu, 26, 6, "Lives in current period : %d", 1);
}

void	player3_handler(t_visu *visu, t_corewar *war)
{
	mvwprintw(visu->menu, 28, 4, "Playser -3 : ");
	mvwprintw(visu->menu, 28, 17, "%s", war->players[2].name);
	mvwprintw(visu->menu, 29, 6, "Last live");
	mvwprintw(visu->menu, 29, 30, ": %d", 1);
	mvwprintw(visu->menu, 30, 6, "Lives in current period : %d", 1);
}

void	player4_handler(t_visu *visu, t_corewar *war)
{
	mvwprintw(visu->menu, 32, 4, "Playser -4 : ");
	mvwprintw(visu->menu, 32, 17, "%s", war->players[3].name);
	mvwprintw(visu->menu, 33, 6, "Last live");
	mvwprintw(visu->menu, 33, 30, ": %d", 1);
	mvwprintw(visu->menu, 34, 6, "Lives in current period : %d", 1);
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
	wattroff(visu->menu, A_BOLD);
	wrefresh(visu->menu);
}
