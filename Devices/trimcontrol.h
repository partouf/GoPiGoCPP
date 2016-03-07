#pragma once

#include "../Common/board.h"
#include "../Common/magic.h"

namespace GoPiGo
{
   typedef char trim_t;

   class TrimControl : public ConnectedDevice
   {
   protected:
      char EncodeTrimValue(trim_t AValue);
   public:
      TrimControl(IBoard *AConnection);

      //Trim test with the value specified
      bool Test(trim_t AValue);

      //Read the trim value in EEPROM if present else return -3
      int GetTrimValue();

      //Write the trim value to EEPROM, use value between -100 and +100
      bool Write(trim_t AValue);
   };
};
