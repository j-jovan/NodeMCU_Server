int ledPins[] = {13, 12, 14, 2, 0, 4, 5, 16}; //Array koji sadrzi sve pinove.
int pinCount = 8; // Broj item-a u nizu ledPins[], jer sizeof() ne radi
int timer = 100; // Timer svega

//Ukljuci pinove redno, pa iskljuci pinove redno
void rednoUkljucivanje() {
  //Inicijalizacija pinova iz ledPins[]
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    pinMode(ledPins[thisPin], OUTPUT);
  }
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    digitalWrite(ledPins[thisPin], HIGH);
    delay(timer);
  }
  for (int thisPin = 8; thisPin > 0; thisPin--) {
    digitalWrite(ledPins[thisPin], LOW);
    delay(timer);
  }
}
//Ukljuci pinove cik-cak (prvi, poslednji), iskljuci redno
void rednoUkljucivanje2() {
  for (int flipFlop = 1; flipFlop <= 2; flipFlop++) {
    int minNum = 0;
    int maxNum = 7;
    for (int i = 0; i < 8; i++) {
      digitalWrite(ledPins[minNum], HIGH);
      delay(timer);
      digitalWrite(ledPins[maxNum], HIGH);
      delay(timer);
      minNum++;
      maxNum--;
    }
    if (flipFlop == 1) {
      for (int thisPin = 8; thisPin >= 0; thisPin--) {
        digitalWrite(ledPins[thisPin], LOW);
        delay(timer);
      }
    }
    if (flipFlop == 2) {
      for (int thisPin = 0; thisPin <= 8; thisPin++) {
        digitalWrite(ledPins[thisPin], LOW);
        delay(timer);
      }
    }
  }
}
//Ukljuci, iskljuci jedan po jedan
void rednoUkljucivanje3() {
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    pinMode(ledPins[thisPin], OUTPUT);
  }
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    digitalWrite(ledPins[thisPin], HIGH);
    delay(timer);
    digitalWrite(ledPins[thisPin], LOW);
  }
  for (int thisPin = 8; thisPin > 0; thisPin--) {
    digitalWrite(ledPins[thisPin], HIGH);
    delay(timer);
    digitalWrite(ledPins[thisPin], LOW);
  }
}
