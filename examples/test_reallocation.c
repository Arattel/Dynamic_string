//
// Created by arattel on 31.10.18.
//
#include "my_string.h"
#include <stdio.h>

void main(int* argc, char* argv[]) {
    my_str_t a;
    my_str_t b;
    my_str_from_cstr(&a, "Hello world");
    printf("\nMy str:\"%s\"\n", my_str_getdata(&a));
    printf("Buffer_size: %zu\n", my_str_capacity(&a));
    my_str_reserve(&a, 39);
    my_str_create(&b, 7);
    my_str_copy(&a, &b, 0);
    my_str_shrink_to_fit(&a);
    printf("Buffer_size: %zu\n", my_str_capacity(&a));
    my_str_pushback(&a, 'f');
    my_str_resize(&a, 38, 'n');
    my_str_shrink_to_fit(&b);
    my_str_append_cstr(&b, "allah akbar");
    my_str_insert_c(&a, 'a', 5);
    my_str_free(&a);
    my_str_free(&b);
}
