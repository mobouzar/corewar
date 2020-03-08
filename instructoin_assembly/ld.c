/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/08 19:10:39 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"




void        stock(t_process *p,int r,size_t data)
{
    ft_memcpy((void *)&p->regster[r],(void *)data, sizeof(size_t));

}

int         ld(t_process *p)
{
    t_corewar *war;
    char_t  d;
    unsigned short indir;
    unsigned int dir;
    int i;

    war = get_struct(0);
    ft_memcpy((void *)&d,(void *)&war->arena[p->pc + 1], sizeof(char_t));
    if ((d & (4 << 6)))
    {
        ft_memcpy((void *)&dir,(void *)&war->arena[p->pc + 2], sizeof(size_t));

    }
    else
    {
        
    }
    


}