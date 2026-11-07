#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define WRITE_FILE_NAME "vypisUctu.txt"
#define INTEREST_RATE 5.61f
#define TAX_RATE 0.15f
#define YEAR 2023

#define MIN_INITIAL_BALANCE 1000.0f
#define MAX_INITIAL_BALANCE 100000.0f
#define MIN_MONTHLY_DEPOSIT 100.0f
#define MAX_MONTHLY_DEPOSIT 100000.0f

void checkFileOpening(FILE *file, const char *fileName)
{
    if (file == NULL)
    {
        printf("[ERROR] - Soubor %s se nepodarilo otevrit.\n", fileName);
        printf("[INFO] - Ukoncuji program.\n");
        exit(EXIT_FAILURE);
    }
}

void checkFileClosingAndClose(FILE *file, const char *fileName)
{
    if (fclose(file) != 0)
    {
        printf("[ERROR] - Soubor %s se nepodarilo zavrit.\n", fileName);
        printf("[INFO] - Ukoncuji program.\n");
        exit(EXIT_FAILURE);
    }
}

// Funkce pro získání reálného čísla v zadaném intervalu
float getValidFloatInput(const char *prompt, float min, float max)
{
    float value = 0.0f;
    while (1)
    {
        printf("%s od %.0f a %.0f:", prompt, min, max);
        if (scanf("%f", &value) == 1 && value >= min && value <= max)
        {
            return value;
        }
        printf("Chybna hodnota. Zadej znovu.\n");
        while (getchar() != '\n'); // vyčištění vstupního bufferu
    }
}

// Funkce pro zjištění, zda je rok přestupný
bool isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Funkce pro zjištění počtu dní v měsíci
int getDaysInMonth(int month, int year)
{
    switch (month)
    {
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return isLeapYear(year) ? 29 : 28;
        default:
            return 31;
    }
}

int main(void)
{
    // Načtení uživatelských vstupů přes požadovanou funkci
    float initialBalance = getValidFloatInput("Zadej pocatecni stav uctu mezi", MIN_INITIAL_BALANCE, MAX_INITIAL_BALANCE);
    float monthlyDeposit = getValidFloatInput("Zadej pravidelny mesicni vklad mezi", MIN_MONTHLY_DEPOSIT, MAX_MONTHLY_DEPOSIT);

    FILE *writeFile = fopen(WRITE_FILE_NAME, "w");
    checkFileOpening(writeFile, WRITE_FILE_NAME);

    printf("\nByl vytvoren soubor %s.\n", WRITE_FILE_NAME);

    // Hlavička výstupního souboru
    fprintf(writeFile, "Sporici ucet, rocni urokova mira %.2f %%\n", INTEREST_RATE);
    fprintf(writeFile, "Stav uctu na pocatku roku %d je %.2f Kc.\n\n", YEAR, initialBalance);
    fprintf(writeFile, "datum       na pocatku mesice        vklad         urok  dan z uroku(15%%)  na konci mesice\n");

    float currentBalance = initialBalance;

    for (int month = 1; month <= 12; month++)
    {
        int lastDay = getDaysInMonth(month, YEAR);
        float startOfMonthBalance = currentBalance;

        // Úrok z částky na počátku měsíce navýšené o měsíční vklad (měsíční úroková míra = roční / 12)
        float baseAmount = startOfMonthBalance + monthlyDeposit;
        float interest = baseAmount * (INTEREST_RATE / 100.0f) / 12.0f;
        
        // Daň z úroku 15 %
        float tax = interest * TAX_RATE;
        
        // Čistý úrok po zdanění
        float netInterest = interest - tax;

        // Stav účtu na konci měsíce
        float endOfMonthBalance = startOfMonthBalance + monthlyDeposit + netInterest;

        // Zápis řádku do souboru
        fprintf(writeFile, "%2d. %2d.%d %16.2f Kc %10.2f Kc %9.2f Kc %12.2f Kc %13.2f Kc\n",
                lastDay, month, YEAR,
                startOfMonthBalance,
                monthlyDeposit,
                interest,
                tax,
                endOfMonthBalance);

        // Příprava stavu účtu pro další měsíc
        currentBalance = endOfMonthBalance;
    }

    fprintf(writeFile, "--------------------------------------------------------------------------------------\n");
    
    float savedAmount = currentBalance - initialBalance;
    fprintf(writeFile, "Stav na konci roku %d je %.2f Kc. Usetril jsi %.2f Kc.\n", YEAR, currentBalance, savedAmount);

    checkFileClosingAndClose(writeFile, WRITE_FILE_NAME);

    return 0;
}