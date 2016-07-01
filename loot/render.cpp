#include "system.h"
#include "render.h"
#include "world.h"
#include "player.h"
#include "direction.h"

Render::Render(System & ab,World & world, Player & player)
{
  this->ab = &ab;
  this->world = &world;
  this->player = &player;
}

inline bool Render::wallCheck(const int8_t x, const  int8_t y)
{
  return (world->get(x, y)==1);
}
inline bool Render::itemCheck(const int8_t x, const int8_t y)
{
  return (world->getItem(x, y));
}

void Render::calculateView(const int8_t x, const int8_t y, const Direction dir)
{
  /*
  if (dir == 0)
  {
    xs[0]=+3; xs[1]=+3; xs[2]=+3; xs[3]=+2; xs[4]=+2; xs[5]=+2; xs[6]=+1; xs[7]=+1; xs[8]=+1; xs[9]=0; xs[10]=0; xs[11]=0;
    ys[0]=-1; ys[1]=0;   ys[2]=+1; ys[3]=-1; ys[4]=0; ys[5]=+1; ys[6]=-1; ys[7]=0; ys[8]=+1; ys[9]=-1; ys[10]=0; ys[11]=+1;
  }
  if (dir == 1)
  {
    xs[0]=+1; xs[1]=0; xs[2]=0-1; xs[3]=+1; xs[4]=0; xs[5]=-1; xs[6]=+1; xs[7]=0; xs[8]=-1; xs[9]=+1; xs[10]=0; xs[11]=-1;
    ys[0]=+3; ys[1]=+3; ys[2]=+3; ys[3]=+2; ys[4]=+2; ys[5]=+2; ys[6]=+1; ys[7]=+1; ys[8]=+1; ys[9]=0; ys[10]=0; ys[11]=0;
  }
  if (dir == 2)
  {
    xs[0]=-3; xs[1]=-3; xs[2]=-3; xs[3]=-2; xs[4]=-2; xs[5]=-2; xs[6]=-1; xs[7]=-1; xs[8]=-1; xs[9]=0; xs[10]=0; xs[11]=0;
    ys[0]=+1; ys[1]=0; ys[2]=-1; ys[3]=+1; ys[4]=0; ys[5]=-1; ys[6]=+1; ys[7]=0; ys[8]=-1; ys[9]=+1; ys[10]=0; ys[11]=-1;
  }
  if (dir == 3)
  {
    xs[0]=-1; xs[1]=0; xs[2]=+1; xs[3]=-1; xs[4]=0; xs[5]=+1; xs[6]=-1; xs[7]=0; xs[8]=+1; xs[9]=-1; xs[10]=0; xs[11]=+1;
    ys[0]=-3; ys[1]=-3; ys[2]=-3; ys[3]=-2; ys[4]=-2; ys[5]=-2; ys[6]=-1; ys[7]=-1; ys[8]=-1; ys[9]=0; ys[10]=0; ys[11]=0;
  }
  */

  static const int8_t arrA[12] = { 3, 3, 3, 2, 2, 2, 1, 1, 1, 0, 0, 0 };
  static const int8_t arrB[12] = { -1, 0, +1, -1, 0, +1, -1, 0, +1, -1, 0, +1 };

  int8_t xs, ys;
  for(uint8_t i = 0; i < 12; ++i)
  {
    switch(dir)
    {
      case Direction::East: xs = arrA[i]; ys = arrB[i]; break;
      case Direction::South: xs = -arrB[i]; ys = arrA[i]; break;
      case Direction::West: xs = -arrA[i]; ys = -arrB[i]; break;
      case Direction::North: xs = arrB[i]; ys = -arrA[i]; break;
    }

    wallShow[i] = wallCheck(x + xs, y + ys);
    itemShow[i] = itemCheck(x + xs, y + ys);
  }


  wallShow[10] = false; //position player is standing on

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

void Render::step(void)
{
  if(player->getMoved())
    calculateView(player->x,player->y,player->getDirection());
}

void Render::draw(void)
{
  drawView();
  drawMap();
}

void Render::drawView(void)
{
  const uint8_t wallSize[] = { 6,10,18,32,64 };  //size in pixels of each step
  char wall = 0;  //current wall

  int drawSize,halfSize,backSize,halfBackSize,left,leftBack,top,topBack;
  for(char i=0; i<4; i++) //distance
  {
    drawSize = wallSize[i+1]; halfSize = drawSize/2;      //size of walls on screen
    backSize = wallSize[i];   halfBackSize = backSize/2;  //size of the backside of the walls, for depth
    leftBack = 32-(halfBackSize*3);      //x position of the walls on screen
    left     = 32-(halfSize*3);
    topBack  = 32-halfBackSize;         //y position of the walls on screen
    top      = 32-halfSize;

    for(char n=0; n<3; n++) //left->right
    {
      if (wallShow[wall]) //if wall exists, draw it
      {
        if((n==0)&&(wallShow[wall+1]==0))  //left wall, only draw if the middle wall is missing
        {
          ab->fillRect(left+drawSize,top,(leftBack+backSize)-(left+drawSize),drawSize,0);  //blank out area behind wall
          ab->drawLine(leftBack+backSize,topBack+backSize,left+drawSize,top+drawSize,1);   //lower line
          ab->drawLine(left+drawSize,top,leftBack+backSize,topBack,1);                     //upper line
          ab->drawLine(leftBack+backSize,topBack,leftBack+backSize,topBack+backSize,1);    //far line
        }
        if((n==2)&&(wallShow[wall-1]==0)) //right wall, ditto
        {
          ab->fillRect(leftBack,top,left-leftBack,drawSize,0);
          ab->drawLine(leftBack,topBack,left,top,1);     //upper
          ab->drawLine(leftBack,topBack+backSize,left,top+drawSize,1); //lower
          ab->drawLine(leftBack,topBack,leftBack,topBack+backSize,1);  //side
        }
        if((i<3)&&(wallShow[wall+3]==0))  //draw flat wall if not immediately next to the camera, and if there is no wall infront
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
      else if(itemShow[wall])
      {
        int8_t itemx = left+drawSize/2;  itemx -= drawSize/4;
        if(itemx<64)
        {
          int8_t itemy = (top+drawSize)-(drawSize*1/3); itemy -= drawSize/4;
          ab->drawRect(itemx,itemy,drawSize/2,drawSize/2,1);
        }
      }
      wall++;
      left += drawSize;     //advance left positions
      leftBack += backSize;
    }
  }
  ab->fillRect(64,0,16,64,0);  //hide any leaky drawing
  ab->drawRect(0,0,64,64,1);

  ab->setCursor(4,4);
  switch(player->getDirection())
  {
    case Direction::East:  ab->print("EAST"); break;
    case Direction::South: ab->print("SOUTH"); break;
    case Direction::West:  ab->print("WEST"); break;
    case Direction::North: ab->print("NORTH"); break;
    default: ab->print("Wat");
  }
  printf(" Direction: %u", player->getDirection());
}

void Render::drawMap(void)
{
  //draw map grid
  const uint8_t offsetx = 63;  //x offset, puts on right side of the screen
  for(int iy=0; iy<8; ++iy) //loops x&y, draws a rectangle for every wall
  {
    for(int ix=0; ix<8; ++ix)
    {
      if (world->get(ix,iy))
      {
        ab->drawRect(offsetx+(ix*8),(iy*8),9,9,1);
      }
    }
  }
  //draws the player as an arrow
  char dx = offsetx+((player->x)*8);
  char dy = ((player->y)*8);
  //ab->drawLine(playerx+2,playery+2,playerx+6,playery+6,1);
  //ab->drawLine(playerx+2,playery+6,playerx+6,playery+2,1)
  switch(player->getDirection())
  {
    case Direction::East: { ab->drawLine(dx+2,dy+2,dx+6,dy+4,1);  ab->drawLine(dx+2,dy+6,dx+6,dy+4,1); }; break;            // >
    case Direction::South:{ ab->drawLine(dx+2,dy+2,dx+4,dy+6,1);  ab->drawLine(dx+6,dy+2,dx+4,dy+6,1); }; break;      // V
    case Direction::West: { ab->drawLine(dx+6,dy+2,dx+2,dy+4,1);  ab->drawLine(dx+6,dy+6,dx+2,dy+4,1); } break;      // <
    case Direction::North:{ ab->drawLine(dx+2,dy+6,dx+4,dy+2,1);  ab->drawLine(dx+6,dy+6,dx+4,dy+4,1);  } break;      // ^
  }

  //outlines the map
  ab->drawLine(offsetx+64,0,offsetx+64,63,1);
  ab->drawLine(offsetx,63,offsetx+64,63,1);
}

void Render::drawStats(void)
{
  ab->setCursor(66,2);
  ab->print(F("HP : "));
  ab->setCursor(66,10);
  ab->print(F("SP : "));
  ab->setCursor(66,18);
  ab->print(F("G  : "));
}
