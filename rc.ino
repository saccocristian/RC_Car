#include <ESP32Servo.h>

#define PIN_JSERVO    34
#define PIN_JMOTOR    35

#define PIN_SERVO     13

#define EN_A          14
#define IN1           27
#define IN2           26

//Servo
  Servo servo;
  int motor_speed;
// L298n
  // Setting PWM properties
  const int freq = 30000;
  const int pwmChannel = 0;
  const int resolution = 8;
  int dutyCycle = 200;

void setup() {
  Serial.begin(115200);
  //Joystick
  pinMode(PIN_JSERVO,INPUT);
  pinMode(PIN_JMOTOR,INPUT);
  
  //servo
  servo.attach(PIN_SERVO);
  servo.write(0);

  //l298n
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN_A, OUTPUT);
  motor_speed = 0;

}

void loop() {
  //lettura valori joystick
  int servoInput = analogRead(PIN_JSERVO);
  int motorInput = analogRead(PIN_JMOTOR);
    
  //servo
  int servoPosition = map(servoInput,0,4095,0,270);
  servo.write(servoPosition);

  //L298N
  if (motorInput < 400){     //Rotating the left motor in clockwise direction
    motor_speed = map(motorInput, 400, 0, 0, 255);   //Mapping the values to 0-255 to move the motor
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(EN_A, motor_speed);
  }
  else if (motorInput>400 && motorInput <600){  //Motors will not move when the joystick will be at center
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  } 
  else if (motorInput > 600){    //Rotating the left motor in anticlockwise direction
    motor_speed = map(motorInput, 600, 1023, 0, 255);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(EN_A, motor_speed);
  }
  
}
