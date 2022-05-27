// include Servo library
#include <Servo.h>

// horizontal servo
Servo horizontal;

int servoh = 20;
int servoDay = 93;
int servoNight = 170;


// LDR pins
int ldrTR = 1; // LDR right
int ldrTL = 0; // LDR left

// Αποδεκτό φώς. Κάτω από αυτό θεψρούμε ότι είναι νύχτα
int LowLight = 500; 


void setup() {
  Serial.begin(9600);
  // servo connections
  horizontal.attach(8);

  // αρχικοποίηση servo στην ανατολή
  int servoh = horizontal.read();
  for (int i = servoh; i >= servoDay; i--) {  //Πάμε σιγά - σιγά στην θέση όπου θα ανατείλει ο ήλιος
       horizontal.write(i);        
       delay(100);
  }


 

 // delay(3000);
}





void loop() {
  int tr = analogRead(ldrTR); // Δεξί 
  int tl = analogRead(ldrTL); // Αριστερό
  Serial.print(tl);
  Serial.print(" ");
  Serial.print(tr);
  Serial.println(" ");
  
 // κίνση του servo

  int servoh = horizontal.read();
  if (servoh <= servoNight) {               // Αν είναι ημέρα
    if (tl > LowLight) {
      if (tl > tr) {                         // Η κίνηση του ήλιου
          servoh = ++servoh;
          horizontal.write(servoh);
          Serial.print("servoh ");
          Serial.println(servoh);
        }
    }
  }
  else {
      delay(2000);
      if (tl < LowLight) {
        day(); 
        delay(2000);
      }
  }
 delay(100);

//  delay(1000);
//night();
//  delay(1000);
//day(); 
}

void day(){
  Serial.println("Day ");

      for (int i = servoNight; i >= servoDay; i--) {  //Πάμε σιγά - σιγά στην θέση όπου θα ανατείλει ο ήλιος
          horizontal.write(i);        
          delay(100);
      }
}

void night(){
  Serial.println("Night");

      for (int i = servoDay; i <= servoNight; i++) {  //Πάμε σιγά - σιγά στην θέση όπου θα ανατείλει ο ήλιος
          horizontal.write(i);        
          delay(100);
      }
}
