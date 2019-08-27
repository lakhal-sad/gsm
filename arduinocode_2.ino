/*
 * SIM800L SMS RELAY v1.0
 * Arduino Hardware (Author): Nano V3 (ATmega328)
 * Arduino IDE (Author): 1.6.9
 * T.K.Hareendran/2018
 */

#include <SoftwareSerial.h>
SoftwareSerial mySerial(10,11);  // (Rx,Tx  > Tx,Rx) 

char incomingByte; 
String inputString;
int relay_1 = 13; // Output for Relay 1 
int relay_2 = 12; // output for Relay 2

void setup() 
{
      pinMode(relay_1, OUTPUT);
      pinMode(relay_2, OUTPUT);
      digitalWrite(relay_1, LOW); // Initial state of the relay
      digitalWrite(relay_2, LOW);
      Serial.begin(9600);
      mySerial.begin(9600); 

     while(!mySerial.available()){
        mySerial.println("AT");
        delay(1000); 
        Serial.println("Connecting...");
        }
      Serial.println("Connected!");  
      mySerial.println("AT+CMGF=1");  //Set SMS to Text Mode 
      delay(1000);  
      mySerial.println("AT+CNMI=1,2,0,0,0");  //Procedure to handle newly arrived messages(command name in text: new message indications to TE) 
      delay(1000);
      mySerial.println("AT+CMGL=\"REC UNREAD\""); // Read Unread Messages
     }

void loop()
{  
  if(mySerial.available()){
      delay(100);

      // Serial Buffer
      while(mySerial.available()){
        incomingByte = mySerial.read();
        inputString += incomingByte; 
        }

        delay(10);      

        Serial.println(inputString);
        inputString.toUpperCase(); // Uppercase the Received Message

        //turn RELAY ON or OFF
        if (inputString.indexOf("1 ON") > -1){
          digitalWrite(relay_1, HIGH);
          
          Serial.print("Reply====>>>> ");
          Serial.println("Relay 1 Status Active");
          }
         if (inputString.indexOf("1 OFF") > -1){
          digitalWrite(relay_1, LOW);
          Serial.print("Reply====>>>> ");
          Serial.println("Relay 1 Status Off");
          }          

        delay(50);
        if (inputString.indexOf("2 ON") > -1){
          digitalWrite(relay_2, HIGH);
           Serial.print("Reply====>>>> ");
          Serial.println("Relay 2 Status Active");
          }
         if (inputString.indexOf("2 OFF") > -1){
          digitalWrite(relay_2, LOW);
          Serial.print("Reply====>>>> ");
          Serial.println("Relay 2 Status Off");
          }  
        

        //Delete Messages & Save Memory
        if (inputString.indexOf("OK") == -1){
        mySerial.println("AT+CMGDA=\"DEL ALL\"");

        delay(1000);}

        inputString = "";
  }
}
