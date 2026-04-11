# IR Remote LCD Text Editor

An Arduino-based text editor that lets you type on a 16x2 LCD screen using an IR remote control. Each button on the remote cycles through a set of letters, similar to old phone T9 input.

## How It Works

- Press a button on the remote to cycle through its assigned letters (e.g. a → b → c → a)
- The LCD updates in real time with each press
- Repeat signals from holding a button are handled correctly

## Hardware Required

- Arduino (Uno or compatible)
- 16x2 LCD display
- IR receiver module (e.g. VS1838B)
- IR remote control
- Jumper wires
- Ideally a breadboard but whatever floats your boat

## Wiring

### LCD
| LCD Pin | Arduino Pin |
|---------|-------------|
| RS      | 7           |
| RW      | 8           |
| D4      | 9           |
| D5      | 10          |
| D6      | 11          |
| D7      | 12          |
| VSS     | GND         |
| VDD     | 5V          |
| V0      | Potentiometer (contrast) |
| A       | 5V (backlight) |
| K       | GND (backlight) |

### IR Receiver
| IR Receiver Pin | Arduino Pin |
|-----------------|-------------|
| Signal          | 6           |
| VCC             | 5V          |
| GND             | GND         |

## Setup

1. Install the following libraries via the Arduino Library Manager: (libraries also provided as separate files)
   - `IRremote` by shirriff
   - `LiquidCrystal` (built-in)

2. **Find your remote's HEX codes** — uncomment `translateRemote()` in the code and open the Serial Monitor at 9600 baud. Press a button and note the HEX value printed.

3. Update the `BTN_ONE` define at the top of the sketch with your remote's HEX code:
```cpp
#define BTN_ONE 0xF30CFF00  // replace with your remote's HEX
```

4. Upload the sketch and tap on the first/whatever relevant hex you defined on the top.

## Notes

- The contrast of the LCD can be adjusted using a potentiometer on the V0 pin
- Currently supports one character position — expanding to full 16-character input is a planned feature
- [RELEVANT TO STEP 2 IN SETUP] You'll have to comment out the translateRemote in two instances, when defining it at the top ie. void translateRemote(x) {y} and at translateRemote(x); //x is just a placehodler for whatever text is within the brackets, you should get the gist of what I mean//
- Also I got AI to write the readme, This commit is just making changes to whatever is wrong/hallucinated
