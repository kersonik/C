#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define FILENAME "vysky_vahy.txt"
#define FILEOUTPUT "obezita.txt"

typedef struct {
    int height;
    int weight;
}PERSON;

void header(FILE *f){
    fprintf(f, "----- B M I  I N F O R M A T I O N -----\n");
    fprintf(f, "----------------------------------------\n");
    fprintf(f, "|order | height(cm) | weight(kg) | BMI  |\n");
    fprintf(f, "----------------------------------------\n");
}

void footer(FILE *f, int counter){
    fprintf(f,"\nFile %s: %d records read\n", FILENAME, counter);
}

double height_Meters(PERSON pers) {
    return pers.height / 100.0;
}

double BMI(PERSON pers) {
    return pers.weight / pow(height_Meters(pers), 2);
}

void printout(FILE *f, int counter, PERSON p) {
    fprintf(f, "|%5d.| %11d| %11d|%6.2f|\n", counter, p.height, p.weight, BMI(p));
}

int main(void) {
    PERSON person;
    int counter = 0;
    int counterBMI = 0;
    double totalHeigh = 0;

    FILE *fr = fopen(FILENAME, "r");


    if(fr == NULL) {
        printf("The file %s wasn't opened correctly. The program will now exit.\n", FILENAME);
        return EXIT_FAILURE;
    }

    FILE *fw  = fopen(FILEOUTPUT, "w");

    if(fw == NULL) {
        printf("The file %s wasn't opened correctly. The program will now exit.\n", FILEOUTPUT);
        fclose(fr);
        return EXIT_FAILURE;
    }

    header(fw);
    header(stdout);
    while (fscanf(fr, "%d %d", &person.height, &person.weight) == 2) {
        counter++;
        float bmi = BMI(person);
        printout(stdout, counter, person);
        if (bmi > 30) {
            counterBMI++;
            printout(fw, counterBMI, person);
        }
        totalHeigh += person.height;
    }

    footer(stdout, counter);
    footer(fw, counterBMI);

    printf("Avarage height of group of %d people is %.2f cm\n", counter, totalHeigh/counter);


    if (fclose(fr) != 0) {
        perror("Error closing file");
        return 1;
    }

    if (fclose(fw) != 0) {
        perror("Error closing file");
        return 1;
    }


    return 0;
}

