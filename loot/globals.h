#pragma once

#include <stdint.h>
#include "system.h"
#include "graphics.h"
#include "gamelogic.h"
#include "constants.h"
#include "render.h"
#include "world.h"
#include "player.h"
#include "menu.h"

System ab;
World world;
Menu menu(ab);
Player player(ab,world);
Render render(ab,world,player);
Game game(ab,render,menu,player,world); //controls everything!
