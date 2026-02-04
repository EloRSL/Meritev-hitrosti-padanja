volatile bool prvi = false;
volatile bool drugi = false;
volatile unsigned long zacetek = 0, konec = 0;
volatile unsigned long startTime = 0;
volatile bool errorPrinted = false;

const int PIN_PRVEGA_LASERJA = 8;

void setup() {
  Serial.begin(115200);
  sei();

  DDRB |= (1 << PB0); //nastavitev na output
  PORTB |= (1 << PB0); //output=high

  DDRD &= ~(1 << PD2); //nastavitev na input
  PORTD |= (1 << PD2); //pull-up resistor

  DDRD &= ~(1 << PD3);   
  PORTD |= (1 << PD3);   

  EICRA |= (1 << ISC00); //trigger on any change
  EICRA |= (1 << ISC10);

  EIMSK |= (1 << INT0);  //enable interrupt request
  EIMSK |= (1 << INT1);  
}

ISR(INT0_vect) {
  EIMSK &= ~(1 << INT0); //izključi interrupte
  if (!prvi) {
    zacetek = micros();
    prvi = true;
    drugi = false;
    startTime = millis();
  }
  EIFR |= (1 << INTF0); //počisti interrupte
  EIMSK |= (1 << INT0);  //vključi interrupte
}

ISR(INT1_vect) {
  EIMSK &= ~(1 << INT1);  
  if (prvi) {
    konec = micros();
    prvi = false;
    drugi = true;
    izpis();
  }
  EIFR |= (1 << INTF1);  
  EIMSK |= (1 << INT1);  
}

void izpis() {
  float Razlika = (konec - zacetek) / 1000000.0;
  Serial.print("Cas med laserjema: ");
  Serial.print(Razlika, 6);
  Serial.println(" sekund");
}

void loop() {
  if (prvi) {
    if (millis() - startTime >= 2000 && !drugi) {
      zacetek = 0;
      prvi = false;
      if (!errorPrinted) {
        PORTB &= ~(1 << PB0); //laser off
        Serial.println("Napaka v merjenju: Padec je trajal več kot 2 sekundi!");
        delay(500);
        PORTB |= (1 << PB0); //laser on
        errorPrinted = true;
      }
    }
  } else {
    errorPrinted = false;
  }
}