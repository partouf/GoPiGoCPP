
#include "encoders.h"

GoPiGo::StatusListener::StatusListener(IBoard * AConnection) : ConnectedDevice(AConnection)
{
}

bool GoPiGo::StatusListener::EnableCommunicationTimeout(milliseconds_t ATimeout)
{
   Transaction Lock(this->Connection);

   return this->Connection->WriteBlock(en_com_timeout_cmd, HighByte(ATimeout), LowByte(ATimeout), 0);
}

bool GoPiGo::StatusListener::DisableCommunicationTimeout()
{
   Transaction Lock(this->Connection);

   return this->Connection->WriteBlock(dis_com_timeout_cmd, 0, 0, 0);
}

GoPiGo::status_t GoPiGo::StatusListener::GetStatus()
{
   status_t result;

   Transaction Lock(this->Connection);

   int16_t w = this->Connection->ReadWord();
   result.EncoderStatus = HighByte(w);
   result.TimeoutStatus = LowByte(w);

   return result;
}

GoPiGo::WheelEncoders::WheelEncoders(IBoard * AConnection) : StatusListener(AConnection)
{
   IsEnabledByCode = false;
}

bool GoPiGo::WheelEncoders::Enable()
{
   Transaction Lock(this->Connection);

   IsEnabledByCode = this->Connection->WriteBlock(en_enc_cmd, 0, 0, 0);

   return IsEnabledByCode;
}

bool GoPiGo::WheelEncoders::Disable()
{
   Transaction Lock(this->Connection);

   IsEnabledByCode = false;

   return this->Connection->WriteBlock(dis_enc_cmd, 0, 0, 0);
}

bool GoPiGo::WheelEncoders::IsEnabled()
{
   return IsEnabledByCode;
}

bool GoPiGo::WheelEncoders::SetTargeting(bool AMotor1, bool AMotor2, encoderpulses_t ATarget)
{
   char selection = (AMotor1 ? 2 : 0) | (AMotor2 ? 1 : 0);

   Transaction Lock(this->Connection);

   bool ret = this->Connection->WriteBlock(enc_tgt_cmd, selection, HighByte(ATarget), LowByte(ATarget));

   return ret;
}

GoPiGo::WheelEncodersWithErrorDetection::WheelEncodersWithErrorDetection(IBoard * AConnection) : ConnectedDevice(AConnection)
{
   StartValue1 = 0;
   StartValue2 = 0;
   Target1 = 0;
   Target2 = 0;
   LatestDistance1 = 0;
   LatestDistance2 = 0;
}

GoPiGo::encoderpulses_t GoPiGo::WheelEncodersWithErrorDetection::GetCurrentEncoderValue(int AMotorId)
{
   Transaction Lock(this->Connection);

   this->Connection->WriteBlock(enc_read_cmd, AMotorId, 0, 0);

   return this->Connection->ReadWord();
}

GoPiGo::encoderpulses_t GoPiGo::WheelEncodersWithErrorDetection::GetDistance(encoderpulses_t AStartValue, encoderpulses_t ACurrentValue)
{
   if (ACurrentValue < AStartValue)
   {
      // value has overflowed
      return (65535 - AStartValue) + ACurrentValue;
   }
   else
   {
      return ACurrentValue - AStartValue;
   }
}

GoPiGo::encoderpulses_t GoPiGo::WheelEncodersWithErrorDetection::TravelDistance1()
{
   encoderpulses_t NewValue = GetCurrentEncoderValue(0);
   LatestDistance1 = GetDistance(StartValue1, NewValue);
   return LatestDistance1;
}

GoPiGo::encoderpulses_t GoPiGo::WheelEncodersWithErrorDetection::TravelDistance2()
{
   encoderpulses_t NewValue = GetCurrentEncoderValue(1);
   LatestDistance2 = GetDistance(StartValue2, NewValue);
   return LatestDistance2;
}

void GoPiGo::WheelEncodersWithErrorDetection::Start(encoderpulses_t ATarget1, encoderpulses_t ATarget2)
{
   Target1 = ATarget1;
   Target2 = ATarget2;

   StartValue1 = GetCurrentEncoderValue(0);
   StartValue2 = GetCurrentEncoderValue(1);
}

bool GoPiGo::WheelEncodersWithErrorDetection::CheckShouldStop()
{
   if ((Target1 != 0) && (Target2 != 0))
   {
      return (TravelDistance1() >= Target1) || (TravelDistance2() >= Target2);
   }
   else if (Target1 > 0)
   {
      return (TravelDistance1() >= Target1);
   }
   else if (Target2 > 0)
   {
      return (TravelDistance2() >= Target2);
   }

   return true;
}

GoPiGo::encoderpulses_t GoPiGo::WheelEncodersWithErrorDetection::GetLatestDistance1()
{
   return LatestDistance1;
}

GoPiGo::encoderpulses_t GoPiGo::WheelEncodersWithErrorDetection::GetLatestDistance2()
{
   return LatestDistance2;
}
