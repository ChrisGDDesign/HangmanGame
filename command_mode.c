#include <stdlib.h>
#include "header.h"

int quit(t_gamestates *gamestates)
{
    ft_putstr("---Thanks for playing---\n");
    free_errors(gamestates-> errors);
    free(gamestates);
    return (1);//1 = Quit
}

int reset(t_gamestates *gamestates)
{
    ft_putstr("---Reinitialization---\n");
    gamestates-> play_state = 0;
    gamestates-> nb_errors = 0;
    gamestates-> letters_played[0] = '\0';
    free(gamestates-> displayed_word);
    gamestates->displayed_word = NULL;
    return (2);//2 = Reset
}

int command_mode(t_gamestates *gamestates, int mode)
{
    char quit_or_reset;

    while(1)
    {
        scanf(" %c", &quit_or_reset);
        flush_stdin();
        if (quit_or_reset == 'Q')
            return (quit(gamestates));//1 = Quit
        else if (quit_or_reset == 'R')
            return (reset(gamestates));//2 = Reset
        else if (mode)
        {
            ft_putstr("Invalid command ! Enter Q to quit or R to reset\n");
            continue;
        }
        else
            return (0);
    } 
    return (0);
}