/*
 * Optical Communication System - Receiver
 */

const int SENSOR_PIN = A0;
const int BIT_PERIOD = 15;   
const int THRESHOLD_OFFSET = 6; 

int avg_val = 0; 

void setup() {
  Serial.begin(9600);
  Serial.println("Receiver Ready (Calibrating...)");

  long sum = 0;
  for(int i=0; i<100; i++) {
    sum += analogRead(SENSOR_PIN);
    delay(2);
  }
  avg_val = sum / 100;
  
  Serial.print("Baseline Calibrated: ");
  Serial.println(avg_val);
}

bool isValidASCII(char c) {
  return (c >= 32 && c <= 126) || c == 10 || c == 13;
}

void loop() {
  int current_val = analogRead(SENSOR_PIN);
  
  if (current_val > avg_val + THRESHOLD_OFFSET) {
    delay(BIT_PERIOD + (BIT_PERIOD / 2)); 
    char receivedChar = readByte();
    if (isValidASCII(receivedChar)) {
      Serial.write(receivedChar);
    }
    delay(BIT_PERIOD); 
  }
}

char readByte() {
  char myData = 0;
  for (int i = 0; i < 8; i++) {
    int reading = analogRead(SENSOR_PIN);
    if (reading > avg_val + THRESHOLD_OFFSET) {
      bitWrite(myData, i, 1);
    } else {
      bitWrite(myData, i, 0);
    }
    delay(BIT_PERIOD);
  }
  return myData;
}