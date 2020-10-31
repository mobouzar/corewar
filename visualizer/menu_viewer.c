/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_viewer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 11:22:18 by mobouzar          #+#    #+#             */
/*   Updated: 2020/10/31 11:22:21 by mobouzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

int		pause_handler(int listener)
{
	int ctrl;

	ctrl = 0;
	if (listener % 2 == 0)
		ctrl = 1;
	else
		ctrl = 0;
	dprintf(open("/dev/ttys002", O_WRONLY), "key |%d|\n", listener);
	return (ctrl);
}

void	event_handler(t_visu *visu, int listener)
{
	if (visu->key == 32 && !pause_handler(listener++))
			mvwprintw(visu->mwin, 2, 4, "*** PAUSED ***");
	else
		mvwprintw(visu->mwin, 2, 4, "*** RUNNING ***");
}