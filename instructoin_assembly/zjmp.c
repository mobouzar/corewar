/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/13 19:35:13 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"


int ft_zjmp(t_process *p)
{
    t_corewar *war;
    unsigned int     dir;
    
    if (!p->carry)
        return (3);
	dir  = 0;
    war = get_struct(0);
    ft_memcpy((void *)&dir, (void*)&war->arena[p->pc + 1],2);
    return (ft_sign(dir,2) % IDX_MOD);
}
