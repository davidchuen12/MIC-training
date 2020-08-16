#define len 17
int ev = 0;

const byte dx[] = {B100001, B010010, B001100, B010010, B100001, B111000, B000111,
                   B111000, B000111, B101010, B010101, B101010, B010101, B111111,
                   B000000, B111111, B000000, 0x3F
                  };

void setup() {
  Serial.begin(9600);
  DDRC = 0xFF;
}

void loop() {
  Serial.print(ev);
  if (ev == len) ev = 0;
  PORTC = dx[ev];
  ev = ++ev;
  Serial.print("\t");
  Serial.print(ev);
  Serial.println(PORTC, DEC);
  delay(500); // ignore for speed test
}
