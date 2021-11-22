/*Robotek I, robort arm with 360 rotating base: multipurpose robort 
Design and development by sTek web: www.stekdigital.com IG: @stekdigital */
#include <IRremote.h>
#include <IRremoteInt.h>

#include <Wire.h>
#include <Servo.h>
#include <Stepper.h>

#include <LiquidCrystal.h>

//stepper
int Pin0 = 8;//definition digital 8 pins as pin to control the IN1 (ULN24L01)
int Pin1 = 9;//definition digital 9 pins as pin to control the IN2 (ULN24L01)
int Pin2 = 10;//definition digital 10 pins as pin to control the IN3 (ULN24L01)
int Pin3 = 11;//definition digital 11 pins as pin to control the IN4 (ULN24L01)

int _step = 128; //512
int _speed = 1; 
int dir;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // LCD screen setup RS,E,D4,D5,D6,D7
int RECV_PIN=5;                         //IR pin
IRrecv irrecv(RECV_PIN);
decode_results results ;
Servo myservo;
int angle = 0;          //setup angle 

void setup()
{
  lcd.begin(16, 2);     //LCD 16*2

  // Initialize Serial
  Serial.begin(9600);
  Serial.println("Tek Robotics");

//stepper
  pinMode(Pin0, OUTPUT);//Set digital 8 port mode, the OUTPUT for the output
  pinMode(Pin1, OUTPUT);//Set digital 9 port mode, the OUTPUT for the output
  pinMode(Pin2, OUTPUT);//Set digital 10 port mode, the OUTPUT for the output
  pinMode(Pin3, OUTPUT);//Set digital 11 port mode, the OUTPUT for the output
  
  myservo.attach(13);    //Servo pin
  myservo.write(angle); //write servo value=0
  irrecv.enableIRIn();  // enable IR

  lcd.setCursor(0, 0);  //this is a loading bar, not a nice code...but work:)
  lcd.print("Betoltes..."); //print the text

  Serial.println("TekRobotics...");
  
  delay(800);
  lcd.clear();
  lcd.print("Betoltes>");

  Serial.println("TekRobotics>");
  
  delay(400);
  lcd.clear();
  lcd.print("Betoltes>>");

  Serial.println("TekRobotics>>");
  
  delay(400);
  lcd.clear();
  lcd.print("Betoltes>>>");

  Serial.println("TekRobotics>>>");
  
  delay(400);
  lcd.clear();
  lcd.print("Betoltes>>>>");

  Serial.println("TekRobotics>>>>");
  
  delay(400);
  lcd.clear();
  lcd.print("Betoltes>>>>>");

  Serial.println("TekRobotics>>>>>");
  
  delay(400);
  lcd.clear();
  lcd.print("Betoltes>>>>>>");

  Serial.println("TekRobotics>>>>>>");
  
  delay(400);
  lcd.clear();
  lcd.print("Betoltes>>>>>>>");

  Serial.println("TekRobotics>>>>>>>>");
  
  delay(400);
  lcd.clear();
  lcd.print("Motor angle:");  //print the text
  lcd.setCursor(0, 1);        //set cursor 2. line
  lcd.print(angle);           //print the servo value

  Serial.println("Motor angle: ");
  Serial.print(angle);
}

void loop()
{
//  stepp();
   if(irrecv.decode(&results))    //read ir code
  {
   translateIR();
   myservo.write(angle);

    if (angle>180)      //when servo angle value max print maximum text
   {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Motor angle:");
    Serial.println("Motor angle:");
    lcd.setCursor(0, 1);
    lcd.print("Maximum angle");
    Serial.println("Maximum zog");
    angle = 190;
   }
    else if (angle<0)   //when servo angle value min print minimum text
   {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Motor angle:");
    Serial.println("Motor angle:");
    lcd.setCursor(0, 1);
    lcd.print("Minimum angle");
    Serial.print("Minimum angle");
    angle = -10;
   }
     else               //print servo angle value
     {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Motor angle:");
    Serial.println("Motor angle:");
    lcd.setCursor(0, 1);
    lcd.print(angle);
    Serial.print(angle);
     }
   irrecv.resume();
  }
}
 void translateIR()     //
 {
   switch(results.value) {
     case 0xFFE01F:  //- button
                        dir = 1;
                        break;
    case 0xFFA857:  //+ button
                        dir = 0;
                        break;
    case 0xFF6897:  //0 button
    angle = 0;      //set angle minimum value
    break;
     
    case 0xFF30CF:  //1 button
  angle = angle + 10; //increase angle value
    break;
    
    case 0xFF18E7:  //2 button
  angle = angle -10;  //decrease angle value
    break;
     
     case 0xFF7A85: //3 button
  angle = 180;      //set angle maximum value
    break;

     case 0xFF10EF: //4 button
                        Speed(15);//Stepper motor speed = 15 fast (note:speed from 1 to 15)
                        if(dir==0){
                          Step(36);//Stepper motor forward 512 steps ---- 360 angle  
                        }else{
                          Step(-36);//Stepper motor backward 512 steps ---- 360 angle
                        }   
                        break;

      case 0xFF38C7: //5 button
                        Speed(15);//Stepper motor speed = 15 fast (note:speed from 1 to 15)
                        if(dir==0){
                          Step(64);//Stepper motor forward 1024 steps ---- 2*360 angle 
                        }else{
                          Step(-64);//Stepper motor backward 1024 steps ---- 2*360 angle
                        }
                        break;

      case 0xFF5AA5: //6 button
                       Speed(15);//Stepper motor speed = 15 fast (note:speed from 1 to 15)
                        if(dir==0){
                          Step(128);//Stepper motor forward 1536 steps ---- 3*360 angle
                        }else{
                          Step(-128);//Stepper motor backward 1536 steps ---- 3*360 angle 
                        }
                        break;

       case 0xFF42BD: //7 button
                        Speed(15);//Stepper motor speed = 15 fast (note:speed from 1 to 15)
                        if(dir==0){
                          Step(256);//Stepper motor forward 2048 steps ---- 4*360 angle
                        }else{
                          Step(-256);//Stepper motor backward 2048 steps ---- 4*360 angle
                        }
                        break;

        case 0xFF4AB5: //8 button
                        Speed(15);//Stepper motor speed = 15 fast (note:speed from 1 to 15)
                        if(dir==0){
                          Step(64);//Stepper motor forward 2560 steps ---- 5*360 angle
                        }else{
                          Step(-64);//Stepper motor backward 2560 steps ---- 5*360 angle
                        }
                        break;

        case 0xFF52AD: //9 button
                        Speed(15);//Stepper motor speed = 15 fast (note:speed from 1 to 15)
                        if(dir==0){
                          Step(16);//Stepper motor forward 3072 steps ---- 6*360 angle 
                        }else{
                          Step(-16);//Stepper motor backward 3072 steps ---- 6*360 angle
                        }
                        break;

        case 0xFF906F: //EQ button
                        Speed(15);//Stepper motor speed = 15 fast (note:speed from 1 to 15)
                        if(dir==0){                      
                          Step(8);//Stepper motor forward 3584 steps ---- 7*360 angle 
                        }else{
                          Step(-8);//Stepper motor backward 3584 steps ---- 7*360 angle 
                        }
                        break;

        case 0xFF9867: //100+ button
                        Speed(15);//Stepper motor speed = 15 fast (note:speed from 1 to 15)
                        if(dir){
                        Step(4);//Stepper motor forward 4096 steps ---- 8*360 angle
                        }else{
                        Step(-4);//Stepper motor backward 4096 steps ---- 8*360 angle
                        }
                        break;

        case 0xFFB04F: //200+ button
                        Speed(15);//Stepper motor speed = 15 fast (note:speed from 1 to 15)
                        if(dir==0){
                        Step(2);//Stepper motor forward 4608 steps ---- 9*360 angle  
                        }else{
                        Step(-2);//Stepper motor backward 4608 steps ---- 9*360 angle 
                        }
                        break;

      default :
             Step(0);   //Stepper motor stop
             break;
    }
 }
 void  stepperr()
 {
   
  }
  void Speed(int stepperspeed)//set Stepper speed 
{
    _speed = 15 - stepperspeed;
    if( _speed<1){
     _speed = 1;
    }
    if( _speed>15){
     _speed = 15;
    }
}
void Step(int _step)//Stepper motor rotation
{
  if(_step>=0){  // Stepper motor forward
    for(int i=0;i<_step;i++){   
      setStep(1, 0, 0, 1);
      delay(_speed); 
      setStep(1, 0, 0, 0);
      delay(_speed);
      setStep(1, 1, 0, 0);
      delay(_speed);
      setStep(0, 1, 0, 0);
      delay(_speed);
      setStep(0, 1, 1, 0);
      delay(_speed);
      setStep(0, 0, 1, 0);
      delay(_speed);
      setStep(0, 0, 1, 1);
      delay(_speed); 
      setStep(0, 0, 0, 1);
      delay(_speed);
    }
  }else{ // Stepper motor backward
     for(int i=_step;i<0;i++){  
      setStep(0, 0, 0, 1);
      delay(_speed);
      setStep(0, 0, 1, 1);
      delay(_speed);
      setStep(0, 0, 1, 0);
      delay(_speed);
      setStep(0, 1, 1, 0);
      delay(_speed);
      setStep(0, 1, 0, 0);
      delay(_speed);
      setStep(1, 1, 0, 0);
      delay(_speed);
      setStep(1, 0, 0, 0);
      delay(_speed);
      setStep(1, 0, 0, 1);
      delay(_speed);
    }
   }
}
void setStep(int a, int b, int c, int d)  
{  
    digitalWrite(Pin0, a);     
    digitalWrite(Pin1, b);     
    digitalWrite(Pin2, c);     
    digitalWrite(Pin3, d);     
}     
