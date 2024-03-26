#ifndef INTERFACE_H
#define INTERFACE_H

#include <ncurses.h>

#include "../../brick_game/tetris/tetris.h"

board init_board();
void init_ncurses();
WINDOW *init_work_screen();
void print_field(board game, WINDOW *work_screen);
void print_stats(board game, WINDOW *work_screen);
void end_game(WINDOW *work_screen, int high_score);

#endif