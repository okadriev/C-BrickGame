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

typedef struct tetris_figure {
  int shape[4];
  int size;
  int y;
  int x;
} figure;

typedef struct tetris_board {
  int field[HEIGHT + 1];
  figure curr_figure;
  figure next_figure;
  int score;
  int high_score;
  int delay;
  int level;
  long long time;
  int in_progress;
} board;

#include "../../gui/cli/interface.h"

void timer_shift(board *game);
void make_user_action(board *game, int ch);
long long get_time();
int timer(long long *prev_time, int delay);
int collision(board game);
void shift_left(figure *fig);
void shift_right(figure *fig);
figure rotate(figure f);
void place_figure(board *game);
void delete_full_lines(board *game);
void delete_one_line(board *game, int line_number);
figure get_new_figure();

#endif