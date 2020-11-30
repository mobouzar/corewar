/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/12 22:06:55 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

static	void		task_fork(t_process *p, t_process *new, t_corewar *war)
{
	int				i;

	i = 0;
	if (new->pc < 0)
	{
		i = 4096 - ((-1 * new->pc) % 4096);
		new->pc = i;
	}
	new->pc += p->pc;
	new->pc %= SIZE_MAX;
	new->cycle_count = 0;
	war->last_process->next = new;
	war->last_process = war->last_process->next;
}

int					ft_lfork(t_process *p)
{
	unsigned	int	byt;
	t_corewar		*war;
	t_process		*new;

	war = get_corewar(0);
	ft_memcpy((void *)&byt, (void *)&war->arena[p->pc + 1], 2);
	if (!(new = (t_process *)malloc(sizeof(t_process))))
		return (0);
	ft_memset((void *)new, 0, sizeof(t_process));
	ft_memcpy((void *)new, (void *)p, sizeof(t_process));
	war->nbr_process++;
	new->pc = ft_sign(byt, 2);
	new->next = NULL;
	new->cycle_create = war->cycle;
	task_fork(p, new, war);
	p->pc += 3;
	p->pc %= 4096;
	return (0);
}
