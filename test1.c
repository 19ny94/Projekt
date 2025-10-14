#include <ctype.h>
#include <stdio.h>
#include <string.h>
// magnum opus

int main(int argc, char *argv[])
{
    char lines[101];
    char enable[256] = {0};
    char matches[256] = {0};
    int i = 0;
    int found = 0;
    int counter = 0;
    int match = 0;
    int longer = 0;
    char *prefix;
    char next_char = '\0';

    if (argc < 2) { // na pripad kdyz prefix prazdny
        prefix = "";
    } else {
        prefix = argv[1];
        for (int q = 0; argv[1][q] != '\0'; q++) { // case_insensitive pro prefix
            argv[1][q] = toupper(argv[1][q]);
        }
    }
    while (fgets(lines, sizeof(lines), stdin) != NULL) {
        // cteme cely vstup
        if (lines[strlen(lines) - 1] == '\n') { // pokud radek z stdin konci \n - odstanime
            lines[strlen(lines) - 1] = '\0';
        }
        match = 1;
        for (i = 0; prefix[i] != '\0'; i++) {
            lines[i] = toupper(lines[i]); // case_insensetive
            if (prefix[i] != lines[i]) {  // kontrola prefixu a vstupu na stejnem radku
                match = 0;
                break;
            }
        }
        if (match == 1 /*&& strncmp(lines, prefix, strlen(prefix)) == 0*/) {
            counter++;
            if (counter > 1 && strlen(lines) > strlen(prefix)) {
                longer = 1;
            }
            if (counter == 1) {
                strcpy(matches, lines);
            }
            if (counter > 1 || (strlen(lines) > strlen(prefix))) {
                next_char = toupper(lines[strlen(prefix)]);
                next_char = toupper(next_char);
            }
            if (strlen(prefix) == 0) {
                next_char = toupper(lines[0]); // pokud arhument neni zadan - vypise se prvni slopec
            } else {
                if ((strncmp(lines, prefix, strlen(prefix)) == 0 && !longer) || strlen(prefix) == strlen(lines)) {
                    found = 1;
                    // strcpy(matches,lines);
                }
                /*
                                            else if (counter > 1)//(strlen(lines) > strlen(prefix))
                                            {
                                            next_char = toupper(lines[strlen(prefix)]);
                                            printf("TEST. NEXT_CHAR: %c\n", next_char);
                                        }
                                            */
                // pokud pristi symbol je odlisni od vsech, co obsahuje prefix, tak pridame dalsi symbol ze vstupu
                /* udelam zde poznamku pro sebe na priste
                 * napr. pokud prefix = "ab", teda ma v sobe dva symboly, tak strlen(prefix) = 2;
                 * zaroven s tim lines = "abc", z toho vychazi ze lines[strlen(prefix)] = lines[2] = 'c', tento znak
                 * predavame promenne, ktera obsahuje dalsi mozny znak;
                 */
                next_char = toupper(next_char); // case_insensitive
            }
            // printf("TEST. NEXT_CHAR: %c\n", next_char);
            int exist = 0;
            for (int j = 0; enable[j] != '\0'; j++) { // kontrolujeme unikatnost do konce radku
                if (next_char == enable[j]) {
                    exist = 1; // pokud symbol z next_char jiz jsme potkali, tak opravdu existuje
                    break;
                }
            }
            if (!exist && next_char != '\n' && next_char != '\0' && strlen(lines) > strlen(prefix)) {
                int len = strlen(enable);
                // printf("TEST.NEXT_CHAR: %c\n", next_char);
                enable[len] =
                    next_char; // pokud program jeste symbol ne potkal, tak pridame jej na konec radku moznych symbolu
                enable[len + 1] = '\0'; // pridame konec
                for (int j = 0; j < len; j++) {
                    if (enable[j] > enable[j + 1]) { // nahrada misto qsort :)
                        char qsort = enable[j];
                        enable[j] = enable[j + 1];
                        enable[j + 1] = qsort; // pokud jakykoli symbol je mensi dalsiho, zmenime
                    }
                }
            }
        }
    }
    if (counter == 0) {
        printf("Not found");
    }
    if (found == 1 && counter == 1 || strncmp(matches, prefix, strlen(prefix)) == 0 && strlen(prefix) == strlen(matches)) {
        printf("Found: %s\n", matches);
    }
    /*else if (strncmp(matches, prefix, strlen(prefix)) == 0 && strlen(matches) != strlen(enable)) {
            printf("Enable: %s", enable);
        }*/
    if (enable[0] != '\0' && /*enable[0] != ' '*/  counter > 1) {
        printf("Enable: %s\n", enable);
    }
    /*if ( counter > 1 && found == 1) {
        printf("Found: %s\n", matches);
        printf("Enable: %s\n", enable);
    }*/
    return 0;
}