#include "player.h"
#include "world.h"
#include "system.h"

Player::Player(System & ab,World & world)
{
  this->ab = &ab;
  this->world = &world;
}

void Player::init()
{
  moved = true;
  x = 1;
  y = 1;
  hp = 10;
  sp = 10;
}

void Player::move(uint8_t dir,int8_t dist)
{
  int8_t nx=0, ny = 0;  //calculate direction
  if(dir==0)  { nx = 1; }
  if(dir==1)  { ny = 1; }
  if(dir==2)  { nx = -1;}
  if(dir==3)  { ny = -1;}

  if(dist != 1)
  {
    nx *= dist; //multiply by distance
    ny *= dist;
  }
  /*
  bool hit = (world->get(x+nx,y+ny)==1);
  if(!hit)
  {
    x = x+nx;
    y = y+ny;
    moved = true;
  }
  */
  jump(x+nx,y+ny);  //reduce duplicated code
}

void Player::jump(uint8_t x,uint8_t y)
{
  if (world->get(x,y)==0)
  {
    this->x = x;
    this->y = y;
    moved = true;
  }
}

void Player::step()
{
  //currently in gamelogic.cpp because reasons
}
