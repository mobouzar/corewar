/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 18:06:05 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/13 18:26:19 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** in this file main programe principall
**
**
**
**
**
**
**
**
*/

#include "../include/corewar.h"

int get_id_player(int id, int flg)
{
	static int array[] = {0, 0, 0, 0};
	int i;

	i = -1;
	if (flg)
	{
		if (id != -1)
		{
			if (array[id - 1] == 2) //222ya3ni mokhd
			{
				array[id - 1] = 1;
				return id;
			}
			else
				return -1;
		}
		while (++i < 4)
		{
			if (!array[i])
			{
				array[i] = 1;
				return i + 1;
			}
		}
	}
	else
		array[id] = 2;
	return -1;
}

int is_intger(char *arg)
{
	int i;
	int n;
	if (!arg)
		return (0);
	i = -1;
	n = ft_strlen(arg);
	while (++i < n)
	{
		if (!ft_isdigit(arg[i]))
			return (0);
	}
	return 1;
}

int is_int(t_corewar *war, char *arg)
{
	if (!is_intger(arg))
		return 0;
	war->dump = ft_atoi(arg);
	return 1;
}

int get_id(char **argv)
{
	int i;
	int index;

	i = 0;
	index = 1;

	while (argv[i])
	{
		if (!ft_strcmp(argv[i], "-n"))
		{
			if (!argv[i + 1] || !is_intger(argv[i + 1]))
				return 0;
			index = ft_atoi(argv[i + 1]);
			if (!(index > 0 && index < 5))
				return 0;
			get_id_player(index - 1, 0);
		}
		i++;
	}

	return -1;
}