/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouzar <mobouzar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/11/20 16:46:09 by mobouzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

int ft_aff(t_process *p)
{
	t_corewar *war;
	unsigned char byt_arg;
	int cursor0;
	int reg;
	char aff;


	p->pc += 3;
	war = get_corewar(0);
	cursor0 = p->pc;
	ft_memcpy(&byt_arg, &war->arena[++p->pc], 1);
	if ((get_size_beyt_flag(p, byt_arg, 16)) > 0)
	{
		p->pc++;

		if ((reg = read_regster(p)) != -1)
		{
			p->pc++;
			aff = (char)((int)p->regster[reg -1] % 256);
			////ft_putchar(aff);/////
		}
		p->erorr = 0;
	}	
 	p->pc = p->size_of_flg + cursor0;
	return 0;
}
