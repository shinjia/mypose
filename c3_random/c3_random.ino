
    case 'b':
       for(int i=0; i<5; i++)
       {
         v1 = random(90-50, 90+50);
         v2 = random(90-80, 90+80);
         v3 = random(90-80, 90+80);
         vt = random(1, 4);
         for(int j=0; j<4; j++)
         {
           pos_now[0] = v1;
           pos_now[1] = v2;
           pos_now[2] = v3;
           tempo_servo(t*2, pos_now);
           pos_now[0] = 90;
           pos_now[1] = 90;
           pos_now[2] = 90;
           tempo_servo(t*2, pos_now);
         }
       }
       tempo_servo(t*2, new0);
       break;
       
    case 'c':
       for(int i=0; i<5; i++)
       {
         v1 = random(-50, +50);
         v2 = random(-80, +80);
         v3 = random(-80, +80);
         vt = random(1, 4);
         for(int j=0; j<2; j++)
         {
           pos_now[0] = 90+v1;
           pos_now[1] = 90+v2;
           pos_now[2] = 90+v3;
           tempo_servo(t*2, pos_now);
           pos_now[0] = 90;
           pos_now[1] = 90;
           pos_now[2] = 90;
           tempo_servo(t*2, pos_now);
         }
         for(int j=0; j<2; j++)
         {
           pos_now[0] = 90-v2;
           pos_now[1] = 90-v1;
           pos_now[2] = 90-v3;
           tempo_servo(t*2, pos_now);
           pos_now[0] = 90;
           pos_now[1] = 90;
           pos_now[2] = 90;
           tempo_servo(t*2, pos_now);
         }
       }
       tempo_servo(t*2, new0);
       break;
       
    case 'd':
       for(int i=0; i<5; i++)
       {
         u1 = random(-50, +50);
         u2 = random(-80, +80);
         u3 = random(-80, +80);
         v1 = random(-50, +50);
         v2 = random(-80, +80);
         v3 = random(-80, +80);
         
         for(int j=0; j<4; j++)
         {
           pos_now[0] = 90+u1;
           pos_now[1] = 90+u2;
           pos_now[2] = 90+u3;
           tempo_servo(t*2, pos_now);
           pos_now[0] = 90+v1;
           pos_now[1] = 90+v2;
           pos_now[2] = 90+v3;
           tempo_servo(t*2, pos_now);
         }
       }
       tempo_servo(t*2, new0);
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
  int pos_old[] = { 0, 0, 0, 0 };

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