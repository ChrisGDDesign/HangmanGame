#ifndef HEADER_H_
#define HEADER_H_
#include <stdio.h>

//STRUCT ERRORS
typedef struct Errors{
    int nb_errors;
    char *draw;
} t_errors;

//FUNCTIONS
void play_loop();
char *file_to_buffer(void);
int count_digit_keys(char *str);
void free_cur_errors(int i, t_errors *errors);
void display_hangman(int nb_errors, char *displayed_word, t_errors *errors);
t_errors *init_error_struct(void);

//UTILS
int ft_atoi(char *str);
int ft_strlen(char *str);
char *ft_strncpy(char *dest, char *src, size_t length);
int ft_strcmp(char *str1, char *str2);
void ft_putstr(char *str);
char *ft_strstr(char *mainstr, char *substr);
char *ft_strchr(char *str, char c);

#endif