#include <Arduino.h>
#include <LED.h>

Led pinLed(40);
uint32_t tempoEspera;

void setup()
{
}

void loop()
{
  tempoEspera = millis();
  pinLed.update(); //Este método deve ser chamado sempre no loop();
  pinLed.acender(1000); //Liga o LED.
  if (tempoEspera >= 1000)
  {
    pinLed.apagar();//Desliga o LED
 }
}
