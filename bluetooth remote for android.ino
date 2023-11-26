/**
 * This example turns the ESP32 into a Bluetooth LE mouse that scrolls down every 2 seconds.
 */
#include <BleKeyboard.h>
#include <ESP32Encoder.h>
BleKeyboard bleKeyboard("BLE Remote(Harsha)", "harsha vardhan", 74);
#include <Keypad.h>
#include <SimpleRotary.h>
const byte ROWS = 2; //four rows
const byte COLS = 4; //four columns

// the library will return the character inside this array
// when the appropriate button is pressed.
char keys[ROWS][COLS] = {
   {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
};

// Looking at the keypad from the front, the row pins are on the left.

byte rowPins[ROWS] = {13, 12}; // Row pinouts
byte colPins[COLS] = {5, 18, 19, 21}; // Column pinouts

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// First param is name
// Second is manufacturer
// Third is initial batter level


// Pin A, Pin B, Button Pin
SimpleRotary rotary(26,33,35);

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();

}

void sendMacroCommand(uint8_t key) {
  bleKeyboard.press(KEY_LEFT_CTRL);
  bleKeyboard.press(KEY_LEFT_SHIFT);
  bleKeyboard.press(KEY_LEFT_ALT);
  bleKeyboard.press(key);
}

void loop() {

  byte j;

  // 0 = not pushed, 1 = pushed, 2 = long pushed
  j = rotary.pushType(1000); // number of milliseconds button has to be pushed for it to be considered a long push.

  if ( j == 1 ) {
    Serial.println("Pushed");
        if(bleKeyboard.isConnected()) {
          Serial.println("Pressing the Play/Pause.Button via the Bluetooth keyboard");
          bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
        }
    }
  
  if ( j == 2 ) {
    Serial.println("Long Pushed");
          if(bleKeyboard.isConnected()) {
            Serial.println("Pressing the next-button via the Bluetooth keyboard");
            bleKeyboard.write(KEY_MEDIA_NEXT_TRACK);
         }

    }

  
  byte i;

  // 0 = not turning, 1 = CW, 2 = CCW
  i = rotary.rotate();

  if ( i == 1 ) {
    Serial.println("CW");
          if(bleKeyboard.isConnected()) {
            Serial.println("Volume up");
            bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
           }

    }

  if ( i == 2 ) {
    Serial.println("CCW");
          if(bleKeyboard.isConnected()) {
            Serial.println("Volume down");
            bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
          }

    }
    char key = keypad.getKey();

  // Only do something with the keypress if we
  // are connected to something via bluetooth
  
  if (bleKeyboard.isConnected() && key) {
    Serial.println(key);
    switch (key) {
      case '4':
        bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
        break;
      case '5':
        bleKeyboard.write(KEY_MEDIA_PREVIOUS_TRACK);
        break;
      case '2':
        bleKeyboard.write(KEY_MEDIA_NEXT_TRACK);
        break;
      case 'B':
        bleKeyboard.write(KEY_F1);
        break;
      case '6':
        bleKeyboard.write(KEY_F2);
        break;
      case '3':
        bleKeyboard.press(KEY_F3);
        break;
      case 'A':
        bleKeyboard.press(KEY_F4);
        break;
    }
    delay(100);
    bleKeyboard.releaseAll();

}
}
