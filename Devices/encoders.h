#pragma once

#include "../Common/board.h"
#include "../Common/magic.h"

namespace GoPiGo
{
   typedef uint16_t encoderpulses_t;
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

   class WheelEncodersWithErrorDetection : public ConnectedDevice
   {
   protected:
      encoderpulses_t StartValue1;
      encoderpulses_t StartValue2;

      encoderpulses_t Target1;
      encoderpulses_t Target2;

      encoderpulses_t LatestDistance1;
      encoderpulses_t LatestDistance2;

      encoderpulses_t GetCurrentEncoderValue(int AMotorId);

      encoderpulses_t GetDistance(encoderpulses_t AStartValue, encoderpulses_t ACurrentValue);

      encoderpulses_t TravelDistance1();
      encoderpulses_t TravelDistance2();
   public:
      WheelEncodersWithErrorDetection(IBoard *AConnection);

      void Start(encoderpulses_t ATarget1, encoderpulses_t ATarget2);

      bool CheckShouldStop();

      encoderpulses_t GetLatestDistance1();

      encoderpulses_t GetLatestDistance2();
   };
};
