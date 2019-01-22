//By liposlt
//HP QDSP6064测试程序

#include <MsTimer2.h>

//CC_1    1   12  SEG_A
//SEG_E   2   11  SEG_B
//SEG_C   3   10  CC_2
//CC_3    4   9   SEG_F
//SEG_DP  5   8   SEG_D
//CC_4    6   7   SEG_G

#define HC595_DS  7   //HC595 PIN14 DS 串行数据输入
#define HC595_RCK 6   //HC595 PIN12 ST_CP 输出存储器锁存时钟线
#define HC595_SCK 5   //HC595 PIN11 SH_CP 数据输入时钟线

#define CC_1 11 //QDSP-6064 PIN1
#define CC_2 8  //QDSP-6064 PIN10
#define CC_3 10 //QDSP-6064 PIN4
#define CC_4 9  //QDSP-6064 PIN6

#define HC595_DS_RESET    digitalWrite(HC595_DS, LOW)     //DS
#define HC595_DS_SET      digitalWrite(HC595_DS, HIGH)

#define HC595_ST_CP_RESET digitalWrite(HC595_RCK, LOW)    //RCK
#define HC595_ST_CP_SET   digitalWrite(HC595_RCK, HIGH)

#define HC595_SH_CP_RESET digitalWrite(HC595_SCK, LOW)    //SCK
#define HC595_SH_CP_SET   digitalWrite(HC595_SCK, HIGH)

unsigned int i;
char table[18] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x80, 0xff};

void counter() {
  i++;
}
void setup() {
  // put your setup code here, to run once:
  pinMode(HC595_DS,  OUTPUT);
  pinMode(HC595_RCK, OUTPUT);
  pinMode(HC595_SCK, OUTPUT);
  pinMode(CC_1,  OUTPUT);
  pinMode(CC_2,  OUTPUT);
  pinMode(CC_3,  OUTPUT);
  pinMode(CC_4,  OUTPUT);

  digitalWrite(CC_1, HIGH);
  digitalWrite(CC_2, HIGH);
  digitalWrite(CC_3, HIGH);
  digitalWrite(CC_4, HIGH);
  MsTimer2::set(10, counter);
  MsTimer2::start();
}

void loop() {
  // put your main code here, to run repeatedly:
  //  for(i = 0; i < 18; i++){
  //    QDSP_6064_WriteChar(0, table[i]);
  //    delay(100);
  //  }
  if (9999 == i) i = 0;
  QDSP_6064_WriteChar(table[i / 1000], table[i % 1000 / 100], table[i % 100 / 10], table[i % 10]);
}

void QDSP_6064_WriteString(char *chr) {
}

void QDSP_6064_WriteChar(char chr0, char chr1, char chr2, char chr3) {
  HC595SendData(chr0); digitalWrite(CC_1, LOW); digitalWrite(CC_2, HIGH); digitalWrite(CC_3, HIGH); digitalWrite(CC_4, HIGH); delay(5);
  HC595SendData(chr1); digitalWrite(CC_1, HIGH); digitalWrite(CC_2, LOW); digitalWrite(CC_3, HIGH); digitalWrite(CC_4, HIGH); delay(5);
  HC595SendData(chr2); digitalWrite(CC_1, HIGH); digitalWrite(CC_2, HIGH); digitalWrite(CC_3, LOW); digitalWrite(CC_4, HIGH); delay(5);
  HC595SendData(chr3); digitalWrite(CC_1, HIGH); digitalWrite(CC_2, HIGH); digitalWrite(CC_3, HIGH); digitalWrite(CC_4, LOW); delay(5);
}

void HC595SendData(char data) {
  int i = 0;
  for (i = 0; i < 8; i++) {
    if (data & 0x80)
      HC595_DS_SET;
    else
      HC595_DS_RESET;
    data <<= 1;
    HC595_SH_CP_SET;  HC595_SH_CP_RESET;
  }
  HC595_ST_CP_SET;
  HC595_ST_CP_RESET;
}
