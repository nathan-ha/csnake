#define RGFW_IMPLEMENTATION
#define RGFW_BUFFER
#define RGFW_OPENGL

#include "RGFW.h"
#include "rgfw_drawing.h"
#include "game_logic.h"
#include <stdio.h>

extern u8 running;
extern u16 score;


int main(void) {
    RGFW_window* win = RGFW_createWindow("Snake by Nathan", RGFW_RECT(0, 0, GAME_WIDTH, GAME_HEIGHT), RGFW_windowCenter | RGFW_windowNoResize);
    RGFW_window_initBuffer(win);
    char windowTitle[128];
    
    screenSize = RGFW_getScreenSize();
    
    init_snake_game();

    while (running) { 
        get_inputs(win);
        
        clear(win, (u8[4]){0, 0, 0, 255});
        
        move_snake();
        draw_snake(win);
        drawRect(win, RGFW_RECT(0, 0, GAME_WIDTH, GAME_SCALE), (u8[4]){255, 255, 0, 255}); // draw top border -- there's a weird bug there that I can't fix, so I make it kill you if you touch it
        check_collisions();

        display_death_message(win, windowTitle);
        
        // update score
        snprintf(windowTitle, sizeof(windowTitle), "Snake by Nathan - Score: %d", score);
        RGFW_window_setName(win, windowTitle);
        
        RGFW_window_setGPURender(win, 0);
        RGFW_window_swapBuffers(win);
        RGFW_window_checkFPS(win, GAME_FPS);
    }

    RGFW_window_close(win);
}
