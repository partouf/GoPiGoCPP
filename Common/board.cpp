#include "board.h"
#include "magic.h"

char GoPiGo::HighByte(int16_t AWord)
{
   return (AWord & 0xff00) >> 8;
}

char GoPiGo::LowByte(int16_t AWord)
{
   return AWord & 0x00ff;
}

int16_t GoPiGo::IBoard::ReadAnalog(char APin)
{
   WriteBlock(analog_read_cmd, APin, 0, 0);

   return ReadWord();
}

bool GoPiGo::IBoard::WriteAnalog(char APin, char AValue)
{
   return this->WriteBlock(analog_write_cmd, APin, LowByte(AValue), 0);
}

void GoPiGo::IBoard::ReloadBoardVersion()
{
   Transaction Lock(this);

   int16_t rawdata = 0;
   for (int i = 0; i < 10; ++i)
   {
      rawdata = ReadAnalog(boardversioninfo_pin);
   }

   if (rawdata > 790)
   {
      BoardVersion = 16;
   }
   else
   {
      BoardVersion = 14;
   }
}

GoPiGo::IBoard::IBoard() : ILockable()
{
}

int GoPiGo::IBoard::GetBoardVersion()
{
   return BoardVersion;
}

void GoPiGo::IBoard::ReloadFirmwareVersion()
{
   Transaction Lock(this);

   this->WriteBlock(fw_ver_cmd, 0, 0, 0);

   int16_t ver = this->ReadWord();

   this->FirmwareVersion = HighByte(ver);
}

int GoPiGo::IBoard::GetFirmwareVersion()
{
   return this->FirmwareVersion;
}

char GoPiGo::IBoard::GetCpuSpeed()
{
   Transaction Lock(this);

   this->WriteBlock(cpu_speed_cmd, 0, 0, 0);

   return HighByte(this->ReadWord());
}

double GoPiGo::IBoard::GetVoltage()
{
   Transaction Lock(this);

   this->WriteBlock(volt_cmd, 0, 0, 0);

   int16_t voltage = this->ReadWord();

   return (5.0 * voltage / 1024) / 0.4;
}

int16_t GoPiGo::IBoard::ReadWord()
{
   char highbyte = this->ReadByte();
   char lowbyte = this->ReadByte();

   if (highbyte == -1 || lowbyte == -1)
   {
      return -1;
   }
   else
   {
      return (highbyte << 8) | lowbyte;
   }
}

GoPiGo::ConnectedDevice::ConnectedDevice(IBoard * AConnection)
{
   this->Connection = AConnection;
}

GoPiGo::Transaction::Transaction(ILockable * ALock)
{
   this->Lock = ALock;

   this->Lock->LockWhenAvailable();
}

GoPiGo::Transaction::~Transaction()
{
   this->Lock->Unlock();
}
