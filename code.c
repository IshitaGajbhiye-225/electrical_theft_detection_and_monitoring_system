#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

// Analog pins for ACS712 sensors
const int sensorPin1 = A0;
const int sensorPin2 = A3;
const int sensorPin3 = A6;

// Averaging settings
const int numSamples = 100;

// ACS712 calibration values
const float VREF = 2.35; // Midpoint voltage (no current)
const float sensitivity = 0.185; // For 5A version: 185mV per Amp

float c1=0;
float c2=0;
float c3=0;
float ct=0;
float actual=0;
int smscnt=0;
int cntdn=10;
float current1;
float current2;
float current3;
String str1;

void setup() {
  // Set up serial for debugging (optional)
  Serial.begin(9600);
  
  // Initialize LCD
  lcd.init();
  lcd.setBacklight(true);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
  delay(1000);
  lcd.clear();
}

void loop() {
  
  float voltage1 = readAveragedVoltage(sensorPin1);
  float voltage2 = readAveragedVoltage(sensorPin2);
  float voltage3 = readAveragedVoltage(sensorPin3);

  current1 = (voltage1 - VREF) / sensitivity;
  current2 = (voltage2 - VREF) / sensitivity;
  current3 = (voltage3 - VREF) / sensitivity;
  if(current1<0.30){current1=0;}
  if(current2<0.30){current2=0;}
  if(current3<0.30){current3=0;}
  ct = current1 + current2;
  ct = ct + current3;
  actual = current1 + current2;
  actual = actual + 0.05;
  if(ct > actual){
     lcd.setCursor(14, 0);
     lcd.print("Theft ");
     lcd.setCursor(14, 1);
     lcd.print("Occur ");
     if(smscnt==0){updatesms();smscnt=1;}
     if(cntdn>1){cntdn--;}
     if(cntdn==0){cntdn=10;smscnt=0;}
     
  }
  else{
     lcd.setCursor(14, 0);
     lcd.print("  NO  ");
     lcd.setCursor(14, 1);
     lcd.print("Theft ");
  }
  // Display on LCD
  
  lcd.setCursor(0, 0);
  lcd.print("Total:");
  lcd.print(ct, 2);
  lcd.print("A ");
  
  lcd.setCursor(0, 1);
  lcd.print("Legal:");
  lcd.print(actual, 2);
  lcd.print("A ");

  lcd.setCursor(0, 2);
  lcd.print("M1:");
  lcd.print(current1, 2);
  lcd.print("A ");

  //lcd.setCursor(0, 2);
  lcd.print(" M2:");
  lcd.print(current2, 2);
  lcd.print("A");

  lcd.setCursor(0, 3);
  lcd.print("U3:");
  lcd.print(current3, 2);
  lcd.print("A");
  delay(1000); 
  
}

float readAveragedVoltage(int pin) {
  long sum = 0;
  for (int i = 0; i < numSamples; i++) {
    sum += analogRead(pin);
    delayMicroseconds(100); // Small delay between samples
  }
  float averageADC = sum / (float)numSamples;
  float voltage = (averageADC / 4095.0) * 3.3; // ESP32 uses 0-3.3V reference
  return voltage;
}

void updatesms(){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(" SMS-1 ");
      
      Serial2.println("AT+CMGS=\"+919322442742\"\r");delay(1000);
       str1 = "Theft Occur!!.. Total:" + String(ct) + " ,Actual:" + String(actual) + ", L1:" + String(current1) + ", L2:" + String(current2) + ", L3:" + String(current3) + "Amp";
      Serial2.println(str1);
      delay(100);
      Serial2.println((char)26);// ASCII code of CTRL+Z
      delay(2000);
      Serial.println(str1);

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(" SMS-2 ");
      
      Serial2.println("AT+CMGS=\"+919172246069\"\r");delay(1000);
       str1 = "Theft Occur!!.. Total:" + String(ct) + " ,Actual:" + String(actual) + ", L1:" + String(current1) + ", L2:" + String(current2) + ", L3:" + String(current3) + "Amp";
      Serial2.println(str1);
      delay(100);
      Serial2.println((char)26);// ASCII code of CTRL+Z
      delay(2000);
      Serial.println(str1);

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(" SMS-3 ");
      
      Serial2.println("AT+CMGS=\"+919607151935\"\r");delay(1000);
       str1 = "Theft Occur!!.. Total:" + String(ct) + " ,Actual:" + String(actual) + ", L1:" + String(current1) + ", L2:" + String(current2) + ", L3:" + String(current3) + "Amp";
      Serial2.println(str1);
      delay(100);
      Serial2.println((char)26);// ASCII code of CTRL+Z
      delay(2000);
      Serial.println(str1);

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(" SMS-4 ");
      
      Serial2.println("AT+CMGS=\"+919021928749\"\r");delay(1000);
       str1 = "Theft Occur!!.. Total:" + String(ct) + " ,Actual:" + String(actual) + ", L1:" + String(current1) + ", L2:" + String(current2) + ", L3:" + String(current3) + "Amp";
      Serial2.println(str1);
      delay(100);
      Serial2.println((char)26);// ASCII code of CTRL+Z
      delay(2000);
      Serial.println(str1);

}