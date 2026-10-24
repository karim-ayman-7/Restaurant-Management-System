# Restaurant Management System

A console-based restaurant management system written in C++.

## Features

### Customer
- Browse menu items by category.
- Add items to an order and change their quantities.
- Confirm the order and send it to the cashier.

### Cashier
- View pending orders and process payments.
- Accept cash payments and calculate change.
- Accept simulated card payments.
- View completed orders and payment summary.

### Admin
- Manage menu items and their categories. Categories are created when adding an item and changed while editing it.
- Remove menu items.
- View order history and sales quantities and revenue per item, with each item's category.

> **Note:** Admin access requires a password. The default password is `admin123` and is hardcoded in the source code.

> **Note:** Card payment is a simulation only. No card numbers or payment details are stored anywhere.

## Data Storage

All data is stored in plain text files under the `data/` folder using `#` as a delimiter. The folder is created automatically on first run.

- `menu.txt` — menu items.
- `menu.txt.nextid` — next menu item ID, kept separately so deleting an item does not reuse its ID after restart.
- `pending_orders.txt` — orders waiting for payment.
- `order_history.txt` — completed orders.

## Requirements

- CMake 3.16 or later.
- A C++17 compiler.

To install CMake on macOS:
```bash
brew install cmake
```

For Windows, download from [cmake.org](https://cmake.org).

## Build and Run on macOS or Linux

```bash
cmake -S . -B build
cmake --build build
./build/RestaurantSystem
```

> **Note:** To exit at any input prompt, press Ctrl+D.

Alternatively, without CMake:
```bash
clang++ -std=c++17 src/*.cpp -o RestaurantSystem
./RestaurantSystem
```

## Build and Run on Windows

```bat
cmake -S . -B build
cmake --build build --config Debug
.\build\Debug\RestaurantSystem.exe
```

> **Note:** The executable path may differ if you are using Ninja or MinGW. In that case, look for `RestaurantSystem.exe` directly under `build/`.

> **Note:** To exit at any input prompt, press Ctrl+Z then Enter.

Alternatively, without CMake:
```bat
g++ -std=c++17 src/*.cpp -o RestaurantSystem.exe
.\RestaurantSystem.exe
```
