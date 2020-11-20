/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouzar <mobouzar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 20:24:48 by yelazrak          #+#    #+#             */
/*   Updated: 2020/11/20 16:47:19 by mobouzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

// static void print_byte(const void *addr)
// {
//     const char *str = "0123456789ABCDEF";
//     char_t *p;

//     p = (char_t *)addr;
//     ft_putchar(str[(p[0] / 16) % 16]);
//     ft_putchar(str[p[0] % 16]);
//     ft_putstr(" ");
// }

t_corewar *get_corewar(t_corewar *lst)
{
    static t_corewar *p;

    if (lst)
        p = lst;
    return (p);
}

t_visu  *get_visu(t_visu *visu)
{
	static t_visu	*v;

	if (visu)
		v = visu;
	return (v);
}

char_t *ft_get_arena(void)
{
    char_t *str;

    if (!(str = (char_t *)malloc(sizeof(char_t) * 4096)))
        return (NULL);
    ft_memset((void *)str, 0, sizeof(char_t) * 4096);
    return (str);
}

// void ft_print_arena()
// {
//     t_corewar *war;
//     int i;

//     war = get_corewar(0);
//     i = -1;
//     while (++i < 4096)
//     {
//         if (i != 0 && !(i % 64))
//             ft_putchar('\n');
//         print_byte(&war->arena[i]);
//     }
//     ft_putchar('\n');
//     ft_putchar('\n');
// }


/**
 * ** ila makach flg -v
 */

void print_game()
{
    t_corewar *war;
    int i;

    war = get_corewar(0);
    i = -1;
    ft_putendl("Introducting contestants ...");
    while (++i < war->nbr_fighters)
    {
        ft_printf("* Player %d, weighing 615 bytes, \"%s\" (\"%s\") !\n", i + 1,
                  war->players[i].data_file->prog_name, war->players[i].data_file->comment);
    }
}
