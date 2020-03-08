/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/08 14:44:19 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

























int     ft_live(int index)
{
    t_corewar *war;
    size_t    index_player;

    war = get_struct(0);
    ft_memcpy((void *)&index,&war->arena[war->players[index]->pc[0]][war->players[index]->pc[1]],sizeof(size_t)); 
    index_player = hex(addr)




}