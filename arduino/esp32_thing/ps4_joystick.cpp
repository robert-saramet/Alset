#include "SerialTransfer.h"
#include <PS4Controller.h>

char auth[] = "r70VT9kv6x1BQJ_iCe7zRaqItWJf_OBS";

SerialTransfer myTransfer;

struct STRUCT {
  int8_t relSpeed;
  uint8_t pos;
} testStruct;

char cmd[] = "move";

void sendSpeed(int relSpeed = 0, int pos = 0) {
    uint16_t sendSize = 0;
    testStruct.relSpeed = relSpeed;
    testStruct.pos = pos;
    sendSize = myTransfer.txObj(testStruct, sendSize);
    sendSize = myTransfer.txObj(cmd, sendSize);
    myTransfer.sendData(sendSize);
}

void setup()
{
  Serial.begin(115200);
  PS4.begin("00:de:ad:be:ef:00");
  Serial2.begin(115200);
  myTransfer.begin(Serial2);
}


void loop()
{
  int mapX, mapY;
  
  // forward
  if (PS4.R2Value() > 10 && PS4.L2Value() < 10) {
    mapY = map(PS4.R2Value(), 0, 255, 0, 100);
  }
  // backward
  else if (PS4.L2Value() > 10 && PS4.R2Value() < 10) {
    mapY = map(PS4.L2Value(), 0, 255, 0, -100);
  }
  // brake
  else {
    mapY = 0;
  }

  mapX = map(PS4.LStickX(), -128, 127, 0, 180);

  sendSpeed(mapY, mapX);
}
