/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>
/* PINS */
const int PIN_PHOTO = A0;
const int PIN_SERVO_HL = 9;
const int PIN_SERVO_LR = 10;

/* POSITIONS */
const int HI_POS  = 120;
const int LOW_POS = 27;
const int RIGHT_POS = 180-45;
const int LEFT_POS  = 45;


#define P_SIZE (8+1)


Servo myservo_hl;  // create servo object to control hight-low (vertical)
Servo myservo_lr;  // create servo object to control leftt-right (horisontal)

int pos_hl = 90;    // variable to store the servo position
int pos_lr = 90;    // variable to store the servo position



void move_platform(int pos_hl, int pos_lr) {
  myservo_hl.write(pos_hl);
  myservo_lr.write(pos_lr);  
} 

int read_light_sensor() {
  return analogRead(PIN_PHOTO);  
}

// move platform to check position find new maximum, return index of position 
int check_position(int P[P_SIZE][2], int size) {
  int min_value = 10000;  // worst unpossible
  int max_value = -1;     // worst unpossible
  int value = min_value;
  int best_pos = 0;
  for (int i = 0; i < size; i++) {
    move_platform(P[i][0], P[i][1]);
    delay(100);
    value = read_light_sensor();
    Serial.print(i); Serial.print(": ");
    Serial.print(P[i][0]); Serial.print(" ");
    Serial.print(P[i][1]); Serial.print(" = ");
    Serial.print(value); Serial.println(" / ");
    if (value < min_value) {
      best_pos = i;
      min_value = value;
    }
    if (value > max_value) {
      max_value = value;
    }
  }
  Serial.print(best_pos); Serial.print(": ");
  Serial.print(P[best_pos][0]); Serial.print(" "); Serial.print(P[best_pos][1]); 
  Serial.print(" val:"); Serial.print(min_value); 
  Serial.print(" nd:"); Serial.print((float)(max_value-min_value)/max_value);
  Serial.println();
  if ((float)(max_value-min_value)/max_value > 0.1) return best_pos;
  else return -1;
}


int P[P_SIZE][2];
int new_pos = 0;
int del = 0;
int r = 1;

//void set_p_cross(int pos_hl, int pos_lr) {
//  P[0][0] = pos_hl+0; P[0][1] = pos_lr-1;
//  P[1][0] = pos_hl-1; P[1][1] = pos_lr+0;
//  P[2][0] = pos_hl+1; P[2][1] = pos_lr+0;
//  P[3][0] = pos_hl+0; P[3][1] = pos_lr+1;    
//}
//void set_p_cross_x2(int pos_hl, int pos_lr) {
//  P[0][0] = pos_hl+0; P[0][1] = pos_lr+0;
//
//  P[1][0] = pos_hl+0; P[1][1] = pos_lr-1;
//  P[2][0] = pos_hl+0; P[2][1] = pos_lr-2;
//  P[3][0] = pos_hl-1; P[3][1] = pos_lr+0;
//  P[4][0] = pos_hl-2; P[4][1] = pos_lr+0;
//  P[5][0] = pos_hl+1; P[5][1] = pos_lr+0;
//  P[6][0] = pos_hl+2; P[6][1] = pos_lr+0;
//  P[7][0] = pos_hl+0; P[7][1] = pos_lr+1;    
//  P[8][0] = pos_hl+0; P[8][1] = pos_lr+2;    
//}

void set_p_square_r(int pos_hl, int pos_lr, int r=1) {
  P[0][0] = pos_hl+0; P[0][1] = pos_lr+0;
  
  P[1][0] = pos_hl+0; P[1][1] = pos_lr-r;
  P[2][0] = pos_hl-r; P[2][1] = pos_lr-r;
  P[3][0] = pos_hl-r; P[3][1] = pos_lr+0;
  P[4][0] = pos_hl-r; P[4][1] = pos_lr+r;    
  P[5][0] = pos_hl+0; P[5][1] = pos_lr+r;
  P[6][0] = pos_hl+r; P[6][1] = pos_lr+r;
  P[7][0] = pos_hl+r; P[7][1] = pos_lr+0;
  P[8][0] = pos_hl+r; P[8][1] = pos_lr-r;    
}

void setup() {
  myservo_hl.attach(PIN_SERVO_HL);  // attaches the servo on pin 9 to the servo object
  myservo_lr.attach(PIN_SERVO_LR);  // attaches the servo on pin 10 to the servo object

  Serial.begin(9600);
  pinMode(PIN_PHOTO, INPUT);

//  for(int i=0; i>P_SIZE; i++) {
//    P[i][0] = i * (HI_POS - LOW_POS) / P_SIZE;
//    P[i][1] = i * (RIGHT_POS - LEFT_POS) / P_SIZE; 
//  }
  delay(200);
  new_pos = 0;
  P[new_pos][0] = pos_hl;
  P[new_pos][1] = pos_lr;
  move_platform(pos_hl, pos_lr);
  del = 50;
  r = 1;
}


void loop() {
   
  //Serial.println(read_light_sensor());
  Serial.println(del);
  delay(del);
  
  set_p_square_r(P[new_pos][0],P[new_pos][1], r);

  new_pos = check_position(P, P_SIZE);
  if (new_pos == -1) { // bad luck
   r++;  
   new_pos = 0;
   del = del/2;
  } else {
    r = 1;
    if (new_pos == 0) { 
      if (del < 6*1000) del = del * 4; 
    }
    else del = 10;
  }
    
  move_platform(P[new_pos][0],P[new_pos][1]);
  
}
