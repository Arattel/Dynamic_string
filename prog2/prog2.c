#include <stdio.h>
#include <ctype.h>
#include "my_string.h"

void get_out_file_name(my_str_t* out_file_name, char inp_file_name[]) {
    
    my_str_from_cstr(out_file_name, inp_file_name, 104);
    
    my_str_t txt_str;
    my_str_from_cstr(&txt_str, ".txt", 4);
    size_t out_pos = my_str_find(out_file_name, &txt_str, 0);
    my_str_insert_cstr(out_file_name, "_out", out_pos);
    my_str_free(&txt_str);
    
}

int main(int argc, char *argv[]) {

//    opens file and check whether it's opened correctly
//    exit(1) otherwise
    FILE* inp_file = fopen(argv[1], "r");
    if (!inp_file) {
        puts("Error while opening file");
        return EXIT_FAILURE;
    }
    puts("File have been opened successfully");

//    get file size to know how long string should be
    fseek(inp_file, 0, SEEK_END);
    size_t file_size = ftell(inp_file);
    fseek(inp_file, 0, SEEK_SET);

//    variable for storing data from file
    my_str_t file_str;
    my_str_create(&file_str, file_size);

//    loop for processing data from file while reading it
    int c_int;
    while ((c_int = getc(inp_file)) != EOF) {
        char c = c_int;

        if ispunct(c) continue;

        if (c == ' ') {
            if (my_str_getlast(&file_str) == ' ') continue;
        }
        my_str_pushback(&file_str, tolower(c));
        
    }

//    create output filename if it is not specified
    my_str_t out_file_name;
     if (!argv[2]) {
        get_out_file_name(&out_file_name, argv[1]);
     } else {
         my_str_from_cstr(&out_file_name, argv[2], str_len(argv[2]));
     }

//    try to create output file
    FILE* out_file = fopen(my_str_getdata(&out_file_name), "w");
    if (!out_file) {
        puts("Error while creating output file");
        return EXIT_FAILURE;
    }
    fputs(my_str_getdata(&file_str), out_file);
    puts("File have been written");

//    close opened files and freeing allocated bytes for strings
    my_str_free(&out_file_name);
    my_str_free(&file_str);
    fclose(inp_file);
    fclose(out_file);
    puts("File have been closed");
    return EXIT_SUCCESS;
}