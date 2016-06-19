#pragma once
#include <stdint.h>
#include "menu.h"
#include "render.h"
#include "player.h"
#include "world.h"
#include "constants.h"

class Game
{
  private:
    System * ab;
    Render * render;
    Menu * menu;
    World * world;
    Player * player;

  public:
    Game(System & ab,Render & render,Menu & menu,Player & player,World & world);

    void step();
    void draw();
    void load(bool slot);
    void save(bool slot);

    void playerStep();
};
