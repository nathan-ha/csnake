#ifndef __GAME_LOGIC_H__
#define __GAME_LOGIC_H__

#include "rgfw_drawing.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define GAME_FPS 8
#define GAME_WIDTH (size_t)600
#define GAME_HEIGHT (size_t)600
#define GAME_SCALE (size_t)40
#define SNAKE_MAX_LENGTH (size_t)(GAME_WIDTH*GAME_HEIGHT/GAME_SCALE/GAME_SCALE)

static u8 running = 1;

enum directions {UP, DOWN, LEFT, RIGHT, NEUTRAL};
struct point {
  i32 x;
  i32 y;
};


static u16 score = 0;
static size_t snake_length = 1;
static struct point snake[SNAKE_MAX_LENGTH];
static struct point apple;
static u8 snake_xdir = RIGHT;
static u8 snake_ydir = NEUTRAL;

int random_int(int min, int max) {
  return min + rand() % (max - min + 1);
}

void draw_snake(RGFW_window* win) {
  for (size_t i = 0; i < snake_length; i++) {
    drawRect(win, RGFW_RECT(snake[i].x, snake[i].y, GAME_SCALE, GAME_SCALE), (u8[4]){255, 255, 255, 255});
  }
  drawRect(win, RGFW_RECT(apple.x, apple.y, GAME_SCALE, GAME_SCALE), (u8[4]){255, 0, 0, 255});
}

void init_snake_game() {
  srand(time(NULL));  
  snake[0].x = (GAME_WIDTH / 2) / GAME_SCALE * GAME_SCALE;
  snake[0].y = (GAME_HEIGHT / 2) / GAME_SCALE * GAME_SCALE;
  
  apple.x = random_int(0, (GAME_WIDTH / GAME_SCALE) - 1) * GAME_SCALE;
  apple.y = random_int(1, (GAME_HEIGHT / GAME_SCALE) - 1) * GAME_SCALE;

  snake_length = 1;  
  snake_xdir = RIGHT;
  snake_ydir = NEUTRAL;
  score = 0;
  running = 1;
}

void get_inputs(RGFW_window* win) {
  while (RGFW_window_checkEvent(win)) {
    if (win->event.type == RGFW_quit || RGFW_isPressed(win, RGFW_escape)) {
      exit(0);
    }
    if (RGFW_isPressed(win, 'w') && snake_ydir != DOWN) {
      snake_xdir = NEUTRAL;
      snake_ydir = UP;
      break;
    } else if (RGFW_isPressed(win, 'a') && snake_xdir != RIGHT) {
      snake_xdir = LEFT;
      snake_ydir = NEUTRAL;
      break;
    } else if (RGFW_isPressed(win, 's') && snake_ydir != UP) {
      snake_xdir = NEUTRAL;
      snake_ydir = DOWN;
      break;
    } else if (RGFW_isPressed(win, 'd') && snake_xdir != LEFT) {
      snake_xdir = RIGHT;
      snake_ydir = NEUTRAL;
      break;
    }
  }
}

void move_snake() {
  // move body
  if (snake_length > 1) {
      for (size_t i = snake_length - 1; i > 0; i--) {
          snake[i] = snake[i - 1];
      }
  }
  // move head
  if (snake_xdir == LEFT) {
      snake[0].x -= GAME_SCALE;
  } else if (snake_xdir == RIGHT) {
      snake[0].x += GAME_SCALE;
  }
  if (snake_ydir == UP && snake[0].y > 1) {
      snake[0].y -= GAME_SCALE;
  } else if (snake_ydir == DOWN) {
      snake[0].y += GAME_SCALE;
  }
}


void check_collisions() {
  // wall collisions
  if (snake[0].x < 0 || snake[0].x >= GAME_WIDTH || snake[0].y < 1 || snake[0].y >= GAME_HEIGHT) {
    running = 0;
    return;
  }
  // apple collisions
  if (snake[0].x == apple.x && snake[0].y == apple.y) {
    // make sure apple doesn't spawn on snake
    for (size_t i = 0; i < snake_length; i++) {
      if (apple.x == snake[i].x && apple.y == snake[i].y) {
        apple.x = random_int(0, (GAME_WIDTH / GAME_SCALE) - 1) * GAME_SCALE;
        apple.y = random_int(1, (GAME_HEIGHT / GAME_SCALE) - 1) * GAME_SCALE;

        i = 0;
      }
    }
    score++;
    snake_length++;
  }

  // self collisions
  for (size_t i = 1; i < snake_length; i++) {
    if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
      running = 0;
      return;
    }
  }
  
}

#endif