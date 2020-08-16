int ev = 0;
byte cx = 0, sx;
byte dg[] = {9, 2, 8};
int cntr;

//----------- pgfedcba pgfedcba pgfedcba pgfedcba
const byte dx[] = {B00111111, B00000110, B01011011, B01001111, B01100110, B01101101, B01111101, B00000111, B01111111, B01101111,
                   B01110111, B01111100, B01011000, B01011110, B01111001, B01110001
                  };
                  
void setup() {
  Serial.begin(9600);
  DDRC = 0x3F; //PC[0..5] as output
  DDRB = 0x3F; //PB[0..5] as output
  TCCR2A = 0x02;
  TCCR2B = B111;
  OCR2A = 128;
  TIMSK2 = 0x02;
  sei();
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), CLEAR_int0, FALLING);
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3), LOAD_int1, FALLING);
}

ISR(TIMER2_COMPA_vect) {
  sx = dx[dg[cx]];
  PORTB = PORTB | B011100;
  PORTC = sx & 0x3F;
  PORTB = ((PORTB & 0xFC) | (sx >> 6));
  PORTB = PORTB & (~(4 << cx));
  cx = ++cx % 3;
}

void LOAD_int1() {
  cntr = 122;
}

void CLEAR_int0() {
  cntr = -1;
}

void loop() {
  cntr = ++cntr % 1000;
  dg[0] = cntr % 10;
  dg[2] = cntr / 100;
  dg[1] = (cntr / 10) % 10;
  delay(200);
}
