#include <SoftwareSerial.h>
#include <EmonLib.h>

EnergyMonitor emon1;   // Create an instance

int CT_pin = A0;       // CT sensor pin connected to A0 pin of Arduino
int relay_pin = 7;     // Changed to avoid conflict
int sensorPin = A1;    // Select the input pin for the photodiode
int ledPin = 6;        // Select the pin for the LED (changed to avoid conflict)
int sensorValue = 0;   // Variable to store the value coming from the sensor

#define GSM_TX 2
#define GSM_RX 3

SoftwareSerial gsmSerial(GSM_TX, GSM_RX);

bool callMade = false;       // Track if a call has been made
bool messageSent = false;    // Track if a message has been sent

#define THINGSPEAK_CHANNEL_ID xxxxxxx // Replace with your ThingSpeak channel ID
#define THINGSPEAK_API_KEY "xxxxxxxxxxxxxxxx"  // Enter your ThingSpeak Write API Key here

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(relay_pin, OUTPUT);
  emon1.current(CT_pin, 32.59);  // Current: input pin, calibration.
  Serial.begin(9600);
  gsmSerial.begin(9600);

  Serial.println("Initializing GSM module...");
  delay(2000);

  gsmSerial.println("AT");
  delay(1000);
  if (gsmSerial.find("OK")) {
    Serial.println("GSM module is ready.");
  } else {
    Serial.println("Error: GSM module not responding.");
    while (1);
  }
}

void loop() {
  // Sensor reading
  sensorValue = analogRead(sensorPin);
  Serial.print("Photo diode value = ");
  Serial.println(sensorValue);

  if (sensorValue < 15) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(relay_pin, HIGH);
    delay(5000);
  } else {
    digitalWrite(ledPin, LOW);
    digitalWrite(relay_pin, LOW);
    delay(5000);
  }

  double Irms = emon1.calcIrms(1480);

  Serial.print("POWER = ");
  Serial.println(Irms * 230.0);
  Serial.print("IRMS = ");
  Serial.println(Irms);
  Serial.print("IM = ");
  Serial.println(Irms * 1.414);

  if (Irms <= 3.3 && Irms > 2.50) {
    // Check if a call has not been made yet
    if (!callMade) {
      Serial.println("Making a call...");
      gsmSerial.println("ATD+91xxxxxxxxxx;");  // Enter the phone number to receive the fault call
      delay(10000); // Wait for 10 seconds (adjust as needed)
      gsmSerial.println("ATH"); // Hang up the call
      callMade = true; // Mark that the call has been made
    }

    // Check if a message has not been sent yet
    if (!messageSent) {
      Serial.println("Sending a message...");
      gsmSerial.println("AT+CMGF=1"); // Set SMS mode to text mode
      delay(1000);
      gsmSerial.println("AT+CMGS=\"+91xxxxxxxxxx\"");  // Enter the phone number to receive the fault SMS
      delay(1000);
      gsmSerial.print("!!HLO OPERATOR STREET LIGHT FAULT OCCURRED!!"); // Replace with your message
      delay(1000);
      gsmSerial.write(26); // Send Ctrl+Z to indicate the end of the message
      delay(5000); // Wait for a response (adjust as needed)
      messageSent = true; // Mark that the message has been sent
    }
  } else {
    // Reset the flags to allow calling and messaging again
    callMade = false;
    messageSent = false;
  }

  // Push data to ThingSpeak
  sendDataToThingSpeak(sensorValue, Irms);
}

void sendDataToThingSpeak(int photodiodeValue, float IRMS) {
  // GSM module setup
  gsmSerial.println("AT");
  delay(1000);
  gsmSerial.println("AT+CGATT=1");
  delay(1000);
  gsmSerial.println("AT+CSTT=\"internet.ng.airtel.com\"");
  delay(1000);
  gsmSerial.println("AT+CIICR");
  delay(1000);
  gsmSerial.println("AT+CIFSR");
  delay(3000);
  gsmSerial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");
  delay(3000);
  gsmSerial.println("AT+CIPSEND");
  delay(2000);

  // Send data to ThingSpeak
  String postStr = String(THINGSPEAK_API_KEY);
  postStr += "&field1=";
  postStr += String(photodiodeValue);
  postStr += "&field2=";
  postStr += String(IRMS);
  postStr += "\r\n\r\n";

  gsmSerial.print("POST /update HTTP/1.1\n");
  gsmSerial.print("Host: api.thingspeak.com\n");
  gsmSerial.print("Connection: close\n");
  gsmSerial.print("X-THINGSPEAKAPIKEY: ");
  gsmSerial.print(THINGSPEAK_API_KEY);
  gsmSerial.print("\n");
  gsmSerial.print("Content-Type: application/x-www-form-urlencoded\n");
  gsmSerial.print("Content-Length: ");
  gsmSerial.print(postStr.length());
  gsmSerial.print("\n\n");
  gsmSerial.print(postStr);
  gsmSerial.print((char)26);

  delay(5000); // Delay before next update
}
