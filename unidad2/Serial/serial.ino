#include <Keypad.h>
String cad = "";

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
        {'1', '2', '3', '+'},
        {'4', '5', '6', '-'},
        {'7', '8', '9', '*'},
        {'x', '0', '=', '/'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
}

void loop() {
  char key = keypad.getKey();

  if (key != NO_KEY) {
    if (key == '=') {
      if (cad.length() > 0) {
        // Realizar la operación aritmética
        Serial.print("Resultado: ");
        Serial.println(eval(cad));
        cad = "";
      }
    } else if (key == 'x') {
      deleteLastEntry();
    } else {
      Serial.println(key);
      cad = cad + key;
    }
  }
}

void deleteLastEntry() {
  if (cad.length() > 0) {
    cad = cad.substring(0, cad.length() - 1);
    Serial.println("ultimo caracter eliminado.");
  }
}

float eval(String expression) {
  int opPos = -1;
  char op;
  for (int i = 0; i < expression.length(); i++) {
    if (expression.charAt(i) == '+' || expression.charAt(i) == '-' ||
        expression.charAt(i) == '*' || expression.charAt(i) == '/') {
      opPos = i;
      op = expression.charAt(i);
      break;
    }
  }

  if (opPos == -1) {
    return expression.toFloat();
  }

  String leftStr = expression.substring(0, opPos);
  String rightStr = expression.substring(opPos + 1);

  float left = leftStr.toFloat();
  float right = rightStr.toFloat();

  if (op == '+') {
    return left + right;
  } else if (op == '-') {
    return left - right;
  } else if (op == '*') {
    return left * right;
  } else if (op == '/') {
    if (right == 0) {
      Serial.println("Error: División por cero");
      return 0;
    }
    return left / right;
  }
  return 0;
}