/*
  flapControl

  Control a servo motor by pressing a pushbutton. A lighting LED shows, that servo is in end position

  The circuit:
  - LED attached from pin 13 to ground
  - pushbutton attached to pin 2 from +5V
  - 10K resistor attached to pin 2 from ground
  - Signal pin of servo attached to pin 9 (yellow cable)
  - VCC attached to +5V (red cable)
  - GND attached to GND (brown cable)
  

  - Note: on most Arduinos there is already an LED on the board
    attached to pin 13.

  created 2021
  by Benjamin Schadde
  
  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Button
  https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/
#include <Servo.h>

// define used pins
const int pin_button_dig = 2; // the number of digital the pushbutton pin
const int pin_button_an = 1;  // the number of analog pushbutton pin
const int pin_led =  13;      // the number of the LED pin
const int pin_servo = 9;      // the number of the servo pin

// define goal positions for servo
const int pos_start = 0;      // start position in °
const int pos_end = 90;       // end position in °
const int pos_threshold = 3;  // thrshold in °

// additional variables
int button_state_dig = 0;     // variable for reading the pushbutton status

Servo my_servo;               // create servo object to control a servo
                              // twelve servo objects can be created on most boards

void setup()
{
  // initialize serial output
  Serial.begin(9600);
  
  // initialize the LED pin as an output:
  pinMode(pin_led, OUTPUT);
  
  // initialize the pushbutton pin as an input:
  pinMode(pin_button_dig, INPUT);

  // attaches the servo on defined pin to the servo object
  my_servo.attach(pin_servo);
}


void loop()
{
  // read the state of the pushbutton value:
  button_state_dig = digitalRead(pin_button_dig);

  // check if the pushbutton is pressed. If it is, the button_state_dig is HIGH:
  if (button_state_dig == HIGH)
  {
    // turn LED on:
    digitalWrite(pin_led, HIGH);

    // check if servo is already in position
    if(abs(pos_end - my_servo.read()) > pos_threshold)
    {
      // rotate servo to end position
      my_servo.write(pos_end);
    }
  }
  else
  {
    // turn LED off:
    digitalWrite(pin_led, LOW);

    // check if servo is already in position
    if(abs(pos_start - my_servo.read()) > pos_threshold)
    {
      // rotate servo to end position
      my_servo.write(pos_start);
    }
  }

  Serial.print("Current position of servo: ");
  Serial.println(my_servo.read());
}
