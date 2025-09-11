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

void play_loop(void)
{
    int play_state;
    int nb_errors;
    int max_errors;
    int difficulty;
    int is_word;
    int is_letter;
    char word_to_find[100];
    char *displayed_word;
    char *res;
    char letters_played[27];
    char played_letter;
    char quit_or_reset;
    t_errors *errors;

    play_state = 0;
    errors = init_error_struct();
    if (!errors)
    {
        ft_putstr("Error: could not initialize hangman drawings\n");
        return;
    }
    max_errors = 13;
    is_word = 0;
    while (1)
    {
        while (play_state == 0)
        {
            ft_putstr("Select a single word for someone else to find\n");
            scanf("%99s", word_to_find);
            is_word = scan_word(word_to_find);
            if (is_word == 1)
            {
                displayed_word = create_displayed_word(word_to_find);
                play_state = 1;
                ft_capitalize(word_to_find);
            }
            else
            {
                ft_putstr("Invalid word\n");
                continue;
            }
        }

        difficulty = 0;
        while (play_state == 1)
        {
            ft_putstr("Select a difficulty: Enter 1 for Easy, 2 for Normal or 3 for Hard\n");
            scanf("%d", &difficulty);
            if (difficulty < 1 || difficulty > 3)
            {
                ft_putstr("Invalid difficulty\n");
                continue;
            }
            else if (difficulty == 1)
                nb_errors = 0;
            else if (difficulty == 2)
                nb_errors = 3;
            else if (difficulty == 3)
                nb_errors = 6;
            play_state = 2;
        }

        letters_played[0] = '\0';
        while (play_state == 2)
        {
            ft_putstr("---Enter a valid letter not already played(Enter : to go to Command mode)---\n");
            scanf(" %c", &played_letter);
            is_letter = scan_letter(played_letter);
            if (is_letter == 0)
            {
                if (played_letter == ':')
                {
                    ft_putstr("---Command mode: Q = Quit, R = Reset. Any other = Back to Play mode---\n");
                    scanf(" %c", &quit_or_reset);
                    if (quit_or_reset == 'Q')
                    {
                        ft_putstr("---Thanks for playing---\n");
                        free_errors(errors);
                        return ;
                    }
                    else if (quit_or_reset == 'R')
                    {
                        ft_putstr("---Reinitialization---\n");
                        play_state = 0;
                        nb_errors = 0;
                        letters_played[0] = '\0';
                        free(displayed_word);
                        break;
                    }
                    else
                    {
                        ft_putstr("---Play Mode---\n");
                        continue;
                    }
                }
                else
                {
                    ft_putstr("Invalid letter\n");
                    continue;
                } 
            }
            else if (ft_strchr(letters_played, played_letter) != NULL)
            {
            ft_putstr("Letter played already\n");
            continue; 
            }
            else
            {
                add_letter_played(letters_played, played_letter);
                res = update_displayed_word(played_letter, word_to_find, displayed_word);
                if (res == NULL)
                {
                    nb_errors++;
                    ft_putstr("/!\\ Wrong letter /!\\\n");
                }
                else
                {
                    ft_putstr("OK Right letter OK\n");
                    displayed_word = res;
                }
            }
            display_hangman(nb_errors, displayed_word, errors);
            if (ft_strcmp(displayed_word, word_to_find) == 0)
            {
                ft_putstr("You won, congratulations ! You can chose to quit (enter Q) or reset the game (enter R)!\n");
                while (1)
                {
                    scanf(" %c", &quit_or_reset);
                    if (quit_or_reset != 'Q' && quit_or_reset != 'R')
                    {
                        ft_putstr("Invalid command ! Enter Q to quit or R to reset\n");
                        continue;
                    }
                    if (quit_or_reset == 'Q' )
                    {
                        free_errors(errors);
                        return;
                    }
                    if (quit_or_reset == 'R' )
                    {
                        play_state = 0;
                        nb_errors = 0;
                        letters_played[0] = '\0';
                        free(displayed_word);
                        break;
                    }    
                }
            }

            if (nb_errors >= max_errors)
            {
                ft_putstr("You lost, too bad ! But you can chose a new word to play again !\n");
                while (1)
                {
                    scanf(" %c", &quit_or_reset);
                    if (quit_or_reset != 'Q' && quit_or_reset != 'R')
                    {
                        ft_putstr("Invalid command ! Enter Q to quit or R to reset\n");
                        continue;
                    }
                    if (quit_or_reset == 'Q' )
                    {
                        free_errors(errors);
                        return;
                    }
                    if (quit_or_reset == 'R' )
                    {
                        play_state = 0;
                        nb_errors = 0;
                        letters_played[0] = '\0';
                        free(displayed_word);
                        break;
                    } 
                }
            }
        }
    }  
}