#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void out(int *num);

int output(FILE *file);

int compare(const int *first, const int *second);

void sort(FILE *file);

int add(FILE *file, int num[8]);

FILE *openfile();

int main() {
    FILE *file = openfile();
    if (!file)
        printf("n/a");
    else {
        int num[8], c, flag = 1;
        while (flag) {
            if (scanf("%d", &c) != 1)
                printf("n/a");
            else {
                switch (c) {
                    case -1:
                        flag = 0;
                        break;
                    case 0:
                        if (output(file) == 0) printf("n/a");
                        break;
                    case 1:
                        sort(file);
                        if (output(file) == 0) printf("n/a");
                        break;
                    case 2:
                        if (!add(file, num))
                            printf("n/a");
                        else {
                            fwrite(num, sizeof(int), 8, file);
                            fseek(file, 0, SEEK_SET);
                            sort(file);
                            output(file);
                        }
                        break;
                    default:
                        printf("n/a");
                        break;
                }
            }
            rewind(stdin);
        }
        fclose(file);
    }
    return 0;
}

void out(int *num) {
    for (int i = 0; i < 8; i++) {
        printf("%d", num[i]);
        if (i < 7) printf(" ");
    }
}

int output(FILE *file) {
    int number[8], ret = 1;
    if (fread(number, sizeof(int), 8, file) == 0)
        ret = 0;
    else {
        out(number);
        while (fread(number, sizeof(int), 8, file) != 0) {
            printf("\n");
            out(number);
        }
    }
    fseek(file, 0, SEEK_SET);
    return ret;
}

int compare(const int *first, const int *second) {
    int res = 0, i = 0;
    while (res == 0 && i < 8) {
        res = first[i] - second[i];
        i++;
    }
    return res;
}

void sort(FILE *file) {
    int number1[8], number2[8];
    fpos_t a, b;
    fgetpos(file, &a);
    while (fread(number1, sizeof(int), 8, file) != 0) {
        fgetpos(file, &b);
        while ((fread(number2, sizeof(int), 8, file)) != 0) {
            if (compare(number1, number2) > 0) {
                fsetpos(file, &a);
                fwrite(number2, sizeof(int), 8, file);
                fsetpos(file, &b);
                fwrite(number1, sizeof(int), 8, file);
                fsetpos(file, &a);
                fread(number1, sizeof(int), 8, file);
                fsetpos(file, &b);
                fread(number2, sizeof(int), 8, file);
            }
            fgetpos(file, &b);
        }
        fsetpos(file, &a);
        fread(number1, sizeof(int), 8, file);
        fgetpos(file, &a);
    }
    fseek(file, 0, SEEK_SET);
}

int add(FILE *file, int num[8]) {
    while (fread(num, sizeof(int), 8, file) != 0)
        ;
    int res = 1;
    if (scanf("%d", &num[0]) != 1 || num[0] < 0) res = 0;
    if (scanf("%d", &num[1]) != 1 || num[1] < 0 || num[1] > 12) res = 0;
    if (scanf("%d", &num[2]) != 1 || num[2] < 0 || num[2] > 31) res = 0;
    if (scanf("%d", &num[3]) != 1 || num[3] < 0 || num[3] > 23) res = 0;
    if (scanf("%d", &num[4]) != 1 || num[4] < 0 || num[4] > 59) res = 0;
    if (scanf("%d", &num[5]) != 1 || num[5] < 0 || num[5] > 59) res = 0;
    if (scanf("%d", &num[6]) != 1 || (num[6] != 1 && num[6] != 0)) res = 0;
    if (scanf("%d", &num[7]) != 1) res = 0;
    return res;
}

FILE *openfile() {
    char str[101], str2[103] = "../";
    fgets(str, 101, stdin);
    strcat(str2, str);
    str2[strlen(str2) - 1] = '\0';
    FILE *file = fopen(str2, "r+b");
    return file;
}
