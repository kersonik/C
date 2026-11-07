#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INPUT_FILENAME "casy.txt"
#define OUTPUT_FILENAME "odpoledne.txt"

typedef struct
{
    int hours;
    int minutes;
    int seconds;
} timeT3;

FILE *openFileAndCheck(const char *filename, const char *mode)
{
    FILE *file = fopen(filename, mode);

    if (file == NULL)
    {
        printf("[ERROR] Soubor '%s' se nepodarilo otevrit.\n", filename);
        printf("[INFO] Program bude ukoncen.\n");
        exit(EXIT_FAILURE);
    }

    return file;
}

void closeFileAndCheck(FILE *file)
{
    if (fclose(file) != 0)
    {
        printf("[ERROR] Soubor se nepodarilo zavrit.\n");
        printf("[INFO] Program bude ukoncen.\n");
        exit(EXIT_FAILURE);
    }
}

int getSecondsFromMidnight(timeT3 time)
{
    return time.hours * 3600 + time.minutes * 60 + time.seconds;
}

int getAngloHour(int europeanHour)
{
    if (europeanHour == 0)
    {
        return 12;
    }
    if (europeanHour > 12)
    {
        return europeanHour - 12;
    }

    return europeanHour;
}

bool isValidTime(timeT3 time)
{
    return time.hours >= 0 && time.hours <= 23 &&
           time.minutes >= 0 && time.minutes <= 59 &&
           time.seconds >= 0 && time.seconds <= 59;
}

void printStdoutHeader(FILE *file)
{
    fprintf(file, "+------+------------+-----------+----------------+\n");
    fprintf(file, "|Poradi| 24h cas    | Sekundy   | 12h cas        |\n");
    fprintf(file, "+------+------------+-----------+----------------+\n");
}

void printStdoutFooter(FILE *file)
{
    fprintf(file, "+------+------------+-----------+----------------+\n\n");
}

void printTimeRow(FILE *file, int order, timeT3 time, int secondsFromMidnight, int angloHour, const char *suffix)
{
    fprintf(file,
            "| %2d   | %02d:%02d:%02d   | %7d   | %02d:%02d:%02d %s    |\n",
            order,
            time.hours,
            time.minutes,
            time.seconds,
            secondsFromMidnight,
            angloHour,
            time.minutes,
            time.seconds,
            suffix);
}

int main()
{
    FILE *readFile = openFileAndCheck(INPUT_FILENAME, "r");
    FILE *writeFile = openFileAndCheck(OUTPUT_FILENAME, "w");

    timeT3 time;
    int order = 1;
    int writtenCount = 0;

    printStdoutHeader(stdout);
    printStdoutHeader(writeFile);

    while (fscanf(readFile, "%d %d %d", &time.hours, &time.minutes, &time.seconds) == 3)
    {
        if (!isValidTime(time))
        {
            printf("[WARN] - Neplatny cas na poradi %d: %02d:%02d:%02d\n", order, time.hours, time.minutes, time.seconds);
            order++;
            continue;
        }

        int secondsFromMidnight = getSecondsFromMidnight(time);
        int angloHour = getAngloHour(time.hours);
        bool isPM = time.hours >= 12;
        const char *suffix = isPM ? "PM" : "AM";

        if (isPM)
        {
            writtenCount++;
            printTimeRow(writeFile, writtenCount, time, secondsFromMidnight, angloHour, suffix);
        }

        printTimeRow(stdout, order, time, secondsFromMidnight, angloHour, suffix);
        order++;
    }

    printStdoutFooter(stdout);
    printStdoutFooter(writeFile);

    fprintf(writeFile, "Pocet zapsanych udaju: %d\n", writtenCount);

    fprintf(stdout, "[INFO] - Ze souboru %s bylo precteno %d zaznamu.\n", INPUT_FILENAME, order - 1);
    fprintf(stdout, "[INFO] - Do souboru %s bylo zapsano %d zaznamu.\n", OUTPUT_FILENAME, writtenCount);

    closeFileAndCheck(readFile);
    closeFileAndCheck(writeFile);

    return EXIT_SUCCESS;
}