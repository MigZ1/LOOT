#pragma once
#include <stdint.h>
#include "direction.h"

class System;
class World;
class Player;

class Render
{
  private:
    System * ab;
    World * world;
    Player * player;

    bool wallShow[11] = {};
    bool itemShow[11] = {};
  public:
    int8_t renderPos;

    Render(System & ab,World & world,Player & player);

    void step();
    void draw();

    bool wallCheck(int8_t x,int8_t y);
    bool itemCheck(int8_t x,int8_t y);
    void calculateView(int8_t x,int8_t y,Direction dir);
    void drawView();
    void drawMap();
    void drawStats();
};
