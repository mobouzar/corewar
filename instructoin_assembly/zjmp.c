/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/09 17:38:39 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"


int zjmp(t_process *p)
{
    t_corewar *war;
    size_t    dir;
    int id;
    
    if (!p->carry)
        return (1);
    war = get_struct(0);
    ft_memcpy((void *)&dir, (void*)war->arena[p->pc + 1], sizeof(size_t));
    return (ft_sign(dir,4) % IDX_MOD);
}
