#define BLYNK_TEMPLATE_ID "TMPLHBU1R-xx"
#define BLYNK_DEVICE_NAME "K-1P"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
#define APP_DEBUG
#define USE_WEMOS_D1_MINI
#define USE_WEMOS_D1_MINI
unsigned long times = 0;
int key1,key2;
#include "BlynkEdgent.h"
void setup()
{
  Serial.begin(9600);
  delay(100);
EEPROM.begin(2000);
EEPROM.get(400,key1);
EEPROM.end();
BlynkEdgent.begin();
}

void loop() { 
BlynkEdgent.run();
if(millis()-times>2000){
times=millis();

EEPROM.begin(2000);
EEPROM.get(404,key2);
EEPROM.end();
}
}

