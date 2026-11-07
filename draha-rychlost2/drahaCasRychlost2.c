#include <stdio.h>
#include <stdlib.h>

#define READ_FILE_NAME "cisla.txt"
#define WRITE_FILE_NAME "prevody.txt"

typedef struct
{
    int kilometers;
    int meters;
    int minutes;
    int seconds;
} distanceTime;

void checkFileOpening(FILE *file)
{
    if (file == NULL)
    {
        printf("[ERROR] - File did not open properly.\n");
        printf("[INFO] - Exiting program.\n");
        exit(EXIT_FAILURE);
    }
}

void checkFileClosingAndClose(FILE *file)
{
    if (fclose(file) != 0)
    {
        printf("[ERROR] - File did not close properly.\n");
        printf("[INFO] - Exiting program.\n");
        exit(EXIT_FAILURE);
    }
}

int getDistanceMeters(distanceTime item)
{
    return item.kilometers * 1000 + item.meters;
}

int getTimeSeconds(distanceTime item)
{
    return item.minutes * 60 + item.seconds;
}

float getSpeedMetersPerSecond(int distanceMeters, int timeSeconds)
{
    return (float)distanceMeters / (float)timeSeconds;
}

float getSpeedKilometersPerHour(int distanceMeters, int timeSeconds)
{
    float speedMps = getSpeedMetersPerSecond(distanceMeters, timeSeconds);
    return speedMps * 3.6f;
}

void printStdoutHeader(FILE *file)
{
    fprintf(file, "==============================================================================\n");
    fprintf(file, "========================= Distance, time and speed ===========================\n");
    fprintf(file, "==============================================================================\n");
    fprintf(file, "|Order| Distance       | Time         |Speed km/h | Speed m/s | Distance (m) |\n");
    fprintf(file, "==============================================================================\n");
}

void printStdoutFooter(FILE *file)
{
    fprintf(file, "==============================================================================\n\n");
}

void printFileHeader(FILE *file)
{
    fprintf(file, "============================================\n");
    fprintf(file, "============= Converted values =============\n");
    fprintf(file, "============================================\n");
    fprintf(file, "|Order|Distance (m) | Time (s) | Speed m/s |\n");
    fprintf(file, "============================================\n");
}

void printFileFooter(FILE *file)
{
    fprintf(file, "============================================\n\n");
}

int main()
{
    FILE *readFile = fopen(READ_FILE_NAME, "r");
    FILE *writeFile = fopen(WRITE_FILE_NAME, "w");

    checkFileOpening(readFile);
    checkFileOpening(writeFile);

    distanceTime item;
    int orderStdout = 0;
    int orderFile = 0;
    int readCount = 0;
    int sumDistanceMeters = 0;
    int fastReadCount = 0;
    int fastSumDistanceMeters = 0;

    printStdoutHeader(stdout);
    printFileHeader(writeFile);

    while (fscanf(readFile, "%d %d %d %d", &item.kilometers, &item.meters, &item.minutes, &item.seconds) == 4)
    {
        int distanceMeters = getDistanceMeters(item);
        int timeSeconds = getTimeSeconds(item);

        orderStdout++;
        readCount++;
        sumDistanceMeters += distanceMeters;

        if (timeSeconds == 0)
        {
            fprintf(stdout, "| %3d | %3d km %4d m | %3d min %2d s |   [WARN]   |   [WARN]  | %8d     |\n", orderStdout, item.kilometers, item.meters, item.minutes, item.seconds, distanceMeters);
            continue;
        }

        float speedMps = getSpeedMetersPerSecond(distanceMeters, timeSeconds);
        float speedKmph = getSpeedKilometersPerHour(distanceMeters, timeSeconds);

        fprintf(stdout,
                "| %3d. | %3d km %4d m | %3d min %2d s | %9.2f | %9.2f | %8d     |\n",
                orderStdout,
                item.kilometers,
                item.meters,
                item.minutes,
                item.seconds,
                speedKmph,
                speedMps,
                distanceMeters);

        if (speedKmph > 20.0f)
        {
            orderFile++;
            fprintf(writeFile,
                    "| %3d | %11d | %8d | %9.2f |\n",
                    orderFile,
                    distanceMeters,
                    timeSeconds,
                    speedMps);
            fastSumDistanceMeters += distanceMeters;
            fastReadCount++;
        }
    }

    printStdoutFooter(stdout);
    printFileFooter(writeFile);

    if (readCount > 0)
    {
        fprintf(stdout, "Average distance is %.2f m.\n", (float)sumDistanceMeters / (float)readCount);
        fprintf(writeFile, "Average distance is %.2f m.\n", (float)fastSumDistanceMeters / (float)fastReadCount);
    }
    else
    {
        fprintf(stdout, "Average distance is 0.00 m.\n");
        fprintf(writeFile, "Average distance is 0.00 m.\n");
    }

    fprintf(stdout, "[INFO] - From file %s were read %d records.\n", READ_FILE_NAME, readCount);
    fprintf(stdout, "[INFO] - Into file %s were written %d records.\n", WRITE_FILE_NAME, orderFile);

    fprintf(writeFile, "[INFO] - Into file %s were written %d records.\n", WRITE_FILE_NAME, orderFile);

    checkFileClosingAndClose(readFile);
    checkFileClosingAndClose(writeFile);

    return 0;
}
