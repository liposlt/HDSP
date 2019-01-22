//测试版pin脚接线
 /*************************
DATA  D2
CLK   D3
VB    D4
COL1  D5
COL2  D6
COL3  D7
COL4  D8
COL5  D9

1 COL1  12 DATA IN
2 COL2  11 GND
3 COL3  10 CLK
4 COL4  9 VCC
5 COL5  8 VB
6 NC    7 DATA OUT
*************************/ 
#include "font.h"

void setup(){
  Serial.begin(9600);
  
  pinMode(2, OUTPUT); // Data
  pinMode(3, OUTPUT); // Clock
  pinMode(4, OUTPUT); // VB                
  pinMode(5, OUTPUT); // Col 1
  pinMode(6, OUTPUT); // Col 2
  pinMode(7, OUTPUT); // Col 3
  pinMode(8, OUTPUT); // Col 4
  pinMode(9, OUTPUT); // Col 5        
}
uint8_t bmp_dat[80] = {
  0xFF, 0x33, 0xFF, 0x7F, 0x3F, 0x1F, 0x0F, 0x07, 0x03, 0x01,
  0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF, 0x33, 0x33, 
  0x33, 0x3F, 0x33, 0x3F, 0x33, 0x3F, 0xFF, 0x33, 0x33, 0x33, 
  0x33, 0x3F, 0x33, 0x3F, 0xFF, 0x3F, 0xFF, 0x3F, 0xFF, 0xFF,
  
  0x0C, 0x12, 0x24, 0x12, 0x0C, 0x0C, 0x12, 0x24, 0x12, 0x0C,
  0x0C, 0x12, 0x24, 0x12, 0x0C, 0x0C, 0x12, 0x24, 0x12, 0x0C,
  0x0C, 0x12, 0x24, 0x12, 0x0C, 0x0C, 0x12, 0x24, 0x12, 0x0C,
  0x0C, 0x12, 0x24, 0x12, 0x0C, 0x0C, 0x12, 0x24, 0x12, 0x0C,
};
void loop() {
//  Serial.println((conversion(0x3e)<<24) | (conversion(0x00)<<17) | (conversion(0x46)<< 10) | (conversion(0x31)<<3),HEX);
//  for (int i=0;i<96;i++){
//    for (int j=0;j<10;j++){
//      HDSP2000_ShowChar(0x20+i, 0x21+i, 0x22+i, 0x23+i);
//    }
//  }
//  HDSP2000_ShowChar(0x20+90, 0x20+58, 0x20+88, 0x20+75);
//hdsp2000_put_pixel(random(0,19),random(0,6));
//delay(600);
//hdsp2000_put_pixel(random(0,7),random(0,7));
//  for (int i=0;i<7;i++){
//    for (int j=0;j<1;j++){
//        hdsp2000_put_pixel(0,i);
//    }
//  }
//hdsp2000_put_pixel(0,6);
//  for (int i=0;i<20;i++){
//    hdsp2000_displayPic(bmp_dat+i);
//  }
  for (int i=0;i<20;i++){
    for (int j=0;j<20;j++){ 
      hdsp2000_displayPic(bmp_dat+40+i);
    }
  }
//HDSP2000_ShowChar('0','5','2','1');
}
void HDSP2000_ShowChar(uint8_t chr1, uint8_t chr2, uint8_t chr3, uint8_t chr4){
  uint8_t c1 = 0, c2 = 0, c3 = 0, c4 = 0;
  c1 = chr1 - ' '; 
  c2 = chr2 - ' ';
  c3 = chr3 - ' ';
  c4 = chr4 - ' ';

  for (int i=5;i<10;i++){
      switch(i) {
       case 5:
          digitalWrite(4,LOW);   // Blank
          shiftlong(F5x7[c1][0], F5x7[c2][0], F5x7[c3][0], F5x7[c4][0]);
          digitalWrite(9,HIGH);  // off previous
          digitalWrite(i,LOW);  // on current
          digitalWrite(4,HIGH);  // stop blank
          break;
       case 6:
          digitalWrite(4,LOW);   // Blank
          shiftlong(F5x7[c1][1], F5x7[c2][1], F5x7[c3][1], F5x7[c4][1]);
          digitalWrite(i-1,HIGH);  // off previous
          digitalWrite(i,LOW);  // on current
          digitalWrite(4,HIGH);  // stop blank
          break;
       case 7:
          digitalWrite(4,LOW);   // Blank
          shiftlong(F5x7[c1][2], F5x7[c2][2], F5x7[c3][2], F5x7[c4][2]);
          digitalWrite(i-1,HIGH);  // off previous
          digitalWrite(i,LOW);  // on current
          digitalWrite(4,HIGH);  // stop blank
          break;
       case 8:
          digitalWrite(4,LOW);   // Blank
          shiftlong(F5x7[c1][3], F5x7[c2][3], F5x7[c3][3], F5x7[c4][3]);
          digitalWrite(i-1,HIGH);  // off previous
          digitalWrite(i,LOW);  // on current
          digitalWrite(4,HIGH);  // stop blank
          break;
       case 9:
          digitalWrite(4,LOW);   // Blank
          shiftlong(F5x7[c1][4], F5x7[c2][4], F5x7[c3][4], F5x7[c4][4]);
          digitalWrite(i-1,HIGH);  // off previous
          digitalWrite(i,LOW);  // on current
          digitalWrite(4,HIGH);  // stop blank
          break;
      }
      delay(2);
  }
}
long conversion(uint8_t dat){
  return (dat&0x01)<<7 | (dat&0x80)>>7 | (dat&0x02)<<5 | (dat&0x40)>>5 | (dat&0x04)<<3 | (dat&0x20)>>3 | (dat&0x08)<<1 | (dat&0x10)>>1;
}
void shiftlong(uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4) {
  long val = 0;
  val = (conversion(c1)<<24) | (conversion(c2)<<17) | (conversion(c3)<< 10) | (conversion(c4)<<3);
  
  digitalWrite(3, LOW);
  for (int i = 0; i < 32; i++) {
    digitalWrite(2, !!(val & (1L << i)));
    digitalWrite(3, HIGH);
    digitalWrite(3, LOW);   
  }
}
void hdsp2000_displayPic(uint8_t *pic){
  uint8_t pixel[20] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  };

  for (int i=0;i<20;i++)
    pixel[i] = pic[i];
  
  for (int i=5;i<10;i++){
      switch(i) {
       case 5:
          digitalWrite(4,LOW);   // Blank
          shiftlong(pixel[0], pixel[5], pixel[10], pixel[15]);
          digitalWrite(9,HIGH);  // off previous
          digitalWrite(i,LOW);  // on current
          digitalWrite(4,HIGH);  // stop blank
          break;
       case 6:
          digitalWrite(4,LOW);   // Blank
          shiftlong(pixel[1], pixel[6], pixel[11], pixel[16]);
          digitalWrite(i-1,HIGH);  // off previous
          digitalWrite(i,LOW);  // on current
          digitalWrite(4,HIGH);  // stop blank
          break;
       case 7:
          digitalWrite(4,LOW);   // Blank
          shiftlong(pixel[2], pixel[7], pixel[12], pixel[17]);
          digitalWrite(i-1,HIGH);  // off previous
          digitalWrite(i,LOW);  // on current
          digitalWrite(4,HIGH);  // stop blank
          break;
       case 8:
          digitalWrite(4,LOW);   // Blank
          shiftlong(pixel[3], pixel[8], pixel[13], pixel[18]);
          digitalWrite(i-1,HIGH);  // off previous
          digitalWrite(i,LOW);  // on current
          digitalWrite(4,HIGH);  // stop blank
          break;
       case 9:
          digitalWrite(4,LOW);   // Blank
          shiftlong(pixel[4], pixel[9], pixel[14], pixel[19]);
          digitalWrite(i-1,HIGH);  // off previous
          digitalWrite(i,LOW);  // on current
          digitalWrite(4,HIGH);  // stop blank
          break;
      }
      delay(2);
  }
}
//在指定的位置显示一个像素点
//列有5*4=20列 x = 0 - 19
//行有7行 y = 0 - 6
void hdsp2000_put_pixel(uint8_t x, uint8_t y){
  uint8_t pixel[20] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  };
  
  switch(y){
    case 0:
      pixel[x] = 0x01;
      break;
    case 1:
      pixel[x] = 0x02;
      break;
    case 2:
      pixel[x] = 0x04;
      break;
    case 3:
      pixel[x] = 0x08;
      break;
    case 4:
      pixel[x] = 0x10;
      break;
    case 5:
      pixel[x] = 0x20;
      break;
    case 6:
      pixel[x] = 0x40;
      break;          
  }
  
  for (int i=5;i<10;i++){
      switch(i) {
       case 5:
          digitalWrite(4,LOW);   // Blank
          shiftlong(pixel[0], pixel[5], pixel[10], pixel[15]);
          digitalWrite(9,HIGH);  // off previous
          digitalWrite(i,LOW);  // on current
          digitalWrite(4,HIGH);  // stop blank
          break;
       case 6:
          digitalWrite(4,LOW);   // Blank
          shiftlong(pixel[1], pixel[6], pixel[11], pixel[16]);
          digitalWrite(i-1,HIGH);  // off previous
          digitalWrite(i,LOW);  // on current
          digitalWrite(4,HIGH);  // stop blank
          break;
       case 7:
          digitalWrite(4,LOW);   // Blank
          shiftlong(pixel[2], pixel[7], pixel[12], pixel[17]);
          digitalWrite(i-1,HIGH);  // off previous
          digitalWrite(i,LOW);  // on current
          digitalWrite(4,HIGH);  // stop blank
          break;
       case 8:
          digitalWrite(4,LOW);   // Blank
          shiftlong(pixel[3], pixel[8], pixel[13], pixel[18]);
          digitalWrite(i-1,HIGH);  // off previous
          digitalWrite(i,LOW);  // on current
          digitalWrite(4,HIGH);  // stop blank
          break;
       case 9:
          digitalWrite(4,LOW);   // Blank
          shiftlong(pixel[4], pixel[9], pixel[14], pixel[19]);
          digitalWrite(i-1,HIGH);  // off previous
          digitalWrite(i,LOW);  // on current
          digitalWrite(4,HIGH);  // stop blank
          break;
      }
      delay(2);
  }
}




