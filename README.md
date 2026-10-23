# Restaurant Management System

A console-based restaurant ordering system written in C++.

## Features

- Browse menu items by category.
- Add items to an order and change their quantities.
- Pay using cash or a simulated card payment.
- View a receipt after successful payment.

The Admin option is a placeholder and is not implemented yet.

> **Note:** Card payment is a simulation only. No card numbers or payment details are stored anywhere.

## Requirements

- CMake 3.16 or later.
- A C++17 compiler.

## Build and Run on macOS or Linux

Open a terminal in the project folder and run:

```bash
cmake -S . -B build
cmake --build build
./build/RestaurantSystem
```

> **Note:** To exit at any input prompt, press Ctrl+D.

## Build and Run on Windows

Open a terminal in the project folder and run:

```bat
cmake -S . -B build
cmake --build build
.\build\Debug\RestaurantSystem.exe
```

> **Note:** To exit at any input prompt, press Ctrl+Z then Enter.
