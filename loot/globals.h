#pragma once

#include <stdint.h>
#include "system.h"
#include "graphics.h"
#include "game.h"
#include "constants.h"
#include "render.h"
#include "world.h"
#include "player.h"
#include "menu.h"

System ab = System();
World world = World();
Menu menu = Menu(ab);
Player player = Player(ab, world);
Render render = Render(ab, world, player);
Game game = Game(ab, render, menu, player, world); //controls everything!
