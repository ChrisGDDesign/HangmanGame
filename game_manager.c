#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void select_word(t_gamestates *gamestates)
{
    int is_word;

    while (gamestates-> play_state == 0)
    {
        ft_putstr("Select a single word for someone else to find\n");
        scanf("%99s", gamestates-> word_to_find);
        is_word = scan_word(gamestates-> word_to_find);
        if (is_word == 1)
        {
            gamestates-> displayed_word = create_displayed_word(gamestates-> word_to_find);
            gamestates-> play_state = 1;
            ft_capitalize(gamestates-> word_to_find);
        }
        else
        {
            ft_putstr("Invalid word\n");
            continue;
        }
    }
}

void select_difficulty(t_gamestates *gamestates)
{
    while (gamestates-> play_state == 1)
    {
        ft_putstr("Select a difficulty: Enter 1 for Easy, 2 for Normal or 3 for Hard\n");
        scanf("%d", &gamestates-> difficulty);
        if (gamestates-> difficulty < 1 || gamestates-> difficulty > 3)
        {
            ft_putstr("Invalid difficulty\n");
            continue;
        }
        if (gamestates-> difficulty == 1)
            gamestates-> nb_errors = 0;
        else if (gamestates-> difficulty == 2)
            gamestates-> nb_errors = 3;
        else
            gamestates-> nb_errors = 6;
        gamestates-> play_state = 2;
    }
}

int end_game(t_gamestates *gamestates)
{
    int cmd;

    while (gamestates-> play_state == 3)
    {
        if (ft_strcmp(gamestates-> displayed_word, gamestates-> word_to_find) == 0)
        {
            ft_putstr("You won, congratulations ! You can chose to quit (enter Q) or reset the game (enter R)!\n");
            cmd = command_mode(gamestates, 1);
            if (cmd == 1)
                return (1);
            else if (cmd == 2)
                return (2);
            else
                return (0);
        }

        if (gamestates-> nb_errors >= gamestates-> max_errors)
        {
            ft_putstr("You lost, too bad ! But you can chose a new word to play again !\n");
            cmd = command_mode(gamestates, 1);
            if (cmd == 1)
                return (1);
            else if (cmd == 2)
                return (2);
            else
                return (0);
        }
    }
    return (0);
}

int play_letter(t_gamestates *gamestates)
{
    int is_letter;
    int cmd;

    while (gamestates-> play_state == 2)
    {
        ft_putstr("---Enter a valid letter not already played(Enter : to go to Command mode)---\n");
        scanf(" %c", &gamestates-> played_letter);
        is_letter = scan_letter(gamestates-> played_letter);
        if (is_letter == 0)
        {
            if (gamestates-> played_letter == ':')
            {
                ft_putstr("---Command mode: Q = Quit, R = Reset. Any other = Back to Play mode---\n");
                cmd = command_mode(gamestates, 0);
                if (cmd == 1)
                    return (1);
                else if (cmd == 2)
                    return (2);
                else
                {
                    ft_putstr("---Play Mode---\n");
                    return (0);
                }
            }
            else
            {
                ft_putstr("Invalid letter\n");
                continue;
            } 
        }
        else if (ft_strchr(gamestates-> letters_played, gamestates-> played_letter) != NULL)
        {
            ft_putstr("Letter played already\n");
            continue; 
        }
        else
            try_play_letter(gamestates);
        display_hangman(gamestates-> nb_errors, gamestates-> displayed_word, gamestates-> errors);
        if ((ft_strcmp(gamestates-> displayed_word, gamestates-> word_to_find) == 0) || (gamestates-> nb_errors >= gamestates-> max_errors))
            gamestates-> play_state = 3;
    }
    return (0);
}

void play_loop(void)
{
    int res;
    t_gamestates *gamestates;

    gamestates = malloc(sizeof(t_gamestates));
    if (!gamestates)
        return;
    gamestates-> play_state = 0;
    gamestates-> errors = init_error_struct();
    if (!gamestates-> errors)
    {
        ft_putstr("Error: could not initialize hangman drawings\n");
        return;
    }
    gamestates-> max_errors = 13;
    while (1)
    {
        select_word(gamestates);
        gamestates-> difficulty = 0;
        select_difficulty(gamestates);
        gamestates-> letters_played[0] = '\0';
        res = play_letter(gamestates);
        if (res == 1)
            break;
        else if (res == 2)
            continue;
        else
            res = end_game(gamestates);

        if (res == 1)
            break;
        else if (res == 2)
            continue;
    } 
    return ;
}