/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/12 22:08:39 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

int ft_sti(t_process *p)
{
	t_corewar *war;
	unsigned char byt_arg;
	unsigned int byt;
	long data;
	int size_flg;
	int reg;
	int cursor0;

	// printf("\n\n nnnnnnn \n\n");
	war = get_struct(0);
	cursor0 = p->pc;
	ft_memcpy(&byt_arg, &war->arena[++p->pc], 1);
	// size_flg =  get_size_beyt_flag(byt_arg, 11);
	if ((size_flg = get_size_beyt_flag(byt_arg, 11)) > 0)
	{
		p->pc++;
		if ((reg = read_regster(p)) == -1)
			return (0);
		p->pc++;
		//  printf("sizeof flg = %d\n\n", size_flg);
		byt = return_data_of_arg(p, ((byt_arg >> 4) & 0x03), 11, cursor0);
		// // ft_putendl("444");
		//  printf("sizeof argument22222 = %s\n\n", addr_to_hex(&p->regster[1] , 2));
		//  printf("sizeof argument44444 = %s\n\n", addr_to_hex(&p->regster[1] , 4));
		// printf("sizeof argument11   hexxx  = %s\n\n", addr_to_hex(&byt, 4));

		if ((((byt_arg >> 4) & 0x03)) == DIR_CODE)
			data = ft_sign(byt, 2); // hex(addr_to_hex(&byt, 2));
		else
			data = ft_sign(byt, 4);
		// printf("sizeof argument11  int  = %d\n\n", ft_sign(byt, 4));
		byt = return_data_of_arg(p, ((byt_arg >> 2) & 0x03), 11, cursor0);
		// printf("sizeof argument22   hexxx  = %s\n\n", addr_to_hex(&byt, 2));

		//   printf("sizeof argument22222_--_ int = %d\n\n", ft_sign(byt, 2));

		if ((((byt_arg >> 2) & 0x03)) == DIR_CODE)
			data += ft_sign(byt, 2);
		else
			data += ft_sign(byt, 4);
		//  printf("sizeof len1 data    int = %ld\n\n", data);
		cpy_reg_to_arena(p, cursor0, data, reg);
	}
	else
		p->pc++;
	// // ft_memcpy(&p->regster[reg - 1], &data, size_flg - 1);
	//  printf("sizeof lregesetrdata = %s\n\n", addr_to_hex(&p->regster[1],4));
	//  printf("\n positoin of cursor = %d\n\n", p->pc);
	return (0);
}
