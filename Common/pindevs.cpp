
#include "pindevs.h"

#include <cassert>

GoPiGo::PinConnection::PinConnection(IBoard * AConnection, int APin) : ConnectedDevice(AConnection)
{
   this->Pin = APin;
}

bool GoPiGo::PinConnection::SetToOutput()
{
   return this->Connection->WriteBlock(pin_mode_cmd, this->Pin, 1, 0);
}

bool GoPiGo::PinConnection::SetToInput()
{
   return this->Connection->WriteBlock(pin_mode_cmd, this->Pin, 0, 0);
}

GoPiGo::DigitalReaderWriter::DigitalReaderWriter(IBoard * AConnection, int APin) : PinConnection(AConnection, APin)
{
}

bool GoPiGo::DigitalReaderWriter::Write(bool AValue)
{
   return this->Connection->WriteBlock(digital_write_cmd, this->Pin, AValue ? 1 : 0, 0);
}

char GoPiGo::DigitalReaderWriter::Read()
{
   assert(this->Pin == 10 || this->Pin == 15 || this->Pin == 0 || this->Pin == 1);  // should fix code when this happens

   if (!this->Connection->WriteBlock(digital_read_cmd, this->Pin, 0, 0))
      return -1;

   int16_t dRead = this->Connection->ReadWord();

   return HighByte(dRead);
}

