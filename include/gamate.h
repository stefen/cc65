/*****************************************************************************/
/*                                                                           */
/*                                gamate.h                                   */
/*                                                                           */
/*                   Gamate system specific definitions                      */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/* (w) 2015 Groepaz/Hitmen (groepaz@gmx.net)                                                  */
/*     based on technical reference by PeT (mess@utanet.at)                  */
/*                                                                           */
/* This software is provided 'as-is', without any expressed or implied       */
/* warranty.  In no event will the authors be held liable for any damages    */
/* arising from the use of this software.                                    */
/*                                                                           */
/* Permission is granted to anyone to use this software for any purpose,     */
/* including commercial applications, and to alter it and redistribute it    */
/* freely, subject to the following restrictions:                            */
/*                                                                           */
/* 1. The origin of this software must not be misrepresented; you must not   */
/*    claim that you wrote the original software. If you use this software   */
/*    in a product, an acknowledgment in the product documentation would be  */
/*    appreciated but is not required.                                       */
/* 2. Altered source versions must be plainly marked as such, and must not   */
/*    be misrepresented as being the original software.                      */
/* 3. This notice may not be removed or altered from any source              */
/*    distribution.                                                          */
/*                                                                           */
/*****************************************************************************/

#ifndef _GAMATE_H
#define _GAMATE_H

/* Check for errors */
#if !defined(__GAMATE__)
#  error This module may only be used when compiling for the Gamate!
#endif

#define AUDIO_BASE      0x4000

/*
   base clock cpu clock/32 ?

0/1: 1. channel(right): 12 bit frequency: right frequency 0 nothing, 1 high; 3 23khz; 4 17,3; 10 6,9; 15 4.6; $60 720hz; $eff 18,0; $fff 16,9 hz)
 (delay clock/32)
2/3: 2. channel(left): 12 bit frequency
4/5: 3. channel(both): 12 bit frequency
6: 0..5 noise frequency 0 fast 1f slow (about 500us) 15.6ns--> clock/32 counts
7 control (hinibble right)
 bit 0: right channel high (full cycle, else square pulse/tone)
 bit 1: left channel high
 bit 2: both channel high
 bit 3: set right tone (else noise)
 bit 4: set left channel normal
 bit 5: set both normal
 bits 30: 11 high, 10 square, 01 noise, 00 noise only when square high
 noise means switches channel to ad converter based noise algorithmen
 (white noise shift register 17bit wide, repeats after about 130000 cycles)
 probably out=!bit16, bit0=bit16 xor bit13; runs through, so start value anything than 0
8: 1st volume: 0..3 square volume; bit 4 envelope (higher priority)
9: 2nd volume
10: 3rd volume
11/12: envelope delay time 0 fast, 0xffff slow/nearly no effect (2 22us, 4 56us)
 frequency $800, envelope $10 2 times in pulse high time (4*16*16)
13: envelope control
 0-3 one time falling
 4-7 one time rising
 8 falling
 9 one time falling
 a starts with down falling, rising; same falling time, but double/longer cycle
 b one time falling, on
 c rising
 d one time rising, on
 e rising, falling (double cycle before restart)
 f one time rising
 bit 0: once only
 bit 1: full tone
 bit 2: start rising (else falling)
 bit 3:
*/

#define JOY_DATA        0x4400

#define JOY_DATA_UP     0x01
#define JOY_DATA_DOWN   0x02
#define JOY_DATA_LEFT   0x04
#define JOY_DATA_RIGHT  0x08
#define JOY_DATA_FIRE_A 0x10
#define JOY_DATA_FIRE_B 0x20
#define JOY_DATA_START  0x40
#define JOY_DATA_SELECT 0x80

/* LCD

    resolution 160x152 in 4 greys/greens
    2 256x256 sized bitplanes (2x 8kbyte ram)
*/
#define LCD_BASE        0x5000

#define LCD_MODE        0x5001
/*
 bit 3..0 (from zeropage 15)
        bit 0 set no normal screen display, seldom scrolling effects on screen;
        bytes written to somewhat actual display refresh position!?
    bytes read "random"
  bit 1,2,3 no effect
 bit 4 swaps plane intensity
 bit 5 ? display effect
 bit 6 on y auto increment (else auto x increment), reading
 bit 7 ? lcd flickering
*/
#define LCD_MODE_INC_Y  0x40

#define LCD_XPOS        0x5002  /* smooth scrolling X */
#define LCD_YPOS        0x5003  /* smooth scrolling Y */
/*
 smooth scrolling until $c8 with 200 limit
 after 200 display if ((value & 0xf) < 8) display of (value & 0xf) - 8
 chaos lines from value + current line from plane 2 only then lines starting
 with zero (problematic 200 limit/overrun implementation!?)
*/
#define LCD_X           0x5004  /* x-addr */
/*
 bit 5,6 no effect
 bit 7 0 1st/1 2nd bitplane
*/
#define LCD_XPOS_PLANE1 0x00
#define LCD_XPOS_PLANE2 0x80

#define LCD_Y           0x5005  /* y-addr */

#define LCD_READ        0x5006  /* read from RAM (no auto inc?) */
#define LCD_DATA        0x5007  /* write to RAM */


/* constants for the conio implementation */
#define COLOR_BLACK     0x03
#define COLOR_WHITE     0x00

#define CH_HLINE                1
#define CH_VLINE                2
#define CH_CROSS                3
#define CH_ULCORNER             4
#define CH_URCORNER             5
#define CH_LLCORNER             6
#define CH_LRCORNER             7
#define CH_TTEE                 8
#define CH_BTEE                 9

#define CH_RTEE                 11
#define CH_LTEE                 12

#define CH_ENTER                13
#define CH_PI                   18

#define TV_NTSC                 0
#define TV_PAL                  1
#define TV_OTHER                2

/* No support for dynamically loadable drivers */
#define DYN_DRV         0

/* The addresses of the static drivers */
extern void gamate_stdjoy_joy[];   /* Referred to by joy_static_stddrv[] */

#define JOY_FIRE_B              5
#define JOY_START               6
#define JOY_SELECT              7

void waitvblank (void);
/* Wait for the vertical blanking */

/* NOTE: all Gamate are "NTSC" */
#define get_tv()                TV_NTSC
/* Return the video mode the machine is using. */

/* End of gamate.h */
#endif

