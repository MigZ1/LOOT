#pragma once
#include <stdint.h>

class System;
class Render;
class Menu;
class World;
class Player;

class Game
{
  private:
    System * ab;
    Render * render;
    Menu * menu;
    World * world;
    Player * player;

  public:
    Game(System & ab, Render & render, Menu & menu, Player & player, World & world);

    void step(void);
    void draw(void);
    void load(bool slot);
    void save(bool slot);
    void playerStep(void);
};
