#include <LiquidCrystal.h>

#define rs 7
#define rw 8
#define d4 9
#define d5 10
#define d6 11
#define d7 12

String userInput = "BROtato Chip";
int userInputLength = userInput.length();
int pageOne[16] = {0};
int pageTwo[16] = {0};
int pageThree[16] = {0};

LiquidCrystal lcd(rs, rw, d4, d5, d6, d7);
void setup() {
  lcd.begin(16, 2);
  lcd.print(userInput);
  lcd.setCursor(0, 1);
  lcd.print("input Length: ");
  lcd.print(userInputLength);
}

void loop() {

}
