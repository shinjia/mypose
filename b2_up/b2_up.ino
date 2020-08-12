//-- myPOSE move position

// 參數：校正的位置 (要調整的角度)
int adj[]={ 0, 0, 0 };

// 參數：起始位置
int pos[]={ 90,90,90 };  // 起始位置

// 參數：各伺服馬達移動的角度
int shift4[][3] = {
  { 90, 90, 90 },
  { 90, 100, 100 },
  { 90, 110, 110 },
  { 90, 120, 120 },
  { 90, 130, 130 },
  { 90, 140, 140 },
  { 90, 130, 140 },
  { 90, 120, 120 },
  { 90, 110, 110 },
  { 90, 100, 100 },
  { 90, 90, 90 },
  { 90, 80, 80 },
  { 90, 70, 70 },
  { 90, 60, 60 },
  { 90, 50, 50 },
  { 90, 60, 60 },
  { 90, 70, 70 },
  { 90, 80, 80 },
  { 90, 90, 90 },
  { 90, 90, 90 }
};

int shift_length; // 直接在程式中計算取得
int shift_delay = 121;


#include <Servo.h>
Servo S0, S1, S2;

// 參數：各伺服馬達的腳位
#define PIN_TH 4
#define PIN_HL 5
#define PIN_HR 6


void move_servo()
{
  S0.write(pos[0]+adj[0]);
  S1.write(180-pos[1]+adj[1]);  // in myPOSE Left Hand
  S2.write(pos[2]+adj[2]);
}


void setup()
{
  Serial.begin(115200);
 
  S0.attach(PIN_TH);
  S1.attach(PIN_HL);
  S2.attach(PIN_HR);
    
  show_message();
  move_servo();
}


void loop()
{
  shift_length = sizeof(shift4) / sizeof(shift4[0]);
  
  for(int j=0; j<shift_length; j++)
  {
    pos[0] = shift4[j][0];
    pos[1] = shift4[j][1];
    pos[2] = shift4[j][2];
    
    move_servo();
    // show_message();
    delay(shift_delay);
  }
}


void show_message()
{
  Serial.println("HOME Position");
  
  Serial.print("Position: ");  
  Serial.print(pos[0]);
  Serial.print(",");
  Serial.print(pos[1]);
  Serial.print(",");
  Serial.print(pos[2]);
  Serial.println("");
  
  Serial.print("Adjusted: ");  
  Serial.print(adj[0]);
  Serial.print(",");
  Serial.print(adj[1]);
  Serial.print(",");
  Serial.print(adj[2]);
  Serial.println("");
}