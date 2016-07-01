#pragma once
#include <stdint.h>

class Item {
  uint8_t type;
  uint8_t x,y;
};

class World
{
  public:
    uint8_t width,height;
    uint8_t level[128]; //biggest map size, 16*16, 32*8, etc
    uint8_t items[128];
    uint8_t itemType[16];
    uint8_t itemAction[16];

    void init(void);
    void load(uint8_t *ID);
    void set(const int8_t x, const int8_t y, const uint8_t wall);
    void setFast(const int8_t x, const int8_t y, const uint8_t wall);
    bool validSize(const uint8_t width, const uint8_t height);
    uint8_t get(const int8_t x, const int8_t y) const;
    uint8_t getFast(const int8_t x, const int8_t y) const;
    bool getItem(const int8_t x, const int8_t y) const;
    bool inbound(const int8_t x, const int8_t y) const;
};
