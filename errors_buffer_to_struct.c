#include "header.h"
#include <stdlib.h>

void free_cur_errors(int i, t_errors *errors)
{
    while (i >= 0)
    {
        free(errors[i].draw);
        i--;
    }
    free(errors);
}

char *parse_error_line(int i, char *buffer, t_errors *errors)
{
    char *start;
    char *end;
    char *tmp;
    size_t len;

    start = ft_strstr(buffer, "ERRORS");
    if (!start)
        return (NULL);
    start += ft_strlen("ERRORS");
    end = ft_strstr(start, "DRAW");
    if (!end)
        return (NULL);
    len = end - start;
    tmp = malloc(sizeof(char) * (len + 1));
    if (!tmp)
        return (NULL);
    ft_strncpy(tmp, start, len);
    errors[i].nb_errors = ft_atoi(tmp);
    free(tmp);
    buffer = end;
    return (buffer);
}

char *parse_draw_line(int i, char *buffer, t_errors *errors)
{
    char *start;
    char *end;
    size_t len;

    start = ft_strstr(buffer, "DRAW");
    if (!start)
        return (NULL);
    start += ft_strlen("DRAW");
    end = ft_strstr(start, "END");
    if (!end)
        return (NULL);
    len = end - start;
    errors[i].draw = malloc(sizeof(char) * (len + 1));
    if (!errors[i].draw)
    {
        free_cur_errors(i, errors);
        return (NULL);
    }
    ft_strncpy(errors[i].draw, start, len);
    buffer = end + ft_strlen("END");
    return (buffer);
}

t_errors *parser_error(char *buffer, t_errors *errors)
{
    int i;

    i = 0;
    while (*buffer != '\0')
    {
        buffer = parse_error_line(i, buffer, errors);
        if (!buffer)
        {
            free_cur_errors(i, errors);
            return (NULL);
        }
        buffer = parse_draw_line(i, buffer, errors);
        if (!buffer)
        {
            free_cur_errors(i, errors);
            return (NULL);
        }
        i++;
    }
    errors[i].nb_errors = -1;
    errors[i].draw = NULL;
    return (errors);
}
t_errors *init_error_struct(void)
{
    char *buffer;
    int struct_size;
    t_errors *errors;

    buffer = file_to_buffer();
    if (!buffer)
    {
        ft_putstr("DEBUG: file_to_buffer returned NULL\n");
        return (NULL);
    }
    struct_size = count_digit_keys(buffer);
    //printf("DEBUG: struct_size = %d\n", struct_size);
    errors = malloc(sizeof(t_errors)* (struct_size + 1));
    if (!errors)
    {
        //ft_putstr("DEBUG: malloc failed\n");
        return (NULL);
    }
    errors = parser_error(buffer, errors);
    free(buffer);
    if (!errors)
    {
        //ft_putstr("DEBUG: parser_error failed\n");
        return (NULL);
    }
    return (errors);
}