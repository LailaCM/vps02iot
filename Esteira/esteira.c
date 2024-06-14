#define ESTEIRA 13
#define BOTAO 1
#define SENSOR 2

bool esteiraLigada = false;
bool lastButtonState = LOW;
bool currentButtonState;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  pinMode(ESTEIRA, OUTPUT);
  pinMode(BOTAO, INPUT_PULLUP);
  Serial.begin(9600);
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

long distancia() {
  long duration, distance;
  pinMode(SENSOR, OUTPUT);
  digitalWrite(SENSOR, LOW);
  delayMicroseconds(2);
  digitalWrite(SENSOR, HIGH);
  delayMicroseconds(5);
  digitalWrite(SENSOR, LOW);
  pinMode(SENSOR, INPUT);
  duration = pulseIn(SENSOR, HIGH);
  distance = microsecondsToCentimeters(duration);
  return distance;
}

void loop() { 
  currentButtonState = digitalRead(BOTAO);

  if (currentButtonState != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (currentButtonState != esteiraLigada) {
      esteiraLigada = currentButtonState;
      if (esteiraLigada) {
        digitalWrite(ESTEIRA, HIGH);
        Serial.println("Esteira ligada.");
      } else {
        digitalWrite(ESTEIRA, LOW);
        Serial.println("Esteira desligada.");
      }
    }
  }

  lastButtonState = currentButtonState;

  if (distancia() < 50) {
    digitalWrite(ESTEIRA, LOW);
    esteiraLigada = false;
    Serial.println("Segurança ativada. Esteira desligada.");
  }
}