//-- myOTTO move

// 參數：校正的位置 (要調整的角度)
int adj[]={ 0, 0, 0 };

// 參數：起始位置
int pos[]={ 90,90,90 };  // 起始位置

// 參數：逐一執行的角度
int shift[] = {
  0,1,2,3,4,5,6,7,8,9,10,
  9,8,7,6,5,4,3,2,1,0,
  -1,-2,-3,-4,-5,-6,-7,-8,-9,-10,
  -9,-8,-7,-6,-5,-4,-3,-2,-1,0
};

int shift_delay = 10;
int shift_scale = 3;  // 倍數

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
  
  move_servo();
  
  int shift_length = sizeof(shift) / sizeof(int);
  Serial.println(shift_length);
}


void loop()
{
  for(int i=0; i<4; i++)
  {
    int shift_length = sizeof(shift) / sizeof(int);
    for(int j=0; j<shift_length; j++)
    {
       pos[i] = 90 + shift[j]*shift_scale;
       move_servo();
       show_message();
       delay(shift_delay);
    }
  }
}


void show_message()
{ 
  Serial.print("Posistion: ");  
  Serial.print(pos[0]);
  Serial.print(",");
  Serial.print(pos[1]);
  Serial.print(",");
  Serial.print(pos[2]);
  Serial.print(" | ");
  
  Serial.print(adj[0]);
  Serial.print(",");
  Serial.print(adj[1]);
  Serial.print(",");
  Serial.print(adj[2]);
  
  Serial.print(" | ");
  
  Serial.print(pos[0]-adj[0]);
  Serial.print(",");
  Serial.print(pos[1]-adj[1]);
  Serial.print(",");
  Serial.print(pos[2]-adj[2]);
  Serial.print(" | ");
  
  Serial.println("");
}