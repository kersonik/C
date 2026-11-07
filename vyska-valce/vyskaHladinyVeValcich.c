#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define READ_FILE_NAME "cisla.txt"
#define WRITE_FILE_NAME "output.txt"
#define PI 3.14159265358979323846

void checkFileOpening(FILE *file, const char *fileName) {
    if (file == NULL)
    {
        printf("[ERROR] - File %s was not opened properly.\n", fileName);
        printf("[INFO] - Exiting program.\n");
        exit(EXIT_FAILURE);
    }
}

void checkFileClosingAndClose(FILE *file, const char *fileName) {
    if (fclose(file) != 0)
    {
        printf("[ERROR] - File %s was not closed properly.\n", fileName);
        printf("[INFO] - Exiting program.\n");
        exit(EXIT_FAILURE);
    }
}

float calculateCylinderVolume(int radius, int height) {
    return (float)(PI * radius * radius * height / 1000.0);
}

float getWaterLevel(int radius, int amount) {
    if (radius <= 0) {
        return 0.0f;
    }

    return (float)((amount * 1000.0) / (PI * radius * radius));
}

void printStdoutHeader(FILE *file) {
    fprintf(file, "===============================================================\n");
    fprintf(file, "========================== Cylinders ==========================\n");
    fprintf(file, "===============================================================\n");
    fprintf(file, "| Order | Radius | Height |   Volume   | Amount of water |\n");
    fprintf(file, "===============================================================\n");
}

void printStdoutFooter(FILE *file) {
    fprintf(file, "===============================================================\n\n");
}

void printFileHeader(FILE *file) {
    fprintf(file, "===============================================================================\n");
    fprintf(file, "================================== Cylinders ==================================\n");
    fprintf(file, "===============================================================================\n");
    fprintf(file, "| Order | Radius | Height |   Volume   | Amount of water |   Water level  |\n");
    fprintf(file, "===============================================================================\n");
}

void printFileFooter(FILE *file) {
    fprintf(file, "===============================================================================\n\n");
}

int main(void)
{
    FILE *readFile = fopen(READ_FILE_NAME, "r");
    FILE *writeFile = fopen(WRITE_FILE_NAME, "w");

    checkFileOpening(readFile, READ_FILE_NAME);
    checkFileOpening(writeFile, WRITE_FILE_NAME);

    int radius = 0;
    int height = 0;
    int amount = 0;
    int order = 0;
    int writtenCount = 0;

    printStdoutHeader(stdout);
    printFileHeader(writeFile);

    while (fscanf(readFile, "%d %d %d", &radius, &height, &amount) == 3)
    {
        order++;

        if (radius <= 0 || height <= 0 || amount < 0)
        {
            fprintf(stdout, "[WARN] - Invalid input on order %d (r=%d, h=%d, water=%d).\n", order, radius, height, amount);
            continue;
        }

        float cylinderVolume = calculateCylinderVolume(radius, height);

        if (cylinderVolume >= amount)
        {
            writtenCount++;
            float waterLevel = getWaterLevel(radius, amount);

            fprintf(writeFile,
                    "| %5d | %4d cm | %4d cm | %7.2f dm3 | %11d l | %11.2f cm |\n",
                    writtenCount,
                    radius,
                    height,
                    cylinderVolume,
                    amount,
                    waterLevel);
        }

        fprintf(stdout,
                "| %5d | %4d cm | %4d cm | %7.2f dm3 | %11d l |\n",
                order,
                radius,
                height,
                cylinderVolume,
                amount);
    }

    printStdoutFooter(stdout);
    printFileFooter(writeFile);

    fprintf(stdout, "[INFO] - From file %s were read %d records.\n", READ_FILE_NAME, order);
    fprintf(stdout, "[INFO] - Into file %s were written %d records.\n", WRITE_FILE_NAME, writtenCount);
    fprintf(stdout, "[INFO] - File %s was created.\n", WRITE_FILE_NAME);

    checkFileClosingAndClose(readFile, READ_FILE_NAME);
    checkFileClosingAndClose(writeFile, WRITE_FILE_NAME);

    return 0;
}