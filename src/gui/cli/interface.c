#include "interface.h"

board init_board() {
  board game = {0};
  game.delay = BASE_DELAY;
  timeout(game.delay);
  game.curr_figure = get_new_figure();
  game.next_figure = get_new_figure();
  game.time = get_time();
  game.in_progress = 1;

  for (int i = 0; i < HEIGHT; i++) {
    game.field[i] = EMPTY_LINE;
  }
  game.field[HEIGHT] = FULL_LINE;

  FILE *f = fopen(HIGH_SCORE_FILE, "r");
  if (f) {
    fscanf(f, "%d", &game.high_score);
    fclose(f);
  }

  return game;
}

void init_ncurses() {
  srand(time(NULL));
  initscr();
  cbreak();
  noecho();
  curs_set(FALSE);
  start_color();
  init_pair(1, COLOR_YELLOW, COLOR_YELLOW);
}

WINDOW *init_work_screen() {
  WINDOW *work_screen = newwin(42, 72, 0, 0);
  keypad(work_screen, TRUE);
  nodelay(work_screen, TRUE);

  box(work_screen, 0, 0);
  for (int i = 1; i < 42; i++) {
    mvwprintw(work_screen, i, 41, "|");
  }

  mvwprintw(work_screen, 2, 45, "NEXT FIGURE");
  mvwprintw(work_screen, 14, 45, "LEVEL");
  mvwprintw(work_screen, 17, 45, "SCORE");
  mvwprintw(work_screen, 20, 45, "HIGH SCORE");

  return work_screen;
}

void print_field(board game, WINDOW *work_screen) {
  for (int i = 0; i < 4; i++) {
    game.field[i + game.curr_figure.y] |= game.curr_figure.shape[i];
  }

  for (int i = 0; i < HEIGHT; i++) {
    int bit = 1 << WIDTH;
    int line = i * 2 + 1;

    for (int j = 1; bit > 1; j += 4, bit >>= 1) {
      if (game.field[i] & bit) wattron(work_screen, COLOR_PAIR(1));
      mvwprintw(work_screen, line, j, "   .");
      mvwprintw(work_screen, line + 1, j, "   .");
      if (game.field[i] & bit) wattroff(work_screen, COLOR_PAIR(1));
    }
  }

  wrefresh(work_screen);
}

void print_stats(board game, WINDOW *work_screen) {
  box(work_screen, 0, 0);

  for (int i = 0; i < 4; i++) {
    int bit = 1 << (game.next_figure.x + game.next_figure.size - 1);
    int line = i * 2 + 4;

    for (int j = 0; j < 16; j += 4, bit >>= 1) {
      if (game.next_figure.shape[i] & bit) wattron(work_screen, COLOR_PAIR(1));
      mvwprintw(work_screen, line, j + 45, "    ");
      mvwprintw(work_screen, line + 1, j + 45, "    ");
      if (game.next_figure.shape[i] & bit) wattroff(work_screen, COLOR_PAIR(1));
    }
  }

  mvwprintw(work_screen, 14, 55, "%10d", game.level);
  mvwprintw(work_screen, 17, 55, "%10d", game.score);
  mvwprintw(work_screen, 20, 55, "%10d", game.high_score);

  wrefresh(work_screen);
}

void end_game(WINDOW *work_screen, int high_score) {
  endwin();
  delwin(work_screen);

  FILE *f = fopen(HIGH_SCORE_FILE, "w");
  if (f) {
    fprintf(f, "%d", high_score);
    fclose(f);
  }
}