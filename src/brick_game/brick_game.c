// конечный автомат?
// управление

#include "../gui/cli/interface.h"
#include "tetris/tetris.h"

int main() {
  init_ncurses();
  GameInfo_t game = init_board();
  WINDOW *work_screen = init_work_screen();
  print_stats(game, work_screen);
  game.in_progress = start_game(work_screen);

  while (game.in_progress) {
    print_stats(game, work_screen);

    while (timer(&game.time, game.delay) && game.in_progress) {
      print_field(game, work_screen);
      int ch = wgetch(work_screen);
      make_user_action(&game, ch);

      if (game.pause) {
        game.in_progress = pause(work_screen);
        game.pause = 0;
      }
    }

    timer_shift(&game);
  }

  end_game(work_screen, game.high_score);

  return 0;
}
