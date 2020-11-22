/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

int HI_POS  = 120;
int LOW_POS = 27;


int LEFT_POS  = 45;
int RIGHT_POS = 180-45;

Servo myservo_hl;  // create servo object to control hight-low (vertical)
Servo myservo_lr;  // create servo object to control leftt-right (horisontal)

int pos_hl = 90;    // variable to store the servo position
int pos_lr = 90;    // variable to store the servo position


void setup() {
  myservo_hl.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo_lr.attach(10);  // attaches the servo on pin 10 to the servo object
}

void loop() {
  
  myservo_hl.write(pos_hl);
  myservo_lr.write(pos_lr);

  delay(2000);
  
  for (pos_hl = LOW_POS; pos_hl <= HI_POS; pos_hl += 1) { 
    myservo_hl.write(pos_hl);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

  for (pos_lr = LEFT_POS; pos_lr <= RIGHT_POS; pos_lr += 1) { 
    myservo_lr.write(pos_lr);              // tell servo to go to position in variable 'pos'
    delay(25);                       // waits 15ms for the servo to reach the position
  }

  for (pos_hl = HI_POS; pos_hl >= LOW_POS; pos_hl -= 1) { // goes from 180 degrees to 0 degrees
    myservo_hl.write(pos_hl);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

  for (pos_lr = RIGHT_POS; pos_lr >= LEFT_POS; pos_lr -= 1) { 
    myservo_lr.write(pos_lr);              // tell servo to go to position in variable 'pos'
    delay(25);                       // waits 15ms for the servo to reach the position
  }

  
}
