/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/12 22:07:03 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

int ft_st(t_process *p)
{
	t_corewar *war;
	unsigned char byt_arg;
	unsigned int data;
	int size_flg;
	int reg;
	int cursor0;
	war = get_struct(0);
	// 	printf("\n\ninstru ft_st cursor = %d    instruction = %d \n\n\n", p->pc, hex(addr_to_hex(&war->arena[p->pc + 1], 1) ));
	// printf("\n\n  dubgg       nbr_cycle out = %d					cycle_die == %d   \
// 	 nbr_cursor == %d	    cycle_last_check == %d     nbr_check ==  %d     nbr_process    = %d  \n\n",
	// 		   war->cycle, war->cycle_to_die, war->players[0].process->pc, war->cycle_last_check, war->nbr_checks, war->nbr_process);
	cursor0 = p->pc;
	ft_memcpy(&byt_arg, &war->arena[++p->pc], 1);
	if ((size_flg = get_size_beyt_flag(byt_arg, 3)) > 0)
	{

		ft_memcpy(&reg, &war->arena[++p->pc], 1); // your must protect this line in segfolte
		if ((((byt_arg >> 4) & 0x03) & IND_CODE) == IND_CODE)
		{
			ft_memcpy(&data, &war->arena[++p->pc], 2);
			//  printf("\n\ninstru ft_st datadatadata   resgtr = =     %d  datt== %d	\n\n\n",  hex(addr_to_hex(&reg, 1)), ft_sign(data, 2));
			cpy_reg_to_arena(p, cursor0, ft_sign(data, 2), hex(addr_to_hex(&reg, 1)));
			p->pc++;
		}
		else if ((((byt_arg >> 4) & 0x03) & REG_CODE) == REG_CODE)
		{
			ft_memcpy(&data, &war->arena[++p->pc], 1); //// your must protect this line in segfolte
			p->regster[hex(addr_to_hex(&data, 1)) - 1] = p->regster[hex(addr_to_hex(&reg, 1)) - 1];
		}
	}
	p->pc++;
	//  ft_putendl("ft_sts_end\n");

	return (0);
}