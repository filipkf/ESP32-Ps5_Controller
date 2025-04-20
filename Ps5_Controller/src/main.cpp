#include <Arduino.h>
#include <ps5Controller.h>
#include <ESP32Servo.h>


int channel_1 = 13; // arbitary number
int channel_2 = 14;
int in_1 = 12;
int in_2 = 14;
int frequency = 1000;
int resolution = 7;
unsigned long lastTimeStamp = 0;
Servo servo;
int servo_pin = 18;


void handleLStickY(int speed) {
  if(speed > 0) {
    ledcWrite(channel_1, speed);
  } else {
    ledcWrite(channel_2, abs(speed));
  }
}

void handleR2Value(int value) {
  int val = map(value, 0, 255, 0, 170); // in_min, in_max, out_min, out_max
  servo.write(180-val);
}

void notify()
{
  // digitalWrite(led1, ps5.Left());
  // digitalWrite(led2, ps5.Down());
  // digitalWrite(led3, ps5.Right());
  // digitalWrite(led4, ps5.Up()); 

  // digitalWrite(led5, ps5.Square());
  // digitalWrite(led6, ps5.Cross());
  // digitalWrite(led7, ps5.Circle());
  // digitalWrite(led8, ps5.Triangle());
  handleLStickY(ps5.LStickY());
  handleR2Value(ps5.R2Value());

  char messageString[200];
  sprintf(messageString, "%4d,%4d,%4d,%4d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d",
  ps5.LStickX(),
  ps5.LStickY(), // Left track
  ps5.RStickX(),
  ps5.RStickY(), // Right track
  ps5.Left(), // Rotate whole crane left
  ps5.Down(), // First arm down
  ps5.Right(), // Rotate whole crane right
  ps5.Up(), // First arm up
  ps5.Square(), // Rotate claw left
  ps5.Cross(), // Second arm down
  ps5.Circle(), // Rotate claw right
  ps5.Triangle(), // Second arm up
  ps5.L1(), // Rotate claw up
  ps5.R1(),
  ps5.L2Value(),
  ps5.R2Value(), // Rotate claw down
  ps5.Share(),
  ps5.Options(),
  ps5.PSButton(),
  ps5.Touchpad(),
  ps5.Charging(),
  ps5.Audio(),
  ps5.Mic(),
  ps5.Battery());

  //Only needed to print the message properly on serial monitor. Else we dont need it.
  if (millis() - lastTimeStamp > 50)
  {
    Serial.println(messageString);
    lastTimeStamp = millis();
  }
}

void onConnect()
{
  Serial.println("Connected!.");
}

void onDisConnect()
{
  Serial.println("Disconnected!.");    
}

void setUpPinModes()
{
  ledcSetup(channel_1, frequency, resolution);
  ledcAttachPin(in_1, channel_1);
  pinMode(in_1,OUTPUT);

  ledcSetup(channel_2, frequency, resolution);
  ledcAttachPin(in_2, channel_2);
  pinMode(in_2,OUTPUT);

  pinMode(servo_pin,OUTPUT);
}

void setupServo(){
  servo.setPeriodHertz(50);    // standard 50 hz servo
	servo.attach(servo_pin, 500, 2400);
}

void setup() 
{
  setUpPinModes();
  setupServo();
  Serial.begin(115200);
  ps5.attach(notify);
  ps5.attachOnConnect(onConnect);
  ps5.attachOnDisconnect(onDisConnect);
  ps5.begin("ac:36:1b:2e:ad:e5");
  while (ps5.isConnected() == false) 
  { 
    Serial.println("PS5 controller not found");
    delay(300);
  } 
  Serial.println("Ready.");
  delay(3000);

}

void loop() 
{

}



// För att komma ihåg syntax

// unsigned long lastTimeStamp = 0;
// void notify()
// {
//   char messageString[200];
//   sprintf(messageString, "%4d,%4d,%4d,%4d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d",
//   ps5.LStickX(),
//   ps5.LStickY(),
//   ps5.RStickX(),
//   ps5.RStickY(),
//   ps5.Left(),
//   ps5.Down(),
//   ps5.Right(),
//   ps5.Up(),
//   ps5.Square(),
//   ps5.Cross(),
//   ps5.Circle(),
//   ps5.Triangle(),
//   ps5.L1(),
//   ps5.R1(),
//   ps5.L2(),
//   ps5.R2(),  
//   ps5.Share(),
//   ps5.Options(),
//   ps5.PSButton(),
//   ps5.Touchpad(),
//   ps5.Charging(),
//   ps5.Audio(),
//   ps5.Mic(),
//   ps5.Battery());

//   //Only needed to print the message properly on serial monitor. Else we dont need it.
//   if (millis() - lastTimeStamp > 50)
//   {
//     Serial.println(messageString);
//     lastTimeStamp = millis();
//   }
// }
