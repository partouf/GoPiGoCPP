
#include "ultrasonic.h"

GoPiGo::Ultrasonic::Ultrasonic(IBoard * AConnection, int APin) : PinConnection(AConnection, APin)
{
}

GoPiGo::centimeters_t GoPiGo::Ultrasonic::GetDistance()
{
   Transaction Lock(this->Connection);

   this->Connection->WriteBlock(us_cmd, this->Pin, 0, 0);

   return this->Connection->ReadWord();
}
