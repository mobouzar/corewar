/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/12 22:06:50 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

int						ft_ld(t_process *p)
{
	t_corewar			*war;
	unsigned	char	byt_arg;
	unsigned	int		byt;
	int					reg;
	int					cr0;

	war = get_corewar(0);
	cr0 = p->pc;
	ft_memcpy(&byt_arg, &war->arena[++p->pc], 1);
	if ((get_size_beyt_flag(p, byt_arg, 2)) > 0)
	{
		p->pc++;
		byt = return_data_of_arg(p, ((byt_arg >> 6) & 0x03), 2, cr0);
		if ((reg = read_regster(p)) != -1 && p->erorr != -1)
		{
			ft_memcpy(&p->regster[reg - 1], &byt, 4);
			p->carry = (!p->regster[reg - 1]) ? 1 : 0;
		}
		p->erorr = 0;
	}
	p->pc = (p->size_of_flg + cr0) % 4096;
	return (0);
}
