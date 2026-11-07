#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define WRITE_FILE_NAME "roky.txt"
#define MIN_YEAR 1900
#define MAX_YEAR 2010
#define COLS 8

void checkFileOpening(FILE *file, const char *fileName)
{
    if (file == NULL)
    {
        printf("[ERROR] - Soubor %s se nepodarilo otevrit.\n", fileName);
        printf("[INFO] - Ukoncuji program.\n");
        exit(EXIT_FAILURE);
    }
}

void checkFileClosingAndClose(FILE *file, const char *fileName)
{
    if (fclose(file) != 0)
    {
        printf("[ERROR] - Soubor %s se nepodarilo zavrit.\n", fileName);
        printf("[INFO] - Ukoncuji program.\n");
        exit(EXIT_FAILURE);
    }
}

bool isLeapYear(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    {
        return true;
    }
    return false;
}

void printYear(FILE *file, int year, bool leap)
{
    if (leap)
    {
        fprintf(file, "%5d*", year);
    }
    else
    {
        fprintf(file, "%6d", year);
    }
}

int main(void)
{
    int startYear = 0;

    while (1)
    {
        printf("Zadej rok v intervalu od %d do %d:", MIN_YEAR, MAX_YEAR);
        if (scanf("%d", &startYear) == 1 && startYear >= MIN_YEAR && startYear <= MAX_YEAR)
        {
            break;
        }
        printf("Chybny rok. Zadej znovu.\n");
        while (getchar() != '\n');
    }

    FILE *writeFile = fopen(WRITE_FILE_NAME, "w");
    checkFileOpening(writeFile, WRITE_FILE_NAME);

    int colCount = 0;

    for (int year = startYear; year <= MAX_YEAR; year++)
    {
        bool leap = isLeapYear(year);

        printYear(stdout, year, leap);
        printYear(writeFile, year, leap);

        colCount++;

        if (colCount % COLS == 0 || year == MAX_YEAR)
        {
            fprintf(stdout, "\n");
            fprintf(writeFile, "\n");
        }
    }

    checkFileClosingAndClose(writeFile, WRITE_FILE_NAME);

    return 0;
}