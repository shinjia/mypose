//-- myPOSE calibration

int N_SERVOS = 3; // 伺服馬達的個數

// 參數：校正的位置 (要調整的角度)
int adj[]={ 0, 0, 0 };

// 參數：起始位置
int pos[]={ 90,90,90 };  // 起始位置

// TEMPO: 121 BPM
int tempo_base = 120;

#define INTERVALTIME 10.0 

// 參數：各伺服馬達的腳位
#define PIN_TH 4
#define PIN_HL 5
#define PIN_HR 6

#include <Servo.h>
Servo S0, S1, S2;


void help(void)
{
  Serial.println("This is used to calibration the servos for 'Otto'");
  Serial.println("The interface uses single character controls");
  Serial.println("");
  Serial.println("'0' - HOME");
  Serial.println("'1, 2, 3, 4, 5, 6' - MOVE");
  Serial.println("");
}


// 處理輸入的字元
void processChar(char c)
{
  int s = sizeof(pos);
  int new0[] = { 90,  90,  90 };
  int new1[] = { 90, 150,  30 };
  int new2[] = { 90,  30, 150 };
  int new3[] = { 90, 150, 150 };
  int new4[] = { 90,  30,  30 };
  int new5[] = { 40, 150,  30 };
  int new6[] = {140,  30, 150 };

  int t = tempo_base;
  switch(c)
  {
    case '0':
       tempo_servo(t*2, new0);
       break;
       
    case '1':
       tempo_servo(t*2, new1);
       break;

    case '2':
       tempo_servo(t*2, new2);
       break;
       
    case '3':
       tempo_servo(t*2, new3);
       break;
       
    case '4':
       tempo_servo(t*2, new4);
       break;
       
    case '5':
       tempo_servo(t*2, new5);
       break;
       
    case '6':
       tempo_servo(t*2, new6);
       break;
       
    case '7':
       tempo_servo(t*2, new6);
       tempo_servo(t*2, new0);
       break;
       
    case '8':
       tempo_servo(t*1, new6);
       tempo_servo(t*1, new0);
       break;
       
    case '9':
       tempo_servo(t*4, new6);
       tempo_servo(t*4, new0);
       break;
       
    case '\n':
    case '\r':
      break;
      
    default:
      Serial.print("Unknown command (");
      Serial.print(c);
      Serial.println(")");
      break;
  }
}


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
  
  help();
}


void loop()
{
  // 取得序列埠傳入的資料
  while(Serial.available() > 0)
  {
    processChar(Serial.read());
  }
  move_servo();
}