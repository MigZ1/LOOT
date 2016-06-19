#include "system.h"
#include "render.h"
#include "world.h"
#include "player.h"

Render::Render(System & ab,World & world,Player & player)
{
  this->ab = &ab;
  this->world = &world;
  this->player = &player;
}

void Render::init()
{
  calculateView(player->x,player->y,player->dir);
}

inline bool Render::wallCheck(int8_t x,int8_t y)
{
  return (world->get(x,y)==1);
}

void Render::calculateView(int8_t x,int8_t y,uint8_t dir)
{
  //wallShow[10] = false;
  wallShow[10] = wallCheck(x,y);
  if (dir == 0)
  {
    wallShow[0] = wallCheck(x+3,y-1);
    wallShow[1] = wallCheck(x+3,y);
    wallShow[2] = wallCheck(x+3,y+1);
    wallShow[3] = wallCheck(x+2,y-1);
    wallShow[4] = wallCheck(x+2,y);
    wallShow[5] = wallCheck(x+2,y+1);
    wallShow[6] = wallCheck(x+1,y-1);
    wallShow[7] = wallCheck(x+1,y);
    wallShow[8] = wallCheck(x+1,y+1);
    wallShow[9] = wallCheck(x,y-1);
    wallShow[11] = wallCheck(x,y+1);
  }
  if (dir == 1)
  {
    wallShow[0] = wallCheck(x+1,y+3);
    wallShow[1] = wallCheck(x,y+3);
    wallShow[2] = wallCheck(x-1,y+3);
    wallShow[3] = wallCheck(x+1,y+2);
    wallShow[4] = wallCheck(x,y+2);
    wallShow[5] = wallCheck(x-1,y+2);
    wallShow[6] = wallCheck(x+1,y+1);
    wallShow[7] = wallCheck(x,y+1);
    wallShow[8] = wallCheck(x-1,y+1);
    wallShow[9] = wallCheck(x+1,y);
    wallShow[11] = wallCheck(x-1,y);
  }
  if (dir == 2)
  {
    wallShow[0] = wallCheck(x-3,y+1);
    wallShow[1] = wallCheck(x-3,y);
    wallShow[2] = wallCheck(x-3,y-1);
    wallShow[3] = wallCheck(x-2,y+1);
    wallShow[4] = wallCheck(x-2,y);
    wallShow[5] = wallCheck(x-2,y-1);
    wallShow[6] = wallCheck(x-1,y+1);
    wallShow[7] = wallCheck(x-1,y);
    wallShow[8] = wallCheck(x-1,y-1);
    wallShow[9] = wallCheck(x,y+1);
    wallShow[11] = wallCheck(x,y-1);
  }
  if (dir == 3)
  {
    wallShow[0] = wallCheck(x-1,y-3);
    wallShow[1] = wallCheck(x,y-3);
    wallShow[2] = wallCheck(x+1,y-3);
    wallShow[3] = wallCheck(x-1,y-2);
    wallShow[4] = wallCheck(x,y-2);
    wallShow[5] = wallCheck(x+1,y-2);
    wallShow[6] = wallCheck(x-1,y-1);
    wallShow[7] = wallCheck(x,y-1);
    wallShow[8] = wallCheck(x+1,y-1);
    wallShow[9] = wallCheck(x-1,y);
    wallShow[11] = wallCheck(x+1,y);
  }
  if (wallShow[7])  //speed up by disabling hidden walls
  {
    wallShow[4] = false;
    wallShow[0] = false;
    wallShow[2] = false;
  }
  if (wallShow[4])
  {
    wallShow[1] = false;
  }
}

void Render::step()
{
  if(player->moved) //only recalculate on movement
  {
    calculateView(player->x,player->y,player->dir);
    player->moved = false;
  }
}

void Render::draw()
{
  drawView();
  drawMap();
}

void Render::drawView()
{
  int wallSize[] = { 6,10,18,32,64 };  //size in pixels of each step
  char wall = 0;  //current wall

  int drawSize,halfSize,backSize,halfBackSize,left,leftBack,top,topBack;
  for(char i=0; i<4; ++i) //distance
  {
    drawSize = wallSize[i+1]; halfSize = drawSize/2;      //size of walls on screen
    backSize = wallSize[i];   halfBackSize = backSize/2;  //size of the backside of the walls, for depth
    leftBack = 32-(halfBackSize*3);      //x position of the walls on screen
    left     = 32-(halfSize*3);
    topBack  = 32-halfBackSize;         //y position of the walls on screen
    top      = 32-halfSize;

    for(char n=0; n<3; ++n) //left->right
    {
      if (wallShow[wall]) //if wall exists, draw it
      {
        if((n==0)&&(!wallShow[wall+1]))  //left wall, only draw if the middle wall is missing
        {
          ab->fillRect(left+drawSize,top,(leftBack+backSize)-(left+drawSize),drawSize,0);  //blank out area behind wall
          ab->drawLine(leftBack+backSize,topBack+backSize,left+drawSize,top+drawSize,1);   //lower line
          ab->drawLine(left+drawSize,top,leftBack+backSize,topBack,1);                     //upper line
          ab->drawLine(leftBack+backSize,topBack,leftBack+backSize,topBack+backSize,1);    //far line
        }
        if((n==2)&&(!wallShow[wall-1])) //right wall, ditto
        {
          ab->fillRect(leftBack,top,left-leftBack,drawSize,0);
          ab->drawLine(leftBack,topBack,min(left,64),top,1);     //upper
          ab->drawLine(leftBack,topBack+backSize,min(left,64),top+drawSize,1); //lower
          ab->drawLine(leftBack,topBack,leftBack,topBack+backSize,1);  //side
        }
        if((i<3)&&(!wallShow[wall+3]))  //draw flat wall if not immediately next to the camera, and if there is no wall infront
        {
          int wid = drawSize; //width of wall
          if ((n==2) && (left+wid > 64))  //if the wall goes off the render area, chop the width down
          {
            wid = 15; //(64-halfSize)-1;  //magic numbering this because the only time it ever happens is on a close right side wall
          }
          ab->fillRect(left,top,wid,drawSize,0);     //blank out wall area and draw then draw the outline
          ab->drawRect(left,top,wid+1,drawSize+1,1);
        }
      }
      wall++;
      left += drawSize;     //advance left positions
      leftBack += backSize;
    }
  }
  ab->drawRect(0,0,64,64,1);
}

void Render::drawMap()
{
  //draw map grid
  const uint8_t dx = 63;  //x offset, puts on right side of the screen
  for(int iy=0; iy<8; ++iy) //loops x&y, draws a rectangle for every wall
  {
    for(int ix=0; ix<8; ++ix)
    {
      if (world->get(ix,iy))
      {
        ab->drawRect(dx+(ix*8),(iy*8),9,9,1);
      }
    }
  }
  //draws the player as a cross
  char cx = (player->x)+1;
  char cy = (player->y)+1;
  ab->drawLine(dx+(((cx)*8)-6),(cy*8)-6,dx+((cx*8)-2),(cy*8)-2,1);
  ab->drawLine(dx+(((cx)*8)-6),(cy*8)-2,dx+((cx*8)-2),(cy*8)-6,1);

  //outlines the map
  ab->drawLine(dx+64,0,dx+64,63,1);
  ab->drawLine(dx,63,dx+64,63,1);
}

void Render::drawStats()
{
  ab->setCursor(66,2);
  ab->print(F("HP : "));
  ab->setCursor(66,10);
  ab->print(F("SP : "));
  ab->setCursor(66,18);
  ab->print(F("G  : "));
}
