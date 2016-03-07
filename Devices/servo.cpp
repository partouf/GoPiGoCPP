
#include "servo.h"

GoPiGo::Servo::Servo(IBoard * AConnection) : ConnectedDevice(AConnection)
{
}

bool GoPiGo::Servo::Enable()
{
   Transaction Lock(this->Connection);

   return this->Connection->WriteBlock(en_servo_cmd, 0, 0, 0);
}

bool GoPiGo::Servo::Disable()
{
   Transaction Lock(this->Connection);

   return this->Connection->WriteBlock(dis_servo_cmd, 0, 0, 0);
}

bool GoPiGo::Servo::SetAngle(degrees_t AAngle)
{
   Transaction Lock(this->Connection);

   return this->Connection->WriteBlock(servo_cmd, AAngle % 181, 0, 0);
}
