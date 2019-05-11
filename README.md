### Android Smartphone controlled Arduino Alphanumeric LCD & RGB LED demo via HC-05 bluetooth module

Circuit: Breadboard, wires, Arduino Nano, 2004 LCD screen, 10kΩ potentiometer, PL9823 LED.

![Bluetooth Arduino Demo](/README_images/bluetooth-demo.jpg)

The PL9823 is Neopixel-compatible. You will need to install the Neopixel library: https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-installation

To connect the LCD screen correctly, see the tutorial over at Arduino.cc: https://www.arduino.cc/en/Tutorial/HelloWorld (I have changed the pin numbers used, read the code...)

The HC-05 TX pin on the left is connected to the Arduino's RX pin; it acts as a 9600 baud serial port.

For the Android part, install one of the HC-05 controller apps on your phone. This one seems nice: https://play.google.com/store/apps/details?id=com.mightyit.gops.bluetoothcontroller

Supported commands which you can send over bluetooth or serial:

```
/R127: Set the red component of the LED colour to 127

/G127: Set the green component of the LED colour to 127

/B127: Set the blue component of the LED colour to 127

/f84: Display the specified 3-digit hexadecimal colour 
(the three digits are R, G, B respectively, and f(15) is the maximum)

/clear: Clear the LCD dsplay

/funky: Change into "funky" mode, which cycles through white, primary and secondary colours

Any other text (without a / in front) is displayed on the screen. 
The Arduino will wrap text over 20 characters onto multiple lines.
```
