#pragma once
#include <stdint.h>
#include "system.h"
#include "world.h"
#include "player.h"
#include "direction.h"

class Player;
enum class Direction : uint8_t;

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
