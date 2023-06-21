#include "LedControl.h" //library for the dot matrix display
#include <MFRC522.h> //library for the rfid module
#include <IRremote.h> //library for the ir remote
#include <Wire.h> //I2C communication library
#include "LiquidCrystal_I2C.h" //library for the I2C version of the LCD display
#include <avr/wdt.h>  //watchdog timer library for resetting the board

void resetFunc() {  //reset function for when switching back to manual mode
  wdt_enable(WDTO_15MS); //enables watchdog timer with 15ms timeout (idk what this means)
  while (1) {} //i know that this is an infinite loop, which is what causes the arduino to reset
}

#define motor7 4   //motor 1 pin 1
#define motor8 5   //motor 1 pin 2
#define motor3 29  //motor 3 pin 1
#define motor4 27  //motor 3 pin 2
#define motor5 25  //motor 4 pin 1
#define motor6 23  //motor 4 pin 2
#define motor1 2   //motor 2 pin 1
#define motor2 3   //motor 2 pin 2
#define echoPin 7  //echo pin for the ultrasonic sensor
#define trigPin 6  //trigger pin for the ultrasonic sensor
#define CLK 32     //8x8 Dot Matrix clk pin
#define CS 35      //8x8 Dot Matrix cs pin
#define DIN 33     //8x8 Dot Matrix DIN pin
#define buzzer 43  //buzzer pin
const int button1 = 44; //button 1 for the pacman song
const int button2 = 46; //button 2 for the pink panther song
const int button3 = 48; //button 3 for the star wars song
#define beepsound1 1500 //first tone for the reversing beep sound
#define beepsound2 1501 //second tone for the reversing beep sound

MFRC522 rfid(53, 49);  //RFID sensor pins
#define IR_RECEIVE_PIN 47 //IR sensor pin
LiquidCrystal_I2C lcd(0x27, 16, 2); //initializes the lcd display

bool autonomousMode = false;  //default start in manual mode

#define NOTE_C5 523 //notes for the turning song sound
#define NOTE_D5 587
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_G5 784
#define NOTE_A5 880
#define NOTE_B5 988
#define NOTE_C6 1047

#define NOTE_B0 31 //notes for the pacman song
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978
#define REST 0

#define NOTE_B0 31 //notes for the pink panther song
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978
#define REST 0

#define NOTE_B0 31 //notes for the star wars song
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978
#define REST 0

LedControl Display = LedControl(DIN, CLK, CS, 0); //dot matrix display initalization

byte forward[8] = { 0x18, 0x3C, 0x7E, 0xFF, 0x18, 0x18, 0x18, 0x18 }; //forward arrow for the dot matrix
byte backward[8] = { 0x18, 0x18, 0x18, 0x18, 0xFF, 0x7E, 0x3C, 0x18 }; //backward arrow for the dot matrix
byte left[8] = { 0x10, 0x30, 0x70, 0xFF, 0xFF, 0x70, 0x30, 0x10 }; //left arrow for the dot matrix
byte right[8] = { 0x08, 0x0C, 0x0E, 0xFF, 0xFF, 0x0E, 0x0C, 0x08 }; //right arrow for the dot matrix
byte stop[8] = { 0x3C, 0x66, 0xC3, 0x81, 0x81, 0xC3, 0x66, 0x3C }; //stop sign for the dot matrix

int musicalmusic[] = { //turning left/right song
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6
};

int musicone[] = { //pacman song
  NOTE_B4, 16, NOTE_B5, 16, NOTE_FS5, 16, NOTE_DS5, 16,  //1
  NOTE_B5, 32, NOTE_FS5, -16, NOTE_DS5, 8, NOTE_C5, 16,
  NOTE_C6, 16, NOTE_G6, 16, NOTE_E6, 16, NOTE_C6, 32, NOTE_G6, -16, NOTE_E6, 8,

  NOTE_B4, 16, NOTE_B5, 16, NOTE_FS5, 16, NOTE_DS5, 16, NOTE_B5, 32,  //2
  NOTE_FS5, -16, NOTE_DS5, 8, NOTE_DS5, 32, NOTE_E5, 32, NOTE_F5, 32,
  NOTE_F5, 32, NOTE_FS5, 32, NOTE_G5, 32, NOTE_G5, 32, NOTE_GS5, 32, NOTE_A5, 16, NOTE_B5, 8
};

int musictwo[] = { //pink panther song
  NOTE_DS4,8, 
  NOTE_E4,-4, REST,8, NOTE_FS4,8, NOTE_G4,-4, REST,8, NOTE_DS4,8,
  NOTE_E4,-8, NOTE_FS4,8,  NOTE_G4,-8, NOTE_C5,8, NOTE_B4,-8, NOTE_E4,8, NOTE_G4,-8, NOTE_B4,8,   
  NOTE_AS4,2, NOTE_A4,-16, NOTE_G4,-16, NOTE_E4,-16, NOTE_D4,-16, 
  NOTE_E4,2, REST,4, REST,8, NOTE_DS4,4,

  NOTE_E4,-4, REST,8, NOTE_FS4,8, NOTE_G4,-4, REST,8, NOTE_DS4,8,
  NOTE_E4,-8, NOTE_FS4,8,  NOTE_G4,-8, NOTE_C5,8, NOTE_B4,-8, NOTE_G4,8, NOTE_B4,-8, NOTE_E5,8,
  NOTE_DS5,1,
};

int musicthree[] = { //star wars song
  NOTE_AS4,8, NOTE_AS4,8, NOTE_AS4,8,//1
  NOTE_F5,2, NOTE_C6,2,
  NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F6,2, NOTE_C6,4,  
  NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F6,2, NOTE_C6,4,  
  NOTE_AS5,8, NOTE_A5,8, NOTE_AS5,8, NOTE_G5,2,
};

int beepbeep[] = { //the sound that plays when the car is reversing
  beepsound1, beepsound2 //loops the two beep sounds
};

int q = 0; //counter for the left/right turn tune
int x = 0; //counter for the reversing beep sound

void singsong() { //simple function that makes the simple tune play when the car is turning
  tone(buzzer, musicalmusic[q]); //plays the song array through the buzzer while the "q" counter counts the notes
  delay(100); //100 ms delay between each note
  noTone(buzzer); //no tone from buzzer
};

void playSound() { //function that makes the beeping sound play when the car is reversing
  tone(buzzer, beepbeep[x]); //plays the beep array through the buzzer while the "x" counter counts the notes
  delay(500); //500ms delay between each beep
  noTone(buzzer); //no tone from buzzer
}

void beginstop() {  //stops the motors completely and displays the stop sign on the dot matrix
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, LOW);
  digitalWrite(motor4, LOW);
  digitalWrite(motor5, LOW);
  digitalWrite(motor6, LOW);
  digitalWrite(motor7, LOW);
  digitalWrite(motor8, LOW);
  printByte(stop);
}

void setup() {
  Serial.begin(9600); //starts serial communication at 9600 baud
  pinMode(trigPin, OUTPUT); //sets ultrasonic trigger pin as output
  pinMode(echoPin, INPUT); //sets ultrasonic echo pin as input
  pinMode(motor1, OUTPUT); //sets motor 1 pin 1 as output
  pinMode(motor2, OUTPUT); //sets motor 1 pin 2 as output
  pinMode(motor3, OUTPUT); //sets motor 2 pin 1 as output
  pinMode(motor4, OUTPUT); //sets motor 2 pin 2 as output
  pinMode(motor5, OUTPUT); //sets motor 3 pin 1 as output
  pinMode(motor6, OUTPUT); //sets motor 3 pin 2 as output
  pinMode(motor7, OUTPUT); //sets motor 1 pin 1 as output
  pinMode(motor8, OUTPUT); //sets motor 4 pin 2 as output
  pinMode(buzzer, OUTPUT); //sets buzzer as output
  pinMode(button1, INPUT); //sets pacman song button as input
  pinMode(button2, INPUT); //sets pink panther song button as input
  pinMode(button3, INPUT); //sets star wars song button as input

  lcd.begin();                   //initializes the lcd
  lcd.setBacklight((uint8_t)1);  //turns on the lcd blacklight
  lcd.print("MODE:");            //first row prints MODE: to the lcd

  Display.shutdown(0, false); //initializes dot matrix
  Display.setIntensity(0, 8); //sets dot matrix brightness
  Display.clearDisplay(0); //clears dot matrix on startup

  SPI.begin();      //initalizes the SPI bus
  rfid.PCD_Init();  //initializes the rfid reader library
  IrReceiver.begin(IR_RECEIVE_PIN); //starts receiving ir input
  Serial.println("Ready to scan RFID tags!"); //rfid scanner serial monitor message
}

void cardreset () { //extension of the reset function for the rfid
  if (rfid.PICC_IsNewCardPresent()) { //if a new rfid tag is present
  resetFunc(); //reset arduino
  }
}

unsigned long turnStartTime = 0;          //variable to store the start time of a turn
const unsigned long turnDuration = 1500;  //duration of each turn in ms

void loop() { //main loop
  if (autonomousMode) { //if car is in autonomous mode
    autonomousLoop(); //run the autonomous function
    buttonbutton(); //run the song button function
    if (rfid.PICC_IsNewCardPresent()) { //if a new rfid tag is present
      if (rfid.PICC_ReadCardSerial()) { //read the tag
        String tagId = ""; //store the id
        for (byte i = 0; i < rfid.uid.size; i++) { //iterate through the id
          tagId += String(rfid.uid.uidByte[i] < 0x10 ? "0" : ""); //store the id
          tagId += String(rfid.uid.uidByte[i], HEX); //store it as a hexadecimal
        }

        if (tagId == "dcdad621") { //if this tag is detected
          resetFunc();
          Serial.println("AUTONOMOUS MODE"); //print autonomous mode to serial monitor

        } else if (tagId == "7374a704") { //if this tag is detected
          resetFunc();
          Serial.println("MANUAL MODE"); //print manual mode to serial monitor
        }

        rfid.PICC_HaltA();  //halt the card
      }
    }
  } else { //else the car is in manual mode
    manualLoop(); //run the manual function
    buttonbutton(); //run the button song function
  }

    if (rfid.PICC_IsNewCardPresent()) { //if a new rfid tag is present
      if (rfid.PICC_ReadCardSerial()) { //read the tag
        String tagId = ""; //store the id
        for (byte i = 0; i < rfid.uid.size; i++) { //iterate through the id
          tagId += String(rfid.uid.uidByte[i] < 0x10 ? "0" : ""); //store the id
          tagId += String(rfid.uid.uidByte[i], HEX); //store it as a hexadecimal
        }

        if (tagId == "dcdad621") { //if this tag is detected
          resetFunc();
          Serial.println("AUTONOMOUS MODE"); //print autonomous mode to serial monitor

        } else if (tagId == "7374a704") { //if this tag is detected
          resetFunc();
          Serial.println("MANUAL MODE"); //print manual mode to serial monitor
        }

        rfid.PICC_HaltA();  //halt the card
      }
  }
}


void autonomousLoop() { //autonomous function
  lcd.setCursor(0, 1); //sets the text to be put in the lcd second row
  lcd.print("AUTONOMOUS"); //prints autonomous to the lcd
  while (autonomousMode) {
    long duration, distance;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;
    if (rfid.PICC_IsNewCardPresent()) {
      if (rfid.PICC_ReadCardSerial()) {
        String tagId = "";
        for (byte i = 0; i < rfid.uid.size; i++) {
          tagId += String(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
          tagId += String(rfid.uid.uidByte[i], HEX);
        }

        if (tagId == "dcdad621") {
          autonomousMode = true;
          Serial.println("AUTONOMOUS MODE");
        } else if (tagId == "7374a704") {
          autonomousMode = false;  // Switch to manual mode
          Serial.println("MANUAL MODE");
        }

        rfid.PICC_HaltA();  // Halt the card
      }
    }


    if (distance < 15) { //if ultrasonic determines distance to be less than 15 cm

      int randomnumber = random(2); //pick a random number from 0 to 1 for the turn decision

      if (randomnumber == 0) {  //right turn if random number is zero: makes motors go right, sets dot matrix as right arrow, plays turn tune
        digitalWrite(motor1, LOW);
        digitalWrite(motor2, LOW);
        digitalWrite(motor3, HIGH);
        digitalWrite(motor4, LOW);
        digitalWrite(motor5, LOW);
        digitalWrite(motor6, LOW);
        digitalWrite(motor7, HIGH);
        digitalWrite(motor8, LOW);
        printByte(right);
        singsong();
        q = q + 1; //tune has 8 notes, so once 8 notes are played, restart the tune
        if (q == 8) {
          q = 0;
        }
                if (rfid.PICC_IsNewCardPresent()) {
          if (rfid.PICC_ReadCardSerial()) {
            String tagId = "";
            for (byte i = 0; i < rfid.uid.size; i++) {
              tagId += String(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
              tagId += String(rfid.uid.uidByte[i], HEX);
            }

            if (tagId == "dcdad621") {
              autonomousMode = true;
              Serial.println("AUTONOMOUS MODE");
            } else if (tagId == "7374a704") {
              autonomousMode = false;  // Switch to manual mode
              Serial.println("MANUAL MODE");
            }

            rfid.PICC_HaltA();  // Halt the card
          }
        }
      } else {  //left turn if random number is one: makes motors go left, sets dot matrix as left arrow, plays turn tune
        digitalWrite(motor1, HIGH);
        digitalWrite(motor2, LOW);
        digitalWrite(motor3, LOW);
        digitalWrite(motor4, LOW);
        digitalWrite(motor5, HIGH);
        digitalWrite(motor6, LOW);
        digitalWrite(motor7, LOW);
        digitalWrite(motor8, LOW);
        printByte(left);
        singsong();
        q = q + 1; //tune has 8 notes, so once 8 notes are played, restart the tune
        if (q == 8) {
          q = 0;
        }
                if (rfid.PICC_IsNewCardPresent()) {
          if (rfid.PICC_ReadCardSerial()) {
            String tagId = "";
            for (byte i = 0; i < rfid.uid.size; i++) {
              tagId += String(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
              tagId += String(rfid.uid.uidByte[i], HEX);
            }

            if (tagId == "dcdad621") {
              autonomousMode = true;
              Serial.println("AUTONOMOUS MODE");
            } else if (tagId == "7374a704") {
              autonomousMode = false;  // Switch to manual mode
              Serial.println("MANUAL MODE");
            }

            rfid.PICC_HaltA();  // Halt the card
          }
        }
      }
      turnStartTime = millis();  //store the start time of the turn
    }
    if (distance >= 50 || distance <= 0) { //if the ultrasonic determines the distance to be more than 50cm or less than 0 (out of range), set motors to go forward and dot matrix as forward arrow
      Serial.println("NOTHING DETECTED :)"); //print nothing detected to serial mintor
      digitalWrite(motor1, HIGH);
      digitalWrite(motor2, LOW);
      digitalWrite(motor3, HIGH);
      digitalWrite(motor4, LOW);
      digitalWrite(motor5, HIGH);
      digitalWrite(motor6, LOW);
      digitalWrite(motor7, HIGH);
      digitalWrite(motor8, LOW);
      printByte(forward);
      buttonbutton();
              if (rfid.PICC_IsNewCardPresent()) {
          if (rfid.PICC_ReadCardSerial()) {
            String tagId = "";
            for (byte i = 0; i < rfid.uid.size; i++) {
              tagId += String(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
              tagId += String(rfid.uid.uidByte[i], HEX);
            }

            if (tagId == "dcdad621") {
              autonomousMode = true;
              Serial.println("AUTONOMOUS MODE");
            } else if (tagId == "7374a704") {
              autonomousMode = false;  // Switch to manual mode
              Serial.println("MANUAL MODE");
            }

            rfid.PICC_HaltA();  // Halt the card
          }
        }
    }
    if (distance > 15 && distance < 50) { //if the ultrasonic sensor determines the distance to be more than 15 but less than 50, go backward, play the reversing beep sound, and show a backward arrow on the dot matrix
      
      if (millis() - turnStartTime >= turnDuration) {//checks if the turn duration has elapsed
        digitalWrite(motor1, LOW);
        digitalWrite(motor2, HIGH);
        digitalWrite(motor3, LOW);
        digitalWrite(motor4, HIGH);
        digitalWrite(motor5, LOW);
        digitalWrite(motor6, HIGH);
        digitalWrite(motor7, LOW);
        digitalWrite(motor8, HIGH);
        printByte(backward);
        playSound();
        x = x + 1;
        if (x == 2) {
          x = 0;
          if (rfid.PICC_IsNewCardPresent()) {
          if (rfid.PICC_ReadCardSerial()) {
            String tagId = "";
            for (byte i = 0; i < rfid.uid.size; i++) {
              tagId += String(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
              tagId += String(rfid.uid.uidByte[i], HEX);
            }

            if (tagId == "dcdad621") {
              autonomousMode = true;
              Serial.println("AUTONOMOUS MODE");
            } else if (tagId == "7374a704") {
              autonomousMode = false;  // Switch to manual mode
              Serial.println("MANUAL MODE");
            }

            rfid.PICC_HaltA();  // Halt the card
          }
        }
        }
        Serial.print(distance); //print distance to serial monitor
        Serial.println(" cm");
      }
    }
    delay(500); //500 ms delay for printing distance
    if (rfid.PICC_IsNewCardPresent()) {
      if (rfid.PICC_ReadCardSerial()) {
        String tagId = "";
        for (byte i = 0; i < rfid.uid.size; i++) {
          tagId += String(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
          tagId += String(rfid.uid.uidByte[i], HEX);
        }

if (tagId != "7374a704") {
  autonomousMode = false;  //exit autonomous mode if a different card is scanned
  Serial.println("EXIT AUTONOMOUS MODE");
  resetFunc(); // Call resetFunc here
}


        rfid.PICC_HaltA();  // Halt the card
      }
    }
  }
}

void manualLoop() { //manual function
  lcd.setCursor(0, 1); //sets text to be pritned to second row of the lcd
  lcd.print("MANUAL"); //prints manual
  while (IrReceiver.decode()) {  //clears any pending IR input
    IrReceiver.resume();
  }

  bool buttonPressed = false;  //boolean to track the button press

  while (!autonomousMode) { //while we aren't in autonomous code
    if (IrReceiver.decode()) { //receive and decode the button press
      unsigned long lastIRTime = millis();  //update the last IR input time
      buttonPressed = true;                 //set buttonPressed to true

      switch (IrReceiver.decodedIRData.command) { //switch statement for button cases, its like a more consise if statement
        case 24:  // forward button
          Serial.println("Forward button pressed");
          goforward();
          break;
        case 82:  // backward button
          Serial.println("Backward button pressed");
          gobackward();
          break;
        case 8:  // Left button
          Serial.println("Left button pressed");
          goleft();
          break;
        case 90:  // Right button
          Serial.println("Right button pressed");
          goright();
          break;
        case 28:  //stop button
          Serial.println("Stop button pressed");
          beginstop();
          break;

        case 69: //autonomous mode button
          Serial.println("Back to autonomous");
          autonomousMode = true;
          return;  //exit the manualLoop() function to allow switching back to autonomous mode
        default: //default case
          Serial.println("Invalid button pressed");
          break;
      }

      while (IrReceiver.decode()) { //waits for the button to be released
        IrReceiver.resume(); //clears any remaining IR input
      }

      IrReceiver.resume(); //clears any remaining IR input
    }

    if (rfid.PICC_IsNewCardPresent()) {
      if (rfid.PICC_ReadCardSerial()) {
        String tagId = "";
        for (byte i = 0; i < rfid.uid.size; i++) {
          tagId += String(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
          tagId += String(rfid.uid.uidByte[i], HEX);
        }

        if (tagId == "7374a704") {
          autonomousMode = true;  //exit autonomous mode if the "7374a704" tag is scanned
          Serial.println("EXIT AUTONOMOUS MODE");
          return;  //exit the manualLoop() function to switch back to autonomous mode
        }

        rfid.PICC_HaltA();  //halt the card
      }
    }
  }
}

void printByte(byte character[]) {
  for (int i = 0; i < 8; i++) {
    Display.setRow(0, i, character[i]);
  };
};

void buttonbutton() {
  //check button 1 (pacman song)
  if (digitalRead(button1) == LOW) { //if button is pressed play the song. the below code plays the song with a specific tempo
    int tempo = 120;
    int notes = sizeof(musicone) / sizeof(musicone[0]) / 2;

    //this calculates the duration of a whole note in ms
    int wholenote = (60000 * 4) / tempo;

    int divider = 0, noteDuration = 0;

    for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

      //calculates the duration of each note
      divider = musicone[thisNote + 1];
      if (divider > 0) {
        //regular note, just proceed
        noteDuration = (wholenote) / divider;
      } else if (divider < 0) {
        //dotted notes are represented with negative durations!!
        noteDuration = (wholenote) / abs(divider);
        noteDuration *= 1.5;  //increases the duration in half for dotted notes
      }

      //we only play the note for 90% of the duration, leaving 10% as a pause
      tone(buzzer, musicone[thisNote], noteDuration * 0.9);

      //wait for the specief duration before playing the next note.
      delay(noteDuration);

      //stop the waveform generation before the next note.
      noTone(buzzer);
    }
  };

  //check button 2 (pink panther song)
  if (digitalRead(button2) == LOW) { //if button is pressed play the song. the below code plays the song with a specific tempo
    int tempo = 220;
    int notes = sizeof(musictwo) / sizeof(musictwo[0]) / 2;

    //this calculates the duration of a whole note in ms
    int wholenote = (60000 * 4) / tempo;

    int divider = 0, noteDuration = 0;

    for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

      //calculates the duration of each note
      divider = musictwo[thisNote + 1];
      if (divider > 0) {
        //regular note, just proceed
        noteDuration = (wholenote) / divider;
      } else if (divider < 0) {
        //dotted notes are represented with negative durations!!
        noteDuration = (wholenote) / abs(divider);
        noteDuration *= 1.5;  //increases the duration in half for dotted notes
      }

      //we only play the note for 90% of the duration, leaving 10% as a pause
      tone(buzzer, musictwo[thisNote], noteDuration * 0.9);

      //wait for the specief duration before playing the next note.
      delay(noteDuration);

      //stop the waveform generation before the next note.
      noTone(buzzer);
    }
  }

  //check button 3 (star wars song)
  if (digitalRead(button3) == LOW) {
    int tempo = 220;
    int notes = sizeof(musicthree) / sizeof(musicthree[0]) / 2;

    //this calculates the duration of a whole note in ms
    int wholenote = (60000 * 4) / tempo;

    int divider = 0, noteDuration = 0;

    for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

      //calculates the duration of each note
      divider = musicthree[thisNote + 1];
      if (divider > 0) {
        //regular note, just proceed
        noteDuration = (wholenote) / divider;
      } else if (divider < 0) {
        //dotted notes are represented with negative durations!!
        noteDuration = (wholenote) / abs(divider);
        noteDuration *= 1.5;  //increases the duration in half for dotted notes
      }

      //we only play the note for 90% of the duration, leaving 10% as a pause
      tone(buzzer, musicthree[thisNote], noteDuration * 0.9);

      //wait for the specief duration before playing the next note.
      delay(noteDuration);

      //stop the waveform generation before the next note.
      noTone(buzzer);
    }
  }
}

void goforward() {
  //sets motor pins for forward movement and shows forward arrow on the dot matrix
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, HIGH);
  digitalWrite(motor4, LOW);
  digitalWrite(motor5, HIGH);
  digitalWrite(motor6, LOW);
  digitalWrite(motor7, HIGH);
  digitalWrite(motor8, LOW);
  printByte(forward);
}

void gobackward() {
  //sets motor pins for backward movement and shows backward arrow on the dot matrix
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, HIGH);
  digitalWrite(motor3, LOW);
  digitalWrite(motor4, HIGH);
  digitalWrite(motor5, LOW);
  digitalWrite(motor6, HIGH);
  digitalWrite(motor7, LOW);
  digitalWrite(motor8, HIGH);
  printByte(backward);
}

void goright() {
  //sets motor pins for right movement and shows right arrow on the dot matrix
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, HIGH);
  digitalWrite(motor4, LOW);
  digitalWrite(motor5, LOW);
  digitalWrite(motor6, LOW);
  digitalWrite(motor7, HIGH);
  digitalWrite(motor8, LOW);
  printByte(right);
}

void goleft() {
  //sets motor pins for left movement and shows left arrow on the dot matrix
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, LOW);
  digitalWrite(motor4, LOW);
  digitalWrite(motor5, HIGH);
  digitalWrite(motor6, LOW);
  digitalWrite(motor7, LOW);
  digitalWrite(motor8, LOW);
  printByte(left);
}