/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouzar <mobouzar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/11/25 10:24:28 by mobouzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

static void task_init(t_corewar *war, int i, const unsigned int *index)
{
	t_process *new;

	if (!(new = (t_process *)malloc(sizeof(t_process))))
		return;
	ft_memset((void *)new, 0, sizeof(t_process));
	new->id = i + 1;
	new->regster[0] = index[i];
	new->pc = war->players[i].Starting_point;
	inedx_color(new->id , new->pc, new->pc + ft_sign(war->players[i].data_file->prog_size, 4), 0);
	if (!war->last_process && !war->all_process)
	{
		war->all_process = new;
		war->last_process = new;
	}
	else
	{
		war->last_process->next = new;
		war->last_process = war->last_process->next;
	}
}
void ft_init_process(t_corewar *war)
{

	int i;
	const unsigned int index[] = {0xffffffff, 0xfeffffff,
								  0xfdffffff, 0xfcffffff};

	i = -1;
	war->nbr_process = war->nbr_fighters;
	war->cycle_to_die = 1536;
	while (++i < war->nbr_fighters)
	{
		task_init(war, i, index);
	}
}

int hextodecimal(char val)
{
	const char tab[16] = "0123456789abcdef";
	int i;
	i = -1;
	while (++i < 16)
	{
		if (val == tab[i])
		{
			return (i);
		}
	}
	return (-1);
}
