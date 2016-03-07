#pragma once

#include "../Common/board.h"
#include "../Common/magic.h"

namespace GoPiGo
{
   typedef char degrees_t;

   class Servo : public ConnectedDevice
   {
   public:
      Servo(IBoard *AConnection);

      // Enables the servo motor
      bool Enable();

      // Disables the servo motor
      bool Disable();

      // Moves the servo motor to the position, max angle is 180 degrees
      bool SetAngle(degrees_t AAngle);
   };
};
