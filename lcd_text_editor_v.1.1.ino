#include <LiquidCrystal.h>

#include <IRremote.hpp>

#define rs 7
#define E 8
#define d4 9
#define d5 10
#define d6 11
#define d7 12
#define receiverPin 6

// you'll want to change these based on the results  from the commented translateRemote function below
#define BTN_ONE 0xF30CFF00
#define BTN_TWO 0xE718FF00
#define BTN_THREE 0xA15EFF00
#define BTN_FOUR 0xF708FF00
#define BTN_FIVE 0xE31CFF00
#define BTN_SIX 0xA55AFF00
#define BTN_SEVEN 0xBD42FF00
#define BTN_EIGHT 0xAD52FF00
#define BTN_NINE 0xB54AFF00

LiquidCrystal lcd(rs, E, d4, d5, d6, d7);
IRrecv irrec(receiverPin);
// global variables
char pageOne[16];
char pageTwo[16];
int pageThree[16] = {0};
int typeCounter = 1;
int curSlot = -1;
int previousCurrentSlot = 0;
int currentDisplayRow = 0;
int userCurrentLine = 0;
uint32_t last_decodedRawData = 0;
uint32_t previousButtonPress;
uint32_t currentData;
unsigned long lastPressTime = 0;
// new tool i learnt -- pointer 
char* activePage;


// button One assignment checker, might have to optimise or hard code it! (the other buttons)
void remoteAssignOne(uint32_t previousData, char* activePage) {
      if (typeCounter == 1) {
        activePage[curSlot] = 'a';
  } else if (typeCounter == 2) {
    activePage[curSlot] = 'b';
  } else if (typeCounter == 3) {
    activePage[curSlot] = 'c';
  }
  typeCounter++;
}

// 2nd button function (proto-typing, just trying to get 2 button functionality before 9 optimisation!!)
void remoteAssignTwo(uint32_t previousData, char* activePage) {
      if (typeCounter == 1) {
        activePage[curSlot] = 'd';
  } else if (typeCounter == 2) {
    activePage[curSlot] = 'e';
  } else if (typeCounter == 3) {
    activePage[curSlot] = 'f';
  }
  typeCounter++;
}

void remoteAssignThree(uint32_t previousData, char* activePage) {
      if (typeCounter == 1) {
        activePage[curSlot] = 'g';
  } else if (typeCounter == 2) {
    activePage[curSlot] = 'h';
  } else if (typeCounter == 3) {
    activePage[curSlot] = 'i';
  }
  typeCounter++;
}

void remoteAssignFour(uint32_t previousData, char* activePage) {
      if (typeCounter == 1) {
        activePage[curSlot] = 'j';
  } else if (typeCounter == 2) {
    activePage[curSlot] = 'k';
  } else if (typeCounter == 3) {
    activePage[curSlot] = 'l';
  }
  typeCounter++;
}

void remoteAssignFive(uint32_t previousData, char* activePage) {
      if (typeCounter == 1) {
        activePage[curSlot] = 'm';
  } else if (typeCounter == 2) {
    activePage[curSlot] = 'n';
  } else if (typeCounter == 3) {
    activePage[curSlot] = 'o';
  }
  typeCounter++;
}

void remoteAssignSix(uint32_t previousData, char* activePage) {
      if (typeCounter == 1) {
        activePage[curSlot] = 'p';
  } else if (typeCounter == 2) {
    activePage[curSlot] = 'q';
  } else if (typeCounter == 3) {
    activePage[curSlot] = 'r';
  }
  typeCounter++;
}

void remoteAssignSeven(uint32_t previousData, char* activePage) {
      if (typeCounter == 1) {
        activePage[curSlot] = 's';
  } else if (typeCounter == 2) {
    activePage[curSlot] = 't';
  } else if (typeCounter == 3) {
    activePage[curSlot] = 'u';
  }
  typeCounter++;
}

void remoteAssignEight(uint32_t previousData, char* activePage) {
      if (typeCounter == 1) {
        activePage[curSlot] = 'v';
  } else if (typeCounter == 2) {
    activePage[curSlot] = 'w';
  } else if (typeCounter == 3) {
    activePage[curSlot] = 'x';
  }
  typeCounter++;
}

void remoteAssignNine(uint32_t previousData, char* activePage) {
      if (typeCounter == 1) {
        activePage[curSlot] = 'y';
  } else if (typeCounter == 2) {
    activePage[curSlot] = 'z';
  } else if (typeCounter == 3) {
    activePage[curSlot] = ' ';
  }
  typeCounter++;
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
    delay(20);
  } else {
    last_decodedRawData = irrec.decodedIRData.decodedRawData;
  }
}

// re-renders the screen upon each click and makes sure that theres spaces lol
void renderScreen(int currentLine) {
  for(int i = 0; i < 16; i++) {
  lcd.setCursor(i, currentLine);
  if (currentLine == 0) {
    lcd.print(pageOne[i]);
  } else if (currentLine == 1) {
    lcd.print(pageTwo[i]);
  }
  }
}

// starting up the hardware!
void setup() {
  memset(pageOne, ' ', sizeof(pageOne));
  memset(pageTwo, ' ', sizeof(pageTwo));
  Serial.begin(9600);
  irrec.begin(6);
  lcd.begin(16, 2);
      lastPressTime = millis();
}

// polling system - lf optimisation later on cuz its hardware intensive i believe!
void loop() {
  if(millis() - lastPressTime < 150) {
    return;
  }
  if(irrec.decode() == true) {
    currentData = irrec.decodedIRData.decodedRawData;
    previousButtonPress = last_decodedRawData;
    unsigned long elapsedTime = millis() - lastPressTime;
    if (irrec.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT) {
      irrec.resume();
      return;
    }
    if (previousButtonPress != currentData || elapsedTime >= 2000) {
      curSlot++;
      typeCounter = 1;
      if (curSlot > 15) {
        curSlot = 0;
        if (userCurrentLine == 0) {
          userCurrentLine = 1;
        } else if (userCurrentLine == 1) {
          userCurrentLine = 0;
        }
      }
      lastPressTime = millis();
    }
    if (userCurrentLine == 0) {
      activePage = pageOne;
    } else if (userCurrentLine == 1) {
      activePage = pageTwo;
    }

    repeatSignal();
    if (currentData == BTN_ONE) {
      remoteAssignOne(last_decodedRawData, activePage);
      renderScreen(userCurrentLine);
      delay(75);
      if (typeCounter == 4) {
        typeCounter = 1;
      }
    }
    if (currentData == BTN_TWO) {
      remoteAssignTwo(last_decodedRawData, activePage);
      renderScreen(userCurrentLine);
      delay(75);
      if (typeCounter == 4) {
        typeCounter = 1;
      }
    }

    if (currentData == BTN_THREE) {
      remoteAssignThree(last_decodedRawData, activePage);
      renderScreen(userCurrentLine);
      delay(75);
      if (typeCounter == 4) {
        typeCounter = 1;
      }
    }
    if (currentData == BTN_FOUR) {
      remoteAssignFour(last_decodedRawData, activePage);
      renderScreen(userCurrentLine);
      delay(75);
      if (typeCounter == 4) {
        typeCounter = 1;
      }
    }
    if (currentData == BTN_FIVE) {
      remoteAssignFive(last_decodedRawData, activePage);
      renderScreen(userCurrentLine);
      delay(75);
      if (typeCounter == 4) {
        typeCounter = 1;
      }
    }
    if (currentData == BTN_SIX) {
      remoteAssignSix(last_decodedRawData, activePage);
      renderScreen(userCurrentLine);
      delay(75);
      if (typeCounter == 4) {
        typeCounter = 1;
      }
    }
    if (currentData == BTN_SEVEN) {
      remoteAssignSeven(last_decodedRawData, activePage);
      renderScreen(userCurrentLine);
      delay(75);
      if (typeCounter == 4) {
        typeCounter = 1;
      }
    }
    if (currentData == BTN_EIGHT) {
      remoteAssignEight(last_decodedRawData, activePage);
      renderScreen(userCurrentLine);
      delay(75);
      if (typeCounter == 4) {
        typeCounter = 1;
      }
    }
    if (currentData == BTN_NINE) {
      remoteAssignNine(last_decodedRawData, activePage);
      renderScreen(userCurrentLine);
      delay(75);
      if (typeCounter == 4) {
        typeCounter = 1;
      }
    }

    // old code (for reference )
    //   if (irrec.decodedIRData.decodedRawData == BTN_ONE) {
    //   remoteAssignOne(last_decodedRawData);
    //   renderScreen();
    //   delay(75);
    //   if (typeCounter == 4) {
    //   typeCounter = 1;
    // }
    // } else if(irrec.decodedIRData.decodedRawData == BTN_TWO) {
    //   remoteAssignTwo(last_decodedRawData);
    //   renderScreen(); 
    //   delay(75);
    //   if (typeCounter == 4) {
    //   typeCounter = 1;
    // }
    // }
    lastPressTime = millis();
    irrec.resume();
  }
}
