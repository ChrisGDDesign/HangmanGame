#include <unistd.h>
#include <stdio.h>
#include "header.h"

void ft_putchar(char c)
{
    write(1, &c, 1);
}

void ft_putstr(char *str)
{
    int i;

    i = 0;
    while(str[i] != '\0')
    {
        ft_putchar(str[i]);
        i++;
    }
}

void display_hangman(int nb_errors, char *displayed_word, t_errors *errors)
{
    int i;

    //printf("DEBUG: entering display_hangman with nb_errors=%d\n", nb_errors);
    i = 0;
    while (errors[i].nb_errors != -1)
    {
        //printf("DEBUG: errors[%d].nb_errors=%d\n", i, errors[i].nb_errors);
        if (errors[i].nb_errors == nb_errors)
        {
            //printf("DEBUG: Found match, about to print draw\n");
            ft_putstr(errors[i].draw);
            break;
        }
        i++;
    }
    ft_putchar('\n');
    i = 0;
    while(displayed_word[i] != '\0')
    {
        ft_putchar(displayed_word[i]);
        ft_putchar(' ');
        i++;
    }
    ft_putstr("\n\n");
    //printf("DEBUG: leaving display_hangman\n");
}