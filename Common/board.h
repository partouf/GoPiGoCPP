#pragma once

#include <cstdint>
#include <string>

namespace GoPiGo
{
   typedef int32_t milliseconds_t;
   typedef double voltage_t;

   char HighByte(int16_t AWord);
   char LowByte(int16_t AWord);

   class ILockable
   {
   public:
      virtual bool LockWhenAvailable(int ATimeout = -1) = 0;
      virtual bool Unlock() = 0;
   };

   class Transaction
   {
   protected:
      ILockable *Lock;
   public:
      Transaction(ILockable *ALock);
      ~Transaction();
   };

   class IBoard : public ILockable
   {
   protected:
      int16_t BoardVersion;
      int8_t FirmwareVersion;

      void ReloadBoardVersion();
      void ReloadFirmwareVersion();

      virtual char ReadByte() = 0;
   public:
      IBoard();

      virtual void Disconnect() = 0;
      virtual bool IsConnected() = 0;
      virtual bool Connect() = 0;

      virtual void Sleep(milliseconds_t ATime) = 0;

      virtual bool WriteBlock(char ACommand, char AValue1, char AValue2, char AValue3) = 0;
      virtual int16_t ReadWord();

      bool WriteAnalog(char APin, char AValue);
      int16_t ReadAnalog(char APin);

      int GetBoardVersion();
      int GetFirmwareVersion();
      char GetCpuSpeed();
      double GetVoltage();

      std::string LastKnownError;
   };

   class ConnectedDevice
   {
   protected:
      IBoard *Connection;
   public:
      ConnectedDevice(IBoard *AConnection);
   };
};
