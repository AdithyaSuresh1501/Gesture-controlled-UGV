
#include <SPI.h>      //SPI library for communicate with the nRF24L01+
#include "RF24.h"     
#include <AFMotor.h>

//Define enable pins of the Motors
const int enbA = 3;
const int enbB = 5;
AF_DCMotor motor1(4);
AF_DCMotor motor2(3);



//Define packet for the direction (X axis and Y axis)
int data[2];

//Define object from RF24 library - 9 and 10 are a digital pin numbers to which signals CE and CSN are connected
RF24 radio(9,10);

//Create a pipe addresses for the communicate
const uint64_t pipe = 0xE8E8F0F0E1LL;

void setup(){
  
  motor1.setSpeed(200);
  motor1.run(RELEASE);
  motor2.setSpeed(200);
  motor2.run(RELEASE);

  
  Serial.begin(9600);
  radio.begin();                    //Start the nRF24 communicate            
  radio.openReadingPipe(1, pipe);   //Sets the address of the transmitter to which the program will receive data.
  radio.startListening();             
  }

void loop(){
  uint8_t i;
  if (radio.available()){
    radio.read(data, sizeof(data));

  


    if(data[0] > 380){
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  // Accelerate from zero to maximum speed
  for (i=0; i<255; i++) 
  {
    motor1.setSpeed(i);
    motor2.setSpeed(i);  

  }
    }
    
    if(data[0] < 310){
      //backward              
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  
  // Accelerate from zero to maximum speed
  for (i=0; i<255; i++) 
  {
    motor1.setSpeed(i);
    motor2.setSpeed(i);   
  
  }
    }
     
    if(data[1] > 180){
      //left
 motor1.run(FORWARD);
 motor2.run(BACKWARD);
   for (i=0; i<255; i++) 
  {
    motor1.setSpeed(i);
    motor2.setSpeed(i);   
  
  }
    }

    if(data[1] < 110){
      //right
 motor1.run(BACKWARD);
 motor2.run(FORWARD);
   for (i=0; i<255; i++) 
  {
    motor1.setSpeed(i);
    motor2.setSpeed(i);   
   
    }}

    if(data[0] > 330 && data[0] < 360 && data[1] > 130 && data[1] < 160){
      //stop car
     motor1.setSpeed(200);
     motor1.run(RELEASE);
     motor2.setSpeed(200);
     motor2.run(RELEASE);
    }
  }
}
