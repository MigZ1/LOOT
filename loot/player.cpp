#include "player.h"
#include "world.h"
#include "system.h"
#include "direction.h"

Player::Player(System & ab, World & world)
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

void Player::changeDirection(const Direction direction)
{
  Direction lastDir = this->dir;
  this->dir = direction;
  this->moved = (this->dir != lastDir);
}

void Player::move(const int8_t distance)
{
  int8_t nx, ny;  //calculate direction
  switch(this->dir)
  {
    case Direction::East: nx = 1; break;
    case Direction::South: ny = 1; break;
    case Direction::West: nx = -1; break;
    case Direction::North: ny = -1; break;
  }
  this->jump(this->x + (nx * distance), this->y + (ny * distance));
}

void Player::jump(const uint8_t x, const uint8_t y)
{
  if (world->get(x, y)==0)
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
