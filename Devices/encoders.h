#pragma once

#include "../Common/board.h"
#include "../Common/magic.h"

namespace GoPiGo
{
   typedef int16_t encoderpulses_t;
   typedef char encstatus_t;
   typedef char trimstatus_t;

   struct status_t {
      encstatus_t EncoderStatus;
      trimstatus_t TimeoutStatus;
   };

   class StatusListener : public ConnectedDevice
   {
   public:
      StatusListener(IBoard *AConnection);

      bool EnableCommunicationTimeout(milliseconds_t ATimeout);
      bool DisableCommunicationTimeout();

      status_t GetStatus();
   };
   
   class WheelEncoders : public StatusListener
   {
   protected:
      bool IsEnabledByCode;
   public:
      WheelEncoders(IBoard *AConnection);

      // Enable the encoders (enabled by default)
      bool Enable();

      // Disable the encoders (use this if you don't want to use the encoders)
      bool Disable();

      bool IsEnabled();

      // Set encoder target to move the GoPiGo to a set distance (18 pulses per rotation) (with the default wheels this is about 19CM?)
      bool SetTargeting(bool AMotor1, bool AMotor2, encoderpulses_t ATarget);
   };
};
