#include <stdio.h>
#include <stdlib.h>

#define VSTUPNI_SOUBOR "cisla.txt"
#define VYSTUPNI_SOUBOR "prevody.txt"

typedef struct
{
    int kilometry;
    int metry;
    int minuty;
    int sekundy;
} vzdalenostCas;

void overeniOtevreniSouboru(FILE *soubor)
{
    if (soubor == NULL)
    {
        printf("Soubor se neotevrel.\n");
        printf("Program konci.\n");
        exit(EXIT_FAILURE);
    }
}

void overeniUzavreniSouboru(FILE *soubor)
{
    if (fclose(soubor) != 0)
    {
        printf("Soubor se nezavrel.\n");
        printf("Program konci.\n");
        exit(EXIT_FAILURE);
    }
}

int metry_vypocet(vzdalenostCas zaznam)
{
    return zaznam.kilometry * 1000 + zaznam.metry;
}

int sekundy_vypocet(vzdalenostCas zaznam)
{
    return zaznam.minuty * 60 + zaznam.sekundy;
}

float rychlostMetrZaSekundu(int metry, int sekundy)
{
    return (float)metry / (float)sekundy;
}

float rychlostKilometruZaHodinu(int metry, int sekundy)
{
    float rychlostMps = rychlostMetrZaSekundu(metry, sekundy);
    return rychlostMps * 3.6f;
}

void vypis_obrazovka(FILE *vystup)
{
    fprintf(vystup, "==============================================================================\n");
    fprintf(vystup, "====================== Vzdalenost, cas a rychlost ==========================\n");
    fprintf(vystup, "==============================================================================\n");
    fprintf(vystup, "|Poradi| Vzdalenost     | Cas          | Rychlost km/h | Rychlost m/s | Metru |\n");
    fprintf(vystup, "==============================================================================\n");
}

void vypisZaveruNaObrazovku(FILE *vystup)
{
    fprintf(vystup, "==============================================================================\n\n");
}

void vypis_soubor(FILE *vystup)
{
    fprintf(vystup, "==============================================================\n");
    fprintf(vystup, "====================== Prevody hodnot =======================\n");
    fprintf(vystup, "==============================================================\n");
    fprintf(vystup, "|Poradi| Metru | Sekundy | Rychlost m/s |\n");
    fprintf(vystup, "==============================================================\n");
}

void vypisZaverDoSouboru(FILE *vystup)
{
    fprintf(vystup, "==============================================================\n\n");
}

int main()
{
    FILE *souborCteni = fopen(VSTUPNI_SOUBOR, "r");
    FILE *souborZapsat = fopen(VYSTUPNI_SOUBOR, "w");

    overeniOtevreniSouboru(souborCteni);
    overeniOtevreniSouboru(souborZapsat);

    vzdalenostCas zaznam;
    int pocetVystupu = 0;
    int poradiVystupu = 0;
    int pocetRadku = 0;
    int celkemMetru = 0;

    vypis_obrazovka(stdout);
    vypis_soubor(souborZapsat);

    while (fscanf(souborCteni, "%d %d %d %d", &zaznam.kilometry, &zaznam.metry, &zaznam.minuty, &zaznam.sekundy) == 4)
    {
        int celkemMetru2 = metry_vypocet(zaznam);
        int celkemSekund = sekundy_vypocet(zaznam);

        pocetRadku++;
        poradiVystupu++;
        celkemMetru += celkemMetru2;

        if (celkemSekund == 0)
        {
            fprintf(stdout, "| %3d | %3d km %4d m | %3d min %2d s |    -          |    -         | %6d |\n",
                    poradiVystupu,
                    zaznam.kilometry,
                    zaznam.metry,
                    zaznam.minuty,
                    zaznam.sekundy,
                    celkemMetru2);
            continue;
        }

        float rychlostMps = rychlostMetrZaSekundu(celkemMetru2, celkemSekund);
        float rychlostKmh = rychlostKilometruZaHodinu(celkemMetru2, celkemSekund);

        fprintf(stdout,
                "| %3d. | %3d km %4d m | %3d min %2d s | %10.2f | %10.2f | %6d |\n",
                poradiVystupu,
                zaznam.kilometry,
                zaznam.metry,
                zaznam.minuty,
                zaznam.sekundy,
                rychlostKmh,
                rychlostMps,
                celkemMetru2);

        if (rychlostKmh > 20.0f)
        {
            pocetVystupu++;
            fprintf(souborZapsat,
                    "| %3d | %6d | %8d | %12.2f |\n",
                    pocetVystupu,
                    celkemMetru2,
                    celkemSekund,
                    rychlostMps);
        }
    }

   
    vypisZaverDoSouboru(souborZapsat);
     vypisZaveruNaObrazovku(stdout);
    if (pocetRadku > 0)
    {
        fprintf(stdout, "Prumerna vzdalenost je %.2f m.\n", (float)celkemMetru / (float)pocetRadku);
    }
    else
    {
        fprintf(stdout, "Prumerna vzdalenost je 0.00 m.\n");
    }

    fprintf(stdout, "Ze souboru %s bylo nacteno %d zaznamu.\n", VSTUPNI_SOUBOR, pocetRadku);
    fprintf(stdout, "Do souboru %s bylo zapsano %d zaznamu.\n", VYSTUPNI_SOUBOR, pocetVystupu);
    fprintf(stdout, "Soubor %s byl vytvoren.\n", VYSTUPNI_SOUBOR);

    overeniUzavreniSouboru(souborCteni);
    overeniUzavreniSouboru(souborZapsat);

    return 0;
}
