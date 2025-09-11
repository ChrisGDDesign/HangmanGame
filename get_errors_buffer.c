#include <stdio.h>
#include <stdlib.h>
#include "header.h"

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

char *file_to_buffer(void)
{
    FILE *file;
    char *buffer;
    long size;

    //Open file
    file = fopen("errors.txt", "r");
    if (file == NULL)
    {//= !file//
        //ft_putstr("DEBUG: open file returned NULL\n");
        perror("Error opening file");
        return (NULL);
    }
    //Get file size
    size = get_fsize(file);
    if (size < 0)
        {
            //ft_putstr("DEBUG: get_fsize returned NULL\n");
            fclose(file);
            return (NULL);
        }
    //Fill buffer
    buffer = fill_buffer(size, file);
    if (!buffer) 
    {
        //ft_putstr("DEBUG: fill_buffer returned NULL\n");
        fclose(file);
        return (NULL);
    }
    fclose(file);
    return (buffer);
}

int count_digit_keys(char *str)
{
    int count;
    int i;
    int is_digit_line;

    is_digit_line = 0;
    i = 0;
    count = 0;
    while (str[i] != '\0')
    {
        if (str[i] >= '0' && str[i] <= '9')
            is_digit_line = 1;
        if (!(str[i] >= '0' && str[i] <= '9') && is_digit_line == 1)
            {
                is_digit_line = 0;
                count++;
            }    
        i++;
    }
    return (count);
}