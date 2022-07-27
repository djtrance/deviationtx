/************************************
This is a our graphics core library, for all our displays. 
We'll be adapting all the
existing libaries to use this core to make updating, support 
and upgrading easier!

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above must be included in any redistribution
****************************************/


#include "common.h"
#include <stdlib.h>
#include <stdio.h>
#include "gui/gui.h"
#include "lcd.h"
#include "lcd_page_props.h"

#define ZOOM cur_str.font.zoom

#if HAS_MAPPED_GFX
#define LCD_DrawPixelXY LCD_DrawMappedPixelXY
#define LCD_DrawPixel   LCD_DrawMappedPixel
#define LCD_DrawStart   LCD_DrawMappedStart
#define LCD_DrawStop()  (void)1
#define LCD_DrawUSBLogo LCD_DrawUSBLogo
#define LCD_FillRect    LCD_FilMappedlRect

void LCD_LoadFont(int idx, const char *file, int x_off, int y_off, int w, int h)
{
    (void)w;
    (void)h;
    LCD_SetMappedWindow(idx+4);
    LCD_DrawWindowedImageFromFile(2, 5, file, 8, 11, x_off, y_off);
    for (int i = 0; i < 12; i++) {
        LCD_DrawMappedPixelXY(i, 0, 0xffff);
        LCD_DrawMappedPixelXY(i, 17, 0xffff);
    }
    for (int i = 1; i < 17; i++) {
        LCD_DrawMappedPixelXY(0, i, 0xffff);
        LCD_DrawMappedPixelXY(11, i, 0xffff);
    }
    LCD_SetMappedWindow(0);
}
#include "../320x240x16/lcd_gfx.c"
#else //MAPPED_GFX
#define swap(x, y) {int __tmp = x; x = y; y = __tmp;}


void LCD_DrawFastVLine(int16_t x, int16_t y, 
                 int16_t h, uint16_t color) {    
    (void) color;
    h+=y;
    for(y; y<= h;y++){
      LCD_PrintCharXY(x, y, 'l');
    }
}

void LCD_DrawFastHLine(u16 x, u16 y, u16 w, u16 color) {
   
    (void) color;
    w+=x;
    for(x; x<=w;x++){
      LCD_PrintCharXY(x, y, '-');
    }
}

void LCD_DrawDashedHLine(int16_t x, int16_t y, 
             int16_t w, int16_t space, uint16_t color)
{
  (void) x;
  (void) y;
  (void) w;
  (void) space;
  (void) color;
}

void LCD_DrawDashedVLine(int16_t x, int16_t y, 
             int16_t h, int16_t space, uint16_t color) {
  (void) x;
  (void) y;
  (void) h;
  (void) space;
  (void) color;
}

// draw a circle outline
void LCD_DrawCircle(u16 x0, u16 y0, u16 r, u16 color)
{
  (void) x0;
  (void) y0;
  (void) r;
  (void) color;
}

void LCD_FillCircle(u16 x0, u16 y0, u16 r, u16 color)
{
  (void) x0;
  (void) y0;
  (void) r;
  (void) color;
}

#if 0
// bresenham's algorithm - thx wikpedia
void LCD_DrawLine(u16 x0, u16 y0, u16 x1, u16 y1, u16 color)
{
 
  (void) color;
  u16 m = (x1 - x0)/ (y1 - y0);
  unsigned c;
  if(m == 0){
    c='-';
  }else if(m >0){
    if(m<=0.5){
      c='.';
      }else{
      c= LCD_CENTER_DOT;
    }

  }else{
    if(m<= -0.5){
      c='.';
      }else{
      c= LCD_CENTER_DOT;
    }

  }

  
  for(x0; x0 <= x1; x0++){
    LCD_PrintCharXY(x0, y1 = m*(x0), c);
  }

  
}
#endif
#if 1
void LCD_DrawLine(u16 x0, u16 y0, u16 x1, u16 y1, u16 color)
{
  (void) color;
  int steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    swap(x0, y0);
    swap(x1, y1);
  }

  if (x0 > x1) {
    swap(x0, x1);
    swap(y0, y1);
  }

  int dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int err = dx / 2;
  int ystep;

  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;
  }

  for (; x0<=x1; x0++) {
    if (steep) {
      if((x1-x0)<=0)
      LCD_PrintCharXY(y0, x0, '.');
      else 
      LCD_PrintCharXY(y0, x0, 'l');

    } else {
      LCD_PrintCharXY(x0, y0, LCD_CENTER_DOT);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}
#endif
// draw a rectangle
void LCD_DrawRect(u16 x, u16 y, u16 w, u16 h, u16 color)
{
  (void) x;
  (void) y;
  (void) w;
  (void) h;
  (void) color;
}

// draw a rounded rectangle!
void LCD_DrawRoundRect(u16 x, u16 y, u16 w, u16 h, u16 r, u16 color)
{
  (void) x;
  (void) y;
  (void) w;
  (void) h;
  (void) r;
  (void) color;
}

// fill a rounded rectangle!
void LCD_FillRoundRect(u16 x, u16 y, u16 w, u16 h, u16 r, u16 color)
{
  (void) x;
  (void) y;
  (void) w;
  (void) h;
  (void) r;
  (void) color;
}

// draw a triangle!
void LCD_DrawTriangle(u16 x0, u16 y0, u16 x1, u16 y1, u16 x2, u16 y2, u16 color)
{
  (void) x0;
  (void) y0;
  (void) x1;
  (void) y1;
  (void) x2;
  (void) y2;
  (void) color;
}

// fill a triangle!
void LCD_FillTriangle(u16 x0, u16 y0, u16 x1, u16 y1, u16 x2, u16 y2, u16 color)
{
  (void) x0;
  (void) y0;
  (void) x1;
  (void) y1;
  (void) x2;
  (void) y2;
  (void) color;
}

u8 LCD_ImageIsTransparent(const char *file)
{
  (void) file;  
  return 0;
}

u8 LCD_ImageDimensions(const char *file, u16 *w, u16 *h)
{
    (void) file;
    *w = 0;
    *h = 0;
    return 1;
}

void LCD_DrawWindowedImageFromFile(u16 x, u16 y, const char *file, s16 w, s16 h, u16 x_off, u16 y_off)
{
  (void) x;
  (void) y;
  (void) file;
  (void) w;
  (void) h;
  (void) x_off;
  (void) y_off;
}

void LCD_DrawImageFromFile(u16 x, u16 y, const char *file)
{
  (void) x;
  (void) y;
  (void) file;
}

void LCD_DrawRLE(const u8 *data, int len, u32 color)
{
  (void) data;
  (void) len;
  (void) color;
}
#endif //MAPPED_GFX

#undef LCD_FillRect
void LCD_FillRect(u16 x, u16 y, u16 w, u16 h, u16 color)
{
  unsigned i, j;
  (void) color;

  #if HAS_MAPPED_GFX
     if (LCD_GetMappedWindow()) {
         LCD_FilMappedlRect(x, y, w, h, color);
         return;
     }
  #endif
  for(i = 0; i < h; i+= ZOOM) {
    LCD_SetXY(x, y + i);
    for(j = 0; j < w; j+= ZOOM)
      LCD_PrintChar(' ');
  }
}

void LCD_DrawUSBLogo(int lcd_width, int lcd_height)
{
  u16 width, height;
  LCD_SetFont(2);
  LCD_SetFontColor(0xffff);
  LCD_GetStringDimensions((u8 *)_tr("Deviation\n   USB"), &width, &height);
  printf("(%d, %d)- > (%d, %d)", lcd_width, lcd_height, width, height);
  LCD_SetFontColor(0x7E0);
  LCD_PrintStringXY((lcd_width - width)/2, lcd_height/2-1, _tr("Deviation\n   USB"));
  LCD_SetFontColor(0xffff);
}
