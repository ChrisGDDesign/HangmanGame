#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void select_word(t_gamestates *gamestates)
{
    int is_word;
    int pick_word;//1 = User choose word to find, 2 = word to find is random
    char *rand_word;

    pick_word = 0;
    while (gamestates-> play_state == 0)
    {
        ft_putstr("---Enter 1 to select a single word for someone else to find, or 2 to generate it randomly---\n");
        if(scanf("%d", &pick_word) != 1)//if scanf doesn't return 1(int), invalid entry
        {
            ft_putstr("Invalid entry\n");
            flush_stdin();
            continue;
        }
        flush_stdin();

        if (pick_word == 1)
        {
            scanf("%99s", gamestates-> word_to_find);
            flush_stdin();

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
        else if (pick_word == 2)
        {
            rand_word = pick_random_word(gamestates);
            ft_strncpy(gamestates-> word_to_find, rand_word, 99);
            gamestates-> displayed_word = create_displayed_word(gamestates-> word_to_find);
            gamestates-> play_state = 1;
            ft_capitalize(gamestates-> word_to_find);
        }
        else
        {
            ft_putstr("Invalid entry\n");
            continue;
        }
        
    }
}

void select_difficulty(t_gamestates *gamestates)
{
    while (gamestates-> play_state == 1)
    {
        ft_putstr("---Select a difficulty: Enter 1 for Easy, 2 for Normal or 3 for Hard---\n");
        if (scanf("%d", &gamestates->difficulty) != 1)
        {
            ft_putstr("Invalid difficulty\n");
            flush_stdin();
            continue;
        }
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
        flush_stdin();
        gamestates-> play_state = 2;
    }
}

int play_letter(t_gamestates *gamestates)
{
    int cmd;

    while (gamestates-> play_state == 2)
    {
        ft_putstr("---Enter a letter (or : for command mode)---\n");
        scanf("%99s", gamestates ->played_letter);
        flush_stdin();

        cmd = handle_played_letter(gamestates);
        if (cmd) 
            return (cmd);

        display_hangman(gamestates->nb_errors, gamestates->displayed_word, gamestates->errors);

        if (ft_strcmp(gamestates ->displayed_word, gamestates ->word_to_find) == 0 
        || gamestates ->nb_errors >= gamestates ->max_errors)
            gamestates->play_state = 3;
    }
    return (0);
}

void play_loop(t_gamestates *g)
{
    int res;

    while (1)
    {
        select_word(g);
        g-> difficulty = 0;
        select_difficulty(g);
        g-> letters_played[0] = '\0';
        res = play_letter(g);
        if (res == 1)
            break;
        else if (res == 2)
            continue;
        else
            res = end_game(g);

        if (res == 1)
            break;
        else if (res == 2)
            continue;
    } 
}

void game_manager(void)
{
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
    if (!init_words_array(gamestates))
    {
        ft_putstr("Error: could not initialize words array\n");
        return;
    }
    for (int i = 0; i < gamestates->nb_words; i++)
        printf("[%d] %s\n", i, gamestates->words_array[i]);
    gamestates-> max_errors = 13;
    play_loop(gamestates);
    return ;
}