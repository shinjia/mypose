//-- myPOSE original position

// 參數：校正的位置 (要調整的角度)
int adj[]={ 0, 0, 0 };

// 參數：起始位置
int pos[]={ 90,90,90 };  // 起始位置


// 參數：各伺服馬達的腳位
#define PIN_TH 4
#define PIN_HL 5
#define PIN_HR 6

#include <Servo.h>
Servo S0, S1, S2;


void move_servo()
{
  S0.write(pos[0]+adj[0]);
  S1.write(pos[1]+adj[1]);
  S2.write(pos[2]+adj[2]);
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
  int shift = 30;  // 偏移的總量
  int shift_inc = 10;  // 遞增量
  int shift_delay = 30;  // 每次延遲的時間
  
  // 愈來愈大
  for(int angle=90; angle<90+shift; angle+=shift_inc)
  {
    pos[0] = angle;  // 指定移的角度
    move_servo();
    delay(shift_delay);
  }
  
  // 愈來愈小
  for(int angle=90+shift; angle>90-shift; angle-=shift_inc)
  {
    pos[0] = angle;  // 指定移的角度
    move_servo();
    delay(shift_delay);
  }
  
  // 愈來愈大，回到定位
  for(int angle=90-shift; angle<90; angle+=shift_inc)
  {
    pos[0] = angle;  // 指定移的角度
    move_servo();
    delay(shift_delay);
  }
}