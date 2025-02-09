#ifndef __RGFW_DRAWING_H__
#define __RGFW_DRAWING_H__

#include "RGFW.h"


RGFW_area screenSize;

/* fill buffer with a color, clearing anything that was on it */
void clear(RGFW_window* win, u8 color[4]) {
  if (color[0] == color[1] && color[0] == color[2] && color[0] == color[3]) {
      memset(win->buffer, 0, screenSize.w * win->r.h * 4 * sizeof(u8));  
      return;
  }
  u32 x, y;
  for (y = 0; y < (u32)win->r.h; y++) {
      for (x = 0; x < screenSize.w; x++) {
          u32 index = (y * 4 * screenSize.w) + x * 4;
          
          /* copy the color to that pixel */
          memcpy(win->buffer + index, color, 4 * sizeof(u8));
      }
  }    
}


void drawRect(RGFW_window* win, RGFW_rect r, u8 color[4]) {
  for(int x = r.x; x < (r.x + r.w); x++) {
      for(int y = r.y; y < (r.y + r.h); y++) {
          int index = y * (4 * screenSize.w) + x * 4;      
          memcpy(win->buffer + index, color, 4 * sizeof(u8));
      }
  }
}


#endif