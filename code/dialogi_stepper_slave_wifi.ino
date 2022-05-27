// Είναι ο πάνω stepper για το μέταλλο


#include <ESP8266WiFi.h>
#include <WiFiClient.h> 


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

// ULN2003 Motor Driver Pins για τα μέταλλα
#define IN_UP_1 5
#define IN_UP_2 4
#define IN_UP_3 0
#define IN_UP_4 2

int detectOnce = 0; // flag Όταν εντοπίσει υλικό να μην μπαίνει συνέχεια στη ρουτίνα
int metal = 0;      // flag Όταν εντοπίσει μέταλλο γίνεται 1
int count = 0;      // Δημιουργείμια καθυστέρηση στην επιλογή του μετάλλου. Αν εξαντληθεί δεν είναι μέταλλο

// initialize the stepper library
AccelStepper stepper_pano(AccelStepper::HALF4WIRE, IN_UP_1, IN_UP_3, IN_UP_2, IN_UP_4);
//
//
//


//Ip of the Host(Our Case esp8266-01 as server. Its the ip of the esp8266-01 as Access point)
const char* host = "192.168.4.1"; 

void setup() {
  Serial.begin(115200);          //Baud Rate for Communication
  delay(10);                     //Baud rate prper initialization
  pinMode(D5,INPUT);             //Pin D5 Έλεγχος για μέταλλο

 
  WiFi.mode(WIFI_STA);           //NodeMcu esp12E in station mode
  WiFi.begin("ESP_D54736");      //Connect to this SSID. In our case esp-01 SSID.  

  while (WiFi.status() != WL_CONNECTED) {      //Wait for getting IP assigned by Access Point/ DHCP. 
  //Our case  esp-01 as Access point will assign IP to nodemcu esp12E.
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());             //Check out the Ip assigned by the esp12E

  // set the speed and acceleration
  stepper_pano.setMaxSpeed(2000);
  stepper_pano.setAcceleration(2000);
  
}

void loop() {
    if ((digitalRead(D0) == 0) && (detectOnce ==0)) {
        Serial.println("Detect");
        detectOnce =1;

        metal = 0;
        count = 0;
        Serial.println("------------------");
        while (metal == 0 && count < 6000) {   //Εντοπίζει αν είναι μέταλλο ή όχι
        Serial.println(count);
            metal = digitalRead(D5);   
            count++;
        }
        
        if(count < 5999) {  //Βρέθηκε το μέταλλο
              delay(2000);
              Serial.println("1024");             // το αδειάζει στα μέταλλα
              stepper_pano.runToNewPosition(1024);
              delay(1000);
              Serial.println("0");
              stepper_pano.runToNewPosition(0);
              delay(1000);
        }
        else
        {
              Serial.println("-1024");            // το οδηγεί στην επόμενη διαλογή
              stepper_pano.runToNewPosition(-1024);
              delay(1000);
              Serial.println("0");
              stepper_pano.runToNewPosition(0);
              delay(1000);

              Serial.print("connecting to ");   // κάνει σύνδεση στο άλλο esp
              Serial.println(host);
              // Use WiFiClient class to create TCP connections
              WiFiClient client;
              const int httpPort = 80;
                if (!client.connect("192.168.4.1", httpPort)) {
                  Serial.println("connection failed");
                  return;
                   }    
              //Request to server to activate the led
              client.print(String("GET ") +"/Led"+" HTTP/1.1\r\n" +    // εισοποιεί το άλλο esp
                           "Host: " + host + "\r\n" + 
                           "Connection: close\r\n\r\n");         
              delay(10);
              // Read all the lines of the reply from server and print them to Serial Monitor etc
              while(client.available()){
                String line = client.readStringUntil('\r');
                Serial.print(line);
              }
              //Close the Connection. Automatically
              Serial.println();
              Serial.println("closing connection");             
              
        }//End if
    }
    if (digitalRead(D0) == 1) {
        Serial.println("No ");
        detectOnce =0;
    }

 
    delay(100);

}//End Loop
