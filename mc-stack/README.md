# Minecraft Stack Calculator

Konzolový výpočetní nástroj v jazyce C pro přepočet celkového počtu bloků na herní stacky (po 64 kusech) a zbývající volné kusy.

## Princip výpočtu

Standardní herní stack v Minecraftu pojme 64 kusů:
- `stacky = (pocet - pocet % 64) / 64`
- `zbytek = pocet % 64`

## Kompilace a spuštění

```bash
# Kompilace
gcc -O2 main.c -o mc-stack

# Spuštění
./mc-stack
```

### Příklad

```text
Zadej pocet bloku: 
1500
stacku: 23
zbytek: 28
```

## Licence

MIT
