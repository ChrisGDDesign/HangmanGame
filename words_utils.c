#include <stdlib.h>
#include "header.h"

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