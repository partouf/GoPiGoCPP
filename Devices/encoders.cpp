
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

