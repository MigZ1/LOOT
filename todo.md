[back](./README.md)

#Task list
off the top of my head at 3am, roughly in order of priority

##Design
- [x] Concept renders
- [ ]  Work out general style of game
- [ ]  Plot?
- [ ]  Player goals (Kill wizard, defeat dragon, that sort of thing)
- [ ]  Make big list of needed assets

##Programming
- [x] learn C++
- [x] Implement game framework
- [x] Get dungeon rendering working under framework
- [ ]  Re-implement System class from scratch
- [ ]  Player stats/items
- [ ]  Battle gameplay
- [ ]  Items/Switches in dungeon
- [ ]  Map loading from PROGMEM
- [ ]  Level editor
- [ ]  Game loading/saving from EEPROM
- [ ]  Overworld town
- [ ]  fix this documents formatting
- [ ]  Spruce game up with animations, using whatever space remains

##Art
- [x] Logo!
- [ ]  Enemy designs
- [ ]  Prop/item designs
- [ ]  Walls (do towards the end, these will eat up loads of space)

##Sounds:
- [ ] beep
- [ ] boop
- [ ] warble
- [ ] piezo speakers are great

##Game flow
- Menu
- Play
	- Empty slot
		- Choose class/name
		- New game
  - Occupied slot
  	- Load game
  - Options
    - Sound on/off
    - Down button behavior (Step back/rotate 180")
  - About
    - Credits page

- New Game
  - Exposition text
  - Maybe have a fullscreen graphic if there's space for it
  - Start in town

- Game flow
  - kill monsters
  - find loot
  - get to next floor
  - Kill wizard or whatever
  - ???
  - Profit

##Tech stuff
also written at 3am, please forgive any stupid decisions or calculation errors

- Level format (proposed)
  - byte monsterTypes             Tells the world instance to load a lookup table of enemy types    
  - byte width                    Width of level
  - byte height
  - repeat width*height           Max : 256 (0-255)
    - byte level[i]               See level format
  - byte itemNo                   Max 16
  - repeat itemNo
    - byte item[i]                See item format

  - Calculated level storage sizes:
    - 16*16 with 16 Items : 1+1+1+256+1+(2*16) = 292 bytes
    - 16*16 with 0  Items : 1+1+1+256+1        = 260 bytes
    - 8*8 with 16 Items   : 1+1+1+64+1+(2*16)  = 100 bytes
    - 8*8 with 0 Items    : 1+1+1+64+1         = 68 bytes

- byte level : WWWWXXXX
  - Wall types (WWWW)
    - 0000  = Empty, can have item
    - 0001  = Plain wall
    - 0010  = brick wall
    - 0011  = brick wall w/torch
    - 0100  = locked door, opened with key item
    - 0101  = open door
    - 0110  = blank trigger floor, performs XXXX function, becomes 0000 afterwards
    - 0111  = blank trigger floor, always performs XXXX function
    - 1001  = heal floor image, performs XXXX function
    - 1001  = shop door, triggered on entry. Items are scaled to players level

  - XXXX = Multipurpose
    - if www == 0000  XXXX is the ID of object on tile
    - if www == 0110  XXXX is the function to perform
    - if www == 0111  see 0110
    - if www == 0100  XXXX is the doors destination level
    - if www == 0101  see 0100

  - Wall function operand (XXXX)
    - fill this bit in
    
- Items (all take the appearance of a box in dungeon view)
  - 0000  = Nothing
  - 0001  = key
  - 0010  = HP potion
  - 0011  = SP potion
  - 0100  = Money (10G)
  - 0101  = Money (20G)
  - 0110  = Money (50G)
  - 0111  = Money (100G)
