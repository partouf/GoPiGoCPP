#include "null.h"


#include <iostream>
#include <windows.h>
#include <stdexcept>


GoPiGo::NullBoard::NullBoard(int AI2CDeviceNumber) : IBoard()
{
   this->I2CDeviceNumber = AI2CDeviceNumber;
   this->fd = 0;
   this->busy = false;
}

GoPiGo::NullBoard::~NullBoard()
{
   this->Disconnect();
}

void GoPiGo::NullBoard::Disconnect()
{
   std::cout << "Disconnected()" << std::endl;
   fd = 0;
}

bool GoPiGo::NullBoard::Connect()
{
   std::cout << "Connect()" << std::endl;
   fd = 1;

   this->ReloadBoardVersion();
   this->ReloadFirmwareVersion();

   return true;
}

bool GoPiGo::NullBoard::IsConnected()
{
   return (fd != 0);
}

void GoPiGo::NullBoard::Sleep(milliseconds_t ATime)
{
   std::cout << "Sleep()" << std::endl;
   ::Sleep(ATime);
}

bool GoPiGo::NullBoard::WriteBlock(char ACommand, char AValue1, char AValue2, char AValue3)
{
   std::cout << "WriteBlock(" << (int)ACommand << "," << (int)AValue1 << "," << (int)AValue2 << "," << (int)AValue3 << ")" << std::endl;

   return true;
}

char GoPiGo::NullBoard::ReadByte()
{
   std::cout << "ReadByte()" << std::endl;

   return 0;
}

bool GoPiGo::NullBoard::LockWhenAvailable(int ATimeout)
{
   // no need to use actual mutex until we're really going to use threads
   while (this->busy)
   {
      Sleep(1);
   }
   this->busy = true;

   return true;
}

bool GoPiGo::NullBoard::Unlock()
{
   this->busy = false;

   return true;
}
