/////////////////////// Line Sensor Setup ////////////////////////
#define LINE_DETECT_WHITE  1  
int Missioin_flag[5]={0,};
int LineSensorPin[5] = {34,35,36,37,38};
int LineSensorPinData[5] = {0,};
int LineType = -1;
/////////////////////// Line Sensor Setup ////////////////////////

/////////////////////// Sonar Sensor Setup ////////////////////////
float sonar1_data =0.0;
#define ECHO 22
#define TRIG 23
/////////////////////// Sonar Sensor Setup ////////////////////////

//////////////////// L298 Motor Driver Setup //////////////////////
#define IN1 2
#define IN2 3
#define ENA 5
#define IN3 4
#define IN4 7
#define ENB 6
//////////////////// L298 Motor Driver Setup //////////////////////


void motor_control_l(int direction, int speed)
{
  switch(direction)
  {
    case 1: digitalWrite(IN1, LOW);
            digitalWrite(IN2, HIGH);
            analogWrite(ENA, 150); // 0-255까지 입력 
            break;

    case 0: digitalWrite(IN1, LOW);
            digitalWrite(IN2, LOW);
            analogWrite(ENA, 0);
            break;
     
    case -1: digitalWrite(IN1, HIGH);
             digitalWrite(IN2, LOW);
             analogWrite(ENA, 50);
             break;
  }
}
void motor_control_r(int direction, int speed)
{
  switch(direction)
  {
    case 1: digitalWrite(IN3, HIGH);
            digitalWrite(IN4, LOW);
            analogWrite(ENA, 50); // 0-255까지 입력 
            break;

    case 0: digitalWrite(IN3, LOW);
            digitalWrite(IN4, LOW);
            analogWrite(ENA, 0);
            break;
     
    case -1: digitalWrite(IN1, LOW);
             digitalWrite(IN2, HIGH);
             analogWrite(ENA, 50);
             break;
  }
}

int read_digital_line_sensor(void)
{
  int i;
  int sum = 0;
  for(i=0;i<5;i++)
  {
     if(LINE_DETECT_WHITE == 0)  //흰색 바탕에 검정색 라인
     {
       LineSensorPinData[i] = 1 - digitalRead(LineSensorPin[i]);
     }
     else
     {
       LineSensorPinData[i] =  digitalRead(LineSensorPin[i]);      
     }  
     sum += LineSensorPinData[i];   
  }

  if(sum == 5)
  {
     return sum;    
  }
  else if(sum == 2)
  {
     if( (LineSensorPinData[3] == 1) && (LineSensorPinData[4] == 1) ) return 3;
     if( (LineSensorPinData[2] == 1) && (LineSensorPinData[3] == 1) ) return 1;
     if( (LineSensorPinData[1] == 1) && (LineSensorPinData[2] == 1) ) return -1;
     if( (LineSensorPinData[0] == 1) && (LineSensorPinData[1] == 1) ) return -3;
  }
  else if(sum == 1)
  {
    if(LineSensorPinData[0] == 1) return -4;
    if(LineSensorPinData[1] == 1) return -2;
    if(LineSensorPinData[2] == 1) return  0;
    if(LineSensorPinData[3] == 1) return  2;
    if(LineSensorPinData[4] == 1) return  4;
  }
  else if(sum == 3)
  {
    return -10;
  } 
  else
  {
     return -5;
  }  
}

void send_serial_data(void)
{
   int i;
   for(i=0;i<5;i++)
   {
      Serial.print(LineSensorPinData[i]);
      Serial.print("  ");
   }
      Serial.print(LineType);      
      Serial.print("  ");
      Serial.println(sonar1_data);
}

float sonar(void)
{
  float duration =0.0;
  float distance = 0.0;
  digitalWrite(TRIG,LOW);
  digitalWrite(TRIG,HIGH);
  delay(10);
  digitalWrite(TRIG,LOW);

  duration = pulseIn(ECHO,HIGH);
  //Serial.println(duration);
  distance = duration * 340.0/(2.0*10000);
  //Serial.print(distance);  Serial.println(" cm");

  return distance;
}

void motor_control(int dir_A, int pwm_A , int dir_B, int pwm_B)
{
   if(dir_A == 0)
   {
     digitalWrite(IN1, 0);  digitalWrite(IN2, 0); 
     analogWrite(ENA,0);
   }
   else if(dir_A == 1)
   {
     digitalWrite(IN1, HIGH);  digitalWrite(IN2, LOW); 
     analogWrite(ENA,pwm_A);
   }
   else if(dir_A == -1)
   {
     digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH); 
     analogWrite(ENA,pwm_A);    
   }
   else
   {
     digitalWrite(IN1, 0);  digitalWrite(IN2, 0); 
     analogWrite(ENA,0);
   }

   if(dir_B == 0)
   {
     digitalWrite(IN3, 0);  digitalWrite(IN4, 0); 
     analogWrite(ENA,0);
   }
   else if(dir_B == 1)
   {
     digitalWrite(IN3, HIGH);  digitalWrite(IN4, LOW); 
     analogWrite(ENB,pwm_B);
   }
   else if(dir_B == -1)
   {
     digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH); 
     analogWrite(ENB,pwm_B);    
   }
   else                                
   {
     digitalWrite(IN3, 0);  digitalWrite(IN4, 0); 
     analogWrite(ENB,0);
   }
}

void robot_line_trace(void)
{
  switch(LineType)
  {

     case -4 :          
              motor_control(-1, 50 , 1, 120);
              break;            
             
     case -3 :
              motor_control(1, 59 , 1, 106);
              break;
     case -2 :
              motor_control(1, 60 , 1, 100);
              break;
     case -1 :
              motor_control(1, 70 , 1, 90);
              break;              
     case 0 :
              motor_control(1, 75 , 1, 80);
              break;                                                                                                                                                                                                                 
     case 1 :
              motor_control(1, 84 , 1, 75);
              break;
     case 2 :
              motor_control(1, 98 , 1, 68);
              break;
     case 3 :
              motor_control(1, 106 , 1, 59);
              break; 
     case 4 :
              motor_control(1, 120 , -1, 50);
              break;              

     case 5 : 
               motor_control(-1,30, -1,35);
               delay(500);
               motor_control(0, 0 , 0, 0);
               delay(1000);
               break;    
  }  
}
void setup() {
  // put your setup code here, to run once:
 int i;
 ///// line sensor setup /////
 for(i=0;i<5;i++)
 {
    pinMode(LineSensorPin[i], INPUT);
 }
 
 ///// sonar sensor setup /////
 pinMode(TRIG, OUTPUT);
 pinMode(ECHO, INPUT);
 Serial.begin(115200);
 
///// motor drive setup /////
 pinMode(IN1, OUTPUT);
 pinMode(IN2, OUTPUT);
 pinMode(IN3, OUTPUT);
 pinMode(IN4, OUTPUT);
 pinMode(ENA, OUTPUT);
 pinMode(ENB, OUTPUT); 
}
void robot_stop(void)
{
   motor_control(-1,30, -1,35);
   delay(100);
   motor_control(0, 0 , 0, 0);
   delay(3000);  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Missioin_flag[4]==0)
  {  

    LineType = read_digital_line_sensor();
    robot_line_trace();   
  //send_serial_data();
  }

  if((Missioin_flag[0]==1) && (Missioin_flag[1]==0) && (Missioin_flag[2]==0) && (Missioin_flag[3]==0) && (Missioin_flag[4]==0) )
  {   
    if(LineType == 5) 
    {

      Missioin_flag[1] = 1;
      robot_stop();   
    }
  }

  if( (Missioin_flag[0]==1) && (Missioin_flag[1]==1) && (Missioin_flag[2]==0) && (Missioin_flag[3]==0)&& (Missioin_flag[4]==0) )
  {  
    if(LineType == 5) 
    {
    
      Missioin_flag[2] = 1;
    }
  }
  
  if( (Missioin_flag[0]==1) && (Missioin_flag[1]==1) && (Missioin_flag[2]==1) && (Missioin_flag[3]==0)&& (Missioin_flag[4]==0) )
  {  
    sonar1_data = sonar();
    if(sonar1_data < 10.0)
    {
        robot_stop();
    }   
    if(LineType == 6) 
    {
      Missioin_flag[3]=1;
    }       
  }  

  if( (Missioin_flag[0]==1) && (Missioin_flag[1]==1) && (Missioin_flag[2]==1) && (Missioin_flag[3]==1)&& (Missioin_flag[4]==0) )
  { 
     if(LineType == 5)
     {
        robot_stop(); 
        Missioin_flag[4]=1;    
     }
  }  
  // put your main code here, to run repeatedly:
  
  sonar1_data = sonar();
  LineType = read_digital_line_sensor();
  send_serial_data();

     
}
