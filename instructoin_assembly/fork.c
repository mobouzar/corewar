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

int   ft_fork(t_process *p)
{
    unsigned int dir;
    t_corewar *war;
    t_process *new;

    war = get_struct(0);
	// ft_putendl("fork");
    ft_memcpy((void *)&dir, (void *)&war->arena[p->pc + 1], 2);
    if (!(new = (t_process *)malloc(sizeof(t_process))))
        return (0);
    ft_memset((void *)new, 0, sizeof(t_process));
    ft_memcpy((void *)new, (void *)p, sizeof(t_process));
    new->pc += ft_sign(dir,2) % IDX_MOD;
    new->next = war->players[p->id - 1].process;
    war->players[p->id - 1].process = new;
	ft_exec(new, war);
	// while(new)
	// {

	// 	printf("ppp1  %d	id = %d\n",new->pc, new->id);
	// 	new = new->next;
	// }
	return (3);
}