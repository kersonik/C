#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define WRITE_FILE_NAME "prvocisla.txt"
#define MIN_LIMIT 3
#define MAX_LIMIT 100
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

bool isPrime(int number)
{
    if (number <= 1)
    {
        return false;
    }

    for (int i = 2; i * i <= number; i++)
    {
        if (number % i == 0)
        {
            return false;
        }
    }

    return true;
}

void printNumber(FILE *file, int number, bool prime)
{
    if (prime)
    {
        fprintf(file, "%5d*", number);
    }
    else
    {
        fprintf(file, "%6d", number);
    }
}

int main(void)
{
    int startNum = 0;

    while (1)
    {
        printf("Zadej cele cislo v intervalu od %d do %d:", MIN_LIMIT, MAX_LIMIT);
        if (scanf("%d", &startNum) == 1 && startNum >= MIN_LIMIT && startNum <= MAX_LIMIT)
        {
            break;
        }
        printf("Chybne cislo. Zadej znovu.\n");
        while (getchar() != '\n'); // vyčištění vstupního bufferu
    }

    FILE *writeFile = fopen(WRITE_FILE_NAME, "w");
    checkFileOpening(writeFile, WRITE_FILE_NAME);

    int colCount = 0;

    for (int i = startNum; i <= MAX_LIMIT; i++)
    {
        bool prime = isPrime(i);

        printNumber(stdout, i, prime);
        printNumber(writeFile, i, prime);

        colCount++;

        if (colCount % COLS == 0 || i == MAX_LIMIT)
        {
            fprintf(stdout, "\n");
            fprintf(writeFile, "\n");
        }
    }

    checkFileClosingAndClose(writeFile, WRITE_FILE_NAME);

    return 0;
}