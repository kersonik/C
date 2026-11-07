#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#define VSTUPNI_SOUBOR "cisla.txt"
#define VYSTUPNI_SOUBOR "output.txt"
#define PI 3.14159265358979323846

void overeniOtevreniSouboru(FILE *soubor) {

    if (soubor == NULL)
    {
        printf("Soubor se neotevrel spravne.\n");
        exit(EXIT_FAILURE);
    }
}

void overeniUzavreniSouboru(FILE *soubor) {
    if (fclose(soubor) != 0)
    {
        printf("Soubor se nezavrel spravne.\n");
        exit(EXIT_FAILURE);
    }
}

float vypocetObjemuValce(int polomer, int vyska) {
    float objemValce = (float)(PI * polomer * polomer * vyska / 1000.0);
    return objemValce;
}

float vyskaHladinyVody(int polomer, int mnozstvi) {
    if (polomer <= 0) {
        return 0.0f;
    }

    float vyskaHladiny = (mnozstvi * 1000.0) / (PI * pow(polomer, 2));
    return vyskaHladiny;
}

void vypis_obrazovka (FILE *soubor) {
    fprintf(soubor, "=========================================================\n");
    fprintf(soubor, "======================Valce==============================\n");
    fprintf(soubor, "=========================================================\n");
    fprintf(soubor, "|-Poradi-|-Polomer-|-Vyska-|--Objem-----|-Mnozstvi vody-|\n");
    fprintf(soubor, "=========================================================\n");
}

void vypisZaveruNaObrazovku (FILE *soubor) {
    fprintf(soubor, "=========================================================\n\n\n");
}

void vypis_soubor (FILE *soubor) {
    fprintf(soubor, "=======================================================================\n");
    fprintf(soubor, "=============================Valce=====================================\n");
    fprintf(soubor, "=======================================================================\n");
    fprintf(soubor, "|-Poradi-|-Polomer-|-Vyska-|---Objem---|-Mnozstvi vody-|-Vyska hladiny-|\n");
    fprintf(soubor, "=======================================================================\n");
}

void vypisZaverDoSouboru (FILE *soubor) {
    fprintf(soubor, "=======================================================================\n\n\n");
}

int main(void)
{
    FILE *souborCteni;
    FILE *souborZapis;

    souborCteni = fopen(VSTUPNI_SOUBOR, "r");
    souborZapis = fopen(VYSTUPNI_SOUBOR, "w");

    overeniOtevreniSouboru(souborCteni);
    overeniOtevreniSouboru(souborZapis);

    int polomer;
    int vyska;
    int mnozstvi;
    int poradi = 0;
    int poradi2 = 0;

    vypis_soubor(souborZapis);
    vypis_obrazovka(stdout);

    while (fscanf(souborCteni,"%d %d %d", &polomer, &vyska, &mnozstvi) == 3)
    {
        poradi++;

        if (polomer <= 0 || vyska <= 0 || mnozstvi < 0)
        {
            fprintf(stdout, "Neplatny vstup na poradi %d (r=%d, h=%d, voda=%d).\n", poradi, polomer, vyska, mnozstvi);
            continue;
        }

        float objemValce = vypocetObjemuValce(polomer, vyska);

        if (objemValce >= mnozstvi)
        {
            poradi2++;

            float vyskaHladiny = vyskaHladinyVody(polomer, mnozstvi);

            fprintf(souborZapis, "| %3d.  | %3d cm |%3d cm |%8.2f dm3|      %3d l      | %7.2f cm  |\n", poradi2, polomer, vyska, objemValce, mnozstvi, vyskaHladiny);
        }
        

        fprintf(stdout, "| %3d.  | %3d cm |%3d cm |%8.2f dm3|      %3d l      |\n", poradi, polomer, vyska, objemValce, mnozstvi);
    }

    vypisZaverDoSouboru(souborZapis);
    vypisZaveruNaObrazovku(stdout);

    fprintf(stdout, "Soubor %s byl vytvoren.\n\n", VYSTUPNI_SOUBOR);

    overeniUzavreniSouboru(souborCteni);
    overeniUzavreniSouboru(souborZapis);

    return 0;
}
