#include <IRremote.hpp>
#include <LiquidCrystal.h>

// pin definition
#define rs 7
#define rw 8
#define d4 9
#define d5 10
#define d6 11
#define d7 12
#define receiverPin 6
#define BTN_ONE 0xF30CFF00

// global variables
char pageOne[16];
int pageTwo[16] = {0};
int pageThree[16] = {0};
int typeCounter = 0;
uint32_t last_decodedRawData = 0;

// hardware parameters
LiquidCrystal lcd(rs, rw, d4, d5, d6, d7);
IRrecv irrec(receiverPin);

// loop back to the first letter!
void resetTypeCounter() {
  if (typeCounter == 3) {
    typeCounter = 0;
  }
}

// button One assignment checker, might have to optimise or hard code it! (the other buttons)
void remoteAssignOne(uint32_t previous_data) {
  if (previous_data == BTN_ONE) {
    typeCounter ++;
      if (typeCounter == 1) {
        pageOne[0] = 'a';
  } else if (typeCounter == 2) {
    pageOne[0] = 'b';
  } else if (typeCounter == 3) {
    pageOne[0] = 'c';
  }
  }
}

// uncomment out this code to actually check your hex's and replace them in the define section...
// void translateRemote() {
//   if (irrec.decodedIRData.flags) {
//     Serial.println("irrec.decodedIRdata.flags is true");
//   } else {
//     Serial.println(irrec.decodedIRData.decodedRawData, HEX);
//   }
// }

/*
 apparently repeat signal isnt the same as a signal (hex)
 so just redefine a repeat signal as the same as the hex signal used
 */
void repeatSignal() {
  if(irrec.decodedIRData.flags) {
    irrec.decodedIRData.decodedRawData = last_decodedRawData;
  } else {
    irrec.decodedIRData.decodedRawData = irrec.decodedIRData.decodedRawData;
  }
}

// re-renders the screen upon each click and makes sure that theres spaces lol
void renderScreen() {
  for(int i = 0; i < 16; i++) {
  lcd.setCursor(i, 0);
  lcd.print(pageOne[i]);
  }
}

// starting up the hardware!
void setup() {
  memset(pageOne, ' ', sizeof(pageOne));
  Serial.begin(9600);
  irrec.begin(6);
  lcd.begin(16, 2);
}
// polling system - lf optimisation later on cuz its hardware intensive i believe!
void loop() {
  if(irrec.decode() == true) {
    resetTypeCounter();
    repeatSignal();
    if(irrec.decodedIRData.decodedRawData == BTN_ONE) {
      last_decodedRawData = BTN_ONE;
      remoteAssignOne(last_decodedRawData);
      delay(75);
      irrec.resume();
      renderScreen();
    }
// uncomment the below line and the function above to check ur hex in serial
//    translateRemote();
  }

}
