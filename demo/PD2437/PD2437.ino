//By liposlt
//SIEMENS PD2437测试程序

#define RST   A0
#define CE1   A1
#define CE0   A2
#define AA2   A3
#define AA1   A4
#define AA0   A5
#define WR    0
#define D7    1
#define D6    2
#define D5    3
#define D4    4
#define D3    5
#define D2    6
#define D1    7
#define D0    8

void setup() {
  // put your setup code here, to run once:
  pinMode(RST, OUTPUT);
  pinMode(CE1, OUTPUT);
  pinMode(CE0, OUTPUT);
  pinMode(AA2, OUTPUT);
  pinMode(AA1, OUTPUT);
  pinMode(AA0, OUTPUT);
  pinMode(WR, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D0, OUTPUT);

  digitalWrite(WR, HIGH);
  digitalWrite(CE1, LOW);
  digitalWrite(CE0, HIGH);
  digitalWrite(RST, HIGH);
  PD_2437_Control_Word(0x40);
  delay(1000);
  PD_2437_Control_Word(0x03);

  PD_2437_WriteChar(0x03, 0x41);
  PD_2437_WriteChar(0x02, 0x42);
  PD_2437_WriteChar(0x01, 0x43);
  PD_2437_WriteChar(0x00, 0x44);
  PD_2437_WriteChar(0x03, 0x80 + 0x41);
  PD_2437_WriteChar(0x02, 0x80 + 0x42);
  PD_2437_WriteChar(0x01, 0x80 + 0x43);
  PD_2437_WriteChar(0x00, 0x80 + 0x44);
  PD_2437_Control_Word(0x17);
}

void loop() {
  ////put your main code here, to run repeatedly:
  //  for (int i = 0; i < 128; i++) {
  //    PD_2437_WriteChar(0x00, i);
  //    PD_2437_WriteChar(0x01, i);
  //    PD_2437_WriteChar(0x02, i);
  //    PD_2437_WriteChar(0x03, i);
  //    delay(400);
  //  }
  //  for (int i = 0; i < 4; i++) {
  //    PD_2437_Control_Word(i);
  //    PD_2437_WriteChar(0x03, 0x41);
  //    PD_2437_WriteChar(0x02, 0x42);
  //    PD_2437_WriteChar(0x01, 0x43);
  //    PD_2437_WriteChar(0x00, 0x44);
  //    delay(1000);
  //  }
  //  PD_2437_WriteChar(0x03, 0x41);
  //  PD_2437_WriteChar(0x02, 0x42);
  //  PD_2437_WriteChar(0x01, 0x43);
  //  PD_2437_WriteChar(0x00, 0x44);
  //  PD_2437_WriteChar(0x03, 0x80 + 0x41);
  //  PD_2437_Control_Word(0x17);
  //  delay(1000);
}

void PD_2437_WriteChar(int pos, int chr) {
  digitalWrite(CE1, HIGH);
  digitalWrite(CE0, LOW);

  digitalWrite(AA2, 1);
  digitalWrite(AA1, (pos & 0x02) >> 1);
  digitalWrite(AA0, (pos & 0x01));

  digitalWrite(D0, (chr & 0x01) >> 0);
  digitalWrite(D1, (chr & 0x02) >> 1);
  digitalWrite(D2, (chr & 0x04) >> 2);
  digitalWrite(D3, (chr & 0x08) >> 3);
  digitalWrite(D4, (chr & 0x10) >> 4);
  digitalWrite(D5, (chr & 0x20) >> 5);
  digitalWrite(D6, (chr & 0x40) >> 6);
  digitalWrite(D7, (chr & 0x80) >> 7);

  digitalWrite(WR, LOW);
}
void PD_2437_Control_Word(int level) {
  digitalWrite(CE1, HIGH);
  digitalWrite(CE0, LOW);

  digitalWrite(AA2, 0);
  digitalWrite(AA1, 0);
  digitalWrite(AA0, 0);

  digitalWrite(D0, (level & 0x01) >> 0);
  digitalWrite(D1, (level & 0x02) >> 1);
  digitalWrite(D2, (level & 0x04) >> 2);
  digitalWrite(D3, (level & 0x08) >> 3);
  digitalWrite(D4, (level & 0x10) >> 4);
  digitalWrite(D5, (level & 0x20) >> 5);
  digitalWrite(D6, (level & 0x40) >> 6);
  digitalWrite(D7, (level & 0x80) >> 7);

  digitalWrite(WR, LOW);
}

