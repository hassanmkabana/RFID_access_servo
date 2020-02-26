/*
 * 
 Attendance system

 by Isaac Mwondi.
 * 
 */
 #include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 8
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int buzer = 7;
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 int servo = 6;
 Servo servo1;
 
void setup() 
{ 
  servo1.attach(servo);
  Serial.begin(9600);   // Initiate a serial communication
  lcd.begin(16, 2);
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  lcd.setCursor(0, 0);
  lcd.print("place your card");
  Serial.println();
  pinMode(buzer, OUTPUT);
   servo1.write(0);

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
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
  Serial.print("Message : ");
  content.toUpperCase();
 
  if (content.substring(1) == "83 0B 34 03") //change here the UID of the card/cards that you want to give access
  { 
    //digitalWrite(servo, HIGH);
    servo1.write(90);
    Serial.println("Welcome Hassan!");
    Serial.println();
    lcd.setCursor(0, 0);
    lcd.print("Welcome Hassan!");
    digitalWrite(buzer, HIGH);
    delay(300);
    digitalWrite(buzer, LOW);
    delay(300);
    digitalWrite(buzer, HIGH);
    delay(300);
    digitalWrite(buzer, LOW);
    delay(300);
    delay(1000);
    lcd.setCursor(0, 0); 
    lcd.print("place your card");
    //digitalWrite(servo, HIGH);
    servo1.write(0);
  }
  else if(content.substring(1) != "83 0B 34 03")
   { 
    //digitalWrite(servo, LOW);
    servo1.write(0);
    Serial.println("ACCESS DENIED!");
     Serial.println();
     lcd.setCursor(0, 0);
    lcd.print("ACCESS DENIED!");
      digitalWrite(buzer, HIGH);
     delay(3000);
      digitalWrite(buzer, LOW);
     delay(300);
      lcd.setCursor(0, 0); 
    lcd.print("place your card");
   } 
  } 
