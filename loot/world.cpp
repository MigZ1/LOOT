#include "world.h"
#include <stdint.h>

void World::init()
{
  width = 8;
  height = 8;

  //replace this bit with a progmem loader doodah
  uint8_t leveldata[64] =
  {
    1,1,1,1,1,1,1,1,
    0,0,0,0,1,0,0,1,
    1,1,0,1,0,0,1,1,
    1,0,0,0,0,1,0,1,
    1,1,0,1,1,1,0,1,
    1,0,0,0,0,0,0,1,
    1,0,1,1,1,1,0,1,
    1,1,1,1,1,1,1,1
  };
  bool itemdata[64] =
  {
    0,0,0,0,0,0,0,0,
    1,0,0,0,0,0,1,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,1,0,0,0,0,1,0,
    0,0,0,0,0,0,0,0,
  };
  for(int8_t i=0; i<64; i++)
  {
    level[i] = leveldata[i];
    items[i] = itemdata[i];
  };

}

void World::load(uint8_t *ID) //reads a map from PROGMEM and loads it into memory
{
  /*
  width = pgm_read_byte(*ID);
  height = pgm_read_byte(*ID+1);

  player.x = pgm_read_byte(*ID+2);
  player.y = pgm_read_byte(*ID+3);

  int length = width*height;
  for(i=0; i<length; ++i)
  {
    level[i] = pgm_read_byte((*ID+4)+i);
  }
  */
}

bool World::validSize(uint8_t width,uint8_t height)  //will our world fit in RAM? Probably unneeded if the maps are precomputed
{
  return (width*height <= 256);
}

void World::set(int8_t x,int8_t y,uint8_t wall)
{
  if(inbound(x,y))
    level[(y*width)+x] = wall;
}

void World::setFast(int8_t x,int8_t y,uint8_t wall)
{
  level[(y*width)+x] = wall;
}

uint8_t World::get(int8_t x,int8_t y)
{
  if(inbound(x,y))
    return level[(y*width)+x];
  else
    return 1;  //outside the map is a sea of walls
}
uint8_t World::getFast(int8_t x,int8_t y)
{
  return level[(y*width)+x];
}
bool World::getItem(int8_t x,int8_t y)
{
  if(inbound(x,y))
    return items[(y*width)+x];
  else
    return false;
}

bool World::inbound(int8_t x,int8_t y)
{
  return((x>=0)&&(y>=0)&&(x<width)&&(y<height));
}
