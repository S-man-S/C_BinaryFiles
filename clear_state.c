#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void out(int *num);

int compare(const int *first, const int *second);

char *filename();

int pulldates(char str[30], int date1[3], int date2[3]);

int main() {
    char *fname = filename();
    FILE *src = fopen(fname, "r");
    if (!src)
        printf("n/a");
    else {
        int number[8];
        char destname[103];
        strcpy(destname, fname);
        strcat(destname, "2");
        int date1[3], date2[3];
        FILE *dest = fopen(destname, "a");
        char dates[30];
        fgets(dates, 30, stdin);
        int flag = pulldates(dates, date1, date2);
        flag &= fread(number, sizeof(int), 8, src) != 0;
        if (flag) {
            fseek(src, 0, SEEK_SET);
            while (fread(number, sizeof(int), 8, src) != 0) {
                if (compare(date1, number) > 0 || compare(number, date2) > 0) {
                    fwrite(number, sizeof(int), 8, dest);
                }
            }
        } else
            printf("n/a");
        remove(fname);
        rename(destname, fname);
        fclose(dest);
        fclose(src);
    }
    free(fname);
    return 0;
}

int pulldates(char str[30], int date1[3], int date2[3]) {
    int flag = 1;
    char *data = strtok(str, ". ");
    if (data)
        date1[2] = atoi(data);
    else
        flag = 0;

    data = strtok(NULL, ". ");
    if (data && flag)
        date1[1] = atoi(data);
    else
        flag = 0;

    data = strtok(NULL, ". ");
    if (data && flag)
        date1[0] = atoi(data);
    else
        flag = 0;

    data = strtok(NULL, ". ");
    if (data && flag)
        date2[2] = atoi(data);
    else
        flag = 0;

    data = strtok(NULL, ". ");
    if (data && flag)
        date2[1] = atoi(data);
    else
        flag = 0;

    data = strtok(NULL, ". ");
    if (data && flag)
        date2[0] = atoi(data);
    else
        flag = 0;
    return flag;
}

int compare(const int *first, const int *second) {
    int res = 0, i = 0;
    while (res == 0 && i < 3) {
        res = first[i] - second[i];
        i++;
    }
    return res;
}

char *filename() {
    char str[101];
    char *str2 = malloc(103 * sizeof(char));
    str2[0] = '.';
    str2[1] = '.';
    str2[2] = '/';
    fgets(str, 101, stdin);
    strcat(str2, str);
    str2[strlen(str2) - 1] = '\0';
    return str2;
}

void out(int *num) {
    for (int i = 0; i < 8; i++) {
        printf("%d", num[i]);
        if (i < 7) printf(" ");
    }
}
