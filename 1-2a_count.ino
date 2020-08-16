int ev = 0;

void setup() {
  Serial.begin(9600);
  DDRC = 0xFF;
  PORTC = 0;
}

void loop() {
  ev++;
  Serial.print(ev);
  PORTC = 0x0F & ++PORTC;
  PORTC = PORTC | B1111;
  if (ev == 1) PORTC = 15;
  Serial.print("\t");
  Serial.println(PORTC, DEC);
  delay(500);
}
