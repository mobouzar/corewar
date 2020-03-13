/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/13 18:58:37 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

int ft_lld(t_process *p)
{
	t_corewar *war;
	char_t d;
	int len1;
	int len;
	int r;
	int i;
	int ret = 0;

	war = get_struct(0);
	len = p->pc + 2;
	len1 = 0;
	i = 6;
	ft_memcpy((void *)&d, (void *)&war->arena[p->pc + 1], 1);
	if ((r = get_size_of_flag(d, hex(addr_to_hex(&war->arena[p->pc], 1)), &ret)) && ret == 1)
		return (r + 1);
	len1 = shift_byte(d, &len, p, &ret, p->pc + len, 6, 4);
	//  printf("tt = %s\n",addr_to_hex(&len1,4));
	if (ret == 1)
		return (r);
	if ((ret = read_regster(len, war)) == -1)
		return (r + 1);
	// cpy_arena_to_reg(war, p, len1, ret);
	ft_memcpy(&p->regster[ret - 1],&len1,4);
	//  printf("tt = %s\n",addr_to_hex(&p->regster[ret - 1],4));
	// printf("pp = %d\n",ret);
	p->carry = 0;
	if (!p->regster[ret - 1])
		p->carry = 1;
	return (r + 1);
}



// int ft_lld(t_process *p)
// {
//     t_corewar *war;
//     char_t d;
//     unsigned short indir;
//     unsigned int dir;

//     war = get_struct(0);
//     ft_memcpy((void *)&d, (void *)&war->arena[p->pc + 1], sizeof(char_t));
//     if ((d & (4 << 6)) == d)
//     {
//         ft_memcpy((void *)&indir, (void *)&war->arena[p->pc + 2], sizeof(unsigned short));
//         indir = ft_sign((size_t)indir, 2);
//         ft_memcpy((void *)&dir, (void *)&war->arena[p->pc + indir % IDX_MOD], sizeof(unsigned int));
//         ft_memcpy((void *)&d, (void *)&war->arena[p->pc + 4], sizeof(char_t));
//     }
//     else
//     {
//         ft_memcpy((void *)&dir, (void *)&war->arena[p->pc + 2], sizeof(unsigned int));
//         ft_memcpy((void *)&d, (void *)&war->arena[p->pc + 6], sizeof(char_t));
//     }
//     ft_memcpy((void *)&p->regster[hex(addr_to_hex(&d, 1)) - 1], (void *)&dir, sizeof(size_t));
//     p->carry = 0;
//     if (!p->regster[hex(addr_to_hex(&d, 1)) - 1])
//         p->carry = 1;
//     return (0);
// }
