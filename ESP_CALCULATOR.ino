#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// KEYPAD
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','/'},
  {'4','5','6','*'},
  {'7','8','9','-'},
  {'C','0','=','+'}
};

byte rowPins[ROWS] = {13, 12, 14, 27};
byte colPins[COLS] = {26, 25, 33, 32};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// VARIABLES
String input = "";
String expression = "";

float num1 = 0, num2 = 0;
char op = 0;
bool resultShown = false;

void setup() {
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED FAIL");
    while (true);
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
}

// FUNCTION: DISPLAY UI
void updateDisplay() {
  display.clearDisplay();

  // Expression (small text)
  display.setTextSize(1);
  display.setCursor(0, 5);
  display.print(expression);

  // Input / Result (big text)
  display.setTextSize(2);
  display.setCursor(0, 30);
  display.print(input);

  display.display();
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.println(key);

    // RESET if new input after result
    if (resultShown && key >= '0' && key <= '9') {
      input = "";
      expression = "";
      resultShown = false;
    }

    // NUMBER INPUT
    if (key >= '0' && key <= '9') {
      input += key;
      expression += key;
    }

    // OPERATOR
    else if (key == '+' || key == '-' || key == '*' || key == '/') {
      if (input != "") {
        num1 = input.toFloat();
        op = key;
        input = "";
        expression += key;
        resultShown = false;
      }
    }

    // EQUAL
    else if (key == '=') {
      if (input != "") {
        num2 = input.toFloat();
        float result = 0;

        if (op == '+') result = num1 + num2;
        else if (op == '-') result = num1 - num2;
        else if (op == '*') result = num1 * num2;
        else if (op == '/') {
          if (num2 == 0) {
            input = "Err";
            expression = "";
            updateDisplay();
            return;
          }
          result = num1 / num2;
        }

        expression += "=" + String(result);
        input = String(result);
        resultShown = true;
      }
    }

    // CLEAR
    else if (key == 'C') {
      input = "";
      expression = "";
      num1 = num2 = 0;
      op = 0;
      resultShown = false;
    }

    updateDisplay();
  }
}