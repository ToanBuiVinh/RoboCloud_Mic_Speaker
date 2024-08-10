/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Lib_Emotion.h"


#include <Servo.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SERVO_RIGHT 17 
#define SERVO_LEFT 16 
Servo servoMotor_Right;
Servo servoMotor_Left;


// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();

  servoMotor_Right.attach(SERVO_RIGHT);  // attaches the servo on ESP32 pin
  servoMotor_Left.attach(SERVO_LEFT);  // attaches the servo on ESP32 pin
}

uint8_t Action_Robot = 3; // 1,2,3,4
void loop() 
{
  if( Action_Robot == 1){
    display.drawBitmap(0, 0, smile, 128, 64, WHITE);
    display.display();
    for (int pos = 0; pos <= 45; pos += 1) {
      // in steps of 1 degree
      servoMotor_Right.write(pos);
      delay(15); // waits 15ms to reach the position
    }
  
    for (int pos = 45; pos >= 0; pos -= 1) {
      servoMotor_Right.write(pos);
      delay(15); // waits 15ms to reach the position
    }
    Action_Robot = 0;
  }
  if( Action_Robot == 2){
    display.drawBitmap(0, 0, talk, 128, 64, WHITE);
    display.display();    
    for (int pos = 0; pos <= 45; pos += 1) {
      // in steps of 1 degree
      servoMotor_Left.write(pos);
      delay(15); // waits 15ms to reach the position
    }
  
    for (int pos = 45; pos >= 0; pos -= 1) {
      servoMotor_Left.write(pos);
      delay(15); // waits 15ms to reach the position
    }
    Action_Robot = 0;
  }
  if( Action_Robot == 3){
    display.drawBitmap(0, 0, happy, 128, 64, WHITE);
    display.display();
    for (int pos = 0; pos <= 45; pos += 1) {
      // in steps of 1 degree
      servoMotor_Right.write(pos);
      servoMotor_Left.write(pos);
      delay(15); // waits 15ms to reach the position
    }
  
    for (int pos = 45; pos >= 0; pos -= 1) {
      servoMotor_Right.write(pos);
      servoMotor_Left.write(pos);
      delay(15); // waits 15ms to reach the position
    }    
    Action_Robot = 0;   
  }
  if( Action_Robot == 4){
    display.drawBitmap(0, 0, opened_eye, 128, 64, WHITE);
    display.display();
    Action_Robot = 0;    
  }
}
