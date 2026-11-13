#include <stdio.h>
#include <stdlib.h>

#define VSTUPNI_SOUBOR "casy.txt"
#define VYSTUPNI_SOUBOR "platby.txt"
#define CENA_ZA_HODINU 20
#define LIMIT_ZDARMA_HOD 2

typedef struct {
    int h1;
    int m1;
    int s1;
    int h2;
    int m2;
    int s2;
} ParkovaciData;

static void overitSoubor(FILE *f, const char *nazev) {
    if (!f) {
        printf("[CHYBA] - Soubor %s se nepodarilo otevrit.\n", nazev);
        printf("[INFO] - Ukoncuji program.\n");
        exit(EXIT_FAILURE);
    }
}

static void vytisknoutHlavickuKonzole(FILE *soubor) {
    fprintf(soubor, "P A R K O V I S T E\n");
    fprintf(soubor, "--------------------------------------------------------\n");
    fprintf(soubor, "%-6s  %-8s  %-8s  %-7s  %-8s\n", "poradi", "cas", "cas", "doba", "parkovani");
    fprintf(soubor, "%-6s  %-8s  %-8s  %-7s  %-8s\n", "", "vjezdu", "vyjezdu", "sekundy", "cas");
    fprintf(soubor, "--------------------------------------------------------\n");
}

static void vytisknoutHlavickuSouboru(FILE *soubor) {
    fprintf(soubor, "Parkoviste - P L A T B Y\n");
    fprintf(soubor, "--------------------------------------------\n");
    fprintf(soubor, "pocet parkovani zdarma             : %d h\n", LIMIT_ZDARMA_HOD);
    fprintf(soubor, "hodinova sazba po prekroceni limitu  : %d Kc\n", CENA_ZA_HODINU);
    fprintf(soubor, "-----------------------------------------------------------------------\n");
    fprintf(soubor, "poradi  cas vjezdu  cas vyjezdu  doba parkovani      nad limit    platba\n");
    fprintf(soubor, "-----------------------------------------------------------------------\n");
}

int main(void) {
    FILE *in = fopen(VSTUPNI_SOUBOR, "r");
    FILE *out = fopen(VYSTUPNI_SOUBOR, "w");

    overitSoubor(in, VSTUPNI_SOUBOR);
    overitSoubor(out, VYSTUPNI_SOUBOR);

    const int limitSekund = LIMIT_ZDARMA_HOD * 3600;
    int idKonzole = 0;
    int idSoubor = 0;
    ParkovaciData d;

    vytisknoutHlavickuKonzole(stdout);
    vytisknoutHlavickuSouboru(out);

    while (fscanf(in, "%d %d %d %d %d %d", &d.h1, &d.m1, &d.s1, &d.h2, &d.m2, &d.s2) == 6) {
        idKonzole++;

        int startSec = d.h1 * 3600 + d.m1 * 60 + d.s1;
        int konecSec = d.h2 * 3600 + d.m2 * 60 + d.s2;
        int rozdilSec = konecSec - startSec;

        int trvaniH = rozdilSec / 3600;
        int trvaniM = (rozdilSec % 3600) / 60;
        int trvaniS = rozdilSec % 60;

        fprintf(stdout, "%3d.    %02d:%02d:%02d  %02d:%02d:%02d  %7d  %02d:%02d:%02d\n",
                idKonzole, d.h1, d.m1, d.s1, d.h2, d.m2, d.s2,
                rozdilSec, trvaniH, trvaniM, trvaniS);

        if (rozdilSec > limitSekund) {
            idSoubor++;
            int navicSec = rozdilSec - limitSekund;
            int uctovaneHodiny = (navicSec + 3599) / 3600;
            int cena = uctovaneHodiny * CENA_ZA_HODINU;

            fprintf(out, "%3d.      %02d:%02d:%02d     %02d:%02d:%02d        %02d:%02d:%02d       %02d:%02d:%02d    %3d Kc\n",
                    idSoubor, d.h1, d.m1, d.s1, d.h2, d.m2, d.s2,
                    trvaniH, trvaniM, trvaniS,
                    navicSec / 3600, (navicSec % 3600) / 60, navicSec % 60,
                    cena);
        }
    }

    fprintf(stdout, "--------------------------------------------------------\n\n");
    printf("Byl vytvoren soubor %s.\n\n\n", VYSTUPNI_SOUBOR);

    if (fclose(in) != 0 || fclose(out) != 0) {
        printf("[CHYBA] - Chyba pri uzavirani souboru.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
