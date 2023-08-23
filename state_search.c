#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(char date[15], const int *mass);

FILE *openfile();

int main() {
    FILE *file = openfile();
    char date[15];
    int flag = 0;
    fgets(date, 15, stdin);
    date[strlen(date) - 1] = '\0';
    if (file) {
        int number[8];
        while (fread(number, sizeof(int), 8, file) != 0) {
            if (compare(date, number)) {
                printf("%d", number[7]);
                flag = 1;
                break;
            }
        }
        fclose(file);
    }
    if (!flag) printf("n/a");
    return 0;
}

int compare(char date[15], const int *mass) {
    int flag = 1;
    char *data = strtok(date, ".");
    if (data)
        flag &= mass[2] - strtod(data, NULL) <= 0.000001;
    else
        flag = 0;
    data = strtok(NULL, ".");
    if (data && flag)
        flag &= mass[1] - strtod(data, NULL) <= 0.000001;
    else
        flag = 0;
    data = strtok(NULL, ".");
    if (flag && data)
        flag &= mass[0] - strtod(data, NULL) <= 0.000001;
    else
        flag = 0;
    return flag;
}

FILE *openfile() {
    char str[101], str2[103] = "../";
    fgets(str, 101, stdin);
    strcat(str2, str);
    str2[strlen(str2) - 1] = '\0';
    FILE *file = fopen(str2, "r+b");
    return file;
}
