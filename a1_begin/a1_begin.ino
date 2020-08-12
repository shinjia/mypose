//-- myPOSE begin test

// 參數：起始位置
int pos0 = 90;
int pos1 = 90;
int pos2 = 90;


// 參數：各伺服馬達的腳位
#define PIN_TH 4
#define PIN_HL 5
#define PIN_HR 6

#include <Servo.h>
Servo S0, S1, S2;


void move_servo()
{
  S0.write(pos0);
  S1.write(pos1);
  S2.write(pos2);
}


void setup()
{
  Serial.begin(115200);
 
  S0.attach(PIN_TH);
  S1.attach(PIN_HL);
  S2.attach(PIN_HR);
  
  move_servo();
  delay(3000);
}


void loop()
{
  // 此處僅改變一個馬達 S0
  int shift = 30;  // 偏移的量
  
  // 愈來愈大
  for(int angle=90; angle<90+shift; angle++)
  {
    S0.write(angle);
    delay(50);
  }
  
  // 愈來愈小
  for(int angle=90+shift; angle>90-shift; angle--)
  {
    S0.write(angle);
    delay(50);
  }
  
  // 愈來愈大，回到定位
  for(int angle=90-shift; angle<90; angle++)
  {
    S0.write(angle);
    delay(50);
  }
}