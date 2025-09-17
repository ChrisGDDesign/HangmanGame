#include <stdio.h>
#include <stdlib.h>
#include "header.h"

char *words_file_to_buffer(void)
{
    FILE *file;
    char *buffer;
    long size;

    //Open file
    file = fopen("words.txt", "r");
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