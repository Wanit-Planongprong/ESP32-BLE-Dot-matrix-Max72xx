
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#define MAX_DEVICES 4 // Number of modules connected
#define CLK_PIN   14   // SPI SCK pin on UNO
#define DATA_PIN  12   // SPI MOSI pin on UNO
#define CS_PIN    15   // connected to pin 10 on UNO
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
textEffect_t scrollEffect = PA_SCROLL_LEFT;
textPosition_t scrollAlign = PA_LEFT;  // how to aligh the text
int scrollSpeed = 25;
int scrollPause = 0;
#define BUF_SIZE 50
char currentMessage[BUF_SIZE] = {""};
bool animateCase = false;
//String Cases = "Wellcome";
String Cases = "Pair your device with ESP32Display";
void Printcase();


#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
String message;
String message1;
char incomingChar;
BluetoothSerial SerialBT;

void setup() {
  P.begin();
 
  Serial.begin(115200);
  
  SerialBT.begin("ESP32Display"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

  
}

void loop ()  // This is a task.
  { 
    
    if (SerialBT.available()){
    char incomingChar = SerialBT.read();
    if (incomingChar != '\n')
    {
     message += String(incomingChar);
     //message.length();
     //message.trim();    // (" ","\t","\v","\f","\r","\n") from String
     //message.replace("\n", "");
     Cases = message;
     
      Serial.println(message);
    }
    else{
      message = "";
    }
    //Serial.write(incomingChar); 
         
  
    }
    
    Printcase();       
    //Serial.print("message: "); Serial.println(message);
    //Serial.print("case: "); Serial.println(Cases);
    
      if (P.displayAnimate())
      {
        if (animateCase)
        {
          P.displayText(currentMessage, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);
          animateCase = false;
        }
        P.displayReset();  // Reset and display it again
      }
    delay(20);
}  
  void Printcase() {
    String wold = Cases;
    char newMessage[BUF_SIZE];
    wold.toCharArray(newMessage, BUF_SIZE);

    strcpy(currentMessage, newMessage);
    animateCase = true;
  }
