/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arena.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 20:24:48 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/08 15:22:09 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

void print_byte(const void *addr)
{
    const char *str = "0123456789abcdef";
    char_t *p;

    p = (char_t *)addr;
    ft_putchar(str[(p[0] / 16) % 16]);
    ft_putchar(str[p[0] % 16]);
    ft_putstr(" ");
}

t_corewar *get_struct(t_corewar *lst)
{
    static t_corewar *p;

    if (lst)
        p = lst;
    return (p);
}

char_t *ft_get_arena(void)
{
    char_t *str;

    if (!(str = (char_t *)malloc(sizeof(char_t) * 4096)))
        return (NULL);
    ft_memset((void *)str, 0, sizeof(char_t) * 4096);
    return (str);
}

void ft_print_arena()
{
    t_corewar *war;
    int i;

    war = get_struct(0);
    i = -1;
    while (++i < 4096)
    {
        if (i != 0 && !(i % 64))
            ft_putchar('\n');
        print_byte(&war->arena[i]);
    }
}