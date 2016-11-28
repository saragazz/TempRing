// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      1

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

// TEMPERATURE CODE

//TMP36 Pin Variables
int sensorPin = A3; //the analog pin the TMP36's Vout (sense) pin is connected to
                        //the resolution is 10 mV / degree centigrade with a
                        //500 mV offset to allow for negative temperatures
 
void setup()
{
  // PIXEL CODE
  pixels.begin(); // This initializes the NeoPixel library.

// TEMPERATURE
  Serial.begin(9600);  //Start the serial connection with the computer
                       //to view the result open the serial monitor 
}

void loop()                     // run over and over again
{
 //getting the voltage reading from the temperature sensor
 int reading = analogRead(sensorPin);  
 
 // converting that reading to voltage, for 3.3v arduino use 3.3
 float voltage = reading * 5.0;
 voltage /= 1024.0;
 
 // print out the voltage
 Serial.print(voltage); Serial.println(" volts");
 
 // now print out the temperature
 float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
 Serial.print(temperatureC); Serial.println(" degrees C");

 int redShade = map(temperatureC, 25, 30, 255, 0);
 int blueShade = map(temperatureC, 18, 25, 0, 255);
 Serial.println(redShade);
 Serial.println(blueShade);

 if (temperatureC < 25) {
pixels.setPixelColor(0, pixels.Color(0,blueShade,255));
pixels.show();
 } else {
  pixels.setPixelColor(0, pixels.Color(255,0,redShade));
  pixels.show();
 }

 

 delay(1000);                                     //waiting a second
}
