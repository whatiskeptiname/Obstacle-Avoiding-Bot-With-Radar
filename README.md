# Obstacle-Avoiding-Bot-With-Radar

Obstacle-Avoiding-Bot-With-Radar is a simple Arduino-based bot, it uses ultrasonic sensor combined with servo motor to act as an ultrasonic radar. It can be controlled manually using Bluetooth or can run on its own avoiding obstacles by using the radar. (Radar?? should be UDAR but never mind :P)

## Components Used

1. Arduino Uno
1. Ultrasonic Sensor HC-SR04
1. Servo Motor
1. Bluetooth module HC-05
1. Motor Driver L298N
1. BO motor \*2
1. Caster wheel
1. LiPo battery

## Images

<div align="center">
   <img src="./images/bot_1.jpg" width="40%" height="40%" />

   <img src="./images/bot_2.jpg" width="40%" height="40%" />
</div>

## Working

The connections are made as described in the code comments.
Ultrasonic sensor is attached to the top of servo so it can scan 180 degree infornt of it acting as a radar. Proximity of only theree directions are measured by the radar. The bot can be controlled manually using  this <a href="https://play.google.com/store/apps/details?id=braulio.calle.bluetoothRCcontroller&hl=en&gl=US"> app </a> or any other bluetooth controller app Howerer this code is configured for this particular app.
</br>
For the autonomous part, bot will move on a straight line and avoid obstacles using the radar. The bot will stop when it detects an obstacle move back a little and scans left and right to find a clear path. Once the path is found it turns to that direction and moves on. This process is repeaded until manual control is enabled.