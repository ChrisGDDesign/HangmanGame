#include <stdio.h>
#include <stdlib.h>
#include "header.h"

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

int seek_letter(char played_letter, char *word_to_find) 
{ 
    if (ft_strchr(word_to_find, played_letter) != NULL) 
        return (1);//letter found at least 1 time 
    else 
        return (0);//not found  
}

char *update_displayed_word(char played_letter, char *word_to_find, char *displayed_word)
{
    int i;

    if ((seek_letter(played_letter, word_to_find)) == 0)
        return (NULL);

    i = 0;
    while (word_to_find[i] != '\0')
    {
        if (word_to_find[i] == played_letter 
            || word_to_find[i] == played_letter + 32
            || word_to_find[i] == played_letter - 32)
            displayed_word[i] = word_to_find[i];
        i++;
    }
    return (displayed_word);
}

char *add_letter_played(char *letters_played, char played_letter)
{
    int i;

    i = 0;
    while(letters_played[i] != '\0')
        i++;
    letters_played[i] = played_letter;
    letters_played[i + 1] = '\0';
    return (letters_played);
}

char *create_displayed_word(char *str)
{
    int i;
    int size;
    char *displayed_word;

    size = ft_strlen(str);
    displayed_word = malloc(sizeof(char) * (size + 1));
    if (!displayed_word)
        return (NULL);
    i = 0;
    while (i < size)
    {
        displayed_word[i] = '_';
        i++;
    }
    displayed_word[i] = '\0';
    return (displayed_word);
}

int scan_letter(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return (1);
    else
        return (0);
}

int scan_word(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
            i++;
        else
            return (0);
    }
    return (1);
}

char *ft_capitalize(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (i == 0 && (str[i] >= 'a' && str[i] <= 'z'))
            str[i] -= 32;
        else if ((str[i] >= 'A' && str[i] <= 'Z'))
            str[i] += 32;

        i++;
    }
    return (str);
}

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

int command_mode(t_gamestates *gamestates, int mode)
{
    char quit_or_reset;

    while(1)
    {
        scanf(" %c", &quit_or_reset);
        if (quit_or_reset == 'Q')
        {
            ft_putstr("---Thanks for playing---\n");
            free_errors(gamestates-> errors);
            free(gamestates);
            return (1);//1 = Quit
        }
        else if (quit_or_reset == 'R')
        {
            ft_putstr("---Reinitialization---\n");
            gamestates-> play_state = 0;
            gamestates-> nb_errors = 0;
            gamestates-> letters_played[0] = '\0';
            free(gamestates-> displayed_word);
            gamestates->displayed_word = NULL;
            return (2);//2 = Reset
        }
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

void try_play_letter(t_gamestates *gamestates)
{
    char *res;

    add_letter_played(gamestates-> letters_played, gamestates-> played_letter);
    res = update_displayed_word(gamestates-> played_letter, gamestates-> word_to_find, gamestates-> displayed_word);
    if (res == NULL)
    {
        gamestates-> nb_errors++;
        ft_putstr("/!\\ Wrong letter /!\\\n");
    }
    else
    {
        ft_putstr("OK Right letter OK\n");
        gamestates->displayed_word = res;
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