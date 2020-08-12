//-- myPOSE

int N_SERVOS = 3; // 伺服馬達的個數

// 參數：校正的位置 (要調整的角度)
int adj[]={ 0, 0, 0 };

// 參數：起始位置
int pos[]={ 90,90,90 };  // 起始位置

// TEMPO: 121 BPM
int tempo_base = 120;

#define INTERVALTIME 10.0 

// 硬體設定
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


void tempo_servo(int stime, int pos_new[])
{
  float increment[N_SERVOS];
  unsigned long final_time;
  unsigned long interval_time;
  int iteration = 1; 
  int oneTime;
  int pos_old[] = { 0, 0, 0 };

  for(int i=0; i<N_SERVOS; i++)
  {
    pos_old[i] = pos[i];
    increment[i] = ((pos_new[i])-pos[i])/(stime/INTERVALTIME);
  }
  
  final_time =  millis() + stime; 
  
  iteration = 1; 
  while(millis() < final_time)
  {
      interval_time = millis()+INTERVALTIME;  
      
      oneTime=0;      
      while(millis()<interval_time)
      {    
          if(oneTime<1)
          { 
              for(int i=0;i<N_SERVOS;i++)
              {
                  pos[i] = pos_old[i] + (iteration * increment[i]);
              }
              move_servo();
              iteration++;
              oneTime++;
          }
      }     
  }   

  for(int i=0;i<N_SERVOS;i++)
  {
    pos[i] = pos_new[i];
  }
}


void setup(void)
{
  Serial.begin(115200);
 
  S0.attach(PIN_TH);
  S1.attach(PIN_HL);
  S2.attach(PIN_HR);
  
  move_servo();
}


void loop()
{
  int move0[] = { 90, 90, 90 };
  int move1[] = { 90, 150, 150 };
  int move2[] = { 90, 30, 30 };

  float t = tempo_base;
  
  tempo_servo(t*2, move2);
  tempo_servo(t*2, move0);
  tempo_servo(t*2, move2);
  tempo_servo(t*2, move0);
  
  tempo_servo(t*2, move2);
  tempo_servo(t*2, move0);
  tempo_servo(t*2, move2);
  tempo_servo(t*2, move0);
  
  tempo_servo(t*4, move1);
  tempo_servo(t*4, move0);
  tempo_servo(t*4, move1);
  tempo_servo(t*4, move0);
}