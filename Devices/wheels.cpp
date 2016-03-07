
#include "wheels.h"

GoPiGo::Wheels::Wheels(IBoard * AConnection) : ConnectedDevice(AConnection)
{
}

bool GoPiGo::Wheels::Forward()
{
   Transaction Lock(this->Connection);

   return this->Connection->WriteBlock(fwd_cmd, 0, 0, 0);
}

bool GoPiGo::Wheels::Backward()
{
   Transaction Lock(this->Connection);

   return this->Connection->WriteBlock(bwd_cmd, 0, 0, 0);
}

bool GoPiGo::Wheels::Stop()
{
   Transaction Lock(this->Connection);

   return this->Connection->WriteBlock(stop_cmd, 0, 0, 0);
}

bool GoPiGo::Wheels::BackwardWithoutPID()
{
   Transaction Lock(this->Connection);

   return this->Connection->WriteBlock(motor_bwd_cmd, 0, 0, 0);
}

bool GoPiGo::Wheels::Left()
{
   Transaction Lock(this->Connection);

   return this->Connection->WriteBlock(left_cmd, 0, 0, 0);
}

bool GoPiGo::Wheels::RotateLeft()
{
   Transaction Lock(this->Connection);

   return this->Connection->WriteBlock(left_rot_cmd, 0, 0, 0);
}

bool GoPiGo::Wheels::Right()
{
   Transaction Lock(this->Connection);

   return this->Connection->WriteBlock(right_cmd, 0, 0, 0);
}

bool GoPiGo::Wheels::RotateRight(void)
{
   Transaction Lock(this->Connection);

   return this->Connection->WriteBlock(right_rot_cmd, 0, 0, 0);
}

bool GoPiGo::Wheels::IncreaseSpeed()
{
   Transaction Lock(this->Connection);

   return this->Connection->WriteBlock(ispd_cmd, 0, 0, 0);
}

bool GoPiGo::Wheels::DecreaseSpeed()
{
   Transaction Lock(this->Connection);

   return this->Connection->WriteBlock(dspd_cmd, 0, 0, 0);
}

bool GoPiGo::Wheels::SetSpeedMotor1(speed_t ASpeed)
{
   Transaction Lock(this->Connection);

   return this->Connection->WriteBlock(set_left_speed_cmd, ASpeed, 0, 0);
}

bool GoPiGo::Wheels::ForwardWithoutPID()
{
   Transaction Lock(this->Connection);

   return this->Connection->WriteBlock(motor_fwd_cmd, 0, 0, 0);
}

bool GoPiGo::Wheels::SetSpeedMotor2(speed_t ASpeed)
{
   Transaction Lock(this->Connection);

   return this->Connection->WriteBlock(set_right_speed_cmd, ASpeed, 0, 0);
}

void GoPiGo::Wheels::SetSpeedBothMotors(speed_t ASpeed)
{
   Transaction Lock(this->Connection);

   this->Connection->WriteBlock(set_left_speed_cmd, ASpeed, 0, 0);
   this->Connection->WriteBlock(set_right_speed_cmd, ASpeed, 0, 0);
}

int16_t GoPiGo::Wheels::GetMotorSpeed()
{
   Transaction Lock(this->Connection);

   this->Connection->WriteBlock(read_motor_speed_cmd, 0, 0, 0);

   return this->Connection->ReadWord();
}

bool GoPiGo::Wheels::Motor1(direction_t ADirection, speed_t ASpeed)
{
   Transaction Lock(this->Connection);

   return this->Connection->WriteBlock(m1_cmd, ADirection, ASpeed, 0);
}

bool GoPiGo::Wheels::Motor2(direction_t ADirection, speed_t ASpeed)
{
   Transaction Lock(this->Connection);

   return this->Connection->WriteBlock(m2_cmd, ADirection, ASpeed, 0);
}
