# PRP - Praktická prověřovací práce

Tento projekt obsahuje 5 řešených úloh z předmětu PRP (Praktická prověřovací práce).

## Struktura projektu

```
PRP/
├── VZOR/          # Vzorové příklady
│   ├── BMI/
│   ├── mocniny/
│   ├── parkoviste/
│   └── pole/
├── ZADANI/         # Zadání jednotlivých úloh
│   ├── praktickaProverkaZadaniA/
│   ├── praktickaProverkaZadaniB/
│   ├── praktickaProverkaZadaniC/
│   ├── praktickaProverkaZadaniD/
│   └── praktickaProverkaZadaniE/
└── VYSLEDEK/       # Řešení úloh
    ├── LCM_GCD/
    ├── DistanceSpeedConverter/
    ├── Parking/
    ├── TrackTimeSpeed/
    └── TimeConversion/
```

## Popis úloh

### 1. LCM_GCD (Nejmenší společný násobek a největší společný dělitel)
**Zadání:** Úloha A - výpočet NSN a NSD ze dvojice čísel

**Vstup:** `cisla.txt` - dvojice čísel (a b)

**Výstup:** `vysledky.txt` - tabulka s NSN a NSD pro každou dvojici

**Algoritmus:**
- NSD - Euklidův algoritmus (postupné dělení)
- NSN - hledání nejmenšího společného násobku

---

### 2. DistanceSpeedConverter (Převodník vzdálenosti a rychlosti)
**Zadání:** Úloha B - převod rychlosti a vzdálenosti, výpočet času

**Vstup:** `cisla.txt` - formát: rychlost jednotka_rychlosti vzdálenost jednotka_vzdalenosti

**Výstup:** `prevody.txt` - tabulka s přepočtenými hodnotami

**Jednotky:**
- Rychlost: 1=km/h, 2=m/s, 3=cm/s
- Vzdálenost: 1=km, 2=m, 3=cm

---

### 3. Parking (Výpočet parkovného)
**Zadání:** Úloha C - výpočet doby parkování a poplatků

**Vstup:** `cisla.txt` - formát: hodiny1 minuty1 sekundy1 hodiny2 minuty2 sekundy2 (čas vjezdu a výjezdu)

**Výstup:** `prevody.txt` - seznam vozidel s platbami

**Pravidla:**
- První 2 hodiny zdarma
- Každá další započatá hodina = 20 Kč

---

### 4. TrackTimeSpeed (Dráha, čas, rychlost)
**Zadání:** Úloha D - výpočet času z dráhy a rychlosti

**Vstup:** `cisla.txt` - formát: rychlost jednotka_rychlosti vzdálenost jednotka_vzdalenosti

**Výstup:** `prevody.txt` - tabulka s vypočítaným časem

**Vzorec:** t = s / v (čas = dráha / rychlost)

---

### 5. TimeConversion (Převod času)
**Zadání:** Úloha E - převod z 24hodinového do 12hodinového formátu

**Vstup:** `casy.txt` - formát: hodiny minuty sekundy

**Výstup:** `odpoledne.txt` - pouze odpolední časy (12:00-23:59) převedené do 12hodinového formátu

**Formát výstupu:**
- 24hodinový čas
- Sekundy od půlnoci
- 12hodinový čas s příponou AM/PM

---

## Jak spustit program

### Kompilace (GCC)
```bash
gcc -o program main.c
```

### Spuštění
```bash
./program
```

### Příklad pro LCM_GCD
```bash
cd PRP/VYSLEDEK/LCM_GCD
gcc -o main main.c
./main
```

