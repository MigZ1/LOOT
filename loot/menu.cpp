#include "menu.h"
#include "constants.h"
#include "graphics.h"
#include "system.h"

Menu::Menu(System & ab)
{
  this->ab = &ab;
}

void Menu::init(void)
{
  select = 0;
  page = 0;
  logoAnim = 64;
}

void Menu::step(void)
{
  logoAnim = max(logoAnim - 1, 0);

  if(logoAnim == 0) //if menu is ready
  {
    if(ab->isPushed(BTN_A))
    {
      switch(page)
      {
        case 0:
        {
          switch(select)
          {
          case 0: { ab->setState(stateGame); break; }
          case 1: { page = 2; break; }
          case 2: { page = 3; select = 2; break; }
          }
          break;
        }
        case 2:
        {
          page = 0;
          select = 1;
          break;
        }
        case 3:
        {
          page = 0;
          break;
        }
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

    select = min(max(select, 0), 2); //seriously, no clamp()?
  }
}

void Menu::draw(void)
{
  switch(page)
  {
    case 0:
    {
      //logo
      if (logoAnim > 0)
        ab->drawSprite(8, 5 - (64 - logoAnim), imgTitle, 1);
      //menu text
      ab->setCursor(16, logoAnim + 8);
      ab->print(F("Play"));
      ab->setCursor(16, logoAnim + 16);
      ab->print(F("Config"));
      ab->setCursor(16, logoAnim + 24);
      ab->print(F("About"));
      //select cursor
      ab->setCursor(8, logoAnim + 8 + (8 * select));
      ab->print(F(">"));
      break;
    }
    case 1: //Slots
    {
    }
    case 2: //options
    {
      ab->setCursor(0, 0);
      ab->print(F("Nothing to see here!"));
      break;
    }
    case 3: //About
    {
      ab->setCursor(0, 0);
      ab->print(F("Test string!"));
      break;
    }
  }
}
