#include <stdlib.h>
#include "header.h"

int ask_pick_word(t_gamestates *gamestates)
{
    int pick_word;//1 = User choose word to find, 2 = word to find is random

    pick_word = 0;
    ft_putstr("---Enter 1 to select a single word for someone else to find, or 2 to generate it randomly---\n");
    if(scanf("%d", &pick_word) != 1)//if scanf doesn't return 1(int), invalid entry
    {
        ft_putstr("Invalid entry\n");
        flush_stdin();
        return (0);
    }
    flush_stdin();
    return (pick_word);
}

void user_pick_word(t_gamestates *gamestates)
{
    int is_word;

    ft_putstr("---Enter a single word for someone else to find---\n");
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
        return ;
    }
}

void select_random_word(t_gamestates *gamestates)
{
    char *rand_word;

    rand_word = pick_random_word(gamestates);
    ft_strncpy(gamestates-> word_to_find, rand_word, 99);
    gamestates-> displayed_word = create_displayed_word(gamestates-> word_to_find);
    gamestates-> play_state = 1;
    ft_capitalize(gamestates-> word_to_find);
}

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