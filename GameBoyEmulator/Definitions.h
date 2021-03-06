#pragma once


// Defined types, we dont care about specific types such as char, short, int etc
// we just care about its size in bits.
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;


// Definitions for keybinds
#define Key_Right	SDLK_RIGHT
#define Key_Left	SDLK_LEFT
#define Key_Up		SDLK_UP
#define Key_Down	SDLK_DOWN
#define Key_A		SDLK_s      // Changed to match BGB
#define Key_B		SDLK_a
#define Key_Select	SDLK_RSHIFT
#define Key_Start	SDLK_RETURN

// Controller keybinds
#define Button_Right	SDL_CONTROLLER_BUTTON_DPAD_RIGHT
#define Button_Left	    SDL_CONTROLLER_BUTTON_DPAD_LEFT
#define Button_Up		SDL_CONTROLLER_BUTTON_DPAD_UP
#define Button_Down	    SDL_CONTROLLER_BUTTON_DPAD_DOWN
#define Button_A		SDL_CONTROLLER_BUTTON_B      
#define Button_B		SDL_CONTROLLER_BUTTON_A
#define Button_Select	SDL_CONTROLLER_BUTTON_GUIDE
#define Button_Start	SDL_CONTROLLER_BUTTON_START

#define CARTRIDGE_TYPE_OFFSET = 0x147