﻿# 2023 TEJ3M SUMMATIVE
## Autonomous Car (with manual mode)
## This is my summative for the TEJ3M course with Mr R <br><br>

**DESCRIPTION** <br>
Welcome to the home of my 2023 summative. I have made an autonomous car that goes forwards, backwards, and turns left and right on its own based on the distance of an object from the ultrasonic sensor. I have incorporated many unique features that I wanted to challenge myself with. This repository contains the code and a demo video of the car and its autonomous & manual control modes, as well as all its other features.<br><br>

**DEMO VIDEO**<br>
Here is a demo video of the car: [https://www.youtube.com/watch?v=Ixj__CH9BaQ](https://www.youtube.com/watch?v=Ixj__CH9BaQ)<br>
Note that there is no body on the car for the sake of visibility on the video. Check out the images folder for complete images of the car with its body.<br><br>

**FEATURES:** <br>
- 4 H-Bridges for the 4 motors of the car
- Autonomous & Manual Mode
- Ultrasonic sensor to detect objects within a certain distance
- 8x8 Dot Matrix Display to display the direction you are going in
- IR Sensor & Remote to control the car manually
- LCD Display to display the current mode: Autonomous or Manual
- Buzzer to play sound
- Push buttons that each play a different song<br><br>

**COMPONENTS USED:**
- Arduino Mega
- NPN Transistors (TIP31C or TIP41C x 8)
- PNP Transistors (TIP32C or TIP42C x 8)
- Motors and wheels x 4
- 1K Ohm Resistors x 16 (4 per h-bridge)
- 330 Ohm Resistors x 3 (one per song push button)
- 100 Ohm Resistor x 1 (for filtering the IR sensor signals)
- Wire (lots of custom length, jumpers, and duponts)
- Ultrasonic sensor x 1
- IR Sensor x 1
- IR Remote x 1
- MAX7219 8x8 Dot Matrix Display x 1
- 3 pin buzzer x 1
- Push buttons x 4 (3 for songs, 1 for a debugging reset button)
- LCD1602 x 1 (I2C version)
- RC522 RFID Module x 1
- RFID Card and Tag x 1 (1 each)
