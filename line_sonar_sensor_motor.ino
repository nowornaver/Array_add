/////////////////////// Line Sensor Setup ////////////////////////
#define LINE_DETECT_WHITE  1  
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
            analogWrite(ENA, speed); // 0-255까지 입력 
            break;

    case 0: digitalWrite(IN1, LOW);
            digitalWrite(IN2, LOW);
            analogWrite(ENA, 0);
            break;
     
    case -1: digitalWrite(IN1, HIGH);
             digitalWrite(IN2, LOW);
             analogWrite(ENA, speed);
             break;
  }
}
void motor_control_r(int direction, int speed)
{
  switch(direction)
  {
    case 1: digitalWrite(IN3, HIGH);
            digitalWrite(IN4, LOW);
            analogWrite(ENA, speed); // 0-255까지 입력 
            break;

    case 0: digitalWrite(IN3, LOW);
            digitalWrite(IN4, LOW);
            analogWrite(ENA, 0);
            break;
     
    case -1: digitalWrite(IN1, LOW);
             digitalWrite(IN2, HIGH);
             analogWrite(ENA, speed);
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
//// motor drive setup //////
 pinMode(IN1, OUTPUT);
 pinMode(IN2, OUTPUT);
 pinMode(IN3, OUTPUT);
 pinMode(IN4, OUTPUT);
 pinMode(ENA, OUTPUT);
 pinMode(ENB, OUTPUT); 

 while(read_digital_line_sensor()!=5)
 {
  Serial.println("Wait!");
 }
 Serial.println("Start Line!");
 Missioin_flag[0] = 1;
 delay(1000);
 motor_control(1, 50 , 1, 45);
 delay(200); 
}


void loop() {
  // put your main code here, to run repeatedly:
  
  sonar1_data = sonar();
  LineType = read_digital_line_sensor();
  send_serial_data();
  motor_control(1,50,-1,30);
  motor_control_l(1,50);
     
}
