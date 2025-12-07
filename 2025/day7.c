#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int w, h;
} Size;

typedef struct {
    bool split;
    char ch;
} Character;

Size get_input_size(FILE* f) {
    Size size = {0, 0};
    char c;
    while ((c = fgetc(f)) != EOF) {
        if (c == '\n') {++size.h;}
        if (size.h == 0 && c != '\n') {++size.w;}
    }
    return size;
}

void fill_arr_input(const Size s, Character (*arr)[s.h], FILE* f, int* s_loc) {
    char c;
    for (int i = 0; i < s.h; i++) {
        for (int j = 0; j < s.w; j++) {
            c = fgetc(f);
            if (c == EOF) {return;}
            if (c == '\n') {--j; continue;}
            if (c == 'S') {*s_loc = j;}
            arr[i][j] = (Character){false, c};
        }
    }
}

//void flip_splits_hit(const Size s, const int x, const int y, Character (*arr)[s.h]) {
//    if (y >= s.h || y < 0 || x >= s.w || x < 0) {return;}
//    if (arr[y][x])
//}

void flip_splits_hit(const Size s, Character (*arr)[s.h]) {
    Character* ch;
    for (int i = 0; i < s.h; i++) {
        for (int j = 0; j < s.w; j++) {
            ch = &arr[i][j];
            if (ch->ch == '^' && ch->split == false) {
                int check = i-2;
                while (check > 1) {
                    if (arr[check][j].ch == '^') {break;}
                    Character lp = arr[check][j-1];
                    Character rp = arr[check][j+1];
                    if ((lp.ch == '^' && lp.split == true) || (rp.ch == '^' && rp.split == true)) {
                        ch->split = true;
                        break;
                    }
                    check-=2;
                }
            } else {continue;}
        }
    }
}

int count_splits_hit(const Size s, Character (*arr)[s.h]) {
    int count = 0;
    for (int i = 0; i < s.h; i++) {
        for (int j = 0; j < s.w; j++) {
            if (arr[i][j].split == true) {++count;}
        }
    }
    return count;
}

int main() {
    FILE* f = fopen("./day7-input.txt", "r");
    if (!f) {return 1;}

    int count = 0;
    const Size input_size = get_input_size(f);
    if (input_size.w == 0 || input_size.h == 0) {return 1;}
    rewind(f);

    int s_loc = 0;
    Character (*arr)[input_size.h] = malloc(sizeof(Character[input_size.w][input_size.h]));
    fill_arr_input(input_size, arr, f, &s_loc);

    //flip_splits_hit(input_size, s_loc, 0, arr);
    arr[2][s_loc].split = true; //always 1 to start under S, and so it's split from the start
    flip_splits_hit(input_size, arr);
    count = count_splits_hit(input_size, arr);

    printf("Count of splits is: %d", count);
    return 0;
}
