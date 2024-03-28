#ifndef TETRIS_H
#define TETRIS_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define HEIGHT 20
#define WIDTH 10
#define BASE_DELAY 1000
#define FULL_LINE 0b111111111111
#define EMPTY_LINE 0b100000000001
#define HIGH_SCORE_FILE "brick_game/tetris/high_score.txt"
#define LEFT 0404
#define RIGHT 0405
#define DOWN 0402
#define UP 0403

typedef struct tetris_figure {
  int shape[4];
  int size;
  int y;
  int x;
} figure;

typedef struct tetris {
  int field[HEIGHT + 1];
  figure curr_figure;
  figure next_figure;
  int score;
  int high_score;
  int delay;
  int level;
  long long time;
  int in_progress;
  int pause;
} GameInfo_t;

void timer_shift(GameInfo_t *game);
void make_user_action(GameInfo_t *game, int ch);
long long get_time();
int timer(long long *prev_time, int delay);
int collision(GameInfo_t game);
void shift_left(figure *fig);
void shift_right(figure *fig);
figure rotate(figure f);
void place_figure(GameInfo_t *game);
void delete_full_lines(GameInfo_t *game);
void delete_one_line(GameInfo_t *game, int line_number);
figure get_new_figure();

#endif