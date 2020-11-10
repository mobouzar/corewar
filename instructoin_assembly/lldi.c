/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/11 20:12:51 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

int ft_lldi(t_process *p)
{
	t_corewar *war;
	unsigned char byt_arg;
	unsigned int byt;
	int data;
	int size_flg;
	int reg;
	int cursor0;

	war = get_struct(0);
	cursor0 = p->pc;
	ft_memcpy(&byt_arg, &war->arena[++p->pc], 1);
	//size_flg = get_size_beyt_flag(byt_arg, 14);
	if ((size_flg = get_size_beyt_flag(byt_arg, 14)) > 0)
	{
		p->pc++;
		byt = return_data_of_arg(p, ((byt_arg >> 6) & 0x03), 14, cursor0);
		// ft_putendl("444");
		if ((((byt_arg >> 6) & 0x03)) == DIR_CODE)
			data = ft_sign(byt, 2); // hex(addr_to_hex(&byt, 2));
		else
			data = ft_sign(byt, 4); //hex(addr_to_hex(&byt, 4));
		byt = return_data_of_arg(p, ((byt_arg >> 4) & 0x03), 14, cursor0);
		if ((((byt_arg >> 4) & 0x03)) == DIR_CODE)
			data += ft_sign(byt, 2); // hex(addr_to_hex(&byt, 2));
		else
			data += ft_sign(byt, 4); //  hex(addr_to_hex(&byt, 4));
		if ((reg = read_regster(p)) != -1)
		{
			// printf("data = %d    regster = %d  cursor00 = %d  cursor = %d cycle= %d\n\n", data,reg ,cursor0, p->pc , war->cycle);
			cpy_arena_to_reg(p, cursor0, data, reg);
			// p->carry = (!p->regster[reg - 1]) ? 1 : 0;
		}
	}
	// ft_putendl("helllo yassine\n");
	p->pc++;
	return (0);
}