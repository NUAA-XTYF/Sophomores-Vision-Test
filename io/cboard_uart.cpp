#include "cboard_uart.hpp"

#include <iostream>

#include "io/gimbal/gimbal.hpp"
#include "tools/crc.hpp"
#include "tools/logger.hpp"
#include "tools/math_tools.hpp"
#include "tools/yaml.hpp"

#ifndef NDEBUG
#include "tools/plotter.hpp"

#endif

namespace io
{

#pragma pack(push, 1)
#ifdef NEW_UART_PROTOCOL
struct SendPacket
{
  uint8_t header = 0xA5;
  uint8_t length = sizeof(SendPacket);
  uint8_t control;
  uint8_t shoot;
  int16_t yaw;
  int16_t pitch;
  int16_t dist;
  uint16_t checksum;
  uint16_t tail = 0x7891;
};
#else
struct SendPacket
{
  uint8_t header = 0xA5;
  uint8_t control;
  uint8_t shoot;
  int16_t yaw;
  int16_t pitch;
  int16_t dist;
  uint16_t checksum;
};
#endif

#pragma pack(pop)

}  // namespace io