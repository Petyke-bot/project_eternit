
// Include Libraries
#include "Arduino.h"
#include "DHT.h"
#include "DS18B20.h"
#include "NewPing.h"
#include "Wire.h"
#include "SPI.h"
#include "Adafruit_SSD1306.h"
#include "Adafruit_GFX.h"


// Pin Definitions
#define DHT_PIN_DATA	0
#define DS18B20WP_PIN_DQ	2
#define HCSR04_PIN_TRIG	5
#define HCSR04_PIN_ECHO	4
#define OLED128X64_PIN_RST	8
#define OLED128X64_PIN_DC	7
#define OLED128X64_PIN_CS	6
#define RELAYMODULE4CH_1_PIN_IN1	9
#define RELAYMODULE4CH_1_PIN_IN2	10
#define RELAYMODULE4CH_1_PIN_IN4	13
#define RELAYMODULE4CH_1_PIN_IN3	11
#define RELAYMODULE4CH_2_PIN_IN1	14
#define RELAYMODULE4CH_2_PIN_IN2	15
#define RELAYMODULE4CH_2_PIN_IN4	17
#define RELAYMODULE4CH_2_PIN_IN3	16
#define WATERLEVELSENSOR_3V3_PIN_SIG	12



// Global variables and defines
//define an array for the 4ch relay module pins
int RelayModule4ch_1Pins[] = { RELAYMODULE4CH_1_PIN_IN1, RELAYMODULE4CH_1_PIN_IN2, RELAYMODULE4CH_1_PIN_IN3, RELAYMODULE4CH_1_PIN_IN4 };
//define an array for the 4ch relay module pins
int RelayModule4ch_2Pins[] = { RELAYMODULE4CH_2_PIN_IN1, RELAYMODULE4CH_2_PIN_IN2, RELAYMODULE4CH_2_PIN_IN3, RELAYMODULE4CH_2_PIN_IN4 };
// object initialization
DHT dht(DHT_PIN_DATA);
DS18B20 ds18b20wp(DS18B20WP_PIN_DQ);
NewPing hcsr04(HCSR04_PIN_TRIG,HCSR04_PIN_ECHO);
#define SSD1306_LCDHEIGHT 64
Adafruit_SSD1306 oLed128x64(OLED128X64_PIN_DC, OLED128X64_PIN_RST, OLED128X64_PIN_CS);


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    dht.begin();
    oLed128x64.begin(SSD1306_SWITCHCAPVCC);  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
    oLed128x64.clearDisplay(); // Clear the buffer.
    oLed128x64.display();
    pinMode(RELAYMODULE4CH_1_PIN_IN1, OUTPUT);
    pinMode(RELAYMODULE4CH_1_PIN_IN2, OUTPUT);
    pinMode(RELAYMODULE4CH_1_PIN_IN3, OUTPUT);
    pinMode(RELAYMODULE4CH_1_PIN_IN4, OUTPUT);
    pinMode(RELAYMODULE4CH_2_PIN_IN1, OUTPUT);
    pinMode(RELAYMODULE4CH_2_PIN_IN2, OUTPUT);
    pinMode(RELAYMODULE4CH_2_PIN_IN3, OUTPUT);
    pinMode(RELAYMODULE4CH_2_PIN_IN4, OUTPUT);
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // DHT22/11 Humidity and Temperature Sensor - Test Code
    // Reading humidity in %
    float dhtHumidity = dht.readHumidity();
    // Read temperature in Celsius, for Fahrenheit use .readTempF()
    float dhtTempC = dht.readTempC();
    Serial.print(F("Humidity: ")); Serial.print(dhtHumidity); Serial.print(F(" [%]\t"));
    Serial.print(F("Temp: ")); Serial.print(dhtTempC); Serial.println(F(" [C]"));

    }
    else if(menuOption == '2') {
    // DS18B20 1-Wire Temperature Sensor - Waterproof - Test Code
    // Read DS18B20 temp sensor value in degrees celsius. for degrees fahrenheit use ds18b20wp.ReadTempF()
    float ds18b20wpTempC = ds18b20wp.readTempC();
    Serial.print(F("Temp: ")); Serial.print(ds18b20wpTempC); Serial.println(F(" [C]"));

    }
    else if(menuOption == '3') {
    // Ultrasonic Sensor - HC-SR04 - Test Code
    // Read distance measurment from UltraSonic sensor           
    int hcsr04Dist = hcsr04.ping_cm();
    delay(10);
    Serial.print(F("Distance: ")); Serial.print(hcsr04Dist); Serial.println(F("[cm]"));

    }
    else if(menuOption == '4') {
    // Monochrome 1.3 inch 128x64 OLED graphic display - Test Code
    oLed128x64.setTextSize(1);
    oLed128x64.setTextColor(WHITE);
    oLed128x64.setCursor(0, 10);
    oLed128x64.clearDisplay();
    oLed128x64.println("Circuito.io Rocks!");
    oLed128x64.display();
    delay(1);
    oLed128x64.startscrollright(0x00, 0x0F);
    delay(2000);
    oLed128x64.stopscroll();
    delay(1000);
    oLed128x64.startscrollleft(0x00, 0x0F);
    delay(2000);
    oLed128x64.stopscroll();
    }
    else if(menuOption == '5') {
    // Relay Module 4-Ch #1 - Test Code
    //This loop will turn on and off each relay in the array for 0.5 sec
    for (int i = 0; i < 4; i++) { 
    digitalWrite(RelayModule4ch_1Pins[i],HIGH);
    delay(500);
    digitalWrite(RelayModule4ch_1Pins[i],LOW);
    delay(500);
    }
    }
    else if(menuOption == '6') {
    // Relay Module 4-Ch #2 - Test Code
    //This loop will turn on and off each relay in the array for 0.5 sec
    for (int i = 0; i < 4; i++) { 
    digitalWrite(RelayModule4ch_2Pins[i],HIGH);
    delay(500);
    digitalWrite(RelayModule4ch_2Pins[i],LOW);
    delay(500);
    }
    }
    else if(menuOption == '7')
    {
    // Disclaimer: The Water Level Sensor Module is in testing and/or doesn't have code, therefore it may be buggy. Please be kind and report any bugs you may find.
    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) DHT22/11 Humidity and Temperature Sensor"));
    Serial.println(F("(2) DS18B20 1-Wire Temperature Sensor - Waterproof"));
    Serial.println(F("(3) Ultrasonic Sensor - HC-SR04"));
    Serial.println(F("(4) Monochrome 1.3 inch 128x64 OLED graphic display"));
    Serial.println(F("(5) Relay Module 4-Ch #1"));
    Serial.println(F("(6) Relay Module 4-Ch #2"));
    Serial.println(F("(7) Water Level Sensor Module"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
    			Serial.println(F("Now Testing DHT22/11 Humidity and Temperature Sensor"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing DS18B20 1-Wire Temperature Sensor - Waterproof"));
    		else if(c == '3') 
    			Serial.println(F("Now Testing Ultrasonic Sensor - HC-SR04"));
    		else if(c == '4') 
    			Serial.println(F("Now Testing Monochrome 1.3 inch 128x64 OLED graphic display"));
    		else if(c == '5') 
    			Serial.println(F("Now Testing Relay Module 4-Ch #1"));
    		else if(c == '6') 
    			Serial.println(F("Now Testing Relay Module 4-Ch #2"));
    		else if(c == '7') 
    			Serial.println(F("Now Testing Water Level Sensor Module - note that this component doesn't have a test code"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}

/*******************************************************

*    Circuito.io is an automatic generator of schematics and code for off
*    the shelf hardware combinations.

*    Copyright (C) 2016 Roboplan Technologies Ltd.

*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.

*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.

*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*    In addition, and without limitation, to the disclaimers of warranties 
*    stated above and in the GNU General Public License version 3 (or any 
*    later version), Roboplan Technologies Ltd. ("Roboplan") offers this 
*    program subject to the following warranty disclaimers and by using 
*    this program you acknowledge and agree to the following:
*    THIS PROGRAM IS PROVIDED ON AN "AS IS" AND "AS AVAILABLE" BASIS, AND 
*    WITHOUT WARRANTIES OF ANY KIND EITHER EXPRESS OR IMPLIED.  ROBOPLAN 
*    HEREBY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT 
*    NOT LIMITED TO IMPLIED WARRANTIES OF MERCHANTABILITY, TITLE, FITNESS 
*    FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT, AND THOSE ARISING BY 
*    STATUTE OR FROM A COURSE OF DEALING OR USAGE OF TRADE. 
*    YOUR RELIANCE ON, OR USE OF THIS PROGRAM IS AT YOUR SOLE RISK.
*    ROBOPLAN DOES NOT GUARANTEE THAT THE PROGRAM WILL BE FREE OF, OR NOT 
*    SUSCEPTIBLE TO, BUGS, SECURITY BREACHES, OR VIRUSES. ROBOPLAN DOES 
*    NOT WARRANT THAT YOUR USE OF THE PROGRAM, INCLUDING PURSUANT TO 
*    SCHEMATICS, INSTRUCTIONS OR RECOMMENDATIONS OF ROBOPLAN, WILL BE SAFE 
*    FOR PERSONAL USE OR FOR PRODUCTION OR COMMERCIAL USE, WILL NOT 
*    VIOLATE ANY THIRD PARTY RIGHTS, WILL PROVIDE THE INTENDED OR DESIRED
*    RESULTS, OR OPERATE AS YOU INTENDED OR AS MAY BE INDICATED BY ROBOPLAN. 
*    YOU HEREBY WAIVE, AGREE NOT TO ASSERT AGAINST, AND RELEASE ROBOPLAN, 
*    ITS LICENSORS AND AFFILIATES FROM, ANY CLAIMS IN CONNECTION WITH ANY OF 
*    THE ABOVE. 
********************************************************/