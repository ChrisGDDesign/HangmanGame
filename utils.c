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

int handle_played_letter(t_gamestates *g)
{
    if (!scan_letter(g->played_letter))
    {
        if (g->played_letter == ':')
        {
            ft_putstr("---Q to quit, R to restart---\n");
            return command_mode(g, 0);
        }
        ft_putstr("Invalid letter\n");
        return 0;
    }
    if (ft_strchr(g->letters_played, g->played_letter))
    {
        ft_putstr("Letter played already\n");
        return 0;
    }
    try_play_letter(g);
    return 0;
}