//-- myPOSE calibration

// 參數：校正的位置 (要調整的角度)
int adj[]={ 0, 0, 0 };  // 此程式不能改這值

// 參數：起始位置
int pos[]={ 90,90,90 };  // 起始位置


// 參數：各伺服馬達的腳位
#define PIN_TH 4
#define PIN_HL 5
#define PIN_HR 6

#include <Servo.h>
Servo S0, S1, S2, S3;


void help()
{
  Serial.println("This is used to calibration the servos for 'Otto'");
  Serial.println("The interface uses single character controls");
  Serial.println("");
  Serial.println("'4' - add value of TH");
  Serial.println("'r' - minus value of TH");
  Serial.println("'d' - add value of HL");
  Serial.println("'c' - minus value of HL");
  Serial.println("'f' - add value of HR");
  Serial.println("'v' - minus value of HR");
  Serial.println("");
}


void show_message()
{ 
  Serial.print("Adjust: "); 
  Serial.print(adj[0]);
  Serial.print(",");
  Serial.print(adj[1]);
  Serial.print(",");
  Serial.print(adj[2]);
  Serial.print(",");
}


// 處理輸入的字元
void processChar(char c)
{
  // see if the first char is a number or a command char

  switch(c)
  {
    case 'h':
    case 'H':
      help();
      break;
      
    case '4':
      adj[0]++;
      break;
      
    case 'r':
    case 'R':
      adj[0]--;
      break;
      
    case 'd':
    case 'D':
      adj[1]++;
      break;
      
    case 'c':
    case 'C':
      adj[1]--;
      break;
      
    case 'f':
    case 'F':
      adj[2]++;
      break;
      
    case 'v':
    case 'V':
      adj[2]--;
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
  show_message();
}


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