#pragma once

#include "../Common/board.h"
#include "../Common/magic.h"
#include "../Common/pindevs.h"

namespace GoPiGo
{
   enum led_t { led_right = 0, led_left = 1 };

   class LED : public DigitalReaderWriter
   {
   public:
      LED(IBoard *AConnection, led_t ALedNumber);

      void On();
      void Off();
   };
};
