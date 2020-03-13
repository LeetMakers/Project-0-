#include <Servo.h>
#include <Pixy2.h>
#include <string.h>

Servo myservo;
Pixy2 pixy;  

int8_t i = 0;
char buf[128];

void setup()
{

    Serial.begin(115200);
    Serial.print("Starting...\n");
  
    myservo.attach(9);
  
    pinMode(2, OUTPUT);
    pinMode(3 , OUTPUT);
    pinMode(4 , OUTPUT);
    pinMode(5 , OUTPUT);
    
    //ENA pwm 
    pinMode(6, OUTPUT);
    //ENB pwm 
    pinMode(11, OUTPUT);

    // we need to initialize the pixy object
  pixy.init();
  // Change to line tracking program
  pixy.changeProg("line");
  
}

void go(int x)
{
     analogWrite(6, x);
     analogWrite(11, x);
 
    digitalWrite(2, LOW);   //BACK RIGHT
    digitalWrite(3, HIGH); //go   Right
  
    digitalWrite(4, LOW);//back  Leeft
    digitalWrite(5, HIGH); //go   Leeft
}


void back(int x)
{
     analogWrite(6, x);
     analogWrite(11, x);
 
    digitalWrite(2, HIGH);   //BACK RIGHT
    digitalWrite(3, LOW); //go   Right
  
    digitalWrite(4, HIGH);//back  Leeft
    digitalWrite(5, LOW); //go   Leeft
}

void stopp()
{
    analogWrite(6, 0);
    analogWrite(11, 0);
 
    digitalWrite(2, LOW);   //BACK RIGHT
    digitalWrite(3, LOW); //go   Right
  
    digitalWrite(4, LOW);//back  Leeft
    digitalWrite(5, LOW); //go   Leeft
}  

void turn(int x)
{
  myservo.write(x);
}

//pixy.line.vectors->m_x0   = a0
//pixy.line.vectors->m_x1   = b0
//pixy.line.vectors->m_y0   = a1
//pixy.line.vectors->m_y1   = b1
//pixy.line.vectors->m_index   = index
//pixy.line.vectors->m_flags   = flag

int x = 0;
int p = 0;


void loop() 
{
 turn(90);
 go(0);
 back(0);
 stopp();
 pixy.line.getMainFeatures();
 //pixy.line.vectors->print();


  
 //stabliser 

 if ((pixy.line.vectors->m_x0) != (39))
  {  
     if ((pixy.line.vectors->m_x0) <  (39 - 2))  
          {
            x = 39 - pixy.line.vectors->m_x0;
            x = abs(x);
            p = map(x, 0,39,0,90);
            Serial.print("turn(gauche) = ");
            Serial.println(p);
            stopp();
            turn(p);
          }
          
     else if ((pixy.line.vectors->m_x0) >  (39 + 2))  
          {
            x -= 39;
            x = abs(x);
            p = map(x,0,39,80,180);
            Serial.print("turn(  droite   ); = ");
            Serial.println(p);
            stopp();
            turn(p);
          }
     else if (  ((pixy.line.vectors->m_x0) >=  (39 - 2))  && ((pixy.line.vectors->m_x0) <=  (39 + 2)))
          {
            turn(90);
            go(120);
            Serial.println("turn(80);");
            
          }
  }


  
//go();
//  back(110);
//  delay(2000);
//  back(255);
//  delay(2000);
//  back(0);
//turn(90);
//delay(1000);
//turn(180);
//delay(1000);
//turn(0);
//delay(1000);




}
