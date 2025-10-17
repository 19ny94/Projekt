#include  <ctype.h>
#include <stdio.h>
#include <string.h>
//magnum opus

void print_result(char enable[256], char matches[256], int counter, int found, char *prefix);

char* qsort(char enable[], int len);

void inicializace_enable(char enable[256], char next_letter, int exist, char lines[101], char *prefix);
//popis fuknci viz pri pouziti

int main(int argc, char *argv[])
{
    char lines[101]; char enable[256] = {0}; char matches[256] = {0};
    int i = 0; int found = 0; int counter = 0; int match = 0; int longer = 0;
    char *prefix; char next_letter = '\0';

    if (argc < 2) { //pokud je prefix prazdni
        prefix = "";
    }else {
        prefix = argv[1];
        for (int q = 0; argv[1][q] != '\0'; q++) {
            argv[1][q] = toupper(argv[1][q]); //case_insensetive pro prefix
        }
    }
    while (fgets(lines, sizeof(lines), stdin) != NULL) { //cteme cely vstup
        if (lines[strlen(lines) - 1] == '\n') { //pokud znak konci na \n, coz ma vliv na porovnani
            lines[strlen(lines) - 1] = '\0'; //dame na konec symbol konce radku(prazdny char)
        }
        match = 1;
        for (i = 0; prefix[i] != '\0'; i++) {
            lines[i] = toupper(lines[i]); //case_insensitive pro sloupce
            if (prefix[i] != lines[i]) {
                match = 0;
                break;
            }
        }
        if (match == 1) {
            counter++; //counter, kolik mame radku shodujici c prefixem
            if (counter > 1 && strlen(lines) > strlen(prefix)) {
                longer = 1; //vice variant a prefix je mensi za radek
            }
            if (counter == 1) {
                strcpy(matches, lines); //pokud mame jenom jeden radek, ktery ma v sobe prefix - ulozime jej
            }
            if (counter > 1 || (strlen(lines) > strlen(prefix))) {
                next_letter = toupper(lines[strlen(prefix)]); // pokud mame vice variant, pridame dalsi(po prefixu) symbol pro hledani
            }
            if (strlen(prefix) == 0) { //prazdny prefix
                next_letter = toupper(lines[0]); //vypise prvni slopec
            }else {
                if (!longer || strlen(prefix) == strlen(lines)) {
                    found = 1; //pokud
                }
            }
            int exist = 0;
            inicializace_enable(enable, next_letter, exist, lines, prefix); //do pole enable predavame symboly, co jsme dostali po kontrolach, a odstranujeme stejna pismena
        }
    }
    print_result(enable, matches, counter, found, prefix); //funkce pro print vysledku
    return 0;
}

char* qsort(char enable[], int len) {
    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j < len; j++) {
            if (enable[i] > enable[j]) { //pokud symboly nejdou po sobe (treba za abecedou)
                char qsort = enable[i]; //dame je jedno za druhym
                enable[i] = enable[j];
                enable[j] = qsort;
            }
        }
    }
    return enable;
}

void print_result(char enable[256], char matches[256], int counter, int found, char *prefix) {
    if (counter == 0) { //nenaslo se zadne match
        printf("Not found");
    }
    if ((found == 1 && counter == 1) || strlen(prefix) == strlen(matches)){ //druha podminka je spis pro york a yorktown
        printf("Found: ");
        for (int i = 0; i < (int)strlen(matches); i++) {
            printf("%c", toupper(matches[i]));
        }
        printf("\n");
    }
    if (enable[0] != '\0' && counter > 1) {
        printf("Enable: %s\n", enable);
    }
}

void inicializace_enable(char enable[256], char next_letter, int exist, char lines[101], char *prefix) {
    for (int j = 0; enable[j] != '\0'; j++) {
        if (next_letter == enable[j]) { //pokud jiz mame symbol v enable - nic se nezmeni
            exist = 1;
            break;
        }
    }
    if (!exist && next_letter != '\n' && next_letter != '\0' && strlen(lines) > strlen(prefix)) {
        int len = strlen(enable);
        enable[len] = next_letter; //pokud znak se nenachazi jeste v enavble - pridame jej na konec
        enable[len + 1] = '\0';
        len = strlen(enable); //po tom, co jsme pridali do enable, obnovime len, protoze ono se uz nerovna tomu, co jsme meli na zacatku
        qsort(enable, len); //nahrada misto qsort))
    }
}