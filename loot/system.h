//Copied from i40000
//todo : replace with custom version

#pragma once

#include "arduboy.h"
#include "constants.h"

#define SCREEN_WIDTH  (WIDTH)
#define SCREEN_HEIGHT (HEIGHT)

#define BTN_U (B00000001)
#define BTN_D (B00000010)
#define BTN_L (B00000100)
#define BTN_R (B00001000)
#define BTN_A (B00010000)
#define BTN_B (B00100000)

struct System {
  void begin() {
    arduboy.begin();
    arduboy.setFrameRate(30);
    nowInput  = 0x00;
    prevInput = 0xff;

    lastState = stateNull;
    state = stateMenu;  //begin on the menu
  }

  void update() {
    //input
    prevInput = nowInput;
    nowInput  = 0;

    //test to see if this can be replaced with a call to Arduboy(Core?).buttonState()
    if(arduboy.pressed(UP_BUTTON)) { nowInput |= BTN_U; }
    if(arduboy.pressed(DOWN_BUTTON)) { nowInput |= BTN_D; }
    if(arduboy.pressed(LEFT_BUTTON)) { nowInput |= BTN_L; }
    if(arduboy.pressed(RIGHT_BUTTON)) { nowInput |= BTN_R; }
    if(arduboy.pressed(A_BUTTON)) { nowInput |= BTN_A; }
    if(arduboy.pressed(B_BUTTON)) { nowInput |= BTN_B; }
  }

  bool pressed(byte button) const {
     return (nowInput & button) != 0;
  }
  bool pushed(byte button) const {
    return (nowInput & button) != 0 && (prevInput & button) == 0; //If pressed this frame, but not last frame
  }
  bool released(byte button) const {
    return (prevInput & button) != 0 && (nowInput & button) == 0; //if released in the last frame
  }

  //I'm 99% sure there's an automatic way of doing this.
  bool nextFrame() { return arduboy.nextFrame(); }
  void clear() { arduboy.clear(); }
  void display() { arduboy.display(); }
  int frameCount() { return arduboy.frameCount; }
  bool everyXFrames(uint8_t frames) { return arduboy.everyXFrames(frames); }
  void drawPixel(uint8_t x, uint8_t y,byte c) { arduboy.drawPixel(x,y,c); }
  void drawBitmap(int8_t x,int8_t y,const byte* bitmap, uint8_t w,uint8_t h,byte c) {
    arduboy.drawBitmap(x, y, bitmap, w,h, c);
  }
  void drawLine(int8_t x,int8_t y,int8_t x2,int8_t y2,byte c)  { arduboy.drawLine(x,y,x2,y2,c);  }
  void fillRect(int8_t x, int8_t y, uint8_t w, uint8_t h, byte c) { arduboy.fillRect(x, y, w, h, c); }
  void drawRect(int8_t x, int8_t y, uint8_t w, uint8_t h, byte c) { arduboy.drawRect(x, y, w, h, c); }
  void setCursor(uint8_t x, uint8_t y) { arduboy.setCursor(x, y); }
  void print(const char* text) { arduboy.print(text); }
  void print(const __FlashStringHelper *string) { arduboy.print(string);  }  //for F("string") stuff
  void fillScreen(uint8_t col) { arduboy.fillScreen(col); }
  int cpuLoad()    { return arduboy.cpuLoad(); }    //why is this an int?

  //putting state in here so everything can set it
  int8_t getState() { return state; }
  int8_t getLastState() { return lastState; }
  void setState(int8_t newstate) { state = newstate; }
  bool stateChanged()  { return (state != lastState);  }
  void stateEndChange()    {  lastState = state;   }

  private:
  Arduboy arduboy;
  byte    nowInput;
  byte    prevInput;
  int8_t  lastState,state;
};
