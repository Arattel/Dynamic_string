//
// Created by arattel on 31.10.18.
//
#include "my_string.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    my_str_t a;
    my_str_from_cstr(&a, "Hello world");
    printf("\nMy str:\"%s\"\n", my_str_getdata(&a));
    printf("Buffer_size: %zu\n", my_str_capacity(&a));
    my_str_reserve(&a, 39);
    printf("Buffer_size: %zu\n", my_str_capacity(&a));
    my_str_shrink_to_fit(&a);
    printf("Buffer_size: %zu\n", my_str_capacity(&a));
    printf("\n After resize:\n");
    my_str_resize(&a, 38, 'b');
    printf("\nMy str:\"%s\", %zu\n", my_str_getdata(&a), my_str_size(&a));
    printf("Buffer_size: %zu\n", my_str_capacity(&a));
    my_str_t b;
    my_str_create(&b, 38);
    my_str_copy(&a, &b, 0);
    printf("B: %s", b.data);
    my_str_insert_c(&b, 'b', 2);
    printf("B: %s", b.data);
    my_str_shrink_to_fit(&b);
    printf("B: %s, %zu", b.data, b.capacity_m);
    my_str_pushback(&b, 'f');
    printf("B: %s, %zu", b.data, b.capacity_m);
    my_str_append_cstr(&b, "alfa");
    printf("B: %s, %zu", b.data, b.capacity_m);
    my_str_free(&a);
    my_str_free(&b);

    return 0;
}

