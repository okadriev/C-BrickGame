#ifndef INTERFACE_H
#define INTERFACE_H

#include <ncurses.h>

#include "../../brick_game/tetris/tetris.h"

GameInfo_t init_board();
void init_ncurses();
WINDOW *init_work_screen();
int start_game(WINDOW *work_screen);
int pause(WINDOW *work_screen);
void print_field(GameInfo_t game, WINDOW *work_screen);
void print_stats(GameInfo_t game, WINDOW *work_screen);
void end_game(WINDOW *work_screen, int high_score);

#endif