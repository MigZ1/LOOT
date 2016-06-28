#pragma once
#include <stdint.h>

class System;

class Menu
{
  private:
    System * ab;
    int8_t select,page;
    int8_t logoAnim;  //slides menu up
  public:
    Menu(System & ab);

    void init();
    void step();
    void draw();
};
