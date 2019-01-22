//By liposlt
//OSRAM SLG-2016测试程序

#define WR    13
#define A1    12
#define A0    11
#define D0    10
#define D1    9
#define D2    8
#define D3    2
#define D4    3
#define D5    4
#define D6    5
#define BL    6
#define CLR   7

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(CLR, OUTPUT);
  pinMode(BL, OUTPUT);
  pinMode(WR, OUTPUT);

  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(D0, HIGH);
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
  digitalWrite(D5, HIGH);
  digitalWrite(D6, HIGH);
  digitalWrite(CLR, HIGH);
  digitalWrite(BL, HIGH);
  digitalWrite(WR, HIGH);

  digitalWrite(CLR, LOW);    //clear the ASCII RAM
  delay(10);
  digitalWrite(CLR, HIGH);

  //  for (int i = 0; i < 128; i++)
  //  {
  //    SLG_2016_WriteChar(3, 0x00 + i);
  //    SLG_2016_WriteChar(2, 0x00 + i);
  //    SLG_2016_WriteChar(1, 0x00 + i);
  //    SLG_2016_WriteChar(0, 0x00 + i);
  //    delay(100);
  //  }

  SLG_2016_WriteChar(3, 0x41);
  SLG_2016_WriteChar(2, 0x42);
  SLG_2016_WriteChar(1, 0x43);
  SLG_2016_WriteChar(0, 0x44);
  delay(1000);

  SLG_2016_WriteString("    1234567890987654321    ", 200);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  SLG_2016_WriteString("    hello world!!!  I'm OSRAM SLG-2016.    ", 400);
}

void SLG_2016_WriteString(char *chr, unsigned int ms)
{
  int i = 0, temp = 0;
  char *s;
  s = chr;

  while (chr[i] != '\0')
  {
    SLG_2016_WriteChar(3, chr[i]);
    SLG_2016_WriteChar(2, chr[i + 1]);
    SLG_2016_WriteChar(1, chr[i + 2]);
    SLG_2016_WriteChar(0, chr[i + 3]);
    i++;
    delay(ms);
    if (i == (strlen(s) - 3))
      i += 3;
  }
}

void SLG_2016_WriteChar(int pos, int chr)
{
  digitalWrite(BL, HIGH);
  digitalWrite(CLR, HIGH);
  digitalWrite(A1, (pos & 2) >> 1);
  digitalWrite(A0, (pos & 1));
  digitalWrite(WR, LOW);

  digitalWrite(D0, (chr & 0x01) >> 0);
  digitalWrite(D1, (chr & 0x02) >> 1);
  digitalWrite(D2, (chr & 0x04) >> 2);
  digitalWrite(D3, (chr & 0x08) >> 3);
  digitalWrite(D4, (chr & 0x10) >> 4);
  digitalWrite(D5, (chr & 0x20) >> 5);
  digitalWrite(D6, (chr & 0x40) >> 6);
}

