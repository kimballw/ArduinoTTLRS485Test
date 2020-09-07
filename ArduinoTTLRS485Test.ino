#include <SoftwareSerial.h>

/*
 * ArduinoTTLRS485Test
 * by Kimball Willard (kimballw@gloininteractive.com)
 * 
 * Used for testing PIR setup, interfacing with an Electronics Displays Inc.
 * model ED402-117-4D-N1
 * 
 * Expected to be run on and Android UNO
 * Uses 1 Electronics Displays Inc ED402-117-4D-N1
 * Unit should be set to Channel 02
 * TTL to RS-485 adapter should have TX plugged into port 0, 
 *   and RX plugged into port 1 on the Arduino
 */

int COUNTER = 1;

void setup() {
  Serial.begin(9600);
}

void showSingleDigit(int digit) {
  switch (digit) {
    case 0:
      Serial.write(0x30);
      break;
    case 1:
      Serial.write(0x31);
      break;
    case 2:
      Serial.write(0x32);
      break;
    case 3:
      Serial.write(0x33);
      break;
    case 4:
      Serial.write(0x34);
      break;
    case 5:
      Serial.write(0x35);
      break;
    case 6:
      Serial.write(0x36);
      break;
    case 7:
      Serial.write(0x37);
      break;
    case 8:
      Serial.write(0x38);
      break;
    case 9:
      Serial.write(0x39);
      break;
  }
}

void showTens(int digit) {
  if (digit <= 99 && digit >= 90) {
    Serial.write(0x39);
  } else if (digit <= 89 && digit >= 80) {
    Serial.write(0x38);
  } else if (digit <= 79 && digit >= 70) {
    Serial.write(0x37);
  } else if (digit <= 69 && digit >= 60) {
    Serial.write(0x36);
  } else if (digit <= 59 && digit >= 50) {
    Serial.write(0x35);
  } else if (digit <= 49 && digit >= 40) {
    Serial.write(0x34);
  } else if (digit <= 39 && digit >= 30) {
    Serial.write(0x33);
  } else if (digit <= 29 && digit >= 20) {
    Serial.write(0x32);
  } else if (digit <= 19 && digit >= 10) {
    Serial.write(0x31);
  }
}

void showHundreds(int digit) {
  if (digit <= 999 && digit >= 900) {
    Serial.write(0x39);
  } else if (digit <= 899 && digit >= 800) {
    Serial.write(0x38);
  } else if (digit <= 799 && digit >= 700) {
    Serial.write(0x37);
  } else if (digit <= 699 && digit >= 600) {
    Serial.write(0x36);
  } else if (digit <= 599 && digit >= 500) {
    Serial.write(0x35);
  } else if (digit <= 499 && digit >= 400) {
    Serial.write(0x34);
  } else if (digit <= 399 && digit >= 300) {
    Serial.write(0x33);
  } else if (digit <= 299 && digit >= 200) {
    Serial.write(0x32);
  } else if (digit <= 199 && digit >= 100) {
    Serial.write(0x31);
  }
}

void showThousands(int digit) {
  if (digit <= 9999 && digit >= 9000) {
    Serial.write(0x39);
  } else if(digit <= 8999 && digit >= 8000) {
    Serial.write(0x38);
  } else if(digit <= 7999 && digit >= 7000) {
    Serial.write(0x37);
  } else if(digit <= 6999 && digit >= 6000) {
    Serial.write(0x36);
  } else if(digit <= 5999 && digit >= 5000) {
    Serial.write(0x35);
  } else if(digit <= 4999 && digit >= 4000) {
    Serial.write(0x34);
  } else if(digit <= 3999 && digit >= 3000) {
    Serial.write(0x33);
  } else if(digit <= 2999 && digit >= 2000) {
    Serial.write(0x32);
  } else if(digit <= 1999 && digit >= 1000) {
    Serial.write(0x31);
  }
}

void clearScreen() {
  Serial.write(0x20);
  Serial.write(0x20);
  Serial.write(0x20);
  Serial.write(0x20);
}

void numberToHex(int digit) {
  if (digit > 9999) {
    // Number is to high for display
    Serial.write(0x39);
    Serial.write(0x39);
    Serial.write(0x39);
    Serial.write(0x39);
  } else if (digit > 999) {
    //Serial.println("Thousands");
    Serial.println(digit);
    showThousands(digit);
    int hundreds = digit;
    while (hundreds > 999) {
      hundreds = hundreds - 1000;
    }
    Serial.println(hundreds);
    showHundreds(hundreds);
    int tens = hundreds;
    while (tens > 99) {
      tens = tens - 10;
    }
    Serial.println(tens);
    showTens(tens);
    int single = tens;
    while (single > 9) {
      single = single - 10;
    }
    Serial.println(single);
    showSingleDigit(single);
  } else if (digit > 99) {
    //Serial.println("Hundreds");
    Serial.write(0x20);
    Serial.println(digit);
    showHundreds(digit);
    int tens = digit;
    while (tens > 99) {
      tens = tens - 10;
    }
    Serial.println(tens);
    showTens(tens);
    int single = tens;
    while (single > 9) {
      single = single - 10;
    }
    Serial.println(single);
    showSingleDigit(single);
  } else if (digit > 9) {
    //Serial.println("Tens");
    Serial.write(0x20);
    Serial.write(0x20);
    Serial.println(digit);
    showTens(digit);
    int single = digit;
    while (single > 9) {
      single = single - 10;
    }
    Serial.println(single);
    showSingleDigit(single);
  } else {
    //Serial.println("Single");
    Serial.write(0x20);
    Serial.write(0x20);
    Serial.write(0x20);
    Serial.println(digit);
    showSingleDigit(digit);
  }
}

void writeLCDChannel2Header() {
  Serial.write(0x02); // Start of text (ctrl-B)
  Serial.write(0x30); // Tens digit of channel
  Serial.write(0x32); // Singles digit of channel (together, 02)
}
void resetTimer() {
  int timer = 9;
  while (timer >= 0) {
    writeLCDChannel2Header();
    switch (timer) {
      case 0:
        Serial.write(0x30);
        Serial.write(0x30);
        Serial.write(0x30);
        Serial.write(0x30);
        break;
      case 1:
        Serial.write(0x31);
        Serial.write(0x31);
        Serial.write(0x31);
        Serial.write(0x31);
        break;
      case 2:
        Serial.write(0x32);
        Serial.write(0x32);
        Serial.write(0x32);
        Serial.write(0x32);
        break;
      case 3:
        Serial.write(0x33);
        Serial.write(0x33);
        Serial.write(0x33);
        Serial.write(0x33);
        break;
      case 4:
        Serial.write(0x34);
        Serial.write(0x34);
        Serial.write(0x34);
        Serial.write(0x34);
        break;
      case 5:
        Serial.write(0x35);
        Serial.write(0x35);
        Serial.write(0x35);
        Serial.write(0x35);
        break;
      case 6:
        Serial.write(0x36);
        Serial.write(0x36);
        Serial.write(0x36);
        Serial.write(0x36);
        break;
      case 7:
        Serial.write(0x37);
        Serial.write(0x37);
        Serial.write(0x37);
        Serial.write(0x37);
        break;
      case 8:
        Serial.write(0x38);
        Serial.write(0x38);
        Serial.write(0x38);
        Serial.write(0x38);
        break;
      case 9:
        Serial.write(0x39);
        Serial.write(0x39);
        Serial.write(0x39);
        Serial.write(0x39);
        break;
    }
    Serial.write(0x03); // End of text (ctrl-C)
    delay(500);
    timer = timer - 1;
  }
}

void loop() {
  int VALUE = COUNTER * 10;

  if (COUNTER == 1) {
    resetTimer();
  }
  
  writeLCDChannel2Header();
  numberToHex(VALUE);
  Serial.write(0x03); // End of text (ctrl-C)
  
  Serial.println("");
  Serial.println(VALUE);
  Serial.println(COUNTER);

  COUNTER++;
  if (COUNTER > 257) {
    COUNTER = 1;
  }

  delay(500);
}
