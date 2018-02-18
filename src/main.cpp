#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7); // 0x27 is the I2C bus address for an unmodified module
//I2C device found at address 0x3F
// Data wire is plugged into pin 2 on the Arduino

#define ONE_WIRE_BUS 4

// Setup a oneWire instance to communicate with any OneWire devices
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

int sensor_pin = A0;
int output_value ;

void setup(void)
{
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH); // NOTE: You can turn the backlight off by setting it to LOW instead of HIGH
  lcd.begin(16, 2);
  lcd.clear();
  Wire.begin();
  // start serial port
  Serial.begin(9600);
  //Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  sensors.begin();
}


void loop(void)
{
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  //Serial.print(" Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  //Serial.println("DONE");

  Serial.print("Temperature: ");
  Serial.println(sensors.getTempCByIndex(0)); // Why "byIndex"?
    // You can have more than one IC on the same bus.
    // 0 refers to the first IC on the wire

  output_value= analogRead(sensor_pin);
  output_value = map(output_value,1023,420,0,100);
  Serial.print("Mositure: ");
  Serial.print(output_value);
  Serial.println(" %");
  lcd.setBacklight(LOW);      // Backlight off
  delay(3000);
  lcd.setBacklight(HIGH);     // Backlight on
  delay(3000);

  lcd.setCursor(0,0);
  lcd.print("http://mklec.com");
  lcd.setCursor(0,1);
  lcd.print("I2C Module Demo");


  delay(5000);           // wait 5 seconds for next scan

}
