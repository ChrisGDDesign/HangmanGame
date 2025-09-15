#include "header.h"

int check_end_condition(t_gamestates *g, int win)
{
    int cmd;
    if (win)
        ft_putstr("---You won! Q=quit, R=reset---\n");
    else
        ft_putstr("---You lost! Q=quit, R=reset---\n");

    cmd = command_mode(g, 1);
    if (cmd == 1) return 1;
    if (cmd == 2) return 2;
    return 0;
}

int end_game(t_gamestates *gamestates)
{
    int cmd;

    while (gamestates-> play_state == 3)
    {
        if (ft_strcmp(gamestates-> displayed_word, gamestates-> word_to_find) == 0)
            return check_end_condition(gamestates, 1);

        if (gamestates-> nb_errors >= gamestates-> max_errors)
            return check_end_condition(gamestates, 0);
    }
    return (0);
}