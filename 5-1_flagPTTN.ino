int ev = 0, ev2 = 0, flag = 0;
const byte dx[] = { B100001, B010010, B001100, B010010, B100001,
                    B111000, B000111, B111000, B000111,
                    B101010, B010101, B101010, B010101,
                    0x3F, 0, 0x3F, 0xFF };//endcode
void setup() {
  Serial.begin(9600);
  DDRC = 0xFF;
  TCCR2A = 0x02; //setup Timer#2 as CTC
  TCCR2B = B111; //prescaler with clk/n
  OCR2A = 255;
  TIMSK2 = 0x02; //enable OCR2A interrupt
  sei();
}
ISR(TIMER2_COMPA_vect) {
  ev++;
  if (ev == 100) {
    ev = 0;
    flag = 1;
  }
}
void loop() {
  Serial.print(ev2);
  if (flag) {
    flag = 0;
    if ( dx[ev2] == 0xFF ) ev2 = 0;
    PORTC = dx[ev2];
    ev2++;
  }
  delay(500);
  Serial.print("\t");
  Serial.print(ev);
  Serial.print(" ");
  Serial.print(flag);
  Serial.print(" ");
  Serial.println(PORTC, BIN);
}
