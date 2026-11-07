#include <stdio.h>

#define SOUBOR_CASY "casy.txt"
#define SOUBOR_VYPIS "platby.txt"
#define HODINY_ZDARMA 2
#define CENA_HODINA 20

typedef struct {
    int hodiny;
    int minuty;
    int sekundy;
} CAS;

typedef struct {
    CAS vjezd;
    CAS vyjezd;
} ZAZNAM;

int prevodNaSekundy(CAS c) {
    return c.hodiny * 3600 + c.minuty * 60 + c.sekundy;
}

CAS prevodNaCas(int sekundy) {
    CAS cas;
    cas.hodiny = sekundy / 3600;
    cas.minuty = (sekundy % 3600) / 60;
    cas.sekundy = sekundy % 60;
    return cas;
}

int platba(CAS cas) {
    if (cas.minuty || cas.sekundy)
        cas.hodiny++;
    return cas.hodiny * CENA_HODINA;
}

void hlavicka() {
    printf("P A R K O V I S TE\n");
    printf("----------------------------------------------\n");
    printf("poradi   cas       cas       doba    parkovani\n");
    printf("         vjezdu    vyjezdu   sekundy       cas\n");
    printf("----------------------------------------------\n");
}

void hlavickaSoubor(FILE *soubor) {
    fprintf(soubor, "Parkoviste- P L A T B Y\n");
    fprintf(soubor, "-----------------------\n");
    fprintf(soubor, "pocet hodin parkovani zdarma        : %d\n", HODINY_ZDARMA);
    fprintf(soubor, "hodinova sazba po prekroceni limitu : %d\n", CENA_HODINA);
    fprintf(soubor, "---------------------------------------------------------------------\n");
    fprintf(soubor, "poradi   cas vjezdu   cas vyjezdu   doba parkovani  nad limit  platba\n");
    fprintf(soubor, "---------------------------------------------------------------------\n");
}

int main(void) {
    ZAZNAM zaznam;
    int doba;
    int poradi = 0;
    int poradiSoubor = 0;
    CAS nadLimit;
    CAS dobaCas;
    FILE *casy = fopen(SOUBOR_CASY, "r");

    if (casy == NULL) {
        printf("Soubor %s se neotevrel spravne.\n", SOUBOR_CASY);
        printf("Program bude nyni ukoncen.\n");
        return 1;
    }
    FILE *platby = fopen(SOUBOR_VYPIS, "w");
    if (platby == NULL) {
        printf("Soubor %s se nevytvoril spravne.\n", SOUBOR_VYPIS);
        printf("Program bude nyni ukoncen.\n");
        fclose(casy);
        return 1;
    }
    hlavicka();
    hlavickaSoubor(platby);
    while (fscanf(casy, "%d %d %d %d %d %d", &zaznam.vjezd.hodiny, &zaznam.vjezd.minuty, &zaznam.vjezd.sekundy,
                  &zaznam.vyjezd.hodiny, &zaznam.vyjezd.minuty, &zaznam.vyjezd.sekundy) == 6) {
        poradi++;
        doba = prevodNaSekundy(zaznam.vyjezd) - prevodNaSekundy(zaznam.vjezd);
        dobaCas = prevodNaCas(doba);
        printf("%5d.   %02d:%02d:%02d  %02d:%02d:%02d %8d  %02d:%02d:%02d\n", poradi,
               zaznam.vjezd.hodiny, zaznam.vjezd.minuty, zaznam.vjezd.sekundy,
               zaznam.vyjezd.hodiny, zaznam.vyjezd.minuty, zaznam.vyjezd.sekundy,
               doba, dobaCas.hodiny, dobaCas.minuty, dobaCas.sekundy);
        if (doba > HODINY_ZDARMA * 3600) {
            poradiSoubor++;
            nadLimit = prevodNaCas(doba - HODINY_ZDARMA * 3600);
            fprintf(platby, "%5d.   %02d:%02d:%02d     %02d:%02d:%02d      %02d:%02d:%02d        %02d:%02d:%02d   %3d Kc\n", poradiSoubor,
                    zaznam.vjezd.hodiny, zaznam.vjezd.minuty, zaznam.vjezd.sekundy,
                    zaznam.vyjezd.hodiny, zaznam.vyjezd.minuty, zaznam.vyjezd.sekundy,
                    dobaCas.hodiny, dobaCas.minuty, dobaCas.sekundy,
                    nadLimit.hodiny, nadLimit.minuty, nadLimit.sekundy, platba(nadLimit));
        }
    }
    printf("----------------------------------------------\n");
    if (fclose(casy) == EOF) {
        printf("Soubor %s nebyl spravne zavren.\n", SOUBOR_CASY);
    }
    if (fclose(platby) == EOF) {
        printf("Soubor %s nebyl spravne zavren.\n", SOUBOR_VYPIS);
    } else {
        printf("Byl vytvoren soubor %s.\n", SOUBOR_VYPIS);
    }

    return 0;
}
