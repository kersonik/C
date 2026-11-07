#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define READFILE "cisla.txt"
#define WRITEFILE "output.txt"

typedef struct
{
    int a;
    int b;
} numberPair;

void checkFileOpening(FILE *file) {
    if (file == NULL) {
        printf("[ERROR] File did not load properly.\n");
        printf("Exiting...\n");
        exit(EXIT_FAILURE);
    }
}

void checkFileCloseingAndClose(FILE *file) {
    if (fclose(file) != 0)
    {
        printf("[ERROR] File did not close properly.\n");
        printf("Exiting...\n");
        exit(EXIT_FAILURE);
    }
}

int getLeastCommonMultiplier (int a, int b) {
    a = abs(a);
    b = abs(b);

    if (a == 0 || b == 0) {
        return 0;
    }

    int max = (a > b) ? a : b;
    int greater = max;

    while (true) {

        if (max % a == 0 && max % b == 0) {break;}

        max += greater;
        
    }

    return max;
}

int getGreatestCommonFactor (int a, int b) {
    a = abs(a);
    b = abs(b);

    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void printHeader(FILE *file) {
    fprintf(file, "==================================\n");
    fprintf(file, "|LCM and GCF from file %10s|\n", READFILE);
    fprintf(file, "==================================\n");
    fprintf(file, "|order | N1  | N2  |  LCM  | GCF |\n");
    fprintf(file, "==================================\n");
}

void printFooter(FILE *file) {
    fprintf(file, "==================================\n\n");
}

float getAverage(float sum, float numberOfItems) {
    if (numberOfItems == 0.0f) {
        return 0.0f;
    }
    return sum / numberOfItems;
}

int main() {
    
    FILE *readFile = fopen(READFILE, "r");
    checkFileOpening(readFile);

    FILE *writeFile = fopen(WRITEFILE, "w");
    checkFileOpening(writeFile);

    numberPair item;

    int lineCounter = 0;
    int lineFileCounter = 0;
    int avarage = 0;
    int avarageFile = 0;
    printHeader(stdout);
    printHeader(writeFile);

    while (fscanf(readFile, "%d %d", &item.a, &item.b) == 2)
    {
        lineCounter++;
        int LCM = getLeastCommonMultiplier(item.a, item.b);
        int GCF = getGreatestCommonFactor(item.a, item.b);
        
        printf("| %3d. | %3d | %3d | %5d | %3d |\n", lineCounter, item.a, item.b, LCM, GCF);

        if (GCF > 1)
        {
            lineFileCounter++;
            fprintf(writeFile, "| %3d. | %3d | %3d | %5d | %3d |\n", lineFileCounter, item.a, item.b, LCM, GCF);
            avarageFile += item.a;
        }
        
        avarage += item.a;
    }
    
    printFooter(stdout);
    printFooter(writeFile);

    fprintf(stdout, "The average of the numbers in the first column is %.2f. The file contains %d pairs.\n", getAverage(avarage, lineCounter), lineCounter);
    fprintf(writeFile, "The average of the numbers in the first column is %.2f. The file contains %d pairs with GCF > 1.\n", getAverage(avarageFile, lineFileCounter), lineFileCounter);

    checkFileCloseingAndClose(readFile);
    checkFileCloseingAndClose(writeFile);

    //getchar();

    return 0;
}

