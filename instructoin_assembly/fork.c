/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/12 22:07:16 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

int					ft_fork(t_process *p)
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
	new->pc = overrided_pos(ft_sign(byt, 2), p->pc);
	new->cycle_create = war->cycle;
	new->cycle_count = 0;
	new->next = NULL;
	war->last_process->next = new;
	war->last_process = war->last_process->next;
	p->pc += 3;
	p->pc %= 4096;
	return (0);
}
