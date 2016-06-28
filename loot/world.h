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
    uint8_t level[256]; //biggest map size, 16*16, 32*8, etc
    uint8_t items[256];
    uint8_t itemType[16];
    uint8_t itemAction[16];

    void init();
    void load(uint8_t *ID);
    void set(int8_t x,int8_t y,uint8_t wall);
    void setFast(int8_t x,int8_t y,uint8_t wall);
    bool validSize(uint8_t width,uint8_t height);
    uint8_t get(int8_t x,int8_t y);
    uint8_t getFast(int8_t x,int8_t y);
    bool getItem(int8_t x,int8_t y);
    bool inbound(int8_t x,int8_t y);
};
