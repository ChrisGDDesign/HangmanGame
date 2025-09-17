#include <stdlib.h>
#include "header.h"

int ft_atoi(char *str)
{
    int res;
    int i;

    i = 0;
    res = 0;
    while (str[i] != '\0')
    {
        if (str[i] >= '0' && str[i] <= '9')
            res = res * 10 + (str[i] - 48);
        i++;
    }
    return (res);
}

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

void flush_stdin(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

long get_fsize(FILE *file)
{
    long size;

    fseek(file, 0, SEEK_END);
    size = ftell(file);
    if (size < 0)
        return (-1);
    rewind(file);
    return (size);
}

char *fill_buffer(long size, FILE *file)
{
    char *buffer;

    //malloc buffer
    buffer = malloc(sizeof(char) * (size + 1));
    if (!buffer)
    {
        //ft_putstr("DEBUG: malloc buffer returned NULL\n");
        fclose(file);
        return (NULL);
    }
    //fread in buffer
    if (fread(buffer, 1, size, file) < size)
    {
        //ft_putstr("DEBUG: fread < size returned NULL\n");
        free(buffer);
        return (NULL);
    }
    //Null terminated
    buffer[size] = '\0';
    return (buffer);
}