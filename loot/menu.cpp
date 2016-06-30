#include "menu.h"
#include "constants.h"
#include "graphics.h"
#include "system.h"

Menu::Menu(System & ab)
{
  this->ab = &ab;
}

void Menu::init()
{
  select = 0;
  page = 0;
  logoAnim = 64;
}

void Menu::step()
{
  logoAnim = max(logoAnim--,0);

  if(logoAnim==0) //if menu is ready
  {
    if(ab->isPushed(BTN_A))
    {
      switch(page)
      {
        case 0:
        {
          if(select==0) { ab->setState(stateGame);  };  //todo: link to a new/load game screen
          if(select==1) { page = 2;};
          if(select==2) { page = 3; select = 2; };
        }; break;
        case 2:
        {
          page = 0; select = 1;
        }; break;
        case 3:
        {
          page = 0;
        }; break;
      }
    }
    if(ab->isPushed(BTN_U))
    {
      --select;
    }
    if(ab->isPushed(BTN_D))
    {
      ++select;
    }

    select = min(max(select,0),2); //seriously, no clamp()?
  }
}
void Menu::draw()
{
  switch(page)
  {
    case 0:
    {
      //logo
      if (logoAnim>0)
        ab->drawBitmap(8,5-(64-logoAnim), imgTitle, 112, 54, 1);
      //menu text
      ab->setCursor(16,logoAnim+8);
      ab->print(F("Play"));
      ab->setCursor(16,logoAnim+16);
      ab->print(F("Config"));
      ab->setCursor(16,logoAnim+24);
      ab->print(F("About"));
      //select cursor
      ab->setCursor(8,logoAnim+8+(8*select));
      ab->print(F(">"));
    };break;
    case 1: //Slots
    {

    };break;
    case 2: //options
    {
      ab->setCursor(0,0);
      ab->print(F("Nothing to see here!"));
    }; break;
    case 3: //About
    {
      ab->setCursor(0,0);
      ab->print(F("Test string!"));
    }; break;
  };
}
