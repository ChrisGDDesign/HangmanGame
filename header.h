#ifndef HEADER_H_
#define HEADER_H_
#include <stdio.h>

//STRUCTS
typedef struct Errors{
    int nb_errors;
    char *draw;
} t_errors;

typedef struct GameStates{
    int play_state;
    int nb_errors;
    int max_errors;
    int difficulty;
    char word_to_find[100];
    char *displayed_word;
    char letters_played[27];
    char played_letter[100];
    t_errors *errors;
    char *words_buffer;
    char **words_array;
    int nb_words;
} t_gamestates;

//FUNCTIONS
void game_manager(void);
char *errors_file_to_buffer(void);
char *words_file_to_buffer(void);
int count_digit_keys(char *str);
int count_words(char *str);
void free_cur_errors(int i, t_errors *errors);
void display_hangman(int nb_errors, char *displayed_word, t_errors *errors);
t_errors *init_error_struct(void);
int init_words_array(t_gamestates *gamestates);
int command_mode(t_gamestates *gamestates, int mode);
char *create_displayed_word(char *str);
void try_play_letter(t_gamestates *gamestates);
int end_game(t_gamestates *gamestates);
int handle_played_letter(t_gamestates *g);
long get_fsize(FILE *file);
char *fill_buffer(long size, FILE *file);
char *pick_random_word(t_gamestates *gamestates);

//UTILS
int ft_atoi(char *str);
int ft_strlen(char *str);
char *ft_strncpy(char *dest, char *src, size_t length);
int ft_strcmp(char *str1, char *str2);
void ft_putstr(char *str);
char *ft_strstr(char *mainstr, char *substr);
char *ft_strchr(char *str, char c);
char *ft_capitalize(char *str);
int scan_letter(char c);
int scan_word(char *str);
int seek_letter(char played_letter, char *word_to_find);
void free_errors(t_errors *errors);
void flush_stdin(void);

#endif