#include <Arduino.h>

const uint8_t PIN_CS = 8;
const uint8_t PIN_UD = 9;
const uint8_t PIN_INC = 10;
const uint8_t PIN_START = 2;
const uint8_t PIN_LED = 13;

int currentPosition = 0;
int targetPosition = 0;
bool started = false;

void setDirection(bool increment) {
  digitalWrite(PIN_UD, increment ? HIGH : LOW);
}

void pulseIncrement() {
  digitalWrite(PIN_CS, LOW);
  delayMicroseconds(50);
  digitalWrite(PIN_INC, LOW);
  delayMicroseconds(50);
  digitalWrite(PIN_INC, HIGH);
  delayMicroseconds(50);
  digitalWrite(PIN_CS, HIGH);
  delayMicroseconds(10);
}

void moveToPosition(int target) {
  if (target < 0) target = 0;
  if (target > 99) target = 99;

  if (target > currentPosition) {
    setDirection(true);
    while (currentPosition < target) {
      pulseIncrement();
      currentPosition++;
      delay(20);
    }
  } else if (target < currentPosition) {
    setDirection(false);
    while (currentPosition > target) {
      pulseIncrement();
      currentPosition--;
      delay(20);
    }
  }

  digitalWrite(PIN_LED, HIGH);
  delay(200);
  digitalWrite(PIN_LED, LOW);
}

void storePosition() {
  // La mayoría de los X9C103 requieren una secuencia de control asociada a la
  // memoria no volátil del fabricante. La rutina se deja preparada para la etapa
  // de persistencia del valor. En hardware real se debe confirmar la secuencia
  // exacta de la hoja de datos del fabricante.
  digitalWrite(PIN_CS, LOW);
  delayMicroseconds(100);
  digitalWrite(PIN_CS, HIGH);
  delayMicroseconds(100);
}

void printHelp() {
  Serial.println("--- Control X9C103 ---");
  Serial.println("Ingrese un valor entre 0 y 99");
  Serial.println("Presione el boton de inicio para ejecutar");
  Serial.println("Ejemplo: 35");
}

void setup() {
  pinMode(PIN_CS, OUTPUT);
  pinMode(PIN_UD, OUTPUT);
  pinMode(PIN_INC, OUTPUT);
  pinMode(PIN_START, INPUT_PULLUP);
  pinMode(PIN_LED, OUTPUT);

  digitalWrite(PIN_CS, HIGH);
  digitalWrite(PIN_INC, HIGH);
  digitalWrite(PIN_UD, LOW);
  digitalWrite(PIN_LED, LOW);

  Serial.begin(9600);
  printHelp();
}

void loop() {
  if (Serial.available() > 0) {
    int value = Serial.parseInt();
    if (value >= 0 && value <= 99) {
      targetPosition = value;
      Serial.print("Valor objetivo setiado: ");
      Serial.println(targetPosition);
      started = true;
    } else {
      Serial.println("Valor fuera de rango. Debe estar entre 0 y 99.");
    }
  }

  if (started && (digitalRead(PIN_START) == LOW)) {
    delay(50);
    Serial.print("Moviendo cursor a ");
    Serial.println(targetPosition);
    moveToPosition(targetPosition);
    storePosition();
    Serial.print("Posicion final: ");
    Serial.println(currentPosition);
    started = false;
  }
}
