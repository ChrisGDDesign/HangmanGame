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

int is_sep(char c, char *charset)
{
    int i;

    i = 0;
    while (charset[i] != '\0')
    {
        if (c == charset[i])
            return (1);
        i++;
    }
    return (0);
}

char **parser_words(char *str, char **tab)
{
    char *charset;
    int start;
    int end;
    int i;
    int j;

    charset = "\n";
    start = 0;
    i = 0;
    while (str[start] != '\0')
    {
        while (is_sep(str[start], charset))
            start++;
        if (str[start] == '\0')
            break;
        end = start;
        while (!is_sep(str[end], charset) && str[end] != '\0')
            end++;
        tab[i] = malloc(sizeof(char) * (end - start + 1));
        if (!tab[i])
        {
            free_cur_words(i, tab);
            return (NULL);
        }
        j = 0;
        while (start < end)
            tab[i][j++] = str[start++];
        tab[i][j] = '\0';
        i++;
        start = end;
    }
    tab[i] = NULL;
    return (tab);
}
char **init_words_array(void)
{
    char *buffer;
    int array_size;
    char **words_array;

    buffer = words_file_to_buffer();
    if (!buffer)
    {
        ft_putstr("DEBUG: file_to_buffer returned NULL\n");
        return (NULL);
    }
    array_size = count_words(buffer);
    //printf("DEBUG: struct_size = %d\n", struct_size);
    words_array = malloc(sizeof(char *) * (array_size + 1));
    if (!words_array)
    {
        //ft_putstr("DEBUG: malloc failed\n");
        return (NULL);
    }
    words_array = parser_words(buffer, words_array);
    free(buffer);
    if (!words_array)
    {
        //ft_putstr("DEBUG: parser_error failed\n");
        return (NULL);
    }
    return (words_array);
}