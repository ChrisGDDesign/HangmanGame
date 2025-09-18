#include <stdlib.h>
#include "header.h"

int generate_random_number(t_gamestates *gamestates)
{
    int max;
    int random_number;

    max = gamestates-> nb_words;
    random_number = rand() % max;
    return (random_number);
}

char *pick_random_word(t_gamestates *gamestates)
{
    int index;

    index = generate_random_number(gamestates);
    return (gamestates-> words_array[index]);
}