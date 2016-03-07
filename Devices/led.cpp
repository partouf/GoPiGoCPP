
#include "led.h"

GoPiGo::LED::LED(IBoard * AConnection, led_t ALedNumber) : DigitalReaderWriter(AConnection, 0)
{
   if (AConnection->GetBoardVersion() > 14)
   {
      if (ALedNumber == led_right)
      {
         this->Pin = 16;
      }
      else if (ALedNumber == led_left)
      {
         this->Pin = 17;
      }
   }
   else
   {
      if (ALedNumber == led_right)
      {
         this->Pin = 5;
      }
      else if (ALedNumber == led_left)
      {
         this->Pin = 10;
      }
   }
}

void GoPiGo::LED::On()
{
   Transaction Lock(this->Connection);

   this->SetToOutput();
   this->Write(true);
}

void GoPiGo::LED::Off()
{
   Transaction Lock(this->Connection);

   this->SetToOutput();
   this->Write(false);
}
