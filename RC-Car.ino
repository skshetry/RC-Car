#include <stdlib.h>
#include <math.h>
//#include <SoftwareSerial.h>

//SoftwareSerial mySerial(9,10); // RX, TX

#define BTSTATE 0

#ifndef DEBUG_MODE
#define DEBUG_MODE 0
#endif

class Motor{
  
  /* 
          MOTOR_MOTOR_PIN1 ------------> IN1/IN3
          MOTOR_MOTOR_PIN2 ------------> IN2/IN4
          ENABLE_MOTOR_MOTOR_PIN ------------> enableMOTOR_MOTOR_PIN
             __    __    __
          __|  |__|  |__|  |__  Pulse Width Modulation PWM (here 'pulsewm' variable)
  */
    
    int MOTOR_PIN1,MOTOR_PIN2, ENABLE_MOTOR_PIN;
    int pulsewm;
   // char state; //get state 0 for reverse, 1 to stopped and 2 for forward states.
    
  public:
    Motor(int moPin1,int moPin2,int enPin): MOTOR_PIN1(moPin1), MOTOR_PIN2(moPin2), ENABLE_MOTOR_PIN(enPin) 
                                                    {}
                                                      
    void forward(int s); // driving motor forward logic
    void reverse2(int s); // driving motor reverse logic
    void reverse(int s);
    void stopMo(); //Stop the motor
    
    void  left(int s);
    void right(int s);

   /* void getState(){
      ///TODO: Don't use this API. In implementation Phase. State representation may change in future.
      Serial.println("Be cautious when working with this API. May change in future"); 
      return this->state;
    }*/
};

void Motor::left(int s){
  forward(s);
}

void Motor::right(int s){
  reverse(s);
}

void Motor::forward(int s){
  ///TODO this->state = 2;
  digitalWrite(this->MOTOR_PIN1,HIGH); 
  digitalWrite(this->MOTOR_PIN2, LOW);
  analogWrite(this->ENABLE_MOTOR_PIN, s);
 // if(DEBUG_MODE) Serial.println("Forward"); 
  ///TODO delay(100);                      
}
void Motor::reverse(int s){
  ///TODO this->state = 2;
  digitalWrite(this->MOTOR_PIN1, LOW); 
  digitalWrite(this->MOTOR_PIN2,HIGH);
  analogWrite(this->ENABLE_MOTOR_PIN, s);
 // if(DEBUG_MODE) Serial.println("Forward"); 
  ///TODO delay(100);                      
}
        
void Motor::reverse2(int s){
  ///TODO this->state = 2;
  digitalWrite(this->MOTOR_PIN1,HIGH); 
  digitalWrite(this->MOTOR_PIN2, LOW);
  analogWrite(this->ENABLE_MOTOR_PIN, s);
 // if(DEBUG_MODE) Serial.println("Forward"); 
  ///TODO delay(100);                      
}

inline void Motor::stopMo(){
  //this->state = 1; // Remove this in future if not needed
  digitalWrite(this->MOTOR_PIN1, LOW);
  digitalWrite(this->MOTOR_PIN2, LOW);
  analogWrite(this->ENABLE_MOTOR_PIN, 0);
 // if(DEBUG_MODE) Serial.println("Stop");

}

 Motor motor1(2, 4, 3), motor2(9, 8 , 5);

 char state;
 int i = 0;
 
/*class Car{
  
};*/

void setup() {
  
  Serial.begin(9600);
  //mySerial.begin(9600);
  pinMode(13,OUTPUT);
}

void loop() {
  
  if(digitalRead(BTSTATE)==LOW) { state='S'; }
  
  // Check incoming data and set it to variable
  if (Serial.available()){
    state = Serial.read(); 
    Serial.println(state);   
  }
  int vSpeed = 150;
  
  // Change speed
  if (state == '0'){
    vSpeed = 0;
  }
  else if (state == '1'){
    vSpeed = 75;
  }
  else if (state == '2'){
    vSpeed = 150;
  }
  else if(state == '3'){
    vSpeed = 200;
  }
  else if(state == '4'){
    vSpeed = 255;
  }

  // change direction
  if (state == 'F'){
    motor2.forward(vSpeed);
    motor1.stopMo();
  }
  else if (state == 'G'){
  motor2.forward(vSpeed);
  motor1.left(vSpeed);
  }
  else if (state == 'I'){
    motor2.forward(vSpeed);
    motor1.right(vSpeed);
  }
  else if (state == 'L'){
    motor2.stopMo();
    motor1.left(vSpeed);
  }
  else if (state == 'R'){
    motor2.stopMo();
    motor1.right(vSpeed);
  }
  else if (state == 'B'){
    motor2.reverse(vSpeed);
    motor1.stopMo();
  }
  else if (state == 'H'){
    motor2.reverse(vSpeed);
    motor1.left(vSpeed);
  }
   else if (state == 'J'){
    motor2.reverse(vSpeed);
    motor1.right(vSpeed);
  }
   else if (state == 'S'){
    motor2.stopMo();
    motor1.stopMo();
  }
  else if(state == 'W'){
    if (i == 0){
    digitalWrite(13, HIGH);}
    else if (i == 1){
      digitalWrite(13, LOW);
    }
  }
  else if (state == 'V'){
    exit(0);
  }

}
