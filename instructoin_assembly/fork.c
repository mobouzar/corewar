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

int ft_fork(t_process *p)
{
    unsigned int byt;
    t_corewar *war;
    t_process *new;

    war = get_struct(0);
    printf("fork _test debut  ID = %d  cycle = %d    nbr_process = %d \n\n\n ", p->id , war->cycle , war->nbr_process  );
    ft_memcpy((void *)&byt, (void *)&war->arena[p->pc + 1], 2);
    if (!(new = (t_process *)malloc(sizeof(t_process))))
        return (0);
    ft_memset((void *)new, 0, sizeof(t_process));
    ft_memcpy((void *)new, (void *)p, sizeof(t_process));
    war->nbr_process++;
    // new->name = 
    ////dahikin
    // printf("ffforkkk  = %d\n\n", war->nbr_process);

    // new->pc += ft_sign(byt,2) % IDX_MOD;
    //new->id = p->id; /////pour test  
    //new->is_live_more = p->is_live_more;
    new->pc += overrided_pos(ft_sign(byt, 2), p->pc);

    // new->pc %= SIZE_MAX;
    new->cycle_count = 0;
    new->wait = 0;
    // new->next = p->next;
    p->next = new;
    // new->next = war->players[p->id - 1].process;
    // war->players[p->id - 1].process = new;
    // ft_exec(new, war);
    printf("parnt = fork _test END        ID = %d  cycle = %d    nbr_process = %d    is_live= %d    cursor = %d  \n\n\n ", \
    p->id , war->cycle , war->nbr_process , p->is_live_more, p->pc );

      printf("\n\n\n child fork _test END        ID = %d  cycle = %d    nbr_process = %d    is_live= %d    cursor = %d  \n\n\n ", \
    new->id , war->cycle , war->nbr_process , new->is_live_more, new->pc );
    ft_putendl("end_fork\n");
    p->pc += 3;
    return (0);
}