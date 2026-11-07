#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define READ_FILE_NAME "cisla.txt"
#define WRITE_FILE_NAME "vystup.txt"

typedef struct
{
    int base;
    int exponent;
} numberPair;

void checkFileOpening(FILE *file, const char *fileName)
{
    if (file == NULL)
    {
        printf("[ERROR] - File %s did not open properly.\n", fileName);
        printf("[INFO] - Exiting program.\n");
        exit(EXIT_FAILURE);
    }
}

void checkFileClosingAndClose(FILE *file, const char *fileName)
{
    if (fclose(file) != 0)
    {
        printf("[ERROR] - File %s did not close properly.\n", fileName);
        printf("[INFO] - Exiting program.\n");
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

void printHeader(FILE *file)
{
    fprintf(file, "=========================================================\n");
    fprintf(file, "============= Powers with prime base numbers ============\n");
    fprintf(file, "=========================================================\n");
    fprintf(file, "| Order |  Base  |  Exponent  |          Power          |\n");
    fprintf(file, "=========================================================\n");
}

void printFooter(FILE *file)
{
    fprintf(file, "=========================================================\n\n");
}

int main(void)
{
    FILE *readFile = fopen(READ_FILE_NAME, "r");
    FILE *writeFile = fopen(WRITE_FILE_NAME, "w");

    checkFileOpening(readFile, READ_FILE_NAME);
    checkFileOpening(writeFile, WRITE_FILE_NAME);

    numberPair item = {0, 0};
    int order = 0;
    int writtenCount = 0;
    int exponentSum = 0;

    printHeader(stdout);
    printHeader(writeFile);

    while (fscanf(readFile, "%d %d", &item.base, &item.exponent) == 2)
    {
        order++;
        exponentSum += item.exponent;

        long long power = getPower(item.base, item.exponent);
        bool prime = isPrime(item.base);

        // Výpis do STDOUT (všechny záznamy)
        if (item.exponent < 0)
        {
            fprintf(stdout, "| %5d | %6d | %10d | %23s |\n", order, item.base, item.exponent, "[WARN]");
        }
        else
        {
            fprintf(stdout, "| %5d | %6d | %10d | %23lld |\n", order, item.base, item.exponent, power);
        }

        // Zápis do SOUBORU v hezké tabulce (jen prvočísla)
        if (prime)
        {
            writtenCount++;
            fprintf(writeFile, "| %5d | %6d | %10d | %23lld |\n", writtenCount, item.base, item.exponent, power);
        }
    }

    printFooter(stdout);
    printFooter(writeFile);

    if (order > 0)
    {
        fprintf(stdout, "Average value in the second column is %.2f.\n", (float)exponentSum / (float)order);
    }
    else
    {
        fprintf(stdout, "Average value in the second column is 0.00.\n");
    }

    fprintf(stdout, "[INFO] - From file %s were read %d pairs.\n", READ_FILE_NAME, order);
    fprintf(stdout, "[INFO] - Into file %s were written %d pairs.\n", WRITE_FILE_NAME, writtenCount);
    fprintf(stdout, "[INFO] - File %s was created.\n", WRITE_FILE_NAME);

    checkFileClosingAndClose(readFile, READ_FILE_NAME);
    checkFileClosingAndClose(writeFile, WRITE_FILE_NAME);

    return 0;
}