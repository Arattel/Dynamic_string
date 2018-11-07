//
// Created by arattel on 27.10.18.
//
#include "my_string.h"
#include <stdio.h>

void main(int* argc, char* argv[]) {
    // Example of type casting
    my_str_t a;
    my_str_t b;
    // Example creation from C-string
    my_str_from_cstr(&a, "Hello world");
    printf("\nMy str:\"%s\"\n", my_str_getdata(&a));
    printf("Buffer_size: %zu\n", my_str_capacity(&a));
    // Example of increasing reserve
    printf("\nIncreasing reserve\n");
    printf("Reserve before: %zu\n", my_str_capacity(&a));
    my_str_reserve(&a, 39);
    printf("Reserve after: %zu\n", my_str_capacity(&a));
    // Example of string creation
    my_str_create(&b, 7);
    // Example of copying
    my_str_copy(&a, &b, 0);
    // Example of shrink
    printf("\nShrinking\n");
    printf("Buffer_size before: %zu\n", my_str_capacity(&a));
    my_str_shrink_to_fit(&a);
    printf("Buffer_size: %zu\n", my_str_capacity(&a));
    // Example of resize
    printf("\nResize\n");
    printf("Before resize: %s", my_str_getdata(&a));
    my_str_resize(&a, 38, 'n');
    printf("After resize: %s", my_str_getdata(&a));
    my_str_shrink_to_fit(&b);
    printf("B: %s, %zu", b.data, b.capacity_m);
    my_str_pushback(&b, 'f');
    printf("B: %s, %zu", b.data, b.capacity_m);
    // Example of appending C-string
    my_str_free(&a);
    my_str_free(&b);

    my_str_t test_string0;

    //Example of pushback function
    printf("Before pushback: %s", my_str_get_cstr(&test_string0));
    my_str_pushback(&test_string0, '1');
    printf("\nPushback");
    printf("\nResult: \"%s\" \n", my_str_getdata(&test_string0));
    printf("Length: %ld\n", my_str_size(&test_string0));

    // Example of appending c-string
    printf("\nAppending c-string\n");
    printf("Before: \"%s\"", my_str_getdata(&test_string0));
    my_str_append_cstr(&test_string0, "3619");
    printf("\nAfter\"%s\" \n", my_str_getdata(&test_string0));
    printf("Length: %ld\n", my_str_size(&test_string0));

    // Example of creation my_str_t from c-string
    printf("\nCreation my_str_t from c-string\n");
    my_str_t test_string1;
    printf("Should be \"Hello word\"");
    my_str_from_cstr(&test_string1, "Hello world");
    printf("Result: \"%s\"\n", my_str_getdata(&test_string1));
    printf("Length: %ld\n", my_str_size(&test_string1));

    // Example of popback function
    printf("\nPopback\n");
    printf("Before: \"%s\"\n", my_str_getdata(&test_string1));
    printf("Length before: %ld\n", my_str_size(&test_string1));
    printf("Character popped: \'%c\'\n", my_str_popback(&test_string1));
    printf("After: \"%s\"\n", my_str_getdata(&test_string1));
    printf("Length after: %ld\n", my_str_size(&test_string1));

    // Example of copying
    printf("\nCopying\n");
    my_str_t test_string2;
    printf("from: %s to %s\n", my_str_get_cstr(&test_string1), my_str_get_cstr(&test_string2));
    my_str_copy(&test_string1, &test_string2, 1);
    printf("After: \"%s\"\n", my_str_getdata(&test_string2));
    printf("Length after: %ld\n", my_str_size(&test_string2));

    my_str_free(&test_string1);

    // Example of size
    printf("\nSize\n");
    printf("Size of test string 2: %ld\n", my_str_size(&test_string2));

    // Example of empty
    printf("\nEmpty\n");
    printf("Test string 2 is empty: %d\n", my_str_empty(&test_string2));

    // Exaple of capacity
    printf("\nCapacity\n");
    printf("Test string 2 capacity: %ld\n", my_str_capacity(&test_string2));

    //Example of substring
    printf("\nSubstring\n");
    my_str_t test_string3;
    my_str_create(&test_string3, 50);
    my_str_t test_string5;
    my_str_copy(&test_string0, &test_string5, 1);
    my_str_free(&test_string0);
    printf("5 is: %s, 3 is: %s\n", my_str_getdata(&test_string5), my_str_getdata(&test_string3));
    my_str_substr(&test_string5, &test_string3, 1, 3);
    printf("Result: \"%s\"\n", my_str_getdata(&test_string3));
    printf("Result length: %ld\n", my_str_size(&test_string3));

    //Example of finding substring
    printf("\nSubstring find\n");
    printf("test string 3 is: %s, test string 5 is: %s\n", my_str_getdata(&test_string3), my_str_getdata(&test_string5));
    printf("Index of test string 3 in test string 0: %ld\n", my_str_find(&test_string5, &test_string3, 0));

    // Example of getting character
    printf("\nGetting character\n");
    printf("Characted on position 3 in test string 0: \'%c\'\n", (char) my_str_getc(&test_string5, 3));

    // Example of putting character
    printf("\nPutting character\n");
    printf("Before: \"%s\"\n", my_str_getdata(&test_string5));
    my_str_putc(&test_string5,  2, 'k');
    printf("After putting character \'k\' in position 2: \"%s\"\n", my_str_getdata(&test_string5));

    // Example of getting last character
    printf("\nGetting last character\n");
    printf("Last character of string \"%s\": \'%c\'\n", my_str_getdata(&test_string5), (char) my_str_getlast(&test_string5));

    // Example of printing
    printf("\nPrinting\n");
    my_str_print(&test_string5);

    // Example of getting c-string from my_str_t
    char *string_example = my_str_getdata(&test_string5);

    // Example of inserting character
    printf("\nInsert character\n");
    printf("Before: \"%s\"\n", my_str_getdata(&test_string5));
    my_str_insert_c(&test_string5, 'm', 4);
    printf("After inserting character \'m\' in position 4: \"%s\"\n", my_str_getdata(&test_string5));

    // Example of inserting another my_str_t
    printf("\nInsert another my_str_t\n");
    printf("5 is: %s, 3 is: %s\n", my_str_getdata(&test_string5), my_str_getdata(&test_string3));
    my_str_insert(&test_string5, &test_string3, 3);
    printf("After inserting  test string 3 in position 3 of string5: \"%s\"\n", my_str_getdata(&test_string5));

    // Example of inserting c-string
    printf("\nInsert c-string\n");
    char *c_string = "Alaska";
    my_str_insert_cstr(&test_string5, c_string, 1);
    printf("After inserting  c-string in position 1: \"%s\"\n", my_str_getdata(&test_string5));

    // Example of appending another my_str_t
    printf("\nAppending another my_str_t\n");
    printf("Before: \"%s\"\n", my_str_getdata(&test_string3));
    my_str_append(&test_string3, &test_string5);
    printf("After appending \"%s\": %s\n", my_str_getdata(&test_string5), my_str_getdata(&test_string3));
    printf("Size after appending: %zu\n", my_str_size(&test_string3));

    // Example of getting cstr
    const char * cstr = my_str_get_cstr(&test_string3);


    // Example of finding character
    printf("\nFinding character\n");
    printf("Character \'1\' is on position %zu in word \"%s\"\n", my_str_find_c(&test_string3, '1', 1), my_str_getdata(&test_string3));

    my_str_free(&test_string5);
    my_str_free(&test_string2);

    // Example of string comparison
    printf("\nString comparison\n");
    my_str_t test_string4;

    char * string0  = "honest";
    my_str_from_cstr(&test_string4, "gravel");
    printf("Our strings to compare : \"%s\", \"%s\"\n", my_str_getdata(&test_string4), string0);
    printf("Result: %d\n", my_str_cmp(&test_string4, string0));

    // Example of getting a link to char array
    const char * string1 = my_str_get_cstr(&test_string4);
    //Example of finding character by function
    int is_eight_or_1(char character){
        if (character == '8' || character == '1'){
            return 1;
        } else{
            return 0;
        }
    }

    my_str_free(&test_string3);
    my_str_free(&test_string4);
}