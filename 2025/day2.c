#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ULLI unsigned long long int

ULLI sum = 0;

void check_invalid_id(char* line) {
    //printf("lineu: %s\n", line);
    char* dash = strchr(line, '-');
    *dash = '\0';

    const ULLI li = atoll(line);
    const ULLI ri = atoll(dash+1);

    char l[20] = "";
    char r[20] = "";
    for (ULLI i = li; i <= ri; i++) {
        char id[20];
        sprintf(id, "%llu", i);
        //printf("string repr: %s\n", id);
        const int slen = strlen(id);
        char* mid;
        if (slen % 2 == 0) { //can have invalid inside
            memcpy(l, id, slen/2);
            mid = &id[slen/2];
            strcpy(r, mid);
            if (!strcmp(l, r)) { //same
                printf("invalid: %s\n", id);
                sum += i;
            }
            //printf("id: %s, l: %s, r: %s\n", id, l, r);
        }
    }
}

int main() {
    FILE* f;
    f = fopen("./day2-input.txt", "r");
    if (f == NULL) {goto end;}

    char line[40] = "";
    char c[2] = "";
    int count = 0;
    while(fgets(c, 2, f)) {
        if (!strcmp(c, ",") || !strcmp(c, "\n")) {
            //printf("unit: %s\n", line);
            check_invalid_id(line);
            memset(line, '\0', count+1);
            count = 0;
        } else {
            line[count] = c[0];
            ++count;
        }
    }
    //printf("line[100]: %c\n", line[99]); //last digit's null terminator so string stops in memory

end:
    printf("The sum of all invalid id's is: [%llu]", sum);
    fclose(f);
    return 0;
}
