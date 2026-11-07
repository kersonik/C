#include <stdio.h>
#include <stdlib.h>

#define READ_FILE_NAME "vysky_vahy.txt"
#define WRITE_FILE_NAME "obezita.txt"

typedef struct
{
    int height;
    int weight;
} personData;

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

float getMetersFromCm(int heightCm)
{
    return (float)heightCm / 100.0f;
}

float getBmi(int weightKg, int heightCm)
{
    float heightM = getMetersFromCm(heightCm);
    return (float)weightKg / (heightM * heightM);
}

void printStdoutHeader(FILE *file)
{
    fprintf(file, "  U D A J E   Z E   S O U B O R U\n");
    fprintf(file, "-------------------------------------\n");
    fprintf(file, "poradi|vyska(cm)|vaha(kg)|  BMI  |\n");
    fprintf(file, "-------------------------------------\n");
}

void printFileHeader(FILE *file)
{
    fprintf(file, "  O B E Z N I   J E D I N C I\n");
    fprintf(file, "-------------------------------------\n");
    fprintf(file, "poradi|vyska(cm)|vaha(kg)|  BMI  |\n");
    fprintf(file, "-------------------------------------\n");
}

void printRow(FILE *file, int order, int height, int weight, float bmi)
{
    fprintf(file, "%6d.|%9d|%8d|%7.2f|\n", order, height, weight, bmi);
}

int main(void)
{
    FILE *readFile = fopen(READ_FILE_NAME, "r");
    FILE *writeFile = fopen(WRITE_FILE_NAME, "w");

    checkFileOpening(readFile, READ_FILE_NAME);
    checkFileOpening(writeFile, WRITE_FILE_NAME);

    personData item = {0, 0};
    int totalCount = 0;
    int obeseCount = 0;
    int sumHeight = 0;

    printStdoutHeader(stdout);
    printFileHeader(writeFile);

    while (fscanf(readFile, "%d %d", &item.height, &item.weight) == 2)
    {
        totalCount++;
        sumHeight += item.height;

        float bmi = getBmi(item.weight, item.height);

        printRow(stdout, totalCount, item.height, item.weight, bmi);

        if (bmi > 30.0f)
        {
            obeseCount++;
            printRow(writeFile, obeseCount, item.height, item.weight, bmi);
        }
    }

    fprintf(stdout, "-------------------------------------\n");
    fprintf(writeFile, "-------------------------------------\n");

    fprintf(stdout, "\nZe souboru %s byly precteny udaje o %d osobach.\n", READ_FILE_NAME, totalCount);

    if (totalCount > 0)
    {
        fprintf(stdout, "Prumerna vyska souboru %d osob je %.2f cm.\n\n", totalCount, (float)sumHeight / (float)totalCount);
    }
    else
    {
        fprintf(stdout, "Prumerna vyska souboru 0 osob je 0.00 cm.\n\n");
    }

    fprintf(stdout, "Byl vytvoren soubor %s.\n", WRITE_FILE_NAME);

    fprintf(writeFile, "Do souboru %s byly zapsany udaje o %d obeznich osobach.\n", WRITE_FILE_NAME, obeseCount);

    checkFileClosingAndClose(readFile, READ_FILE_NAME);
    checkFileClosingAndClose(writeFile, WRITE_FILE_NAME);

    return 0;
}