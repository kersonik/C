# C Programming — Školní projekty a cvičení

Kolekce algoritmů, cvičení a ročníkových prověrek v jazyce C vytvořených v rámci výuky programování na SŠPU Opava.

## Struktura repozitáře

Repozitář je rozdělen na dvě hlavní části: **samostatná cvičení** z průběžné výuky a souhrnný testovací modul **OPAKOVANI-PRVAK**.

### 1. Průběžná cvičení a algoritmy (kořenové složky)

Jednotlivé složky obsahují ucelené programy zaměřené na práci se soubory, strukturami, cykly, podmínkami a matematickými algoritmy:

| Složka | Zaměření programu | Popis |
| :--- | :--- | :--- |
| **`BMI`** | Dávkový výpočet BMI | Načítání ze souboru `vysky_vahy.txt`, zápis do `obezita.txt` |
| **`vypocet-bmi`** | Konzolový kalkulátor BMI | Interaktivní vstup přes `scanf`, vyhodnocení kategorií WHO |
| **`buffer`** | Práce se vstupním bufferem | Bezpečné načítání znaků, prevence zacyklení vstupu |
| **`draha-rychlost1` / `2`** | Fyzikální kinematické výpočty | Převody jednotek, výpočet dráhy, času a průměrné rychlosti |
| **`mc-stack`** | Minecraft Stack Calculator | Celočíselné dělení a modulo pro přepočet bloků na stacky (64x) |
| **`moc-a-prvo`** | Mocniny a test prvočíselnosti | Dělitelnost, optimalizované hledání prvočísel |
| **`mocniny`** | Výpočet mocnin | Celočíselné i reálné mocniny pomocí cyklů |
| **`nsn-nsd`** | NSN a NSD | Eukleidův algoritmus pro nejmenší násobek a největší dělitel |
| **`parkoviste`** | Výpočet parkovného | Struktura `ParkovaciData`, výpočet doby stání a ceníku |
| **`prestupny-rok`** | Gregoriánský kalendář | Algoritmus ověření přestupného roku |
| **`prevod-cas`** | Formátování času | Přepočet celkových sekund na formát `HH:MM:SS` |
| **`prvocisla`** | Test prvočíselnosti | Testování dělitelnosti do odmocniny z čísla |
| **`vypis-ucet`** | Bankovní výpis | Formátovaný tabulkový výstup z účtu |
| **`vyska-valce`** | Geometrické výpočty kapalin | Výpočet objemu, hladiny a přetečení válcových nádob |

### 2. OPAKOVANI-PRVAK/ (Ročníkový test & AI kontext)

Adresář `OPAKOVANI-PRVAK/` obsahuje kompletní podklady k praktickému souhrnnému testu z 1. ročníku. Slouží jak pro archivaci zadání a studentských řešení, tak jako referenční datová báze:

- **`ZADANI/`**: Oficiální textová zadání testových úloh, specifikace formátu výstupů a testovací vstupní soubory.
- **`VZOR/`**: Vzorová řešení od vyučujícího demonstrující kanonický styl, ošetření chyb a předepsané formátování.
- **`VYSLEDEK/`**: Výsledná odevzdaná řešení a výstupy stažené po testu. Tyto soubory zároveň sloužily jako přesný kontext a trénovací podklad pro AI asistenty, aby modely přesně znaly požadovanou konvenci kódu, struktury funkcí a formátování výstupů pro SŠPU Opava.

## Kompilace a spuštění

Všechny programy lze přeložit pomocí GCC nebo Clang:

```bash
# Kompilace
gcc -Wall -Wextra -std=c99 parkoviste/parkoviste.c -o parkoviste

# Spuštění
./parkoviste
```

## Licence

MIT / Výukové účely SŠPU Opava
