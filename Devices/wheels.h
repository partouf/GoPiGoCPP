#pragma once

#include "../Common/board.h"
#include "../Common/magic.h"

namespace GoPiGo
{
   typedef unsigned char speed_t;

   enum direction_t { dir_backward = 0, dir_forward = 1 };

   class Wheels : public ConnectedDevice
   {
   public:
      Wheels(IBoard *AConnection);

      //Move the GoPiGo forward
      bool Forward();

      //Move GoPiGo back
      bool Backward();

      //Stop the GoPiGo
      bool Stop();

      //Move the GoPiGo forward without PID
      bool ForwardWithoutPID();

      //Move GoPiGo back without PID control
      bool BackwardWithoutPID();

      //Turn GoPiGo Left slow (one motor off, better control)    
      bool Left();

      //Turn GoPiGo right slow (one motor off, better control)
      bool Right();

      //Rotate GoPiGo left in same position (both motors moving in the opposite direction)
      bool RotateLeft();

      //Rotate GoPiGo right in same position both motors moving in the opposite direction)
      bool RotateRight(void);

      //Increase the speed
      bool IncreaseSpeed();

      //Decrease the speed
      bool DecreaseSpeed();

      //Set speed of the left motor
      //    arg:
      //        speed-> 0-255
      bool SetSpeedMotor1(speed_t ASpeed);

      //Set speed of the right motor
      //    arg:
      //        speed-> 0-255
      bool SetSpeedMotor2(speed_t ASpeed);

      //Set speed of the both motors
      //    arg:
      //        speed-> 0-255
      void SetSpeedBothMotors(speed_t ASpeed);

      // Get motor speed back
      int16_t GetMotorSpeed();

      //Control Motor 1
      bool Motor1(direction_t ADirection, speed_t ASpeed);

      //Control Motor 2
      bool Motor2(direction_t ADirection, speed_t ASpeed);
   };
};
