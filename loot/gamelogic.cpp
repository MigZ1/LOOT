#include "gamelogic.h"
#include "constants.h"

Game::Game(System & ab,Render & render,Menu & menu,Player & player,World & world)
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

void Game::save(bool slot)
{

}
void Game::load(bool slot)
{

}

void Game::step()
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
          render->init();
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

      if(ab->pushed(BTN_A))
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
      if(ab->pushed(BTN_A))
        ab->setState(stateGame);
    };break;

  };
}

void Game::playerStep() //Here just for testing reasons, will be relocated soon
{
  int8_t dir,lastDir;
  dir = player->dir;
  lastDir = player->dir;

  if(ab->pushed(BTN_L))
    --dir;
  if(ab->pushed(BTN_R))
    ++dir;

  if(dir != lastDir)
  {
    if (dir<0)  dir = 3;
    if (dir>3)  dir = 0;
    player->moved = true;
  }
  player->dir = dir;

  if(ab->pushed(BTN_U)) //move 1 step in the looking direction
    player->move(dir,1);
  if(ab->pushed(BTN_D))
    player->move(dir,-1);
}
