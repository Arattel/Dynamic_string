#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "my_string.h"

// struct my_str_t {
//     size_t capacity_m; // Розмір блока
//     size_t size_m;     // Фактичний розмір стрічки
//     char *data;       // Вказівник на блок пам'яті
// };

//size_t my_str_len(my_str_t *str) {
//    size_t i = 0;
//    while (str->data[++i]) {
//    }
//    return i;
//}

char *str_copy(char *destination, char *source) {
    char *start = destination;

    while (*source) {
        *destination = *source;
        destination++;
        source++;
    }

    *destination = '\0';
    return start;
}

size_t str_len(const char *str) {
    size_t i = 0;
    while (str[++i]) {}
    return i;
}

char *str_cat(char *dest_ptr, const char *src_ptr) {

    char *strret = dest_ptr;
    if (dest_ptr && src_ptr) {
        while (*dest_ptr) {
            dest_ptr++;
        }

        while (*src_ptr) {
            *dest_ptr++ = *src_ptr++;
        }
        *dest_ptr = '\0';
    }
    return strret;
}

//! Повертає булеве значення, чи стрічка порожня:
int my_str_empty(const my_str_t *str) {
    return (str->size_m) ? 0 : 1;
}

//! Створити стрічку із буфером вказаного розміру із переданої С-стрічки.
//! Якщо розмір -- 0, виділяє блок, рівний розміру С-стрічки, якщо
//! менший за її розмір -- вважати помилкою.
//! Пам'ять виділяється динамічно.
//! 0 -- якщо все ОК, -1 -- недостатній розмір буфера, -2 -- не вдалося виділити пам'ять
int my_str_from_cstr(my_str_t *str, char *cstr, size_t buf_size) {

    if (str) {
        char *allocatedMemory;
        if (!buf_size) {
            allocatedMemory = malloc(str_len(cstr));
        } else if (buf_size >= str_len(cstr)) {
            allocatedMemory = malloc(buf_size + 1);
        } else {
            return EXIT_FAILURE;
        }
        if (allocatedMemory) {
            str->data = allocatedMemory;
            str->capacity_m = buf_size ? buf_size : str_len(cstr);
            str->size_m = str_len(cstr);
            size_t i = 0;

            str_copy(str->data, cstr);

            return EXIT_SUCCESS;
        }

        return EXIT_FAILURE;
    }
}

//! Створити стрічку із буфером вказаного розміру. Пам'ять виділяється динамічно.
//! Варто виділяти buf_size+1 для спрощення роботи my_str_get_cstr().
int my_str_create(my_str_t *str, size_t buf_size) {
    if (str) {
        char *allocatedMemory = malloc(buf_size + 1);
        if (allocatedMemory) {
            str->data = allocatedMemory;
            str->capacity_m = buf_size;
            str->size_m = 0;
            str->data[0] = '\0';
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}

//! Повертає розмір стрічки:
size_t my_str_size(const my_str_t *str) {
    return str->size_m;
}

void my_str_free(my_str_t *str) {
    free(str->data);
}

//! Повертає розмір буфера:
size_t my_str_capacity(const my_str_t *str) {
    return str->capacity_m;
};

//! Додає символ в кінець.
//! Повертає 0, якщо успішно, -1, якщо буфер закінчився.
int my_str_pushback(my_str_t *str, char c) {
    if ((str->size_m + 2) > str->capacity_m) {
        return EXIT_FAILURE;
    } else {
        str->data[str->size_m] = c;
        str->data[str->size_m + 1] = '\0';
        str->size_m++;
        return EXIT_SUCCESS;
    }
}

//! Додати С-стрічку в кінець.
//! Якщо це неможливо, повертає -1, інакше 0.
int my_str_append_cstr(my_str_t *str, char *from) {

    if (str->capacity_m - str->size_m < str_len(from)) return EXIT_FAILURE;

    while(*from){
        my_str_pushback(str, *from++);
    }
    return EXIT_SUCCESS;
}

//! Очищає стрічку -- робить її порожньою. Складність має бути О(1).
void my_str_clear(my_str_t *str) {
    my_str_create(str, str->capacity_m);
}

//! Скопіювати підстрічку, із beg включно, по end не включно ([beg, end)).
//! Якщо end виходить за межі str -- скопіювати скільки вдасться, не вважати
//! це помилкою. Якщо ж в ціловій стрічці замало місця, або beg більший
//! за розмір str -- це помилка. Повернути відповідний код завершення.
int my_str_substr(const my_str_t *str, my_str_t *to, size_t beg, size_t end_s) {
    if (end_s - beg > to->capacity_m || beg >= str->size_m) {
//        printf("\nERROR\n");
//        printf("(end) %zu - (beg) %zu = %zu, capacity: %zu\n",
//        end_s, beg, end_s - beg, to->capacity_m);
        return -1;
    } else {
//        printf("\ngot: %s\n", str->data);
//        my_str_clear(to);
        size_t slice_size;
        size_t end_index;
        if (end_s < str->size_m) {
            slice_size = end_s - beg;
            end_index = end_s;
        } else {
            slice_size = str->size_m - beg;
            end_index = str->size_m;
        }
        to->size_m = slice_size;
        to->data[slice_size] = '\0';
        for (size_t i = beg; i < end_index; i++) {
            to->data[i - beg] = str->data[i];
        }
//        my_str_pushback(to, '\0');
        return 0;
    }
}

void getZarr(char str[], size_t* Z, size_t n) {
//    size_t n = str_len(str);
    size_t L, R, k;

    L = R = 0;
    for (size_t i = 1; i < n; ++i) {
        if (i > R) {
            L = R = i;
//            printf("\nstr is: %s\n", str);
            while (R < n && str[R - L] == str[R]) {
                R++;
//                printf("\nR++\n");
            }
            Z[i] = R - L;
//            printf("\nafter = %zu: %zu\n", R - L, Z[i]);
            R--;
        } else {
            k = i - L;
            if (Z[k] < R - i + 1) {
                Z[i] = Z[k];
            } else {
                L = i;
                while (R < n && str[R - L] == str[R]) R++;
                Z[i] = R - L;
//                printf("\nafter = %zu: %zu\n", R - L, Z[i]);
                R--;
            }
        }
    }
//    printf("\nZ in get is: [ ");
//    for (size_t i = 0; i < l; i++){
//        printf("%zu ", Z[i]);
//    }
//    printf("]\n");
}

//! Знайти першу підстрічку в стрічці, повернути номер її
//! початку або -1u, якщо не знайдено. from -- місце, з якого починати шукати.
//! Якщо більше за розмір -- вважати, що не знайдено.
size_t my_str_find(const my_str_t *str, const my_str_t *tofind, size_t from) {
    if (tofind->size_m > str->size_m) return (size_t) -1u;
    size_t size_of_str = str->size_m + 1;
    char *text = malloc(tofind->size_m + 1 + size_of_str - from);

    my_str_t str_in_use;
    my_str_create(&str_in_use, size_of_str++);
//    my_str_substr(str, &str_in_use, from, size_of_str);
//    my_str_copy(str, &str_in_use, 0);

    size_t temp_i;
    for (temp_i = 0; temp_i < size_of_str - 1; temp_i++) {
        my_str_pushback(&str_in_use, str->data[temp_i]);
//        printf("add: %c\n", str->data[temp_i]);
//        str_in_use.data[temp_i] = str->data[temp_i];
//        printf("string is: %s\n", str_in_use.data);
    }

//    str_in_use.data[temp_i + 1] = '\0';
    str_copy(text, tofind->data);
    str_cat(text, "$");
//    printf("\ntext is: %s,\tstr is: %s\n", text, str_in_use.data);
    str_cat(text, str_in_use.data);
    size_t l = str_len(text);

    my_str_free(&str_in_use);

    size_t Z[l];
    for (size_t i = 0; i < l; i++) {
        Z[i] = 0;
    }
    getZarr(text, Z, l);

//    printf("\nZ is: [ ");
    for (size_t i = 0; i < l; i++){
//        printf("%zu ", Z[i]);
    }
//    printf("]\n");

    free(text);

    for (size_t i = 0; i < l; ++i) {
        if (Z[i] == str_len(tofind->data)) {
            return i - str_len(tofind->data) - 1;
        }
    }

    return (size_t) -1u;

}

char* my_str_getdata(my_str_t *str) {
//    return str->data;
    if (str->size_m) return str->data;
    return NULL;
}

//! Повертає символ у вказаній позиції, або -1, якщо вихід за межі стрічки
//! Тому, власне, int а не char
int my_str_getc(const my_str_t *str, size_t index) {
    if (index >= str->size_m) {
        return -1;
    } else {
        return (int) str->data[index];
    }
}

//! Записує символ у вказану позиції (заміняючи той, що там був),
//! Повертає 0, якщо позиція в межах стрічки,
//! Поветає -1, не змінюючи її вмісту, якщо ні.
int my_str_putc(my_str_t *str, size_t index, char c) {
    if (index >= str->size_m) {
        return -1;
    } else {
        str->data[index] = c;
        return 0;
    }
}

//! Викидає символ з кінця.
//! Повертає його, якщо успішно, -1, якщо буфер закінчився.
int my_str_popback(my_str_t *str) {
    if (str->capacity_m < str->size_m) {
        return -1;
    } else {
        int symbol = (int) str->data[str->size_m - 1];
        my_str_putc(str, str->size_m - 1, '\0');
        str->size_m -= 1;
        // printf("\nstr is: %s (%zu)", str->data, str->size_m);
        return symbol;
    }
}

int my_str_getlast(my_str_t *str) {
    if (str->capacity_m < str->size_m) {
        return -1;
    } else {
        int symbol = (int) str->data[str->size_m - 1];
        return symbol;
    }

}

void my_str_print(const my_str_t *str) {
    for (size_t i = 0; i < str->size_m; i++) {
        char symbol = str->data[i];
        printf("%c", symbol);
    }
    printf("\n");
}

int my_str_copy(const my_str_t *from, my_str_t *to, int reserve) {
    if (from->size_m) {
        if (reserve) {
            my_str_create(to, from->capacity_m);
        } else {
            my_str_create(to, from->size_m);
        }
        for (size_t i = 0; i < from->size_m; i++) {
            my_str_pushback(to, from->data[i]);
        }

        to->data[from->size_m + 1] = '\0';

        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

//! Вставити символ у стрічку в заданій позиції, змістивши решту символів праворуч.
//! Якщо це неможливо, повертає -1, інакше 0.
int my_str_insert_c(my_str_t *str, char c, size_t pos) {
    if (pos > str->size_m || pos >= str->capacity_m || (str->size_m + 1) > str->capacity_m) {
        return -1;
    } else {
        if (pos == str->size_m) {
            str->data[str->size_m] = c;
            str->data[str->size_m + 1] = '\0';
        } else {
            size_t i = (str->size_m);
            while (i-- > pos) {
                str->data[i + 1] = str->data[i];
            }
            str->data[pos] = c;
            str->size_m++;
        }
        return 0;
    }
}

void move_on(my_str_t *str, size_t start_pos, size_t gap) {
    size_t old_size = str->size_m;
    str->size_m += gap;
//    str->data[old_size] = '\0';
    str->data[str->size_m + 1] = '\0';
//    for (size_t i = start_pos; i < str->size_m; i++) {
//        my_str_pushback(str, str->data[i]);
//
//    }
    size_t i = old_size;
    while (i >= start_pos) {
        str->data[i + gap + 1] = str->data[i--];
    }
}

//! Вставити стрічку в заданій позиції, змістивши решту символів праворуч.
//! Якщо це неможливо, повертає -1, інакше 0.
int my_str_insert(my_str_t *str, my_str_t *from, size_t pos) {
    if (str->size_m + from->size_m > str->capacity_m || pos > str->size_m) {
        return -1;
    } else {
        if (pos < str->size_m) {
            move_on(str, pos, from->size_m);
            size_t i = pos;
            while (i - pos < from->size_m) {
                str->data[i] = from->data[i - pos];
                i++;
            }
        } else if (pos == str->size_m) {
            my_str_append(str, from);
//            str->data[str->size_m] = '\0';
//            printf("\n\n\tFROM LIB\nstr->size_m: %zu, from->size_m: %zu\n\n",
//                   str->size_m, from->size_m);
//            while (*from->data) {
//                my_str_pushback(str, *from->data++);
//            }
//            str->size_m += from->size_m;
//            printf("\n\n\tFROM LIB\nstr->size_m: %zu, from->size_m: %zu\n\n",
//                    str->size_m, from->size_m);
//            str->data[str->size_m + 1] = '\0';
//            size_t i = pos;
//            while (i - pos < from->size_m) {
//                str->data[i] = from->data[i - pos];
//                i++;
//            }
        }
        return 0;
    }
}

//! Вставити C-стрічку в заданій позиції, змістивши решту символів праворуч.
//! Якщо це неможливо, повертає -1, інакше 0.
int my_str_insert_cstr(my_str_t *str, const char *from, size_t pos) {
    size_t string_size = strlen(from);
    if (str->size_m + string_size > str->capacity_m || pos > str->size_m) {
        return -1;
    } else {
        if (pos < str->size_m) {
            move_on(str, pos, string_size);
            size_t i = pos;
            while (i - pos < string_size) {
                str->data[i] = from[i - pos];
                i++;
            }
        } else if (pos == str->size_m) {
            str->data[str->size_m] = '\0';
            str->size_m += string_size;
            str->data[str->size_m + 1] = '\0';
            size_t i = pos;
            while (i - pos < string_size) {
                str->data[i] = from[i - pos];
                i++;
            }
        }
        return 0;

    }
}

//! Додати стрічку в кінець.
//! Якщо це неможливо, повертає -1, інакше 0
int my_str_append(my_str_t *str, my_str_t *from) {

    if (str->capacity_m - str->size_m < from->size_m) return EXIT_FAILURE;

    size_t i = 0;
    while(from->data[i]) {
        my_str_pushback(str, from->data[i++]);
//        str->data[str->size_m + i + 1] = from->data[i];
//        str->size_m++;
//        i++;
    }
//    str->data[str->size_m + i + 1] = '\0';

//    *from->data -= from->size_m;
    return EXIT_SUCCESS;

}

//! Порівняти стрічки, повернути 0, якщо рівні (за вмістом!)
//! -1, якщо перша менша, 1 -- якщо друга.
//! Поведінка має бути такою ж, як в strcmp.
int my_str_cmp(const my_str_t *str, const char *from) {
    for (size_t i = 0; i < str->size_m + 1; i++) {
        if (str->data[i] < from[i]) {
            return -1;
        } else if (str->data[i] > from[i]) {
            return 1;
        } else {
            if (str->data[i] == '\0') {
                return 0;
            }
        }
    }
}

//! Повернути вказівник на С-стрічку, еквівалентну str.
//! Вважатимемо, що змінювати цю С-стрічку заборонено.
//! Якщо в буфері було зарезервовано на байт більше за макс. розмір, можна
//! просто додати нульовий символ в кінці та повернути вказівник data.
const char *my_str_get_cstr(my_str_t *str) {
    if (str->size_m) return str->data;
    return NULL;
}


//! Знайти перший символ в стрічці, повернути його номер
//! або -1u, якщо не знайдено. from -- місце, з якого починати шукати.
//! Якщо більше за розмір -- вважати, що не знайдено.
size_t my_str_find_c(const my_str_t* str, char tofind, size_t from){
    if(from >= str->size_m){
        return (size_t) -1u;
    } else{
        for(size_t i = from; i < str->size_m; i++){
            if(str->data[i] == tofind){
                return i;
            }
        }
        return (size_t) -1u;
    }
}

//! Знайти символ в стрічці, для якого передана
//! функція повернула true, повернути його номер
//! або -1u, якщо не знайдено:
size_t my_str_find_if(const my_str_t* str, int (*predicat)(char)){
    for(size_t i = 0; i < str->size_m; i++){
        if((*predicat)(str->data[i])){
            return i;
        }
    }
    return (size_t) -1u;
}

//! Прочитати стрічку із файлу. Повернути, 0, якщо успішно, -1,
//! якщо сталися помилки. Кінець вводу -- не помилка, однак,
//! слід не давати читанню вийти за межі буфера!
//! Рекомендую скористатися fgets().
int my_str_read_file(my_str_t* str, FILE* file) {

    if (!file) return EXIT_FAILURE;

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    my_str_create(str, file_size);
    char file_cstr[file_size];

    while (fgets(file_cstr, file_size, file)) {
        my_str_append_cstr(str, file_cstr);
    };

    return EXIT_SUCCESS;

}

//! Аналог my_str_read_file, із stdin
int my_str_read(my_str_t* str) {

    my_str_create(str, 2000);
    char read_cstr[2000];

    while (*fgets(read_cstr, 2000, stdin) != '\n') {
        if (str->capacity_m - str->size_m < str_len(read_cstr))
            return EXIT_FAILURE;
        my_str_append_cstr(str, read_cstr);
    };

    return EXIT_SUCCESS;

}

//int main(int* argc, char* argv[]) {

//  tesr read file
//    FILE* inp_file = fopen(argv[1], "r");
//    my_str_t file_str;
//    my_str_read_file(&file_str, inp_file);
//    printf("\n%s\n", my_str_getdata(&file_str));

//test read
//    my_str_t read_str;
//    my_str_read(&read_str);
//    printf("\n%s\n", my_str_getdata(&read_str));


////
//    my_str_t test_str;
//    my_str_create(&test_str, 200);
//    my_str_from_cstr(&test_str, "afkafk", 200);

//    my_str_t test_str2;
//    my_str_create(&test_str2, 100);
//    my_str_substr(&test_str, &test_str2, 1, 3);
//    my_str_pushback(&test_str, 'a');
//    my_str_pushback(&test_str, 'f');
//    my_str_pushback(&test_str, 'k');
//    my_str_t test1;
//    my_str_create(&test1, 120);
//    my_str_pushback(&test1, 'x');
//    my_str_pushback(&test1, 'y');
//    my_str_pushback(&test1, 'z');
//    my_str_append(&test_str2, &test1);
//    printf("res: %s\n", test_str2.data);

//    my_str_substr(&test_str, &test1, 2, 38);
//    char *str = my_str_get_cstr(&test_str);
//    printf("%i\n", strlen(str));
//    printf("%s\n", str);
//    print(&test1)
//
//    printf("Hello, World!\n");
//    printf("Hello, World!\n");
//    char cstr[] = "hello";
//    my_str_t this;
//
////    test cstr to str
//    printf("\ntest cstr to str\n");
//    my_str_from_cstr(&this, cstr, 30);
//    printf("%s\n", this.data);
//    printf("%zu\n", this.size_m);
//    printf("%zu\n", this.capacity_m);
//
//    printf("\nTest pushback: \n");
//    printf("\nBefore: %s\n", this.data);
//    my_str_pushback(&this, ',');
//    printf("\nAfter: %s\n", this.data);
//
//    printf("\nTest pohback: \n");
//    printf("\nBefore: %s\n", this.data);
//    my_str_popback(&this);
//    printf("\nAfter: %s\n", this.data);
//
//    char cstr2[] = ", world";
//
////    test append cstr
//    printf("\ntest append cstr\n");
//    my_str_append_cstr(&this, cstr2);
//    printf("new %s\n", this.data);
//    printf("%zu\n", this.size_m);
//    printf("%zu", this.capacity_m);
//
////    test copy
//    printf("\ntest copy\n");
//    char try_copy[] = "try copy! 123";
//    char to_copy[30];
//    str_copy(to_copy, try_copy);
//    printf("%s", to_copy);
//
////    test cat
//    printf("\ntest cat\n");
//    char yes[] = " yes";
//    char *after_cat[30];
//    *after_cat = str_cat(to_copy, yes);
//    printf("%s", *after_cat);
//
//    test find substring
//    printf("\ntest find substring\n");
//    my_str_t to_find;
//    my_str_from_cstr(&to_find, ".txt", 30);
//    my_str_t num;
//    my_str_from_cstr(&num, "sample.txt", 30);
//    my_str_append_cstr(&num, "lak");
//    my_str_popback(&num);
//    printf("search %s in %s\n", to_find.data, num.data);
//    printf("%zu", my_str_find(&num, &to_find, 0));

//
////    test get substring
//    printf("\ntest get substring\n");
//    my_str_t substr;
//    my_str_create(&substr, 30);
//    printf("\nbefore: %s", substr.data);
//    my_str_substr(&this, &substr, 6, this.size_m);
//    printf("\nafter: %s\n", substr.data);
//
//
//    printf("\nTest find:\n");
//    my_str_t test_str;
//    my_str_create(&test_str, 20);
//    my_str_pushback(&test_str, '2');
//    my_str_pushback(&test_str, '1');
//    my_str_pushback(&test_str, '0');
//    my_str_pushback(&test_str, '1');
//    printf("Our string: %s\n", test_str.data);
//    printf("Index of 1, beginning with 0: %zu\n", my_str_find_c(&test_str, '1', 0));
//    printf("Index of 1, beginning with 2: %zu\n", my_str_find_c(&test_str, '1', 2));
//    printf("Index of 8, beginning with 0: %zu\n", my_str_find_c(&test_str, '8', 0));
//    printf("\nTest find if:\n");
//    printf("Our string: %s\n", test_str.data);
//    printf("Index of first symbol that is either 1 or 8: %zu", my_str_find_if(&test_str, &test_function_for_chars));
////    test pop
//    printf("\ntest pop\n");
//    my_str_t new_this;
//    my_str_from_cstr(&new_this, "12345", 20);
//    printf("Before: %s\n", new_this.data);
//    printf("Char deleted: %c\n",(char)my_str_popback(&new_this));
//    printf("After: %s\n", new_this.data);
//
//    return 0;
//}

