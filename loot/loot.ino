#include <stdint.h>
#include <Arduboy.h>
#include "system.h"
#include "globals.h"
#include "gameLogic.h"
#include "graphics.h"
#include "constants.h"
#include "render.h"
#include "world.h"
#include "player.h"
#include "menu.h"

void setup()
{
	ab.begin();
	ab.fillScreen(0);
	ab.drawBitmap(8, 5, imgTitle, 112, 54, 1);
	ab.display();
	while(!ab.isPushed(BTN_A))	//keep titlescreen up until a button is pressed
	{
		ab.update();
	}
}

void loop()
{
  if(!ab.nextFrame())
    return;

  ab.update();
  ab.clear();
  game.step();
  ab.display();
}
