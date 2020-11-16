
#include "../include/corewar.h"

int ft_ldi(t_process *p)
{
	t_corewar *war;
	unsigned char byt_arg;
	unsigned int byt;
	int data;
	int cursor0;

	war = get_struct(0);
	cursor0 = p->pc;
	ft_memcpy(&byt_arg, &war->arena[++p->pc], 1);
	if ((get_size_beyt_flag( p ,byt_arg, 10)) > 0)
	{
		p->pc++;
		byt = return_data_of_arg(p, ((byt_arg >> 6) & 0x03), 10, cursor0);
		if ((((byt_arg >> 6) & 0x03) & DIR_CODE) == DIR_CODE)
			data = ft_sign(byt, 2);
		else
			data = ft_sign(byt, 4); 
		byt = return_data_of_arg(p, ((byt_arg >> 4) & 0x03), 10, cursor0);
		if ((((byt_arg >> 4) & 0x03) & DIR_CODE) == DIR_CODE)
			data += ft_sign(byt, 2);
		else
			data += ft_sign(byt, 4); 
		if ((int)(byt = read_regster(p)) != -1)
			cpy_arena_to_reg(p, cursor0, data, byt);
		p->pc++;
	}
	else
		p->pc = p->size_of_flg + 	cursor0;
	
	return (0);
}
