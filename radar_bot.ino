#include<Servo.h> // import libarary for servo control

#define mA1 12   // A motor
#define mA2 11
#define mB1 10   // B motor
#define mB2 9
#define trigPin 7 // trigger pin of ultrasonic sensor
#define echoPin 6 // echo pin of ultrasonic sensor
#define ena 13 // enable pin of motor (pwm)
#define enb 8 // enable pin of motor (PWM)

Servo servo;// create servo object
long int duration, data; // duration ultrasonic wave and data received from serial device
int dist, vel, pos = 90,distl, distr; // distance, velocity, position of servo, left and right distance

void setup() // setup function
{
  servo.attach(5);// attach servo to pin 5
  pinMode(mA1, OUTPUT);
  pinMode(mA2, OUTPUT);
  pinMode(mB1, OUTPUT);
  pinMode(mB2, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  Serial.begin (9600); // begin serial communication at 9600 baud
}

int dist_check() // check distance using ultrasonic sensor
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  return ((duration / 2) / 29.1); // convert  time into  distance
}

void sensor_check() // check the data received from serial device and data from ultrasonic sensor
{

  if (Serial.available() > 0)
  {
    data = Serial.read();
  }
  // set the velocity of the bot to the respective data value
  if (data == '0') 
  {
    vel = 0;
  }
  else if (data == '1')
  {
    vel = 25;
  }
  else if (data == '2')
  {
    vel = 50;
  }
  else if (data == '3')
  {
    vel = 75;
  }
  else if (data == '4')
  {
    vel = 100 ;
  }
  else if (data == '5')
  {
    vel = 125;
  }
  else if (data == '6')
  {
    vel = 150;
  }
  else if (data == '7')
  {
    vel = 175;
  }
  else if (data == '8')
  {
    vel = 200;
  }
  else if (data == '9')
  {
    vel = 225;
  }
  else if (data == 'q')
  {
    vel = 255;
  }

  dist = dist_check();

// print the distance from ultrasonic sensor and data received from serial device
  Serial.print(dist);
  Serial.print(" cm ");
  Serial.println("data:" + data);
}
void for_left() // move the bot to forward left 
{
  Serial.println("Forward Left");
  analogWrite(ena, vel);
  analogWrite(enb, vel);
  digitalWrite(mA1, LOW);
  digitalWrite(mA2, HIGH);
  digitalWrite(mB1, HIGH);
  digitalWrite(mB2, LOW);
}
void right() // move the bot to forward right
{
  Serial.println("Right");
  analogWrite(ena, vel);
  analogWrite(enb, vel);
  digitalWrite(mA1, HIGH);
  digitalWrite(mA2, LOW);
  digitalWrite(mB1, LOW);
  digitalWrite(mB2, LOW);
}
void forward() // move the bot to forward
{
  Serial.println("Forward");
  analogWrite(ena, vel);
  analogWrite(enb, vel);
  digitalWrite(mA1, HIGH);
  digitalWrite(mA2, LOW);
  digitalWrite(mB1, HIGH);
  digitalWrite(mB2, LOW);
}
void backward() // move the bot to backward
{
  Serial.println("Backward");
  analogWrite(ena, vel);
  analogWrite(enb, vel);
  digitalWrite(mA1, LOW);
  digitalWrite(mA2, HIGH);
  digitalWrite(mB1, LOW);
  digitalWrite(mB2, HIGH);
}
void for_right() // move the bot to forward right
{
  Serial.println("Forward Right");
  analogWrite(ena, vel);
  analogWrite(enb, vel);
  digitalWrite(mA1, HIGH);
  digitalWrite(mA2, LOW);
  digitalWrite(mB1, LOW );
  digitalWrite(mB2, HIGH);
}
void left()// move the bot to left
{
  Serial.println("Left");
  analogWrite(ena, vel);
  analogWrite(enb, vel);
  digitalWrite(mA1, LOW);
  digitalWrite(mA2, LOW);
  digitalWrite(mB1, HIGH);
  digitalWrite(mB2, LOW);
}
void back_left() // move the bot to backward left
{
  Serial.println("Backward Left");
  analogWrite(ena, vel);
  analogWrite(enb, vel);
  digitalWrite(mA1, LOW);
  digitalWrite(mA2, HIGH);
  digitalWrite(mB1, HIGH);
  digitalWrite(mB2, LOW);
}
void back_right() // move the bot to backward right
{
  Serial.println("Forward Right");
  analogWrite(ena, vel);
  analogWrite(enb, vel);
  digitalWrite(mA1, HIGH);
  digitalWrite(mA2, LOW);
  digitalWrite(mB1, LOW);
  digitalWrite(mB2, HIGH);
}
void wait() // wait for the next command
{
  Serial.println("Stop");
  analogWrite(ena, vel);
  analogWrite(enb, vel);
  digitalWrite(mA1, LOW);
  digitalWrite(mA2, LOW);
  digitalWrite(mB1, LOW);
  digitalWrite(mB2, LOW);
}
void auto_mode() // auto mode
{
  if (dist_check() <= 15) // 
  {
    wait();
    delay(50);

    servo.write(0); // move the servo head to 0 degree (Right)
    delay(700);
    distr = dist_check(); // check the distance from ultrasonic sensor at 0 degree (Right)

    servo.write(180); // move the servo head to 180 degree (Left)
    delay(700);
    distl = dist_check(); // check the distance from ultrasonic sensor at 180 degree (Left)

    servo.write(90); // move the servo head to 90 degree (forward)
    delay(300);

    backward(); // move the bot to backward
    delay(200);

    // can use the same srvo ultrasonic combination to scan the distance for every angle ranging from 0 to 180 degree making it a radar

    if (distl >= distr) // compare the distance to move the vehicle in the larger proximity direction
    {
      while (dist <= 18) // move the bot to the left until the distance is greater than 18 cm
      {

        dist = dist_check();
        for_left();
      }
    }
    else
    {
      while (dist <= 18) // move the bot to the right until the distance is greater than 18 cm
      {
        dist = dist_check();
        for_right();
      }
    }
  }
  else // if no obstacle is detected, move the bot forward
  {
    forward();
  }
}

void manual_mode() // manual mode
{
  sensor_check(); // check the sensor data

  switch (data) // read the data from serial device and execute the corresponding command
  {
    case 'X':
      auto_mode();
      break;
    case 'x':
      manual_mode();
      break;
    case 'F':
      forward();
      break;
    case 'R':
      right();
      break;
    case 'B':
      backward();
      break;
    case 'L':
      left();
      break;
    case 'G':
      for_left();
      break;
    case 'I':
      for_right();
      break;
    case 'H':
      back_left();
      break;
    case 'J':
      back_right();
      break;
    case 'S':
      wait();
      break;
deafult:
      wait();
      break;
  }
}

void loop()
{
  manual_mode(); // can switch to auto mode by sending 'X' via bluetooth and to go back to manual mode by sending 'x'
}

// copilot is fun ;)