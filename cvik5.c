#include <stdio.h>

int main(void) {
    struct date_t{
        int year;
        int month;
        int day;
    };
}
    int valid(struct date_t d) {

        if (d.year < 0 || d.month < 1 || d.month > 12 || d.day < 1) {
            return 0;
        }
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    //prestupny rok
        if (d.year % 4 == 0 && d.year % 100 != 0 || d.year % 400 == 0) {
            days[1] = 29;
        }




    return 1;
}