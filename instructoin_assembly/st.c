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
	printf("\n\ninstru ft_st \n\n\n");

	war = get_struct(0);
	cursor0 = p->pc;
	ft_memcpy(&byt_arg, &war->arena[++p->pc], 1);
	size_flg =  get_size_beyt_flag(byt_arg, 3);
	ft_memcpy(&reg, &war->arena[++p->pc], 1);// your must protect this line in segfolte 
	if ((((byt_arg >> 4) & 0x03)& IND_CODE) == IND_CODE)
	{
		ft_memcpy(&data, &war->arena[++p->pc], 2);
		printf("\n\ninstru ft_st resgtr = =     %s  datt== %d	\n\n\n",  addr_to_hex(&data,2), ft_sign(data, 2));
		cpy_reg_to_arena(p, cursor0, ft_sign(data, 2), hex(addr_to_hex(&reg, 1)));
		p->pc++;
	}
	else if ((((byt_arg >> 4) & 0x03)& REG_CODE) == REG_CODE)
	{
		ft_memcpy(&data, &war->arena[++p->pc], 1);//// your must protect this line in segfolte 
		p->regster[hex(addr_to_hex(&data, 1)) - 1] = p->regster[hex(addr_to_hex(&reg, 1)) - 1];
	}
	p->pc++;
	return (0);
}