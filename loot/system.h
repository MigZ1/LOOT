#pragma once

#include "core/core.h"
#include "arduboy.h"
#include "constants.h"

#define SCREEN_WIDTH  (WIDTH)
#define SCREEN_HEIGHT (HEIGHT)

// IMPORTANT: These change value depending whether you're compiling for Arduboy 10 or the Devkit.
// Please remember to define ARDUBOY_10 or AB_DEVKIT in your ino file.
#define BTN_U (UP_BUTTON)
#define BTN_D (DOWN_BUTTON)
#define BTN_L (LEFT_BUTTON)
#define BTN_R (RIGHT_BUTTON)
#define BTN_A (A_BUTTON)
#define BTN_B (B_BUTTON)

class System : public Arduboy
{
  private:
  uint8_t nowInput, prevInput, lastState, state;

  public:
  // Explicitly calling parent's default constructor for the sake of clarity.
  // Arduboy's constructor would be called even if the exlicit call were removed.
  System(void) : Arduboy()
  {
    this->lastState = stateNull;
    this->state = stateMenu;  //begin on the menu
    this->nowInput  = 0x00;
    this->prevInput = 0xff;
    this->setFrameRate(30); // I checked, it's safe to do this
  }

  void update(void)
  {
    //input
    this->prevInput = this->nowInput;
    this->nowInput  = this->buttonsState();

    // Remapping the button byte every frame is a big waste of time, just use the native bit arrangement
    // Not to mention every one of these function calls was reading from 3 input pins each time, just to arrive
    // at the same result each time. That's 6 times the necessary number of instructions.

    // if(arduboy.pressed(UP_BUTTON)) { nowInput |= BTN_U; }
    // if(arduboy.pressed(DOWN_BUTTON)) { nowInput |= BTN_D; }
    // if(arduboy.pressed(LEFT_BUTTON)) { nowInput |= BTN_L; }
    // if(arduboy.pressed(RIGHT_BUTTON)) { nowInput |= BTN_R; }
    // if(arduboy.pressed(A_BUTTON)) { nowInput |= BTN_A; }
    // if(arduboy.pressed(B_BUTTON)) { nowInput |= BTN_B; }
  }

  bool isPressed(const uint8_t button) const
  {
     return ((this->nowInput & button) != 0);
  }

  bool isPushed(const uint8_t button) const
  {
    // If pressed this frame, but not last frame
    return ((this->nowInput & button) != 0) && ((this->prevInput & button) == 0);
  }

  bool isReleased(const uint8_t button) const
  {
    // If released in the last frame
    return ((this->prevInput & button) != 0) && ((this->nowInput & button) == 0);
  }

  void drawSprite(int8_t x, int8_t y, const byte* bitmap, byte c) {
    this->drawBitmap(x ,y , bitmap+2, pgm_read_byte(bitmap), pgm_read_byte(bitmap+1), c);
  }

  void drawSpriteMasked(int8_t x,int8_t y,const byte* bitmap,const byte* mask)
  {
    this->drawBitmap(x, y, mask+2, pgm_read_byte(mask), pgm_read_byte(mask+1),0);
    this->drawBitmap(x, y, bitmap+2, pgm_read_byte(bitmap), pgm_read_byte(bitmap+1),1);
  }

  uint8_t getState(void) const
  {
    return this->state;
  }

  uint8_t getLastState(void) const
  {
    return this->lastState;
  }

  bool stateChanged(void) const
  {
    return (this->state != this->lastState);
  }

  void setState(const uint8_t newstate)
  {
    this->lastState = this->state;
    this->state = newstate;
  }

  void stateEndChange(void)
  {
    this->lastState = this->state;
  }
};
