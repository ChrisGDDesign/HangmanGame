#include "header.h"
#include <stdlib.h>

void free_cur_words(int i, char **words_array)
{
    while (i >= 0)
    {
        free(words_array[i]);
        i--;
    }
    free(words_array);
}

int count_words(char *str)
{
    int count;
    int i;

    i = 0;
    count = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '\n')
            count++;
        i++;
    }
    count++;
    return (count);
}

int init_words_array(t_gamestates *gamestates)
{
    char *buffer;
    int count;
    char *ptr;

    count = 0;//count words and is used as index in array
    buffer = words_file_to_buffer();//save file in buffer
    if (!buffer)
        return (0);
    gamestates->words_array = malloc(sizeof(char *) * (count_words(buffer) + 1));
    if (!gamestates->words_array)
    {
        free(buffer);
        return (0);
    }
    ptr = buffer;
    while (*ptr)
    {
        // sauter les séparateurs (\n transformés en \0)
        while (*ptr == '\n')
        {
            *ptr = '\0';
            ptr++;
        }

        if (*ptr == '\0')
            break; // fin du buffer

        // début d'un mot
        gamestates->words_array[count++] = ptr;

        // avancer jusqu'à la fin du mot
        while (*ptr && *ptr != '\n')
            ptr++;
    }
    gamestates-> words_array[count] = NULL;//terminate NULL
    gamestates-> nb_words = count;//Save nb_words
    gamestates-> words_buffer = buffer;//save buffer
    return (1);
}