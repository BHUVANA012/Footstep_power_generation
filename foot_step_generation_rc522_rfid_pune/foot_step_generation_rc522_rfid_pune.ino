#include <SPI.h>
#include <MFRC522.h>
int count = 0;
#include <LiquidCrystal.h>
LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);
int rohit=0,sonu=0;
#define SS_PIN 10
#define RST_PIN 9
#define light  4 //lcd
#define charge  2 //RELAY
#define mobile  3 //boostcircuit
int lec=0;
int fac=0;
int st1=0,st2=0;
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.


void setup() 
{
 lcd.begin(16,2);
 pinMode(charge,INPUT);
 pinMode(mobile,OUTPUT);
 pinMode(light,OUTPUT);
 digitalWrite(mobile,LOW);
 lcd.print("RFID ");
 Serial.begin(9600);   // Initiate a serial communication
 SPI.begin();      // Initiate  SPI bus
 mfrc522.PCD_Init();   // Initiate MFRC522
 Serial.println("Put your card to the reader...");
 Serial.println();
}
void loop() 
{
 lcd.setCursor(0, 1);
 lcd.print("swipe your card"); //RFID insertion
 fac=digitalRead(charge);
 if(fac==LOW)
 {
  lcd.setCursor(0, 0);
  digitalWrite(light,HIGH);
  lcd.print("--   charging--"); 
  delay(2000);
  //digitalWrite(light,LOW);
  delay(2000);
  
 }
 else
 {
  lcd.setCursor(0, 0);
  lcd.print("--No charging--"); 
  digitalWrite(light,LOW);
 }
 rfid();
 
}
void rfid()
{
  
 if( ! mfrc522.PICC_IsNewCardPresent()) 
 {
  return;
 }
 // Select one of the cards
 if ( ! mfrc522.PICC_ReadCardSerial()) 
 {
  return;
 }
 //Show UID on serial monitor
 Serial.print("UID tag :");
 String content= "";
 byte letter;
 for (byte i = 0; i < mfrc522.uid.size; i++) 
 {
  Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
  Serial.print(mfrc522.uid.uidByte[i], HEX);
  content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
  content.concat(String(mfrc522.uid.uidByte[i], HEX));     
 }
  
 Serial.println();
 content.toUpperCase();
 if (content.substring(1) == "21 0E BA 1D")  //RFID tag for switchin on the circuit 
 {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("--Charging ON---");
  Serial.print("--Charging ON--");
  digitalWrite(mobile,LOW);  
 }
  
 else if(content.substring(1) == "F0 B2 55 1F")  //RFID tag for switching off the circuit
 {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("--   Admin  ---");
  lcd.setCursor(0, 1);
  lcd.print("--Charging OFF---");
  Serial.print("--Charging ON--");
  digitalWrite(mobile,HIGH);
 }
 else  
 {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("INVALID CARD");
  delay(400);   
  delay(1000);  
 }
 lcd.clear();
}
