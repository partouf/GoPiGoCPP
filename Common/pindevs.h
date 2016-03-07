#pragma once

#include "../Common/board.h"
#include "../Common/magic.h"

namespace GoPiGo
{
   class PinConnection : public ConnectedDevice
   {
   protected:
      int Pin;

      bool SetToOutput();
      bool SetToInput();
   public:
      PinConnection(IBoard *AConnection, int APin);
   };

   class DigitalReaderWriter : public PinConnection
   {
   protected:
      bool Write(bool AValue);
      char Read();
   public:
      DigitalReaderWriter(IBoard *AConnection, int APin);
   };
};
