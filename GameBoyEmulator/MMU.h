#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>

#include "Definitions.h"
#include "Cartridge.h"
#include "Display.h"
#include "Joypad.h"


const u32 MAX_ROM_SIZE = 0x7A1200; // 8 MB
const u16 ONE_BANK_SIZE = 0x4000;

const u8 NUM_VRAM_BANKS = 2;
const u16 NUM_ROM_BANKS = 0x300;

const u16 EIGHT_KB = 0x2000;
const u16 SIXTEEN_KB = 0x4000;


const u16 EXTERNAL_RAM_START = 0xA000;
const u16 INTERNAL_RAM_START = 0xC000;
//const u16 OAM_START = 0xFE00;
const u16 IOREG_START = 0xFF00;
const u16 HRAM_START = 0xFF80;


// Memory management unit, redirects requests for memory to the correct location according to the map
// Total addressable memory 0000 - FFFF 
class MMU
{
public:
    Cartridge* cart;

private:
    char* romPath;
    u32 romSize;


    u8 activeRomBank;
    u16 numberOfRomBanks;

    u8 activeExternalRamBank;
    u16 numberOfExternalRamBanks;
    
    
    //u8 vram[NUM_VRAM_BANKS][EIGHT_KB];    // 8kB vram
    u8 rom[NUM_ROM_BANKS][SIXTEEN_KB];      // up to 0x200 16kb banks ~ 8MB max rom size
    u8 externalRam[1][EIGHT_KB];            // 8k external ram
    u8 internalRam[SIXTEEN_KB];             // 1 bank in GB 1-7 banks in GBC
    u8 IORegs[0x80];
    u8 hram[0x80];
    

    u8 bios[0x100] = {
        0x31, 0xFE, 0xFF, 0xAF, 0x21, 0xFF, 0x9F, 0x32, 0xCB, 0x7C, 0x20, 0xFB, 0x21, 0x26, 0xFF, 0x0E,
        0x11, 0x3E, 0x80, 0x32, 0xE2, 0x0C, 0x3E, 0xF3, 0xE2, 0x32, 0x3E, 0x77, 0x77, 0x3E, 0xFC, 0xE0,
        0x47, 0x11, 0x04, 0x01, 0x21, 0x10, 0x80, 0x1A, 0xCD, 0x95, 0x00, 0xCD, 0x96, 0x00, 0x13, 0x7B,
        0xFE, 0x34, 0x20, 0xF3, 0x11, 0xD8, 0x00, 0x06, 0x08, 0x1A, 0x13, 0x22, 0x23, 0x05, 0x20, 0xF9,
        0x3E, 0x19, 0xEA, 0x10, 0x99, 0x21, 0x2F, 0x99, 0x0E, 0x0C, 0x3D, 0x28, 0x08, 0x32, 0x0D, 0x20,
        0xF9, 0x2E, 0x0F, 0x18, 0xF3, 0x67, 0x3E, 0x64, 0x57, 0xE0, 0x42, 0x3E, 0x91, 0xE0, 0x40, 0x04,
        0x1E, 0x02, 0x0E, 0x0C, 0xF0, 0x44, 0xFE, 0x90, 0x20, 0xFA, 0x0D, 0x20, 0xF7, 0x1D, 0x20, 0xF2,
        0x0E, 0x13, 0x24, 0x7C, 0x1E, 0x83, 0xFE, 0x62, 0x28, 0x06, 0x1E, 0xC1, 0xFE, 0x64, 0x20, 0x06,
        0x7B, 0xE2, 0x0C, 0x3E, 0x87, 0xE2, 0xF0, 0x42, 0x90, 0xE0, 0x42, 0x15, 0x20, 0xD2, 0x05, 0x20,
        0x4F, 0x16, 0x20, 0x18, 0xCB, 0x4F, 0x06, 0x04, 0xC5, 0xCB, 0x11, 0x17, 0xC1, 0xCB, 0x11, 0x17,
        0x05, 0x20, 0xF5, 0x22, 0x23, 0x22, 0x23, 0xC9, 0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B,
        0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E,
        0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC,
        0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E, 0x3C, 0x42, 0xB9, 0xA5, 0xB9, 0xA5, 0x42, 0x3C,
        0x21, 0x04, 0x01, 0x11, 0xA8, 0x00, 0x1A, 0x13, 0xBE, 0x20, 0xFE, 0x23, 0x7D, 0xFE, 0x34, 0x20,
        0xF5, 0x06, 0x19, 0x78, 0x86, 0x23, 0x05, 0x20, 0xFB, 0x86, 0x20, 0xFE, 0x3E, 0x01, 0xE0, 0x50,
    };
    
    bool biosComplete;

    Display* display;
	Joypad* joypad;


public:

    MMU();
    MMU(char* path, Display* d, Joypad* j);
    ~MMU();

    bool LoadRom();
    u8 ReadByte(u16 addr);
    u16 ReadTwoBytes(u16 addr);
    
    void PushTwoBytes(u16 &sp, u16 data);
    u16 PopTwoBytes(u16 &sp);

    void WriteByte(u16 addr, u8 data);
    void WriteTwoBytes(u16 addr, u16 data);


    void SetBiosComplete(bool val) { biosComplete = val; }
    bool GetBiosComplete() { return biosComplete; }

    void DumpToFile();

private:


};

/* 
  ----- Memory Structure (top down) -----

       ------------------------------
       Interupts Enable Registers (IE)
       ------------------------------   FFFF
       ------------------------------   FFFE
       High RAM (HRAM) 0x7E (126 Bytes)
       ------------------------------   FF80
       ------------------------------   FF7F
       I/O Registers 0x7F (127 Bytes)
       ------------------------------   FF00
       ------------------------------   FEFF ----
       Not Usable - 60 (96 Bytes)                |
       ------------------------------   FEA0     |
       ------------------------------   FE9F     | = 0xFF (255 Bytes)
       Sprite attribute table (OAM)              |
       Size: 0x9F (159 Bytes)                    |
       ------------------------------   FE00 ----
       ------------------------------   FDFF
       Mirror of C000-DDFF (ECHO)
       Generally not used
       ------------------------------   E000
       ------------------------------   DFFF
       8kB internal ram
       D000-DFFF switchable in GBC
       0x01 - 0x07 select bank 1-7
       Select Byte - 0xFF70
       ------------------------------   C000
       ------------------------------   BFFF
       8kB external RAM
       In cartridge, can be switcable
       ------------------------------   A000  
       ------------------------------   9FFF
       8kB VRAM (8kB GB, 16kB GBC)
       Switchable bank 0/1 if GBC
       ------------------------------   8000 
       ------------------------------   7FFF ----
       16kB switchable ROM bank                  |
       01-NN                                     |                                             
       ------------------------------   4000     | = 32kB Cartrigbe
       ------------------------------   3FFF     |
       16kB ROM bank #0 |                        |
       ------------------------------   0000 ----




*/