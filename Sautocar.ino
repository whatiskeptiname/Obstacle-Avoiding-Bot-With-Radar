#define mA1 12   // A motor
#define mA2 11
#define mB1 10   // B motor
#define mB2 9
#define trigPin 7
#define echoPin 6
#define IR1 5
#define IR2 4
#define ena 13
#define enb 8
#include<Servo.h>
Servo servo;
long int dist, duration, IRs1, IRs2, data, vel, pos = 90, distl, distr;

void setup()
{
  servo.attach(5);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(mA1, OUTPUT);
  pinMode(mA2, OUTPUT);
  pinMode(mB1, OUTPUT);
  pinMode(mB2, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  Serial.begin (9600);
}

void music()
{
  tone(23, 1000);
  delay(100);
  tone(23, 2000);
  delay(100);
  tone(23, 3000);
  delay(100);
  tone(23, 4000);
  delay(100);
  tone(23, 5000);
  delay(100);
}

int dist_check()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  // convert  time into  distance

  return ((duration / 2) / 29.1);
}

void sensor_check()
{

  if (Serial.available() > 0)
  {
    data = Serial.read();
  }
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

  IRs1 = digitalRead(IR1);
  IRs2 = digitalRead(IR2);

  dist = dist_check();

  Serial.print(dist);
  Serial.print(" cm IR state: ");
  Serial.print(IRs1);
  Serial.print(",");
  Serial.print(IRs2);
  Serial.println();
  Serial.println(data);
}
void for_left()
{
  Serial.println("Forward Left");
  analogWrite(ena, vel);
  analogWrite(enb, vel);
  digitalWrite(mA1, LOW);
  digitalWrite(mA2, HIGH);
  digitalWrite(mB1, HIGH);
  digitalWrite(mB2, LOW);
}
void right()
{
  Serial.println("Right");
  analogWrite(ena, vel);
  analogWrite(enb, vel);
  digitalWrite(mA1, HIGH);
  digitalWrite(mA2, LOW);
  digitalWrite(mB1, LOW);
  digitalWrite(mB2, LOW);
}
void forward()
{
  Serial.println("Forward");
  analogWrite(ena, vel);
  analogWrite(enb, vel);
  digitalWrite(mA1, HIGH);
  digitalWrite(mA2, LOW);
  digitalWrite(mB1, HIGH);
  digitalWrite(mB2, LOW);
}
void backward()
{
  Serial.println("Backward");
  analogWrite(ena, vel);
  analogWrite(enb, vel);
  digitalWrite(mA1, LOW);
  digitalWrite(mA2, HIGH);
  digitalWrite(mB1, LOW);
  digitalWrite(mB2, HIGH);
}
void for_right()
{
  Serial.println("Forward Right");
  analogWrite(ena, vel);
  analogWrite(enb, vel);
  digitalWrite(mA1, HIGH);
  digitalWrite(mA2, LOW);
  digitalWrite(mB1, LOW );
  digitalWrite(mB2, HIGH);
}
void left()
{
  Serial.println("Left");
  analogWrite(ena, vel);
  analogWrite(enb, vel);
  digitalWrite(mA1, LOW);
  digitalWrite(mA2, LOW);
  digitalWrite(mB1, HIGH);
  digitalWrite(mB2, LOW);
}
void back_left()
{
  Serial.println("Backward Left");
  analogWrite(ena, vel);
  analogWrite(enb, vel);
  digitalWrite(mA1, LOW);
  digitalWrite(mA2, HIGH);
  digitalWrite(mB1, HIGH);
  digitalWrite(mB2, LOW);
}
void back_right()
{
  Serial.println("Forward Right");
  analogWrite(ena, vel);
  analogWrite(enb, vel);
  digitalWrite(mA1, HIGH);
  digitalWrite(mA2, LOW);
  digitalWrite(mB1, LOW);
  digitalWrite(mB2, HIGH);
}
void wait()
{
  Serial.println("Stop");
  analogWrite(ena, vel);
  analogWrite(enb, vel);
  digitalWrite(mA1, LOW);
  digitalWrite(mA2, LOW);
  digitalWrite(mB1, LOW);
  digitalWrite(mB2, LOW);
}
void AI()
{
  if (dist_check() <= 15)
  {
    wait();
    delay(50);

    servo.write(0);
    delay(700);
    distr = dist_check();

    servo.write(180);
    delay(700);
    distl = dist_check();

    servo.write(90);
    delay(300);

    backward();
    delay(200);

    if (distl >= distr)
    {
      while (dist <= 18)
      {

        dist = dist_check();
        for_left();
      }
    }
    else
    {
      while (dist <= 18)
      {
        dist = dist_check();
        for_right();
      }
    }
  }
  else
  {
    forward();
  }
}

void manual()
{
  sensor_check();

  switch (data)
  {
    case 'X':
      AI();
      break;
    case 'x':
      manual();
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
  manual();
}
