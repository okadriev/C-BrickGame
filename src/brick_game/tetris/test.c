#include <check.h>

#include "tetris.h"

void paint_tyan();
GameInfo_t init_game();
void eq_game_state(GameInfo_t game, GameInfo_t game_2);

START_TEST(timer_shift_1) {
  GameInfo_t game = init_game();
  GameInfo_t game_2 = init_game();

  game.curr_figure.size = 2;
  game.curr_figure.y = 19;
  game.curr_figure.x = 5;
  game.curr_figure.shape[0] = 0b11 << 5;
  game.curr_figure.shape[1] = 0b11 << 5;

  game.next_figure = get_new_figure();
  game_2.curr_figure = game.next_figure;
  game_2.field[19] |= 0b11 << 5;
  game_2.field[20] |= 0b11 << 5;

  timer_shift(&game);
  eq_game_state(game, game_2);
}
END_TEST

int main() {
  Suite *s1 = suite_create("Core");
  TCase *tc_core = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  suite_add_tcase(s1, tc_core);

  tcase_add_test(tc_core, timer_shift_1);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  srunner_free(sr);

  // paint_tyan();

  return 0;
}

GameInfo_t init_game() {
  GameInfo_t game = {0};
  game.delay = BASE_DELAY;
  game.curr_figure = get_new_figure();
  game.next_figure = get_new_figure();
  game.time = get_time();

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

void eq_game_state(GameInfo_t game, GameInfo_t game_2) {
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(game.curr_figure.shape[i], game_2.curr_figure.shape[i]);
  }
  ck_assert_int_eq(game.curr_figure.size, game_2.curr_figure.size);
  ck_assert_int_eq(game.curr_figure.x, game_2.curr_figure.x);
  ck_assert_int_eq(game.curr_figure.y, game_2.curr_figure.y);

  for (int i = 0; i < HEIGHT; i++) {
    ck_assert_int_eq(game.field[i], game_2.field[i]);
  }

  ck_assert_int_eq(game.delay, game_2.delay);
  ck_assert_int_eq(game.high_score, game_2.high_score);
  ck_assert_int_eq(game.in_progress, game_2.in_progress);
  ck_assert_int_eq(game.level, game_2.level);
  ck_assert_int_eq(game.pause, game_2.pause);
  ck_assert_int_eq(game.score, game_2.score);
}

void paint_tyan() {
  printf("\033[48;5;93m\033[1;37m  ⠀⠀⠀⠀⠀⣀⡀⠀⠀⠀⠀⠀⡠⢴⣴⣾⣿⡿⠓⡠⠀⠀⠀⠀⠠⢄⠁⢀\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠀⠀⠀⠳⣽⡽⠀⠀⡠⢊⣴⣿⣿⣿⣡⠖⠁⣀⡤⢖⠟⠁⡠⠀⡙⢿⣷⣄\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠐⡀⠀⠀⠀⠀⢠⣾⣿⣿⢽⣿⣿⣿⣥⠖⣻⣯⡾⠃⠀⡔⡀⠀⣷⢸⢿⣿\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠀⢰⠀⠀⠀⢠⢟⣿⠃⢀⣾⣿⠟⠋⢀⡾⢋⣾⠃⣠⡾⢰⡇⡇⣿⣿⡞⣿\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⡤⣈⡀⠀⢀⠏⣼⣧⡴⣼⠟⠁⠀⠀⡾⠁⣾⡇⣰⢿⠃⢾⣿⣷⣿⣿⣇⢿\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠱⠼⠊⠀⠄⡜⣿⣿⡿⠃⠈⠁⠀⢸⠁⢠⡿⣰⢯⠃⠀⠘⣿⣿⣿⣿⣿⠸\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠀⠀⠀⠀⡘⡀⣸⣿⣱⡤⢴⣄⠀⠈⠀⠘⣷⠏⠌⠢⡀⠀⢿⣿⣿⣿⡟⡄\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠀⠀⢀⣌⠌⣴⣿⣿⠃⣴⣿⣟⡇⠀⠀⠀⠟⠀⠀⠀⠈⠢⢈⣿⡟⣿⡗⡇\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⢀⡴⡻⣡⣾⠟⢹⡇⠀⡇⢄⢿⠇⠀⠀⠀⠀⠀⠀⣽⣶⣄⡀⠘⢷⡹⣿⣿\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⣧⣾⡿⠋⠁⢀⡜⠙⡄⠓⠐⠁⠀⠀⠀⠀⠀⠀⡼⠛⠻⣟⠛⣆⠈⢷⣿⣿\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⣴⣾⣟⣵⣿⣿⣿⣁⢇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡧⠠⠔⡹⠀⢸⠀⣼⣿⣿\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠿⡽⢫⡉⠀⣠⠔⠁⡀⠕⠠⡀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠖⠊⠀⠀⢊⣾⢿⡿⠉\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠁⠀⡹⢨⠁⠐⠈⢀⡠⠐⠁⠄⠡⡀⡀⠀⠀⠀⠀⠀⠀⠀⠠⠶⢛⡨⠊⠀⠀\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⡜⠀⠈⣂⠀⠀⠀⠀⡠⠐⠉⡆⠀⣀⢀⣀⣀⣀⡀⠀⠀⣀⠴⣁⡀⠤⠀⠀\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠈⠀⠀⠀⡇⠑⢄⠀⠀⠀⠀⣲⢥⡎⠀⢰⠀⢸⠀⢀⠉⠙⣿⣧⣀⣀⣂⣤⣼\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠀⠆⠁⠃⠀⠀⠈⠒⠒⠊⣸⠚⠁⠀⠀⠀⠀⠀⠀⠀⡜⠁⠀⠀⠀⠀⠈⠚\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠀⠀⠀⠂⠀⠀⠀⠀⠀⢀⠋⢆⠀⠀⠀⠀⠀⠀⠀⡘⠀⠀⠀⠀⠀⠀⠀⠀\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠒⠂⠀⠀⠐⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀\033[0m\n");

  printf("\033[42m\033[1;37m   YOU'RE AWESOME!  \\(^.^)/   \033[0m\n");
}