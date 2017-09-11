  /* DHT11-based 'Weather Station'
   * (without using a potentiometer)
   * 
   * Components: RG1602A, DHT11
   *  
   * Circuit (using a breadboard): 
   * VSS of LCD to negative rail
   * VDD of LCD to positive rail
   * V0 of LCD to digital pin 6 
   * RS of LCD to digital pin 12
   * RW of LCD to negative rail
   * E of LCD to digital pin 11
   * D4 of LCD to digital pin 5
   * D5 of LCD to digital pin 4
   * D6 of LCD to digital pin 3
   * D7 of LCD to digital pin 2
   * A of LCD to positive rail
   * K of LCD to negative rail
   * VCC of DHT to positive rail
   * Data of DHT to digital pin 7
   * GND of DHT to negative rail
   * 
   * DHT Lib. D/L Link: http://www.circuitbasics.com/wp-content/uploads/2015/10/DHTLib.zip
   */
  
  #include <dht.h>
  #include <LiquidCrystal.h>

  #define DHT11_PIN 7
  #define CONTRAST_VALUE 150
  #define RS 12
  #define E 11
  #define D4 5
  #define D5 4
  #define D6 3
  #define D7 2
  #define V0 6
  
  LiquidCrystal LCD(RS, E, D4, D5, D6, D7);
  dht DHT;
  
  void setup()
  {
    analogWrite(V0, CONTRAST_VALUE); //alternative to using a potentiometer
    LCD.begin(16, 2);
  }
  
  void loop()
  {
    int readDHT = DHT.read11(DHT11_PIN);
    LCD.setCursor(0, 0); //cursor is set to first position of first row (offset: 0, 0)
    LCD.print("Temp: ");
    LCD.print(DHT.temperature);
    LCD.print((char)223); //223 is the ASCII value of the ° symbol
    LCD.print("C");
    LCD.setCursor(0, 1); //cursor is set to first position of second row (offset: 0, 1)
    LCD.print("Humidity: ");
    LCD.print(DHT.humidity);
    LCD.print("%");
    delay(2000); //delay to ensure that sensor data is read at an interval of 2 seconds
  }
