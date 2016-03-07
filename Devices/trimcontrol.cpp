
#include "trimcontrol.h"

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

char GoPiGo::TrimControl::EncodeTrimValue(trim_t AValue)
{
   return max(-100, min(100, AValue)) + 100;
}

GoPiGo::TrimControl::TrimControl(IBoard * AConnection) : ConnectedDevice(AConnection)
{
}

bool GoPiGo::TrimControl::Test(trim_t AValue)
{
   Transaction Lock(this->Connection);

   return this->Connection->WriteBlock(trim_test_cmd, this->EncodeTrimValue(AValue), 0, 0);
}

int GoPiGo::TrimControl::GetTrimValue()
{
   Transaction Lock(this->Connection);

   if (!this->Connection->WriteBlock(trim_read_cmd, 0, 0, 0))
      return -1;

   int16_t trimvalue = this->Connection->ReadWord();
   if (trimvalue == -1)
   {
      return -1;
   }
   else if (trimvalue == 255)
   {
      return -3;
   }

   return trimvalue;
}

bool GoPiGo::TrimControl::Write(trim_t AValue)
{
   Transaction Lock(this->Connection);

   return this->Connection->WriteBlock(trim_write_cmd, this->EncodeTrimValue(AValue), 0, 0);
}
