#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define VSTUPNI_SOUBOR "casy.txt"
#define VYSTUPNI_SOUBOR "odpoledne.txt"

typedef struct
{
    int hodiny;
    int minuty;
    int sekundy;
} casTrojice;

FILE *otevriSouborAKontroluj(const char *nazevSouboru, const char *rezim)
{
    FILE *soubor = fopen(nazevSouboru, rezim);

    if (soubor == NULL)
    {
        printf("Soubor '%s' se nepodarilo otevrit.\n", nazevSouboru);
        printf("Program bude ukoncen.\n");
        exit(EXIT_FAILURE);
    }

    return soubor;
}

void zavriSouborAKontroluj(FILE *soubor)
{
    if (fclose(soubor) != 0)
    {
        printf("Soubor se nepodarilo zavrit.\n");
        printf("Program bude ukoncen.\n");
        exit(EXIT_FAILURE);
    }
}

int sekundyOdPulnoci(casTrojice cas)
{
    return cas.hodiny * 3600 + cas.minuty * 60 + cas.sekundy;
}

int angloHodina(int evropskaHodina)
{
    if (evropskaHodina == 0)
    {
        return 12;
    }
    if (evropskaHodina > 12)
    {
        return evropskaHodina - 12;
    }

    return evropskaHodina;
}

bool jePlatnyCas(casTrojice cas)
{
    return cas.hodiny >= 0 && cas.hodiny <= 23 &&
           cas.minuty >= 0 && cas.minuty <= 59 &&
           cas.sekundy >= 0 && cas.sekundy <= 59;
}

void vypisRadekCasu(FILE *soubor, int poradi, casTrojice cas, int sekundyOdPulnoci, int angloHodina, const char *pripona)
{
    fprintf(soubor,
            "| %2d | %02d:%02d:%02d   | %7d   | %02d:%02d:%02d %s    |\n",
            poradi,
            cas.hodiny,
            cas.minuty,
            cas.sekundy,
            sekundyOdPulnoci,
            angloHodina,
            cas.minuty,
            cas.sekundy,
            pripona);
}

int main()
{
    FILE *souborCteni = otevriSouborAKontroluj(VSTUPNI_SOUBOR, "r");
    FILE *souborZapis = otevriSouborAKontroluj(VYSTUPNI_SOUBOR, "w");

    casTrojice cas;
    int poradi = 1;
    int pocetZapsanych = 0;

    fprintf(souborZapis, "+------+------------+-----------+----------------+\n");
    fprintf(souborZapis, "|Poradi| 24h cas    | Sekundy   | 12h cas        |\n");
    fprintf(souborZapis, "+------+------------+-----------+----------------+\n");

    while (fscanf(souborCteni, "%d %d %d", &cas.hodiny, &cas.minuty, &cas.sekundy) == 3)
    {
        if (!jePlatnyCas(cas))
        {
            printf("%d) Neplatny cas: %02d:%02d:%02d\n", poradi, cas.hodiny, cas.minuty, cas.sekundy);
            poradi++;
            continue;
        }

        int sekundy = sekundyOdPulnoci(cas);
        int anglo = angloHodina(cas.hodiny);
        bool jePM = cas.hodiny >= 12;
        const char *pripona = jePM ? "PM" : "AM";

        if (jePM)
        {
            pocetZapsanych++;
            vypisRadekCasu(souborZapis, pocetZapsanych, cas, sekundy, anglo, pripona);
        }

        vypisRadekCasu(stdout, poradi, cas, sekundy, anglo, pripona);
        poradi++;
    }

    fprintf(souborZapis, "+------+------------+-----------+----------------+\n");
    fprintf(souborZapis, "Pocet zapsanych udaju: %d\n", pocetZapsanych);

    zavriSouborAKontroluj(souborCteni);
    zavriSouborAKontroluj(souborZapis);

    return EXIT_SUCCESS;
}