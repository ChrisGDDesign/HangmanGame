#include "header.h"

int seek_letter(char played_letter, char *word_to_find) 
{ 
    if (ft_strchr(word_to_find, played_letter) != NULL) 
        return (1);//letter found at least 1 time 
    else 
        return (0);//not found  
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