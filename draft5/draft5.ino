#include <Servo.h> 
#include <Keypad.h> 
#include <LiquidCrystal.h>

Servo servo1;
Servo servo2;
char customKey; 

const byte ROWS = 4; 
const byte COLS = 4; 

int angle[] = {30, 60, 90, 120, 150};
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const int rs = 30, en = 31, d4 = 32, d5 = 33, d6 = 34, d7 = 35;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  servo1.attach(10);
  servo2.attach(11);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
   lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop() {
  int rno1 = random(0, 5);
  int rno2 = random(0, 5);
  Serial.print("Random angles: ");
  Serial.print(angle[rno1]);
  Serial.print(", ");
  Serial.println(angle[rno2]);
  
  servo1.write(angle[rno1]);
  servo2.write(angle[rno2]);

  customKey = customKeypad.getKey();
  while (customKey == NO_KEY) {
    customKey = customKeypad.getKey();
  }

  Serial.println("Input: " + String(customKey));

  int inputNum = customKey - '0'; // Convert char to int

  if (inputNum == rno1 + rno2 +2) {
    digitalWrite(13, HIGH); // Green LED
    delay(500);
    digitalWrite(33, LOW);
    Serial.println("RIGHT");
    lcd.print("Right");
    delay(1000);
    lcd.clear();
  } else {
    digitalWrite(13, HIGH); // Red LED
    delay(500);
    digitalWrite(33, LOW);
    Serial.println("WRONG");
    lcd.print("wrong");
    
    delay(1000);
    lcd.clear();
  }
}
