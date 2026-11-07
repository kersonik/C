#include <stdio.h>
#include <stdlib.h>

#define READ_FILE_NAME "cisla.txt"
#define WRITE_FILE_NAME "vysledky.txt"

typedef struct
{
    int base;
    int exponent;
} numberPair;

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

long long getPower(int base, int exponent)
{
    if (exponent < 0)
    {
        return 0;
    }

    long long result = 1;

    for (int i = 0; i < exponent; i++)
    {
        result *= base;
    }

    return result;
}

int main(void)
{
    FILE *readFile = fopen(READ_FILE_NAME, "r");
    FILE *writeFile = fopen(WRITE_FILE_NAME, "w");

    checkFileOpening(readFile, READ_FILE_NAME);
    checkFileOpening(writeFile, WRITE_FILE_NAME);

    numberPair item = {0, 0};

    while (fscanf(readFile, "%d %d", &item.base, &item.exponent) == 2)
    {
        long long result = getPower(item.base, item.exponent);
        fprintf(writeFile, "%4d ^ %2d = %12lld\n", item.base, item.exponent, result);
    }

    checkFileClosingAndClose(readFile, READ_FILE_NAME);
    checkFileClosingAndClose(writeFile, WRITE_FILE_NAME);

    return 0;
}