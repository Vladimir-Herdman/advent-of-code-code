#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ULLI unsigned long long int

ULLI sum = 0;

void get_factors(const int n, int* arri) {
    int count = 0;
    for (int i = 1; i <= n/2; i++) {
        if (i == n) {break;}
        if (n % i == 0) {
            arri[count] = i;
            ++count;
        }
    }
}

bool check_for_repeats(const char* numc) {
    //printf("numc: %s\n", numc);
    const int numc_len = strlen(numc);
    int factors[10] = {0};
    get_factors(numc_len, factors); //factors will be factors not including repeats or final factor, rest val's are 0

    //loop over numc chunks and check for repeats. if repeats == (size/factor) - 1, we found one, so add sum and return
    for (int i = 0; i < 10; i++) { //iterate through chunk sizes
        const int chunk_size = factors[i];
        if (chunk_size == 0) {return false;} //no more factors to check, return

        char repeat[20] = ""; for (int j=0; j<chunk_size; j++) {repeat[j]=numc[j];}
        int repeats_counted = 0;
        for (int j = chunk_size; j < numc_len; j+=chunk_size) { //iterate through string in chunks checking for repeats (start ahead of first as that's already repeat)
            char current[20] = ""; for (int k=0; k<chunk_size; k++) {current[k]=numc[k+j];}
            if (!strcmp(repeat, current)) {
                ++repeats_counted;
            } else {break;}
        }
        if (repeats_counted == (numc_len/chunk_size)-1) { //repeater found
            //printf("Repeat: %s, chunk_size: %d\n", numc, chunk_size);
            return true;
        }
    }
    return false;
}

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
        if (check_for_repeats(id)) {sum += i;}
        //printf("string repr: %s\n", id);
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
