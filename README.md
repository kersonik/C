# 💻 C Programming — Školní projekty a cvičení

> Kolekce algoritmů, cvičení a ročníkových prověrek v jazyce C vytvořených v rámci výuky programování na SŠPU Opava.

[![Language](https://img.shields.io/badge/Language-C99%20%2F%20C11-00599C?style=for-the-badge&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Compiler](https://img.shields.io/badge/Compiler-GCC%20%7C%20Clang-informational?style=for-the-badge&logo=gnu&logoColor=white)](https://gcc.gnu.org/)
[![School](https://img.shields.io/badge/Škola-SŠPU%20Opava-red?style=for-the-badge)](https://www.sspu-opava.cz/)
[![License](https://img.shields.io/badge/License-MIT-success?style=for-the-badge)](LICENSE)

---

## 📌 Struktura repozitáře

Repozitář je rozdělen na dvě hlavní části: **samostatná cvičení** z průběžné výuky a komplexní modul **OPAKOVANI-PRVAK**, který zachycuje ročníkový praktický test.

---

### 1. Průběžná cvičení a algoritmy (kořenové složky)

Jednotlivé složky obsahují ucelené programy zaměřené na práci se soubory, strukturami, cykly, podmínkami a matematickými algoritmy:

| Složka | Zaměření programu | Klíčové koncepty |
| :--- | :--- | :--- |
| **`BMI`** | Dávkový výpočet indexu tělesné hmotnosti | Načítání ze souboru `vysky_vahy.txt`, zápis do `obezita.txt` |
| **`vypocet-bmi`** | Interaktivní konzolový kalkulátor BMI | Vstup přes `scanf`, větvení podmínek, kategorie WHO |
| **`buffer`** | Čištění a správa vstupního bufferu | Bezpečné načítání znaků, prevence zacyklení vstupu |
| **`draha-rychlost1` / `2`** | Fyzikální kinematické výpočty | Převody jednotek, výpočet dráhy, času a průměrné rychlosti |
| **`mc-stack`** | Minecraft Stack Calculator | Celočíselné dělení a modulo pro přepočet bloků na stacky (64x) |
| **`moc-a-prvo`** | Kombinovaný algoritmus mocnin a prvočísel | Dělitelnost, optimalizované hledání prvočísel |
| **`mocniny`** | Výpočet celočíselných i reálných mocnin | Matematické cykly, práce s akumulátorem |
| **`nsn-nsd`** | Nejméně společný násobek & Největší společný dělitel | Eukleidův algoritmus |
| **`parkoviste`** | Automatizovaný parkovací systém | Struktury `ParkovaciData`, výpočet doby stání a ceníku |
| **`prestupny-rok`** | Gregoriánský kalendář | Logické operátory (`rok % 4 == 0 && (rok % 100 != 0 \|\| rok % 400 == 0)`) |
| **`prevod-cas`** | Formátování časových intervalů | Přepočet celkových sekund na formát `HH:MM:SS` |
| **`prvocisla`** | Síto a test prvočíselnosti | Testování dělitelnosti do odmocniny z čísla |
| **`vypis-ucet`** | Formátovaný bankovní výpis | Tabulkový formátovaný výstup, práce s měnou |
| **`vyska-valce`** | Geometrické výpočty kapalin ve válcích | Výpočet objemu, hladiny a přetečení válcových nádob |

---

### 2. `OPAKOVANI-PRVAK/` (Ročníkový test & AI kontext)

Adresář [`OPAKOVANI-PRVAK/`](OPAKOVANI-PRVAK/) obsahuje kompletní podklady k praktickému souhrnnému testu z 1. ročníku. Slouží jak pro archivaci zadání a studentských řešení, tak jako referenční datová báze:

* **`ZADANI/`**: Oficiální textová zadání testových úloh, specifikace formátu výstupů a testovací vstupní soubory.
* **`VZOR/`**: Vzorová řešení od vyučujícího demonstrující kanonický styl, ošetření chyb a předepsané formátování.
* **`VYSLEDEK/`**: Výsledná odevzdaná řešení a výstupy stažené po testu. Tyto soubory zároveň sloužily jako přesný kontext a trénovací podklad pro AI asistenty, aby modely přesně znaly požadovanou konvenci kódu, struktury funkcí a formátování výstupů pro SŠPU Opava.

---

## 🛠️ Kompilace a spuštění

Všechny programy jsou psány v čistém ANSI C a lze je snadno zkompilovat pomocí GCC nebo Clang s přepínači pro kontrolu chyb:

```bash
# Příklad kompilace libovolného programu:
gcc -Wall -Wextra -std=c99 parkoviste/parkoviste.c -o parkoviste

# Spuštění zkompilovaného programu:
./parkoviste
```

---

## 📄 Licence

Vytvořeno pro studijní a výukové účely na SŠPU Opava.
