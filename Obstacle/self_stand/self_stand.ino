
#include <Servo.h>

// Create a Servo object
Servo myservoOne;
Servo myservoTwo;


#include <SoftwareSerial.h>

// Define the pins for the software serial communication
const int rxPin = 2; // Receive pin
const int txPin = 3; // Transmit pin

// Create a SoftwareSerial object
SoftwareSerial mySerial(rxPin, txPin);

#define IN1 A0
#define IN2 A1
#define IN3 A2
#define IN4 A3
#define ENA 5
#define ENB 6


#define TRIGGER_PIN 8
#define ECHO_PIN 9


bool manual = true;-- manual r auto r jnno

bool left = false;
bool right = false;-- arm

void setup() {
  // Initialize the hardware serial communication for debugging
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial port to connect
  }
-------------------ekbar run hoy void setup.. set kore dey bibhinno jinish
-- serial.begin(9600)------- serial monitor e amra dekte parbo ki kore robot
---while---- serial monitor open na hoile kono code kaaj korbena


  // Initialize the software serial communication
  mySerial.begin(9600); ---- bluetooth connection rxtx 

  //Initialise the Motor outpu pins--motor er pin(output port) motor diver k instruction dicchi tai output
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);

  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);

-----shb low thake jate stop thake gari
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
-----speed 0 jate na chole
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

----------ultrasonic sensor
ekta diye sound dei arekta diye set kori.. koto durutto otikrom kore

  pinMode(TRIGGER_PIN, OUTPUT); // Set trigger pin as output
  pinMode(ECHO_PIN, INPUT);    // Set echo pin as input

  Serial.println("");
  delay(100);
-------servomotor attach korsi
  myservoTwo.attach(10);
  myservoOne.attach(11);
------ekta k 0 position e ekta 180 te upore thakbe
  myservoOne.write(0);
  myservoTwo.write(180);

}
-----repeatly run korbe

void loop() {


----arm er jnno right true hole right arm nambe 90 degree

    if (right==true) { //right
      Serial.println("Right");
      for (int i = 0; i < 90; i++) { // servo pin 10
        myservoOne.write(i);
        delay(5);
      }
------arm upore utbe
      delay(1000);
      for (int i = 90; i > 0; i--) { // servo pin 10
        myservoOne.write(i);
        delay(5);
      }
      delay(1000);
      right=false; ----- r jate repeat na hoy
    } 
  
  
  if (left==true) {
      Serial.println("Left");
      for (int i = 180; i > 90; i--) { // servo pin 10
        myservoTwo.write(i);
        delay(5);
      }
      delay(1000);
      for (int i = 90; i < 180; i++) { // servo pin 10
        myservoTwo.write(i);
        delay(5);
      }
      delay(1000);
      left = false;
    }
  


--------manual false hole manual cholbe 

  if (manual == false) {
    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(2);
---obstacle avoid korbe ekhane

    // Send a 10us pulse to the trigger pin
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);

    // Measure the duration of the echo pulse
    unsigned long duration = pulseIn(ECHO_PIN, HIGH);

    // Calculate the distance based on the speed of sound (343 meters per second)
    // Divide by 2 because the sound wave travels to the object and back
    float distance = (duration * 0.0343) / 2.0;

    Serial.println(distance);

    if (distance > 2 && distance < 20) {
      gobackturn();  ---- pichay jaya abr dane jabe
    } else {
      analogWrite(ENA, 210);
      analogWrite(ENB, 210);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    }---- shamner dike cholte thakbe jdi 20cm er modde kisu na pay obstacle

  }





  // Read data from software serial and send to hardware serial

--bluetooth available data thakle 
  if (mySerial.available()) {    
    char data = mySerial.read();
    Serial.println(data);
    Serial.println();
manual m
auto a
left arm l
right arm r

    if (data == 'm') {
      manual = true;
    } else if (data == 'a') {
      manual = false;
    } else if (data == 'l') {
      left = true;
    } else if (data == 'r') {
      right = true;
    }


--------character pathay int e pathaite parena tai emne dise
    char tempArray[2] = {data, '\0'};
    int intValue = atoi(tempArray);
    //int msg = data.toInt();
    switch (intValue) {
      case 1:    --on ashle forward
        Serial.println("Forward");
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        break;
      case 2:  ----backward
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        break;
      case 3:  ----right
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        break;
      case 4:  ----left
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        break;


      case 5: ----stop
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        break;

----------speed high 255
      case 6:
        analogWrite(ENA, 180);
        analogWrite(ENB, 180);
        break;
      case 7:
        analogWrite(ENA, 220);
        analogWrite(ENB, 220);
        break;
      case 8:
        analogWrite(ENA, 250);
        analogWrite(ENB, 250);
        break;

    }
  }


}




void gobackturn() {
  Serial.println("Go back Trun");
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  delay(1000);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(300);
  analogWrite(ENA, 240);
  analogWrite(ENB, 240);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(600);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(500);
}
