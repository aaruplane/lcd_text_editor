# 📟 IR Remote LCD Text Editor

An advanced Arduino-based text editor that simulates the classic T9 predictive-style input on a 16x2 LCD. This project has evolved from a single-character prototype to a fully functional, two-line editor with smart timing and memory management.

## ✨ Key Features

- **Full Alphabet Support:** Buttons 1-9 are mapped to 'a-z' and spaces, allowing for complete sentence construction.
- **Dual-Line Navigation:** Automatic cursor wrapping from Line 0 to Line 1 (32 total character slots).
- **Smart T9 Logic:** Uses a 2000ms (2-second) timeout to distinguish between cycling letters on the current slot and advancing to the next position.
- **Memory Optimization:** Implements C++ pointers (`char* activePage`) to dynamically switch between memory buffers for the first and second rows.
- **Robust IR Handling:** Filters out IR repeat flags and uses `millis()` timing to ensure stable input and prevent "ghost" double-types.

## 🛠 Hardware Required

- **Arduino Uno** (or any ATmega328P based board)
- **16x2 LCD Display** (HD44780 compatible)
- **IR Receiver Module** (e.g., VS1838B or TSOP38238)
- **IR Remote Control** (NEC protocol preferred)
- **10k Potentiometer** (for screen contrast)
- **Jumper Wires & Breadboard**

## 🔌 Wiring Diagram

### LCD Display
| LCD Pin | Arduino Pin | Description |
|---------|-------------|-------------|
| **RS**  | 7           | Register Select |
| **E**   | 8           | Enable |
| **D4**  | 9           | Data 4 |
| **D5**  | 10          | Data 5 |
| **D6**  | 11          | Data 6 |
| **D7**  | 12          | Data 7 |
| **VSS** | GND         | Ground |
| **VDD** | 5V          | Power |
| **V0**  | Center Pin  | Potentiometer (Contrast) |

### IR Receiver
| IR Pin | Arduino Pin |
|--------|-------------|
| **Signal** | 6       |
| **VCC**    | 5V      |
| **GND**    | GND     |

## 🚀 Getting Started

1.  **Library Installation:**
    Ensure you have `IRremote` (by Armin Joachimsmeyer) and the built-in `LiquidCrystal` libraries installed in your Arduino IDE.

2.  **Mapping Your Remote:**
    Every remote sends different HEX codes. To configure yours:
    - Uncomment the `translateRemote()` function in the code.
    - Open the **Serial Monitor** at **9600 Baud**.
    - Press buttons 1 through 9.
    - Copy those HEX values into the `#define BTN_X` section at the top of the sketch.

3.  **Typing Logic:**
    - **Cycle:** Tap a button quickly to cycle through its assigned letters (e.g., 'abc').
    - **Lock & Move:** Wait 2 seconds for the character to "lock in," or simply press a different button to move to the next slot immediately.
    - **Newline:** Once you finish the 16th character on the first row, the cursor will automatically jump to the second row.

---

### 📝 Development Note
This project represents a significant refactor from the initial version. By moving away from hard-coded array indices and adopting a pointer-based "active page" system, the code is now more modular and ready for further expansion, such as adding a backspace function or EEPROM storage.
