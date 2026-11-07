#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define VSTUPNI_SOUBOR "cisla.txt"
#define VYSTUPNI_SOUBOR "output.txt"

typedef struct
{
    int prvni;
    int druha;
} cisloPar;

void overeniOtevreniSouboru(FILE *soubor) {
    if (soubor == NULL) {
        printf("Soubor se neotevrel.\n");
        printf("Program konci.\n");
        exit(EXIT_FAILURE);
    }
}

void overeniUzavreniSouboru(FILE *soubor) {
    if (fclose(soubor) != 0)
    {
        printf("Soubor se nezavrel.\n");
        printf("Program konci.\n");
        exit(EXIT_FAILURE);
    }
}

int metry_vypocet(int a, int b) {
    a = abs(a);
    b = abs(b);

    if (a == 0 || b == 0) {
        return 0;
    }

    int max = (a > b) ? a : b;
    int krokuj = max;

    while (true) {
        if (max % a == 0 && max % b == 0) {
            break;
        }
        max += krokuj;
    }

    return max;
}

int sekundy_vypocet(int a, int b) {
    a = abs(a);
    b = abs(b);

    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void vypis_obrazovka(FILE *file) {
    fprintf(file, "=========================================\n");
    fprintf(file, "| Nejmensi spolecny nasobek a nejvetsi spolecny delitel |\n");
    fprintf(file, "=========================================\n");
    fprintf(file, "| Poradi | Cislo A | Cislo B | NSN | NSD |\n");
    fprintf(file, "=========================================\n");
}

void vypis_soubor(FILE *file) {
    fprintf(file, "=========================================\n");
    fprintf(file, "| Prehled hodnot se NSD > 1 |\n");
    fprintf(file, "=========================================\n");
    fprintf(file, "| Poradi | Cislo A | Cislo B | NSN | NSD |\n");
    fprintf(file, "=========================================\n");
}

void vypisZaveruNaObrazovku(FILE *file) {
    fprintf(file, "=========================================\n\n");
}

void vypisZaverDoSouboru(FILE *file) {
    fprintf(file, "=========================================\n\n");
}

float prumer_vypocet(float soucet, float pocet) {
    if (pocet == 0.0f) {
        return 0.0f;
    }
    return soucet / pocet;
}

int main() {
    FILE *souborCteni = fopen(VSTUPNI_SOUBOR, "r");
    overeniOtevreniSouboru(souborCteni);

    FILE *souborZapsat = fopen(VYSTUPNI_SOUBOR, "w");
    overeniOtevreniSouboru(souborZapsat);

    cisloPar zaznam;

    int poradi = 0;
    int poradiSoubor = 0;
    int soucet = 0;
    int soucetSoubor = 0;

    vypis_obrazovka(stdout);
    vypis_soubor(souborZapsat);

    while (fscanf(souborCteni, "%d %d", &zaznam.prvni, &zaznam.druha) == 2)
    {
        poradi++;
        int nsn = metry_vypocet(zaznam.prvni, zaznam.druha);
        int nsd = sekundy_vypocet(zaznam.prvni, zaznam.druha);
        
        printf("| %3d. | %5d | %5d | %5d | %4d |\n", poradi, zaznam.prvni, zaznam.druha, nsn, nsd);

        if (nsd > 1)
        {
            poradiSoubor++;
            fprintf(souborZapsat, "| %3d. | %5d | %5d | %5d | %4d |\n", poradiSoubor, zaznam.prvni, zaznam.druha, nsn, nsd);
            soucetSoubor += zaznam.prvni;
        }
        
        soucet += zaznam.prvni;
    }
    
    vypisZaveruNaObrazovku(stdout);
    vypisZaverDoSouboru(souborZapsat);

    fprintf(stdout, "Prumer prvnich cisel je %.2f. Soubor obsahuje %d radku.\n", prumer_vypocet(soucet, poradi), poradi);
    fprintf(souborZapsat, "Prumer prvnich cisel v zapsanych radcich je %.2f. Soubor obsahuje %d radku.\n", prumer_vypocet(soucetSoubor, poradiSoubor), poradiSoubor);

    overeniUzavreniSouboru(souborCteni);
    overeniUzavreniSouboru(souborZapsat);

    return 0;
}

