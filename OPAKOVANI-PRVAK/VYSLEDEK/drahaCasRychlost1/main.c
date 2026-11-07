#include <stdio.h>
#include <stdlib.h>

#define CTENI_SOUBOR "cisla.txt"
#define ZAPIS_SOUBOR "output.txt"

typedef struct
{
    int vzdalenost;
    int cas;
} vzdalenost_Cas;

typedef struct
{
    int minuty;
    int sekundy;
} minuty_Sekundy;

void Otevreni_kontrola(FILE *soubor)
{
    if (soubor == NULL)
    {
        printf("Soubor se neotevrel.\n");
        printf("Ukoncuji program.\n");
        exit(EXIT_FAILURE);
    }
}

void Zavreni_kontrola(FILE *soubor)
{
    if (fclose(soubor) != 0)
    {
        printf("Soubor se nezavrel.\n");
        printf("Ukoncuji program.\n");
        exit(EXIT_FAILURE);
    }
}

void tisk_Hlavicka(FILE *soubor)
{
    fprintf(soubor, "======Tabulka vzdalenosti casu a rychlosti======\n");
    fprintf(soubor, "=============================================\n");
    fprintf(soubor, "|--Poradi--|--Vzdalenost--|--Cas--|---Rychlost---|\n");
    fprintf(soubor, "=============================================\n");
}

void tisk_Hlavicka_Soubor(FILE *soubor)
{
    fprintf(soubor, "=========Tabulka vzdalenosti, casu a rychlostiMs========\n");
    fprintf(soubor, "=====================================================\n");
    fprintf(soubor, "|--Poradi--|--Vzdalenost--|-----Cas----|---Rychlost m/s--|\n");
    fprintf(soubor, "=====================================================\n");
}

void tisk_Paticka(FILE *soubor)
{
    fprintf(soubor, "=============================================\n\n\n");
}

void tisk_Paticka_Soubor(FILE *soubor)
{
    fprintf(soubor, "=====================================================\n\n\n");
}

minuty_Sekundy sekundyNaSlozeny(int sekundy) {
    
    minuty_Sekundy minuty_Sekundy = {sekundy/60, sekundy%60};
    return minuty_Sekundy;
}

float ms(int vzdalenost, int cas) {
    float ms = (float)vzdalenost / (float)cas;
    return ms;
}

float msNaKmh(float ms) {
    float kmh = ms * 3.6;
    return kmh;
}

int main()
{
    FILE *cisla;
    FILE *vysledek;

    cisla = fopen(CTENI_SOUBOR, "r");
    vysledek = fopen(ZAPIS_SOUBOR, "w");

    Otevreni_kontrola(cisla);
    Otevreni_kontrola(vysledek);

    vzdalenost_Cas polozka = {0, 0};
    int poradi = 0;
    int poradi2 = 0;
    int suma = 0;

    tisk_Hlavicka_Soubor(vysledek);
    tisk_Hlavicka(stdout);

    while (fscanf(cisla, "%d %d", &polozka.vzdalenost, &polozka.cas) == 2)
    {
        suma += polozka.vzdalenost;
        poradi++;

        if (polozka.cas <= 0)
        {
            fprintf(stdout, "Cas je %d, rychlost nelze spocitat.\n", polozka.cas);
            continue;
        }

        float rychlostMs = ms(polozka.vzdalenost, polozka.cas);

        if (rychlostMs > 10)
        {
            poradi2++;
            minuty_Sekundy slozenyCas = sekundyNaSlozeny(polozka.cas);
            fprintf(vysledek, "|   %2d.   |  %6d m  | %2d min %2d s | %7.2f m/s  |\n", poradi2, polozka.vzdalenost, slozenyCas.minuty, slozenyCas.sekundy, rychlostMs);
        }

        fprintf(stdout, "|   %3d.   |  %8d m  | %4d s | %6.2f m/s |\n", poradi, polozka.vzdalenost, polozka.cas, rychlostMs);
    }

    tisk_Paticka_Soubor(cisla);
    tisk_Paticka(stdout);

    fprintf(vysledek, "Do souboru %s bylo zapsano %d dvojic cisel.\n", ZAPIS_SOUBOR, poradi2);

    if (poradi > 0)
    {
        fprintf(stdout, "Prumerna vzdalenost je %.2f metru.\n", (float)suma / (float)poradi);
    }
    else
    {
        fprintf(stdout, "Prumerna vzdalenost je 0 metru.\n");
    }

    fprintf(stdout, "Ze souboru %s bylo precteno %d dvojic cisel.\n", CTENI_SOUBOR, poradi);
    fprintf(stdout, "Soubor %s byl vytvoren.\n", ZAPIS_SOUBOR);
    fprintf(stdout, "\n\n\n");

    Zavreni(cisla);
    Zavreni(vysledek);

    return 0;
}
