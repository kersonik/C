#include <stdio.h>
#include <stdlib.h>
#define ARRAYSIZE 15000
#define N_VYSTUPU "obezita.txt"
#define NAZEV_VSTUP "vysky_vahy.txt"


typedef struct {
    int vyska;
    int vaha;
} LIDE;

float vyska_v_M(LIDE lide) {
    return lide.vyska / 100.0;
}

float BMI(LIDE lide) {
    return (float) lide.vaha / (vyska_v_M(lide) * vyska_v_M(lide));
}


void h(FILE* sz){
    fprintf(sz,"========================================\n");
    fprintf(sz,"        EVIDENCE OBEZITY\n");
    fprintf(sz,"========================================\n");
    fprintf(sz," poradi | vyska(cm) | vaha(kg) |  BMI\n");
    fprintf(sz,"----------------------------------------\n");
}

void serazeni(LIDE lide[ARRAYSIZE], int pocet ){
    for (int i = 0; i < pocet - 1 ; ++i) {
        int serazeni = 0;
        for (int j = 0; j < pocet - 1 - i; ++j) {
            if (BMI(lide[j]) < BMI(lide[j + 1])) {
                LIDE clovek = lide[j];
                lide[j] = lide[j + 1];
                lide[j +1] = clovek;
                serazeni = 1;
            }
        }
        if (serazeni == 0) {
            break;
        }
    }
}

int nacteni(LIDE lide[ARRAYSIZE]) {
    int i = 0;
    FILE *soubor;
    soubor = fopen(NAZEV_VSTUP, "r");
    if (soubor == NULL) {
        printf("Soubor %s nebyl vubec otevren \n",NAZEV_VSTUP);
        return EXIT_FAILURE;
    }
    while (i < ARRAYSIZE && fscanf(soubor, "%d %d", &lide[i].vyska, &lide[i].vaha) != EOF) {
        i++;
    }
    if (fclose(soubor) == EOF) {
        printf("Chyba pri zavirani souboru %s \n", NAZEV_VSTUP);
        return EXIT_FAILURE;
    }
    return i;
}

void radek(LIDE lide, int order, FILE* file) {
    fprintf(file, "%6d. | %9d | %8d | %6.2f \n", order+1,lide.vyska, lide.vaha, BMI(lide));
}

void vypis(LIDE lide[ARRAYSIZE], int pocet) {
    h(stdout);
    int poradiSoubor = 0;
    FILE *soubor = fopen(N_VYSTUPU, "w");
    if (soubor == NULL ) {
        printf("Soubor %s nebyl vubec otevren \n",N_VYSTUPU);
    }
    h(soubor);
    for (int i = 0; i < pocet; ++i) {
        radek(lide[i], i, stdout);
        if (BMI(lide[i]) > 30){
           radek(lide[i], poradiSoubor, soubor);
            poradiSoubor++;
        }
    }
}


int main(void) {
    LIDE lide[ARRAYSIZE];
    int i = nacteni(lide);
    serazeni(lide, i);
    vypis(lide, i);


    //ILE * sz;
    //sz = fopen("obezita.txt", "w");

    return 0;
}
