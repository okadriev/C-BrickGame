#ifndef TETRIS_H
#define TETRIS_H

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>


#define HEIGHT 20
#define WIDTH 10
#define BASE_DELAY 1000
#define FULL_LINE 0b111111111111
#define EMPTY_LINE 0b100000000001

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

void timer_shift(board *game);
void init_ncurses();
board init_board();
WINDOW *init_work_screen();
void make_user_action(board *game, WINDOW *work_screen);
long long get_time();
int timer(long long *prev_time, int delay);
int collision(board game);
void shift_left(figure *fig);
void shift_right(figure *fig);
figure rotate(figure f);
void print_field(board game, WINDOW *work_screen);
void print_stats(board game, WINDOW *work_screen);
void place_figure(board *game);
void delete_full_lines(board *game);
void delete_one_line(board *game, int line_number);
figure get_new_figure();

#endif