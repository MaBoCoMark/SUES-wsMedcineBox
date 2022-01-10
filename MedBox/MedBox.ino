#include "WebHTTPs.h"
void setup() 
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  HTMLsetup(1);
}
void loop()
{
  HTTPloop(0);
}
