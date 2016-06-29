#pragma once
#include <stdint.h>
#include "direction.h"

class System;
class World;

class Player
{
  private:
    System * ab;
    World * world;

  public:
    Player(System & ab,World & world);

    bool moved;
    int8_t x,y; //needs to be signed so checking negative positions doesn't bug out
    Direction dir;
    uint8_t hp,sp;
    char name[8];

    void init();
    void step();
    void move(Direction,int8_t);
    void jump(uint8_t,uint8_t);
};
