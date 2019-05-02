/**************************************************************************/
/*! 
    This example will wait for any ISO14443A card or tag, and
    depending on the size of the UID will attempt to read from it.
   
    If the card has a 4-byte UID it is probably a Mifare
    Classic card, and the following steps are taken:
   
    - Authenticate block 4 (the first block of Sector 1) using
      the default KEYA of 0XFF 0XFF 0XFF 0XFF 0XFF 0XFF
    - If authentication succeeds, we can then read any of the
      4 blocks in that sector (though only block 4 is read here)
	 
    If the card has a 7-byte UID it is probably a Mifare
    Ultralight card, and the 4 byte pages can be read directly.
    Page 4 is read by default since this is the first 'general-
    purpose' page on the tags.

    To enable debug message, define DEBUG in PN532/PN532_debug.h
*/
/**************************************************************************/

#include <LWiFi.h>
#include <SPI.h>
#include <PN532_SPI.h>
#include "PN532.h"

PN532_SPI pn532spi(SPI, 10);
PN532 nfc(pn532spi);

//char ssid[] = "ES715_2.4G";      //  your network SSID (name)
char ssid[] = "ES302";
//char pass[] = "AI715nxt4391rcx"; // your network password (use for WPA, or use as key for WEP)
char pass[] = "es302es715";
//String host = "192.168.1.110";
String host = "192.168.0.107";
uint16_t port = 3005;
int status = WL_IDLE_STATUS;
WiFiClient client;

//int keyIndex = 0;               // your network key Index number (needed only for WEP)

void setup(void) {

  //led
  pinMode(14, OUTPUT);
  
  //7seg
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  Serial.begin(115200);
  Serial.println("Hello!");

  while (status != WL_CONNECTED) {
        Serial.print("Attempting to connect to SSID: ");
        Serial.println(ssid);
        // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
        status = WiFi.begin(ssid, pass);
  }
    
  Serial.println("Connected to wifi");
  printWifiStatus();

  
  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }
  // Got ok data, print it out!
  Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX); 
  Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC); 
  Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);
  
  // configure board to read RFID tags
  nfc.SAMConfig();
  nfc.setPassiveActivationRetries(0x01);
  Serial.println("Waiting for an ISO14443A Card ...");
}

uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0}; // Buffer to store the returned UID  
uint8_t tpuid[] = { 0, 0, 0, 0, 0, 0, 0 }; // Buffer to store the returned UID  
uint8_t success;
uint8_t uidLength,tpuidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
int s=0,j=0,k=0,od=0;

void loop(void) {
  // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
  // 'uid' will be populated with the UID, and uidLength will indicate
  // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)

    //=============================================================7seg:
   if(j<uidLength && k>30){
      j++; 
      k=0; 
      if(j>=uidLength){
        j=0;
      }
    }
   k++;
   if(s==0){
      digitalWrite(7, LOW);
      digitalWrite(8, HIGH);
      od=uid[j]/16;
    }else{
      digitalWrite(7, HIGH);
      digitalWrite(8, LOW);
      od=uid[j]%16;
    }
    s=~s;
    if(od==15){
      digitalWrite(16, LOW);
      digitalWrite(17, HIGH);
      digitalWrite(2, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
    }else if(od==14){
      digitalWrite(16, LOW);
      digitalWrite(17, HIGH);
      digitalWrite(2, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
    }else if(od==13){
      digitalWrite(16, HIGH);
      digitalWrite(17, LOW);
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(6, LOW);
    }else if(od==12){
      digitalWrite(16, LOW);
      digitalWrite(17, HIGH);
      digitalWrite(2, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, HIGH);
    }else if(od==11){
      digitalWrite(16, HIGH);
      digitalWrite(17, HIGH);
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
    }else if(od==10){
      digitalWrite(16, LOW);
      digitalWrite(17, LOW);
      digitalWrite(2, LOW);
      digitalWrite(3, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
    }else if(od==9){
      digitalWrite(16, LOW);
      digitalWrite(17, LOW);
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
    }else if(od==8){
      digitalWrite(16, LOW);
      digitalWrite(17, LOW);
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
    }else if(od==7){
      digitalWrite(16, LOW);
      digitalWrite(17, LOW);
      digitalWrite(2, LOW);
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
    }else if(od==6){
      digitalWrite(16, LOW);
      digitalWrite(17, HIGH);
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
    }else if(od==5){
      digitalWrite(16, LOW);
      digitalWrite(17, HIGH);
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
    }else if(od==4){
      digitalWrite(16, HIGH);
      digitalWrite(17, LOW);
      digitalWrite(2, LOW);
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
    }else if(od==3){
      digitalWrite(16, LOW);
      digitalWrite(17, LOW);
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(6, LOW);
    }else if(od==2){
      digitalWrite(16, LOW);
      digitalWrite(17, LOW);
      digitalWrite(2, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(6, LOW);
    }else if(od==1){
      digitalWrite(16, HIGH);
      digitalWrite(17, LOW);
      digitalWrite(2, LOW);
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
    }else if(od==0){
      digitalWrite(16, LOW);
      digitalWrite(17, LOW);
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, HIGH);
    }
  
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  if (success) {
    // Display some basic information about the card
    Serial.println("Found an ISO14443A card");
    Serial.print("  UID Length: ");Serial.print(uidLength, DEC);Serial.println(" bytes");
    Serial.print("  UID Value: ");
    nfc.PrintHex(uid, uidLength);
    Serial.println("");
    
    Serial.print("  UID Value with string: ");
    int i;
    String StringUID = "";
    for (i = 0; i < 4; i = i + 1) {
      StringUID += String(uid[i], HEX);
    }
    
    Serial.println(StringUID);
    Serial.println("== Start to compare UID on database. ==");
    Serial.println("\nStarting connection to server...");
    
    // if you get a connection, report back via serial:
    if (client.connect(host.c_str(), port)) {
        Serial.println("connected to server (GET)");
        // Make a HTTP request:
        client.println("GET /rfid/" + StringUID + " HTTP/1.1");
        client.println("Host: " + host + ":" + (String)port);
        client.println("Accept: */*");
        client.println("Connection: close");
        client.println();
        delay(500);

        char c;
        while (client.available()) {
            c = client.read();
        }

        if(c == 'y'){
            digitalWrite(14, HIGH);
            digitalWrite(15, LOW);
          }
          
        if(c == 'n'){
            digitalWrite(15, HIGH);
            digitalWrite(14, LOW);
          }
        
        Serial.println(c);
        
    }
    

    


    
//    if (uidLength == 4)
//    {
//      // We probably have a Mifare Classic card ... 
//      Serial.println("Seems to be a Mifare Classic card (4 byte UID)");
//	  
//      // Now we need to try to authenticate it for read/write access
//      // Try with the factory default KeyA: 0xFF 0xFF 0xFF 0xFF 0xFF 0xFF
//      Serial.println("Trying to authenticate block 4 with default KEYA value");
//      uint8_t keya[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
//	  
//	  // Start with block 4 (the first block of sector 1) since sector 0
//	  // contains the manufacturer data and it's probably better just
//	  // to leave it alone unless you know what you're doing
//      success = nfc.mifareclassic_AuthenticateBlock(uid, uidLength, 4, 0, keya);
//	  
//      if (success)
//      {
//        Serial.println("Sector 1 (Blocks 4..7) has been authenticated");
//        uint8_t data[16];
//		
//        // If you want to write something to block 4 to test with, uncomment
//		// the following line and this text should be read back in a minute
//        // data = { 'a', 'd', 'a', 'f', 'r', 'u', 'i', 't', '.', 'c', 'o', 'm', 0, 0, 0, 0};
//        // success = nfc.mifareclassic_WriteDataBlock (4, data);
//
//        // Try to read the contents of block 4
//        success = nfc.mifareclassic_ReadDataBlock(4, data);
//		
//        if (success)
//        {
//          // Data seems to have been read ... spit it out
//          Serial.println("Reading Block 4:");
//          nfc.PrintHexChar(data, 16);
//          Serial.println("");
//		  
//          // Wait a bit before reading the card again
//          delay(1000);
//        }
//        else
//        {
//          Serial.println("Ooops ... unable to read the requested block.  Try another key?");
//        }
//      }
//      else
//      {
//        Serial.println("Ooops ... authentication failed: Try another key?");
//      }
//    }
//    
//    if (uidLength == 7)
//    {
//      // We probably have a Mifare Ultralight card ...
//      Serial.println("Seems to be a Mifare Ultralight tag (7 byte UID)");
//	  
//      // Try to read the first general-purpose user page (#4)
//      Serial.println("Reading page 4");
//      uint8_t data[32];
//      success = nfc.mifareultralight_ReadPage (4, data);
//      if (success)
//      {
//        // Data seems to have been read ... spit it out
//        nfc.PrintHexChar(data, 4);
//        Serial.println("");
//		
//        // Wait a bit before reading the card again
//        delay(1000);
//      }
//      else
//      {
//        Serial.println("Ooops ... unable to read the requested page!?");
//      }
//    }
  }



}

void printWifiStatus() {
    // print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print your WiFi shield's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    // print the received signal strength:
    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
}
