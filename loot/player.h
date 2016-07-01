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

    void init(void);
    void changeDirection(const Direction direction);
    void move(const int8_t distance);
    void jump(const uint8_t x, const uint8_t y);
    void step(void);
};
