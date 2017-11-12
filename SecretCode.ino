/* Arduino Security System with Keypad and LCD */

#include <LiquidCrystal.h> //include LCD library
#include <Keypad.h> //include Keypad library

//define LED pins
#define redLED 11 
#define greenLED 10

char* password ="1424"; //create a password
int pos = 0; //keypad position

const byte rows = 4; //number of rows and columns of the keypad */
const byte cols = 4;

char keyMap[rows][cols] = { //define the symbols on the buttons of the keypad

  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[rows] = {1, 2, 3, 4}; //pins of the keypad
byte colPins[cols] = {5, 6, 7, 8};

Keypad myKeypad = Keypad(makeKeymap(keyMap), rowPins, colPins, rows, cols);

LiquidCrystal lcd (A0, A1, A2, A3, A4, A5); // pins of the LCD. (RS, E, D4, D5, D6, D7)

void setup()
{
  analogWrite(9, 150); //LCD contrast
  lcd.begin(16, 2);
  pinMode(redLED, OUTPUT);  //set the LED as an output
  pinMode(greenLED, OUTPUT);
  setLock(true); //lock the system
}

void loop()
{
  char whichKey = myKeypad.getKey(); //detect which key is pressed with getKey()

  lcd.setCursor(0, 0);
  lcd.print("    Welcome");
  lcd.setCursor(0, 1);
  lcd.print(" Enter Password");

  if(whichKey == '*' || whichKey == '#' || whichKey == 'A' || whichKey == 'B' || whichKey == 'C' || whichKey == 'D') //invalid keys
  {
    pos = 0;
    setLock(true);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Invalid Key!");
    delay(1000);
    lcd.clear();
  }
  
  if(whichKey == password[pos])
    pos++; //increment pos for each matched character
  
  if(pos == 4) //password matched
  {
    setLock(false); //unlock the system
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("*** Verified ***");
    delay(3000);
    
    //display secret message
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Aliens are");
    lcd.setCursor(0, 1);
    lcd.print("real!");
    
    //after a delay of 7 seconds, lock back the system
    delay(7000);
    lcd.clear();
    setLock(true);  
    pos = 0;
  }
}

void setLock(int locked)
{
  if(locked)
  {
    digitalWrite(redLED, HIGH); //red LED indicates that the system is locked
    digitalWrite(greenLED, LOW);
  }
  else
  {
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH); //green LED indicates that the system is unlocked
  }
}

