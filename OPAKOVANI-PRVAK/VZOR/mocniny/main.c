#include <stdio.h>
#include <stdlib.h>

#define SOUBOR "cisla.txt"
#define VYSLEDKY "vysledky.txt"

unsigned int mocnina(int base, int exponent) {
    unsigned int vysledek = 1;
    for (;exponent > 0;exponent--) {
        vysledek *= base;
    }
    return vysledek;
}

void zapisVysledek (FILE* fw, int base, int exponent) {
    fprintf(fw, "%2d ^ %2d = %u\n", base, exponent, mocnina(base, exponent));
}

int zavreniSouboru (FILE* f,const char *filename) {
    int vystup = fclose(f);
    if (vystup != 0) {
        printf("Chyba pri zavirani souboru %s", filename);
    }
    return vystup;
}

int main() {
    int base;
    int exponent;
    FILE *soubor;
    FILE *vysledky;

    soubor = fopen(SOUBOR, "r");

    if (soubor == NULL) {
        printf("Chyba: Soubor %s se nepodarilo otevrit.\n", SOUBOR);
        return 1;
    }

    vysledky = fopen(VYSLEDKY, "w");

    if (vysledky == NULL) {
        printf("Soubor %s se nepodarilo otevrit\n", VYSLEDKY);
    }


    while (fscanf(soubor,"%d %d",&base, &exponent) != EOF) {
        zapisVysledek(stdout, base, exponent);
        zapisVysledek(vysledky, base, exponent);
    }

    if (fclose(vysledky) != 0) {
        printf("Chyba pri zavirani souboru %s", VYSLEDKY);
        return 1;
    }

    if (fclose(soubor) != 0) {
        printf("Chyba pri zavirani souboru %s", SOUBOR);
        return 1;
    }

    printf("Soubor %s byl uspesne vytvoren\n", VYSLEDKY);
    return 0;


}
