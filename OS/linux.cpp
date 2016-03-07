#include "linux.h"


#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <stdexcept>
#include <string>


GoPiGo::LinuxBoard::LinuxBoard(int AI2CDeviceNumber) : IBoard()
{
   this->I2CDeviceNumber = AI2CDeviceNumber;
   this->fd = 0;
   this->busy = false;
}

GoPiGo::LinuxBoard::~LinuxBoard()
{
   this->Disconnect();
}

void GoPiGo::LinuxBoard::Disconnect()
{
   ::close(fd);
   fd = 0;
}

bool GoPiGo::LinuxBoard::Connect()
{
   int i, raw;
   std::string fileName = "/dev/i2c-" + std::to_string(I2CDeviceNumber);
   int address = 0x08;

   if ((fd = ::open(fileName.c_str(), O_RDWR)) < 0)
   {
      // Open port for reading and writing
      LastKnownError = "Failed to open i2c port - " + fileName;

      return false;
   }

   if (::ioctl(fd, I2C_SLAVE, address) < 0)
   {
      Disconnect();

      // Set the port options and set the address of the device 
      LastKnownError = "Unable to get bus access to talk to slave";

      return false;
   }

   this->ReloadBoardVersion();
   this->ReloadFirmwareVersion();

   return true;
}

bool GoPiGo::LinuxBoard::IsConnected()
{
   return (fd != 0);
}

void GoPiGo::LinuxBoard::Sleep(milliseconds_t ATime)
{
   ::usleep(ATime * 1000);
}

bool GoPiGo::LinuxBoard::WriteBlock(char ACommand, char AValue1, char AValue2, char AValue3)
{
   unsigned char w_buf[5];

   w_buf[0] = 1;
   w_buf[1] = ACommand;
   w_buf[2] = AValue1;
   w_buf[3] = AValue2;
   w_buf[4] = AValue3;

   if ((::write(fd, w_buf, 5)) != 5)
   {
      LastKnownError = "Error writing to GoPiGo";
      return false;
   }

   this->Sleep(70);

   return true;
}

char GoPiGo::LinuxBoard::ReadByte()
{
   unsigned char r_buf[32];
   int reg_size = 1;

   if (::read(fd, r_buf, reg_size) != reg_size) {
      throw new std::exception();

      return -1;
   }

   return r_buf[0];
}

bool GoPiGo::LinuxBoard::LockWhenAvailable(int ATimeout)
{
   // no need to use actual mutex until we're really going to use threads
   while (this->busy)
   {
      Sleep(1);
   }
   this->busy = true;

   return true;
}

bool GoPiGo::LinuxBoard::Unlock()
{
   this->busy = false;

   return true;
}
