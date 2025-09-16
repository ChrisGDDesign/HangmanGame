#include <stdlib.h>
#include "header.h"

int ft_atoi(char *str)
{
    int res;
    int i;

    i = 0;
    res = 0;
    while (str[i] != '\0')
    {
        if (str[i] >= '0' && str[i] <= '9')
            res = res * 10 + (str[i] - 48);
        i++;
    }
    return (res);
}

void free_errors(t_errors *errors)
{
    int i;

    i = 0;
    while (errors[i].nb_errors != -1)
    {
        free(errors[i].draw);
        i++;
    }
    free(errors);
}

void flush_stdin(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}