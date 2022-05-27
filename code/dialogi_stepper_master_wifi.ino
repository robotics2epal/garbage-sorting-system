// Είναι ο κάτω stepper για το γυαλί
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>




// https://circuitdigest.com/microcontroller-projects/arduino-stepper-motor-control-tutorial
// https://randomnerdtutorials.com/esp8266-nodemcu-stepper-motor-28byj-48-uln2003/




///watch video for details of lines below
//static const uint8_t D0   = 16;
//static const uint8_t D1   = 5;
//static const uint8_t D2   = 4;
//static const uint8_t D3   = 0;
//static const uint8_t D4   = 2;
//static const uint8_t D5   = 14;
//static const uint8_t D6   = 12;
//static const uint8_t D7   = 13;
//static const uint8_t D8   = 15;
//static const uint8_t D9   = 3;
//static const uint8_t D10  = 1;



//
//
//
#include <AccelStepper.h>  // την εγκαθηστώ από τις βιβλιοθήκες

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
int glass = 0;       // flag Όταν εντοπίσει μέταλλο γίνεται 1

// ULN2003 Motor Driver Pins για τα μέταλλα
#define IN_UP_1 5
#define IN_UP_2 4
#define IN_UP_3 0
#define IN_UP_4 2

int detectOnce = 0; // flag Όταν εντοπίσει υλικό να μην μπαίνει συνέχεια στη ρουτίνα
int arxikiLDR = 0;
// initialize the stepper library
AccelStepper stepper_pano(AccelStepper::HALF4WIRE, IN_UP_1, IN_UP_3, IN_UP_2, IN_UP_4);
//
//
//



const char* ssid = "ESP_D54736";  // SSID of esp8266
//const char* password = "123";   //
bool toggle=0;                  //Variable to switch on and off the solenoid
ESP8266WebServer server(80);    //Specify port for TCP connection

void handleRoot() {
  toggle=!toggle;               //Toggling Led Variable
    digitalWrite(16,toggle);     //Toggle Led
        String s = "  <!DOCTYPE HTML>\n<html><h1>Esp8266 Communication</h1> ";
        s += "<p>Success!!!</html>\n";  
        server.send(200,"text/html",s);      //Reply to the client

        Serial.println("Kato dialogi");
 
 //       Serial.println("0");
        stepper_pano.runToNewPosition(0);
        delay(3000);

        // glass = digitalRead(D5) να ενεργοποιηθεί σε κανονικές συνθήκες
        if (glass == 0) {  // demo
          glass = 1;
        }
        else {
          glass = 0;
        }
        int c = analogRead(A0);
        Serial.print("A0  ");
        Serial.println(c);
        if (c < arxikiLDR - 100) {  
          glass = 0;
        }
        else {
          glass = 1;
        }       
     
        if(glass == 1) {                  // το αδειάζει στα γυαλιά
            Serial.println("gyali ");
            stepper_pano.runToNewPosition(-1224);
            delay(1000);
 //           Serial.println("0");
            stepper_pano.runToNewPosition(0);
            delay(1000);
        }
        else {                          // το αδειάζει στα πλαστικά
            Serial.println("plastiko ");
            stepper_pano.runToNewPosition(1224);
            delay(1000);
//            Serial.println("0");
            stepper_pano.runToNewPosition(0);
            delay(1000);
       }
 

c = analogRead(A0);
       Serial.print("A0  ");
   Serial.println(c);

        

        
}

void setup() {
  delay(200);                           //Stable Wifi
  Serial.begin(115200);                 //Set Baud Rate

  pinMode(A0 , INPUT);
  arxikiLDR = analogRead(A0);
  Serial.print("arxikiLDR  ");
  Serial.println(arxikiLDR);
  
  pinMode(16, OUTPUT);                   //Led/Solenoid at pin 2
  WiFi.softAP(ssid);//, password);      //In Access Point Mode

  IPAddress myIP = WiFi.softAPIP();     //Check the IP assigned. Put this Ip in the client host.
  Serial.print("AP IP address: ");
  Serial.println(myIP);         //Print the esp8266-01 IP(Client must also be on the save IP series)
  server.on("/Led", handleRoot);           //Checking client connection
  server.begin();                       // Start the server
  Serial.println("Server started");

// set the speed and acceleration
  stepper_pano.setMaxSpeed(1000);
  stepper_pano.setAcceleration(1000);
    
}

void loop() {
  // Check if a client has connected. On first connection switch on the Solenoid on next switch off.
  server.handleClient();
}
