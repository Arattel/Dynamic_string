//
// Created by 3naza on 10/25/2018.
//

#ifndef MY_STRING_STRING_H
#define MY_STRING_STRING_H

#include <stdlib.h>
#include <stdio.h>

// typedef struct my_str_t my_str_t;
typedef struct
{
	size_t capacity_m; // Розмір блока
	size_t size_m;	   // Фактичний розмір стрічки
	char*  data;	   // Вказівник на блок пам'яті
} my_str_t;
char *str_copy(char *destination, char *source);
size_t str_len(const char *str);
char *str_cat(char *dest_ptr, const char *src_ptr);
int my_str_empty(const my_str_t *str);
int my_str_from_cstr(my_str_t *str, char *cstr, size_t buf_size);
int my_str_create(my_str_t *str, size_t buf_size);
size_t my_str_size(const my_str_t *str);
void my_str_free(my_str_t *str);
size_t my_str_capacity(const my_str_t *str);
int my_str_pushback(my_str_t *str, char c);
int my_str_append_cstr(my_str_t *str, char *from);
void my_str_clear(my_str_t *str);
int my_str_substr(const my_str_t *str, my_str_t *to, size_t beg, size_t end);
size_t my_str_find(const my_str_t *str, const my_str_t *tofind, size_t from);
int my_str_getc(const my_str_t *str, size_t index);
int my_str_putc(my_str_t *str, size_t index, char c);
int my_str_popback(my_str_t *str);
int my_str_getlast(my_str_t *str);
void my_str_print(const my_str_t *str);
char* my_str_getdata(my_str_t *str);
int my_str_copy(const my_str_t *from, my_str_t *to, int reserve);
int my_str_insert_c(my_str_t *str, char c, size_t pos);
void move_on(my_str_t *str, size_t start_pos, size_t gap);
int my_str_insert(my_str_t *str, my_str_t *from, size_t pos);
int my_str_insert_cstr(my_str_t *str, const char *from, size_t pos);
int my_str_append(my_str_t *str, my_str_t *from);
int my_str_cmp(const my_str_t *str, const char *from);
const char *my_str_get_cstr(my_str_t *str);
size_t my_str_find_c(const my_str_t* str, char tofind, size_t from);
size_t my_str_find_if(const my_str_t* str, int (*predicat)(char));
int my_str_read_file(my_str_t* str, FILE* file);
int my_str_read(my_str_t* str);
int my_str_reserve(my_str_t* str, size_t buf_size);
int my_str_shrink_to_fit(my_str_t* str);
int my_str_resize(my_str_t* str, size_t new_size, char sym);
#endif //MY_STRING_STRING_H
