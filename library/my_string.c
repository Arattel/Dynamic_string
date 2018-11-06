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


int my_str_from_cstr(my_str_t *str, const char *cstr) {
    str->size_m = str_len(cstr);
    str->capacity_m = str->size_m + 1;
    str->data = malloc(str->capacity_m);
    for(size_t i = 0; i < str->capacity_m; i++){
        str->data[i] = '\0';
    }
    for(size_t j = 0; j < str->size_m; j++){
        str->data[j] = cstr[j];
    }
    return 0;
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
            for(size_t i = 0; i < buf_size + 1; i++){
                str->data[i] = '\0';
            }
        }
            return EXIT_SUCCESS;
        }
    return EXIT_FAILURE;
    }

//! Збільшує буфер стрічки, із збереженням вмісту,
//! якщо новий розмір більший за попередній,
//! не робить нічого, якщо менший або рівний.
//! (Як показує практика, це -- корисний підхід).
//! Для збільшення виділяє новий буфер, копіює вміст
//! стрічки (size_m символів -- немає сенсу копіювати
//! решту буфера) із старого буфера та звільняє його.
int my_str_reserve (my_str_t *str, size_t buf_size) {
    if (str->capacity_m < buf_size) {
        str->capacity_m = buf_size;
        char *allocatedMemory = malloc(buf_size + 1);
        if (!allocatedMemory){
            return EXIT_FAILURE;
        }
        for (size_t i = 0; i <= str->size_m; i++) {
            allocatedMemory[i] = str->data[i];
        }
        free (str->data);
        str->data = allocatedMemory;
        return EXIT_SUCCESS;
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
        my_str_reserve(str, str->capacity_m * 2);
    }
        str->data[str->size_m] = c;
        str->data[str->size_m + 1] = '\0';
        str->size_m++;
        return EXIT_SUCCESS;
    }

//! Додати С-стрічку в кінець.
//! Якщо це неможливо, повертає -1, інакше 0.
int my_str_append_cstr(my_str_t *str, char *from) {

    if (str->capacity_m - str->size_m < str_len(from)){
        my_str_reserve(str, str->capacity_m * 2);
    }

    while (*from) {
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
    if (beg >= str->size_m) {
        return EXIT_FAILURE;
    }
    if (end_s - beg > to->capacity_m) {
        my_str_reserve(to, (to->capacity_m + end_s - beg) * 2);
    }
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

    return EXIT_SUCCESS;
}

#define my_sizeof(x) ((char *)(&x + 1) - (char *)&x)
//! C-string варіант my_str_substr'у
int my_str_substr_cstr(const my_str_t* str, char to[], size_t beg, size_t end_s, size_t cstr_size) {
    if (beg >= str->size_m) {
        return EXIT_FAILURE;
    }
//    char to_char = to;
//    char** to_char = &to;
//    printf("%zu >? %zu\n", end_s - beg, my_sizeof(to_char));
    if (end_s - beg > cstr_size) {
//        printf("wtf\n");
        char new_to[(cstr_size + end_s - beg) * 2];
//        str_copy(new_to, to);
        *to = *new_to;
    }
    size_t slice_size;
    size_t end_index;
    if (end_s < str->size_m) {
        slice_size = end_s - beg;
        end_index = end_s;
    } else {
        slice_size = str->size_m - beg;
        end_index = str->size_m;
    }
    to[slice_size] = '\0';
    for (size_t i = beg; i < end_index; i++) {
//        if (!to[i - beg]) {
//            printf("this %c", to[i - beg]);
//        }
        to[i - beg] = str->data[i];
//        *to = str->data[i];
//        *to++;
    }

    return EXIT_SUCCESS;

}

void getZarr(const char str[], size_t *Z, size_t n) {
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
    for (size_t i = 0; i < l; i++) {
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

char *my_str_getdata(my_str_t *str) {
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
    size_t buffer_size = from->size_m;
    if(reserve){buffer_size *= 2;}
    if(to->capacity_m < from->size_m){
        while(to->capacity_m < from->size_m){
            my_str_reserve(to, buffer_size);
        }
    }
    for(size_t i = 0; i < to->capacity_m; i++){
        to->data[i] = '\0';
    }
    for(size_t j = 0; j < from->size_m; j++){
        to->data[j] = from->data[j];
    }
    to->size_m = from->size_m;
    return EXIT_SUCCESS;
}

//! Вставити символ у стрічку в заданій позиції, змістивши решту символів праворуч.
//! Якщо це неможливо, повертає -1, інакше 0.
int my_str_insert_c(my_str_t *str, char c, size_t pos) {
    if (pos > str->size_m) {
        return EXIT_FAILURE;
    }
    if((str->size_m + 1) > str->capacity_m) {
        my_str_reserve(str, str->capacity_m * 2);
    }
    size_t i = (str->size_m);
    while (i-- > pos) {
        str->data[i + 1] = str->data[i];
    }
    str->data[pos] = c;
    str->size_m++;
    return EXIT_SUCCESS;
}

void move_on(my_str_t *str, size_t start_pos, size_t gap) {
    size_t old_size = str->size_m;
//    printf("old size: %zu\n", old_size);
    str->size_m += gap;
//    str->data[old_size] = '\0';
    str->data[str->size_m + 1] = '\0';
//    for (size_t i = start_pos; i < str->size_m; i++) {
//        my_str_pushback(str, str->data[i]);
//
//    }
    size_t i = old_size - 1;
//    printf("i = %zu, start pos = %zu\n", i, start_pos);
    while (i > start_pos) {
        str->data[i + gap] = str->data[i];
//        printf("from %zu to %zu\n", i, i + gap);
        i--;
    }
//    if (!start_pos) {
//        i = 0;
    str->data[i + gap] = str->data[i];
//    printf("from %zu to %zu\n", i, i + gap);
    str->data[str->size_m] = '\0';
//    printf("from \'\\0\' to %zu\n", str->size_m);
//    my_str_pushback(str, str->data[i]);
//    }
}

//! Вставити стрічку в заданій позиції, змістивши решту символів праворуч.
//! Якщо це неможливо, повертає -1, інакше 0.
int my_str_insert(my_str_t *str, my_str_t *from, size_t pos) {
    if (pos > str->size_m)
        return EXIT_FAILURE;

    if (str->size_m + from->size_m > str->capacity_m) {
        my_str_reserve(str, (str->capacity_m + from->size_m) * 2);
//        printf("str2 after reserve: %s, size: %zu, buffer: %zu\n", str->data, str->size_m, str->capacity_m);
    }
    if (pos < str->size_m) {
        move_on(str, pos, from->size_m);
        size_t i = pos;
        while (i - pos < from->size_m) {
            str->data[i] = from->data[i - pos];
            i++;
        }
    } else if (pos == str->size_m) {
        my_str_append(str, from);
    }
    return 0;

}

//! Вставити C-стрічку в заданій позиції, змістивши решту символів праворуч.
//! Якщо це неможливо, повертає -1, інакше 0.
int my_str_insert_cstr(my_str_t *str, const char *from, size_t pos) {
    size_t string_size = str_len(from);
    if (pos > str->size_m) {
        return EXIT_FAILURE;
    }
    if (str->size_m + string_size > str->capacity_m) {
        my_str_reserve(str, (str->size_m + string_size) * 2);
//        printf("str2 after reserve: %s, size: %zu, buffer: %zu\n", str->data, str->size_m, str->capacity_m);
    }
//    if (pos == 0) {
//        printf("\n\nHERE\n\n");
//        my_str_t new_str;
//        my_str_from_cstr(&new_str, from);
//        my_str_append(&new_str, str);
//        *str = new_str;
//        my_str_free(&new_str);
//    } else
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

//! Додати стрічку в кінець.
//! Якщо це неможливо, повертає -1, інакше 0
int my_str_append(my_str_t *str, my_str_t *from) {

    if (str->capacity_m - str->size_m < from->size_m) {
        my_str_reserve(str, (str->capacity_m + from->size_m) * 2);
    }

    size_t i = 0;
    while (from->data[i]) {
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
size_t my_str_find_c(const my_str_t *str, char tofind, size_t from) {
    if (from >= str->size_m) {
        return (size_t) -1u;
    } else {
        for (size_t i = from; i < str->size_m; i++) {
            if (str->data[i] == tofind) {
                return i;
            }
        }
        return (size_t) -1u;
    }
}

//! Знайти символ в стрічці, для якого передана
//! функція повернула true, повернути його номер
//! або -1u, якщо не знайдено:
size_t my_str_find_if(const my_str_t *str, int (*predicat)(char)) {
    for (size_t i = 0; i < str->size_m; i++) {
        if ((*predicat)(str->data[i])) {
            return i;
        }
    }
    return (size_t) -1u;
}

//! Прочитати стрічку із файлу. Повернути, 0, якщо успішно, -1,
//! якщо сталися помилки. Кінець вводу -- не помилка, однак,
//! слід не давати читанню вийти за межі буфера!
//! Рекомендую скористатися fgets().
int my_str_read_file(my_str_t *str, FILE *file) {

    if (!file) return EXIT_FAILURE;

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    my_str_create(str, (size_t) file_size);
    char file_cstr[file_size];

    while (fgets(file_cstr, (int) file_size, file)) {
        my_str_append_cstr(str, file_cstr);
    };

    return EXIT_SUCCESS;

}

//! Аналог my_str_read_file, із stdin
int my_str_read (my_str_t *str) {

    my_str_create(str, 2000);
    char read_cstr[2000];

    while (*fgets(read_cstr, 2000, stdin) != '\n') {
        if (str->capacity_m - str->size_m < str_len(read_cstr))
            return EXIT_FAILURE;
        my_str_append_cstr(str, read_cstr);
    };

    return EXIT_SUCCESS;

}


int my_str_shrink_to_fit (my_str_t *str) {
    str->capacity_m = str->size_m;
    char * allocatedMemory = malloc(str->size_m + 1);
    for (size_t i  = 0; i < str->size_m + 1; i++) {
        allocatedMemory[i] = '\0';
    }
    for (size_t j = 0; j < str->size_m; j++) {
        allocatedMemory[j] = str->data[j];
    }
    my_str_free(str);
    str->data = allocatedMemory;
    return EXIT_SUCCESS;
}

//! Якщо new_size менший за поточний розмір -- просто
//! відкидає зайві символи (зменшуючи size_m). Якщо
//! більший -- збільшує фактичний розмір стрічки,
//! встановлюючи нові символи рівними sym.
//! За потреби, збільшує буфер.
//! Сподіваюся, різниця між розміром буфера та фактичним
//! розміром стрічки зрозуміла?
int my_str_resize (my_str_t *str, size_t new_size, char sym) {
    printf("New size, size before : %zu, %zu", new_size, str->size_m);
    if (new_size < str->size_m) {
        while (new_size < str->size_m) {
            my_str_popback(str);
        }
    } else if (new_size > str->size_m) {
        if (new_size > str->capacity_m) {
            my_str_reserve(str, new_size + 1);
        }
        size_t number_of_chars = new_size - str->size_m;
        for (size_t i = 0; i <= number_of_chars; i++) {
            my_str_pushback(str, sym);
        }
    }
    return 0;
}

//! На відміну від my_str_read_file(), яка читає по
//! whitespace, читає по вказаний delimiter, за потреби
//! збільшує стрічку.
int my_str_read_file_delim(my_str_t* str, FILE* file, char delimiter) {
    int ch;
    my_str_create(str, 10);
    ch = fgetc(file);
    while ((ch != delimiter) && (ch)) {
        my_str_pushback(str, (char) ch);
        ch = fgetc(file);
//        printf("read: %c\n", ch);
    }

    if (ch == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
//
//int main(int argc, char* argv[]) {
////    FILE* inp_file = fopen(argv[1], "r");
////    if (!inp_file) {
////        puts("Error while opening file");
////        return EXIT_FAILURE;
////    }
////    my_str_t file_str;
////    my_str_read_file_delim(&file_str, inp_file, 'G');
////    printf("result string is: %s\n", file_str.data);
////    fclose(inp_file);
////    my_str_free(&file_str);
//
//    my_str_t str1;
//    my_str_from_cstr(&str1, "hello!");
//    my_str_t str2;
//    my_str_from_cstr(&str2, ", world");
//
//    my_str_insert(&str1, &str2, 5);
//    printf("str1 after insert: %s\n", my_str_get_cstr(&str1));
//
//    printf("str1 is: %s, str2 is: %s\n", str1.data, str2.data);
//    my_str_insert_cstr(&str2, "hello", 0);
//    printf("str2 after insert: %s\n", str2.data);
//
//    printf("str1 is: %s, str2 is: %s\n", str1.data, str2.data);
//    my_str_append(&str1, &str2);
//    printf("str1 + str2: %s\n", str1.data);
//
//    my_str_t str3;
//    my_str_create(&str3, 5);
//    my_str_substr(&str1, &str3, 0, 13);
//    printf("substr is: %s\n", my_str_get_cstr(&str3));
//
//    my_str_free(&str1);
//    my_str_free(&str2);
//    my_str_free(&str3);
//
//    my_str_t str4;
//    my_str_from_cstr(&str4, "HELLO, WORLD!");
//    char cstr[15];
//
//    my_str_substr_cstr(&str4, cstr, 0, 13, my_sizeof(cstr));
//    printf("substr2 is: %s\n", cstr);
//    my_str_free(&str4);
//
//    return 0;
//}