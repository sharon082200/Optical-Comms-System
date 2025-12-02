/*
 * Optical Communication System - Transmitter
 */

const int LED_PIN = 12;      
const int BIT_PERIOD = 15;   
const int HALF_PERIOD = 7;   

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.println("Transmitter Ready. Type a message:");
}

void loop() {
  if (Serial.available() > 0) {
    char myChar = Serial.read();
    sendByte(myChar);
    delay(60); 
  }
}

void sendOneWave() {
  digitalWrite(LED_PIN, HIGH);
  delay(HALF_PERIOD);
  digitalWrite(LED_PIN, LOW);
  delay(BIT_PERIOD - HALF_PERIOD); 
}

void sendZero() {
  digitalWrite(LED_PIN, LOW);
  delay(BIT_PERIOD);
}

void sendByte(char myData) {
  sendOneWave(); // Start Bit
  for (int i = 0; i < 8; i++) {
    if (bitRead(myData, i) == 1) {
      sendOneWave(); 
    } else {
      sendZero();
    }
  }
  sendZero(); // Stop Bit
}