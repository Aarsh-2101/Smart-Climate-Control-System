const int temp_trans_pin = A0, Heater_pin = 13, FAN_pin = 6;

float MinTemp = 20, MaxTemp = 25;/*Room temperature is [20,25] degree C */

#include <LiquidCrystal.h>

LiquidCrystal LCD(12, 11, 5, 4, 3, 2);

void setup() {
  
  LCD.begin(16, 2);
  pinMode(Heater_pin, OUTPUT);
  pinMode(FAN_pin, OUTPUT);
    
  // Display the desired range of temperature
  LCD.print("Room temp(C):");
  LCD.setCursor(2,1);
  LCD.print(MinTemp); LCD.print("-");LCD.print(MaxTemp);
    
  delay(2000);
  }

void loop() {
   
  float Eqv_volt, SensorTemp;
  Eqv_volt = analogRead(temp_trans_pin) * 5.0 / 1023;
  SensorTemp = 100.0 * Eqv_volt-50.0;
  
  LCD.clear();
  LCD.print("Sensor reading:");
  LCD.setCursor(2,1);
  LCD.print(SensorTemp); LCD.print(" C");
   
  delay(2000);

  if(SensorTemp > MaxTemp){
    LCD.clear();
    LCD.print("temp is HIGHER!");//higher than the max
    
    LCD.setCursor(0, 1);LCD.print("Turn on FAN!");
    for( int i = 0; i <= 255; i++ ) {
      analogWrite(FAN_pin, i);
      }
    delay(2000);
  
    LCD.clear();
    LCD.print("Now temp is OK!");
    LCD.setCursor(0, 1);
    LCD.print("Turn off FAN!");
    
    // Turn off FAN slowly
    for( int i = 255; i >= 0; i-- ) {
      analogWrite(FAN_pin, i);
    }
    delay(2000);
    }

  else if(SensorTemp < MinTemp){
    LCD.clear();
    LCD.print("temp is LOWER!");//Less than the min
    LCD.setCursor(0, 1);
    LCD.print("Turn on HEATER!");
  
    //Turn the heater ON, LED in this case 
  
    digitalWrite(Heater_pin, HIGH);
  
    delay(3000);
  
    LCD.clear();
    LCD.print("Now temp is OK!");
    LCD.setCursor(0, 1);
    LCD.print("Turn off HEATER!");
  
    delay(1000);
  
    digitalWrite(Heater_pin, LOW);
    LCD.clear();
      }
  else if(SensorTemp > MinTemp && SensorTemp < MaxTemp){/*Now temperature is perfect.*/
     
    LCD.clear();
    LCD.print("Temp is NORMAL!");LCD.setCursor(2,1);
    LCD.print("Turn off all!");
  
    delay(1000);
    LCD.clear();
   }

  else {
    LCD.clear();
    LCD.print("Something went");
    LCD.setCursor(2,1); LCD.print("WRONG in the ckt");
    delay(1000);
    LCD.clear();
    }
  delay(1000);
  } 