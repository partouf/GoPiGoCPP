#pragma once

#include "../Common/board.h"
#include "../Common/magic.h"
#include "../Common/pindevs.h"

namespace GoPiGo
{
   typedef int16_t centimeters_t;
   
   class Ultrasonic : public PinConnection
   {
   public:
      Ultrasonic(IBoard *AConnection, int APin);

      centimeters_t GetDistance();
   };
};
