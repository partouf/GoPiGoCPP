#pragma once

#include "../Common/board.h"

namespace GoPiGo
{
   class NullBoard : public IBoard
   {
   protected:
      int fd;
      int I2CDeviceNumber;
      bool busy;
   public:
      NullBoard(int AI2CDeviceNumber = 1);
      ~NullBoard();

      void Disconnect();
      bool Connect();
      bool IsConnected();
      void Sleep(milliseconds_t ATime);

      bool WriteBlock(char ACommand, char AValue1, char AValue2, char AValue3);
      char ReadByte();

      bool LockWhenAvailable(int ATimeout = -1);
      bool Unlock();
   };
};
