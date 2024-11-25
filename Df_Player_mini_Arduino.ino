#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "Ultrasonic.h"

// Use pins 10 and 11 to communicate with DFPlayer Mini
static const uint8_t PIN_MP3_TX = 2; // Connects to module's RX 
static const uint8_t PIN_MP3_RX = 3; // Connects to module's TX 
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);

// Create the Player object
DFRobotDFPlayerMini player;

// Define the pins for ultrasonic sensor
const int trigPin = 9;
const int echoPin = 8;

// Create Ultrasonic object
Ultrasonic ultrasonic(trigPin, echoPin);

void setup() {
  // Init USB serial port for debugging
  Serial.begin(9600);
  // Init serial port for DFPlayer Mini
  softwareSerial.begin(9600);

  // Start communication with DFPlayer Mini
  if (player.begin(softwareSerial)) {
    Serial.println("OK");

    // Set volume to maximum (0 to 30).
    player.volume(20);
  } else {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }
}

void loop() {
  // Read distance from ultrasonic sensor
  long distance = ultrasonic.distanceRead();

  // Check if an object is detected within a certain range (adjust as needed)
  if (distance > 0 && distance < 20) {
    // Play the first MP3 file on the SD card
    player.play(1);
    delay(1000); // Delay to avoid repeated triggering
  }

  // You can add additional code here for other functionalities
}
