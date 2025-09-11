#include <stdlib.h>

int ft_strcmp(char *str1, char *str2)
{
    int i;

    i = 0;
    while (str1[i] && str2[i])
    {
        if (str1[i] != str2[i])
            return (1);
        i++;
    }
    return (str1[i] != str2[i]);
}

char *ft_strncpy(char *dest, char *src, size_t length)
{
    size_t i;

    i = 0;
    while (i < length && src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    while (i < length) // fill with \0
    {
        dest[i] = '\0';
        i++;
    }
    dest[length] = '\0';
    return (dest);
}

char *ft_strstr(char *mainstr, char *substr)
{
    int i;
    int j;

    if (*substr == '\0') // empty substr
        return (mainstr);

    i = 0;
    while (mainstr[i] != '\0')
    {
        j= 0;
        while (substr[j] != '\0' && mainstr[i + j] == substr[j])
        {
            if (substr[j + 1] == '\0')
                return (&mainstr[i]);
            j++;
        }
        i++;
    }
    return (NULL);
}

char *ft_strchr(char *str, char c)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (c == str[i] || c + 32 == str[i] || c - 32 == str[i])
            return (&str[i]);
        i++;
    }
    if (c == '\0')
        return (&str[i]);
    return (NULL);
}

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
        i++;
    return (i);
}