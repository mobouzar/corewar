#include "../include/corewar.h"

t_header *ft_read_file(char *file)
{
	int fd;
	t_header *new;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (NULL);
	if (!(new = (t_header *)malloc(sizeof(t_header))))
		return (NULL);
	ft_memset((void *)new, 0, sizeof(t_header));
	if ((read(fd, (void *)&new->magic, sizeof(unsigned int))) < 0)
		return (NULL);
	if ((read(fd, (void *)new->prog_name, sizeof(char) * (PROG_NAME_LENGTH + 4))) < 0)
		return (NULL);
	if ((read(fd, (void *)&new->prog_size, sizeof(unsigned int))) < 0)
		return (NULL);
	if ((read(fd, (void *)new->comment, sizeof(char) * (COMMENT_LENGTH + 4))) < 0)
		return (NULL);
	if ((read(fd, (void *)new->champ, sizeof(char_t) * (CHAMP_MAX_SIZE))) < 0)
		return (NULL);
	return (new);
}

int hextodecimal(char val)
{
	const char tab[16] = "0123456789abcdef";
	int i;
	i = -1;
	while (++i < 16)
	{
		if (val == tab[i])
		{
			return (i);
		}
	}
	return (-1);
}
int hex(char *value)
{
	int result;
	int base;
	int len;

	base = 1;
	result = 0;
	len = ft_strlen(value);
	while (--len >= 0)
	{
		result += hextodecimal(value[len]) * base;
		base *= 16;
	}
	return (result);
}

void print(const void *addr, size_t size)
{
	const char *str = "0123456789abcdef";
	size_t i;
	size_t j;
	char_t *p;

	p = (char_t *)addr;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < 16 && i + j < size)
		{
			ft_putchar(str[(p[i + j] / 16) % 16]);
			ft_putchar(str[p[i + j] % 16]);
			if (j % 2)
				ft_putchar(' ');
			j++;
		}
		ft_putchar('\n');
		i += 16;
	}
}

char *addr_to_hex(void *addr, size_t size)
{
	const char *str = "0123456789abcdef";
	char_t *p;
	int j;
	int i;
	char *s;

	s = ft_strnew(size * 2);
	p = (char_t *)addr;
	i = -1;
	j = 0;
	j = size - 1;
	i = (int)(size * 2);
	ft_memset((void *)s, 0, sizeof(s));
	while (i >= 0 && j >= 0)
	{
		s[--i] = str[p[j] % 16];
		s[--i] = str[(p[j] / 16) % 16];
		j--;
	}
	// printf("%s ",s);
	return (s);
}

static short		rev(unsigned char *s)
{
	unsigned short a;

	a = 0;
	//  printf("sss => %d\n", *(int*)s);
	 a |= ((s[0]) & (0xff)) << 8;
	 a |= ((s[1]) & (0xff));
	 a = (a - 1);
	 a = ~a;
	return (a);
}

int ft_sign(unsigned int s, int size)
{
	char *str = addr_to_hex(&s, size);
	// printf("s => %s\n", str);
	if (str[0] >= '0' && str[0] <= '7')
		return (hex(str));
	else
	{
		return ( -1 * rev((unsigned char *)&s));
	}
	return 0;
}

// unsigned int	binary_rev(unsigned char *str)
// {
// 	unsigned char a[4];

// 	a[3] = str[0];
// 	a[2] = str[1];
// 	a[1] = str[2];
// 	a[0] = str[3];
// 	return (*(unsigned  int *)a);
// }


// unsigned int	binary_rev(unsigned char *s)
// {
// 	unsigned int a;

// 	a = 0;

// 	a |= (s[0] & (0xff)) <<24;
	
// 	a |= ((s[1]) & (0xff)) <<16;
// 	a |= ((s[2]) & (0xff)) << 8;
// 	a |= ((s[3]) & (0xff));
// 	return (a);
// }

 unsigned int	binary_rev( unsigned int s)
{
	unsigned int a;

	a = 0;
	a |= ((s) & (0xff)) <<24;
	a |= ((8 >>s) & (0xff)) <<16;
	a |= ((16 >> s) & (0xff)) << 8;
	a |= ((24 >> s) & (0xff));
	return (a);
}


void	ft_init_process(t_corewar *war)
{
	int	i;

	i = -1;
	while (++i < war->nbr_fighters)
	{
		if (!(war->players[i].process = (t_process*)malloc(sizeof(t_process))))
			return ;
		ft_memset((void*)war->players[i].process, 0, sizeof(t_process));
		war->players[i].process->id = i + 1;
		war->players[i].process->regster[0] = 0xffffffff;
		//binary_rev((i + 1));

	}
}

int main(int argc, char **argv)
{

	(void)argc;
	(void)argv;
// unsigned int a = 1;
// 	 printf("u=%u  v=%u     hex = %u\n",binary_rev(a),a ,hex("ffffffff"));
	

	// unsigned int a = 19; 
	// printf("ss = %u  gg = %u\n",(~a), a);
	t_header *lst;
	t_corewar *war;

	if (!(war = (t_corewar *)malloc(sizeof(t_corewar))))//285212672
		return (1);
	ft_memset((void *)war, 0, sizeof(t_corewar));
	war->nbr_fighters = argc - 1;
	ft_init_process(war);
	// printf("register => %s\n",addr_to_hex(&war->players[0].process->regster[0] ,4));
	lst = ft_read_file(argv[1]);
	war->arena = ft_get_arena();
	get_struct(war);
	ft_memcpy(&war->arena[0], lst->champ, hex(addr_to_hex(&lst->prog_size,4)));
	// ft_memcpy(&war->arena[640], lst->champ, hex(addr_to_hex(&lst->prog_size,4)));
	 ft_loop();
	// ft_print_arena();

	return (0);
}
































// print(&lst->magic, sizeof(lst->magic));
// print(lst->prog_name, sizeof(lst->prog_name));
// print(&lst->prog_size, 4);
// printf("d = %u\n", lst->prog_size);
// print(&lst->comment, sizeof(lst->comment));
// print(&lst->champ, sizeof(char_t) * hex(addr_to_hex(&lst->prog_size, 4)));
// printf("dd = %d ,   in= %d\n", hex(addr_to_hex(&lst->prog_size ,4)), lst->prog_size);