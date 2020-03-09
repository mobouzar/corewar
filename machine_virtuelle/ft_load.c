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
    ft_memset((void *)s, '0', sizeof(s));
    while (i >= 0 && j >= 0)
    {
        s[--i] = str[p[j] % 16];
        s[--i] = str[(p[j] / 16) % 16];
        j--;
    }
    return (s);
}

int ft_sign(unsigned int s, int size)
{
    char *str = addr_to_hex(&s, size);

    if (str[0] >= '0' && str[0] <= '7')
        return (hex(str));
    else
    {
        s = hex(addr_to_hex(&s, size));
        s = (~s) - 1;
        return (s);
    }
    return 0;
}

int main(int argc, char **argv)
{
    t_header *lst;
     t_corewar *war;
    (void)argc;
    (void)argv;

    // unsigned int s = 0x3e1;
    //  lst = ft_read_file(argv[1]);
    // printf("dd= %s  str = %s   aa= %d\n", addr_to_hex(&s,4),addr_to_hex(&lst->prog_size,4),lst->prog_size);
    if (!(war = (t_corewar *)malloc(sizeof(t_corewar))))
        return (1);
    ft_memset((void *)war, 0, sizeof(t_corewar));
    lst = ft_read_file(argv[1]);
    war->arena = ft_get_arena();
    get_struct(war);
    ft_memcpy(&war->arena[0], lst->champ, 993);
    ft_memcpy(&war->arena[640], lst->champ, 993);
     ft_print_arena();
}
































// print(&lst->magic, sizeof(lst->magic));
// print(lst->prog_name, sizeof(lst->prog_name));
// print(&lst->prog_size, 4);
// printf("d = %u\n", lst->prog_size);
// print(&lst->comment, sizeof(lst->comment));
// print(&lst->champ, sizeof(char_t) * hex(addr_to_hex(&lst->prog_size, 4)));
// printf("dd = %d ,   in= %d\n", hex(addr_to_hex(&lst->prog_size ,4)), lst->prog_size);