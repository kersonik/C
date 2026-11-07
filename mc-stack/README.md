# ⛏️ Minecraft Stack Calculator

> A lightweight, fast CLI calculator written in C to instantly convert arbitrary block and item quantities into Minecraft inventory stacks and leftover items.

[![Language](https://img.shields.io/badge/Language-C99-00599C?style=for-the-badge&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Windows%20%7C%20macOS-informational?style=for-the-badge)](https://github.com/kersonik/minecraft-stack)
[![Minecraft](https://img.shields.io/badge/Minecraft-Stack%20Size%2064-green?style=for-the-badge&logo=minecraft&logoColor=white)](https://minecraft.wiki/w/Inventory)
[![License](https://img.shields.io/badge/License-MIT-blue?style=for-the-badge)](LICENSE)

---

## 📌 Overview

In Minecraft, most building blocks and resources stack up to **64 units** per inventory slot. When designing massive builds, calculating materials for redstone contraptions, or preparing chest layouts, figuring out exact inventory slot requirements can be tedious.

`mc-stack` is an efficient command-line utility that computes the exact number of full stacks and leftover items for any given quantity.

```
+-------------------------------------------------------+
|  Total Blocks: 1,500                                  |
|  = 23 full stacks (64x) + 28 remaining loose blocks   |
+-------------------------------------------------------+
```

---

## ✨ Features

- **⚡ Instant Calculations**: Zero overhead, instant execution directly in your terminal.
- **🪶 Zero Dependencies**: Implemented in standard ISO C99 (`stdio.h`).
- **🌐 Cross-Platform**: Compiles seamlessly on Linux, macOS, and Windows.

---

## 🧮 Mathematical Logic

Minecraft items group into standard stacks of size $S = 64$:

$$\text{Stacks} = \left\lfloor \frac{\text{Total Blocks}}{64} \right\rfloor$$

$$\text{Remaining Blocks} = \text{Total Blocks} \pmod{64}$$

---

## 🛠️ Build & Installation

### Prerequisites
- A C compiler (e.g. `gcc`, `clang`, or MSVC).

### Compilation (GCC / Clang)

```bash
# Clone the repository
git clone git@github.com:kersonik/minecraft-stack.git
cd minecraft-stack

# Compile the binary
gcc -O2 main.c -o mc-stack
```

---

## 🚀 Usage

Execute the compiled program from your terminal:

```bash
./mc-stack
```

### Example Interaction

```text
Zadej pocet bloku: 
1500
stacku: 23
zbytek: 28
```

---

## 📂 Project Structure

```
mc-stack/
├── main.c        # Main C source file containing calculation logic
└── README.md     # Project documentation and usage guide
```

---

## 📄 License

This project is licensed under the MIT License - feel free to use and modify it for your Minecraft projects.
