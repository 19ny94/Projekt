#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void sort(char* arr1) {
    char buff;
    for (int i = 0; i < strlen(arr1); i++) {
        for (int j = i+1; j < strlen(arr1); j++) {
            if (arr1[i] > arr1[j]) {
                buff = arr1[i];
                arr1[i] = arr1[j];
                arr1[j] = buff;
            }
        }
    }
}

bool if_equal(char *arg1, char *arg2)
{
    for (int i = 0; arg2[i] != '\0'; i++) {
        if (arg1[i] != arg2[i]) {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[])
{

    char buffer[101];
    int found_counter = 0;
    int enable_counter = 0;
    char enable[256] = {0};
    if (argc < 2) {
        printf("Enable: ");
        while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            //buffer[strcspn(buffer, "\n")] = '\0';
            if (strchr(enable, toupper(buffer[0])) == NULL) {
                enable[enable_counter] = toupper(buffer[0]);
                enable_counter++;
            }
        }
        sort(enable);
        printf("%s\n", enable);
        return 0;
    }
    else {
        while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            for (int i = 0; argv[1][i] != '\0'; i++) {
                argv[1][i] = toupper(argv[1][i]);
            }
            for (int i = 0; buffer[i] != '\0'; i++) {
                buffer[i] = toupper(buffer[i]);
                if (buffer[i] == '\n') {
                    buffer[i] = '\0';
                }
            }
            if (if_equal(buffer, argv[1]) == true) {
                if (if_equal(argv[1], buffer) == true) {
                    char ready_word[101];
                    strcpy(ready_word, buffer);
                    found_counter++;
                    printf("Found: %s", ready_word);
                    // printf("%d", found_counter);
                } else {
                    printf("Enable %c", buffer[0]);
                    enable_counter++;
                    // printf("%d", enable_counter);
                }
            }
        }
    }
    return 0;
}