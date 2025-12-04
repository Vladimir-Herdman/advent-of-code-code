#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ULLI unsigned long long int

ULLI sum = 0;

typedef struct {
    int w;
    int h;
} Size;

Size get_input_size(FILE* f) {
    Size size = {0, 0};
    char c[2] = "";
    while (fgets(c, 2, f)) {
        if (c[0] == '\n') {++size.h;}
        if (size.h == 0 && c[0] != '\n') {++size.w;}
    }
    return size;
}

void fill_arr_input(const Size s, char (*arr)[s.h], FILE* f) {
    char c;
    for (int i = 0; i < s.h; i++) {
        for (int j = 0; j < s.w; j++) {
            c = fgetc(f);
            if (c == EOF) {return;}
            if (c == '\n') {--j; continue;}
            arr[i][j] = c;
        }
    }
}

void print_arr(const Size s, char (*arr)[s.h]) {
    for(int i = 0; i < s.h; i++) {
        for(int j = 0; j < s.w; j++) {
            printf("%c", arr[i][j]);
        }
        printf("\n");
    }
}

void remove_x_from_arr(const Size s, char (*arr)[s.h]) {
    for (int i = 0; i < s.h; i++) {
        for (int j = 0; j < s.w; j++) {
            if (arr[i][j] == 'x') {arr[i][j] = '.';}
        }
    }
}

bool check_available_rolls(const Size s, char (*arr)[s.h]) {
    bool set_x = false;
    for (int i = 0; i < s.h; i++) {
        for (int j = 0; j < s.w; j++) {
            if (arr[i][j] == '.') {continue;}
            int count = 0;

            if (i > 0) { //check up and left|right
                if (arr[i-1][j] == '@' || arr[i-1][j] == 'x') {++count;}
                if (j > 0) {if(arr[i-1][j-1] == '@' || arr[i-1][j-1] == 'x') {++count;}}
                if (j < s.w-1) {if(arr[i-1][j+1] == '@' || arr[i-1][j+1] == 'x') {++count;}}
            };
            if (i < s.h-1) { //check down and left|right
                if (arr[i+1][j] == '@' || arr[i+1][j] == 'x') {++count;}
                if (j > 0) {if(arr[i+1][j-1] == '@' || arr[i+1][j-1] == 'x') {++count;}}
                if (j < s.w-1) {if(arr[i+1][j+1] == '@' || arr[i+1][j+1] == 'x') {++count;}}
            }
            if (j > 0) { //check left
                if (arr[i][j-1] == '@' || arr[i][j-1] == 'x') {++count;}
            }
            if (j < s.w-1) { //check right
                if (arr[i][j+1] == '@' || arr[i][j+1] == 'x') {++count;}
            }

            if (count < 4) {++sum; arr[i][j] = 'x'; set_x = true;}
        }
    }
    return set_x;
}

int main() {
    FILE* f = fopen("./day4-input.txt", "r");
    if (!f) {goto end;}

    const Size input_size = get_input_size(f);
    if (input_size.w == 0 || input_size.h == 0) {goto end;}
    rewind(f);

    char (*arr)[input_size.h] = malloc(sizeof(char[input_size.w][input_size.h]));
    fill_arr_input(input_size, arr, f);

    while (true) {
        if(!check_available_rolls(input_size, arr)) {break;}
        remove_x_from_arr(input_size, arr);
    }
    print_arr(input_size, arr);

    free(arr);
end:
    printf("The sum of all toilet roles the forklifts can reach is: [%llu]\n", sum);
    fclose(f);
    return 0;
}
