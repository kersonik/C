#include <stdio.h>
#include <stdlib.h>

#define READ_FILE_NAME "cisla.txt"
#define WRITE_FILE_NAME "output.txt"

typedef struct
{
    int distance;
    int time;
} distanceTime;

typedef struct
{
    int km;
    int m;
} kilometersMeters;

typedef struct
{
    int min;
    int sec;
} minutesSeconds;


void checkFileOpening(FILE *file)
{
    if (file == NULL)
    {
        printf("[ERROR] - File did not open properly.\n");
        printf("[INFO] - Exiting program.\n");
        exit(EXIT_FAILURE);
    }
}

void checkAndCloseFile(FILE *file)
{
    if (fclose(file) != 0)
    {
        printf("[ERROR] - File did not close properly.\n");
        printf("[INFO] - Exiting program.\n");
        exit(EXIT_FAILURE);
    }
}

void printStdoutHeader(FILE *file)
{
    fprintf(file, "========Table of distance, time and speed========\n");
    fprintf(file, "=================================================\n");
    fprintf(file, "|--Order--|--Distance--|--Time--|---Speed km/h--|\n");
    fprintf(file, "=================================================\n");
}

void printFileHeader(FILE *file)
{
    fprintf(file, "=============Table of distance, time and speed===============\n");
    fprintf(file, "=============================================================\n");
    fprintf(file, "|--Order--|----Distance---|-----Time----|-----Speed km/h----|\n");
    fprintf(file, "=============================================================\n");
}

void printStdoutFooter(FILE *file)
{
    fprintf(file, "=================================================\n\n\n");
}

void printFileFooter(FILE *file)
{
    fprintf(file, "=============================================================\n\n\n");
}

minutesSeconds secondsToCombined(int seconds) {
    minutesSeconds ms = {seconds / 60, seconds % 60};
    return ms;
}

kilometersMeters metersToCombined(int meters) {
    kilometersMeters km = {meters / 1000, meters % 1000};
    return km;
}

float mps(int distance, int time) {
    float mps = (float)distance / (float)time;
    return mps;
}

float mpsTOkmph(float mps) {
    float kmph = mps * 3.6f;
    return kmph;
}

int main()
{
    FILE *readFile;
    FILE *writeFile;

    readFile = fopen(READ_FILE_NAME, "r");
    writeFile = fopen(WRITE_FILE_NAME, "w");

    checkFileOpening(readFile);
    checkFileOpening(writeFile);

    distanceTime item = {0, 0};
    int order = 0;
    int order2 = 0;
    int sum = 0;

    printFileHeader(writeFile);
    printStdoutHeader(stdout);

    while (fscanf(readFile, "%d %d", &item.distance, &item.time) == 2)
    {
        sum += item.distance;
        order++;

        if (item.time <= 0)
        {
            fprintf(stdout, "[WARN] - Time is %d, speed cannot be computed.\n", item.time);
            continue;
        }

        float speedMps = mps(item.distance, item.time);
        float speedKmph = mpsTOkmph(speedMps);

        if (speedMps > 10)
        {
            order2++;
            kilometersMeters distCombined = metersToCombined(item.distance);
            minutesSeconds timeCombined = secondsToCombined(item.time);

            fprintf(writeFile, "|   %2d.   | %3d km %3d m  | %2d min %2d s | %10.2f km/h   |\n", 
                    order2, 
                    distCombined.km, distCombined.m, 
                    timeCombined.min, timeCombined.sec, 
                    speedKmph);
        }

        fprintf(stdout, "|   %2d.   |  %6d m  | %4d s |  %6.2f m/s  |\n", order, item.distance, item.time, speedMps);
    }

    printFileFooter(writeFile);
    printStdoutFooter(stdout);

    fprintf(writeFile, "[INFO] - Into file %s there were %d pairs of numbers written.\n", WRITE_FILE_NAME, order2);

    if (order > 0)
    {
        fprintf(stdout, "Average distance is %.2f meters.\n", (float)sum / (float)order);
    }
    else
    {
        fprintf(stdout, "Average distance is 0.00 meters.\n");
    }

    fprintf(stdout, "[INFO] - From file %s were read %d pairs of numbers.\n", READ_FILE_NAME, order);
    fprintf(stdout, "[INFO] - File %s was created.\n", WRITE_FILE_NAME);
    fprintf(stdout, "\n\n\n");

    checkAndCloseFile(readFile);
    checkAndCloseFile(writeFile);

    return 0;
}