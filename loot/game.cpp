#include "game.h"
#include "system.h"
#include "render.h"
#include "menu.h"
#include "player.h"
#include "world.h"
#include "constants.h"
#include "direction.h"

Game::Game(System & ab, Render & render,Menu & menu,Player & player,World & world)
{
  this->ab = &ab;
  this->menu = &menu;
  this->render = &render;
  this->player = &player;
  this->world = &world;
}

/*
Same difference:
Game::Game(Menu & menu) : menu(&menu) {}
*/

void Game::save(const bool slot)
{

}
void Game::load(const bool slot)
{

}

void Game::step(void)
{
  if (ab->stateChanged())
  {
    auto state = ab->getState();
    switch(state)
    {
      case stateMenu: { menu->init(); }; break;
      case stateGame: {
        if (ab->getLastState()==stateMenu)
        {
          player->init();
          world->init();
        }; break;
      }
      case stateBattle: {

      };
    }
  }
  ab->stateEndChange();

  switch(ab->getState())
  {
    case stateMenu:
    {
      menu->step();
      menu->draw();
    };break;
    case stateGame:
    {
      playerStep();
      render->step();
      render->draw();

      if(ab->isPushed(BTN_A))
        ab->setState(stateBattle);
    };break;
    case stateBattle:
    {
      render->drawView();
      ab->drawRect(24,40,17,16,1);  //enemy placement test
      ab->setCursor(66,2);
      ab->print(F("Battle"));
      ab->setCursor(66,10);
      ab->print(F("goes here!"));
      if(ab->isPushed(BTN_A))
        ab->setState(stateGame);
    };break;

  };
}

void Game::playerStep(void) //Here just for testing reasons, will be relocated soon
{
  Direction dir = player->getDirection();

  if(ab->isPushed(BTN_L))
    dir = rotateLeft(dir);

  if(ab->isPushed(BTN_R))
    dir = rotateRight(dir);

  player->changeDirection(dir);

  if(ab->isPushed(BTN_U)) //move 1 step in the looking direction
    player->move(1);

  if(ab->isPushed(BTN_D))
    player->move(-1);
}
