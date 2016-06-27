#pragma once
#include <stdint.h>

enum class Direction : uint8_t
{
  East = 0,
  South = 1,
  West = 2,
  North = 3
};

Direction rotateRight(Direction dir)
{
  return static_cast<Direction>((static_cast<uint8_t>(dir) + 1) % 4);
}

Direction rotateLeft(Direction dir)
{
  return static_cast<Direction>((static_cast<uint8_t>(dir) - 1) % 4);
}
