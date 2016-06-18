#pragma once
#include <stdint.h>
#include "world.h"
#include "system.h"

class Player
{
  private:
    System * ab;
    World * world;

  public:
    Player(System & ab,World & world);

    bool moved;
    int8_t x,y; //needs to be signed so checking negative positions doesn't bug out
    uint8_t dir;
    uint8_t hp,sp;
    char name[8];

    void init();
    void step();
    void move(uint8_t,int8_t);
    void jump(uint8_t,uint8_t);
};
