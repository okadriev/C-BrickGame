#include <check.h>

#include "tetris.h"

void paint_tyan();
GameInfo_t init_game();
void eq_game_state(GameInfo_t game, GameInfo_t game_2);

START_TEST(timer_shift_1) {
  GameInfo_t game = init_game();

  game.curr_figure.size = 2;
  game.curr_figure.x = 5;
  game.curr_figure.shape[0] = 0b11 << game.curr_figure.x;
  game.curr_figure.shape[1] = 0b11 << game.curr_figure.x;
  game.curr_figure.shape[2] = 0;
  game.curr_figure.shape[3] = 0;

  GameInfo_t game_2 = game;
  game_2.curr_figure.y++;

  timer_shift(&game);
  eq_game_state(game, game_2);
}
END_TEST

START_TEST(timer_shift_2) {
  GameInfo_t game = init_game();

  game.curr_figure.size = 2;
  game.curr_figure.y = 19;
  game.curr_figure.x = 5;
  game.curr_figure.shape[0] = 0b11 << game.curr_figure.x;
  game.curr_figure.shape[1] = 0b11 << game.curr_figure.x;
  game.curr_figure.shape[2] = 0;
  game.curr_figure.shape[3] = 0;

  GameInfo_t game_2 = game;
  game_2.curr_figure = game.next_figure;
  game_2.field[19] |= game.curr_figure.shape[0];
  game_2.field[20] |= game.curr_figure.shape[1];

  timer_shift(&game);
  eq_game_state(game, game_2);
}
END_TEST

START_TEST(make_user_action_1) {
  GameInfo_t game = init_game();

  game.curr_figure.size = 4;
  game.curr_figure.x = 5;
  game.curr_figure.shape[0] = 0b100 << game.curr_figure.x;
  game.curr_figure.shape[1] = 0b100 << game.curr_figure.x;
  game.curr_figure.shape[2] = 0b100 << game.curr_figure.x;
  game.curr_figure.shape[3] = 0b100 << game.curr_figure.x;

  GameInfo_t game_2 = game;
  game_2.curr_figure.shape[0] = 0;
  game_2.curr_figure.shape[1] = 0;
  game_2.curr_figure.shape[2] = 0b1111 << 5;
  game_2.curr_figure.shape[3] = 0;

  make_user_action(&game, 'w');
  eq_game_state(game, game_2);
}
END_TEST

START_TEST(make_user_action_2) {
  GameInfo_t game = init_game();

  game.curr_figure.size = 4;
  game.curr_figure.x = 0;
  game.curr_figure.shape[0] = 0;
  game.curr_figure.shape[1] = 0;
  game.curr_figure.shape[2] = 0b1111 << game.curr_figure.x;
  game.curr_figure.shape[3] = 0;

  GameInfo_t game_2 = game;

  make_user_action(&game, 'w');
  eq_game_state(game, game_2);
}
END_TEST

START_TEST(make_user_action_3) {
  GameInfo_t game = init_game();

  game.curr_figure.size = 2;
  game.curr_figure.x = 5;
  game.curr_figure.shape[0] = 0b11 << game.curr_figure.x;
  game.curr_figure.shape[1] = 0b11 << game.curr_figure.x;
  game.curr_figure.shape[2] = 0;
  game.curr_figure.shape[3] = 0;

  GameInfo_t game_2 = game;
  game_2.curr_figure.x++;
  for (int i = 0; i < 4; i++) {
    game_2.curr_figure.shape[i] <<= 1;
  }

  make_user_action(&game, 'a');
  eq_game_state(game, game_2);
}
END_TEST

START_TEST(make_user_action_4) {
  GameInfo_t game = init_game();

  game.curr_figure.size = 2;
  game.curr_figure.x = 9;
  game.curr_figure.shape[0] = 0b11 << game.curr_figure.x;
  game.curr_figure.shape[1] = 0b11 << game.curr_figure.x;
  game.curr_figure.shape[2] = 0;
  game.curr_figure.shape[3] = 0;

  GameInfo_t game_2 = game;

  make_user_action(&game, 'a');
  eq_game_state(game, game_2);
}
END_TEST

START_TEST(make_user_action_5) {
  GameInfo_t game = init_game();

  game.curr_figure.size = 2;
  game.curr_figure.x = 5;
  game.curr_figure.shape[0] = 0b11 << game.curr_figure.x;
  game.curr_figure.shape[1] = 0b11 << game.curr_figure.x;
  game.curr_figure.shape[2] = 0;
  game.curr_figure.shape[3] = 0;

  GameInfo_t game_2 = game;
  game_2.curr_figure.y++;

  make_user_action(&game, 's');
  eq_game_state(game, game_2);
}
END_TEST

START_TEST(make_user_action_6) {
  GameInfo_t game = init_game();

  game.curr_figure.size = 2;
  game.curr_figure.y = 19;
  game.curr_figure.x = 5;
  game.curr_figure.shape[0] = 0b11 << game.curr_figure.x;
  game.curr_figure.shape[1] = 0b11 << game.curr_figure.x;
  game.curr_figure.shape[2] = 0;
  game.curr_figure.shape[3] = 0;

  GameInfo_t game_2 = game;

  make_user_action(&game, 's');
  eq_game_state(game, game_2);
}
END_TEST

START_TEST(make_user_action_7) {
  GameInfo_t game = init_game();

  game.curr_figure.size = 2;
  game.curr_figure.x = 5;
  game.curr_figure.shape[0] = 0b11 << game.curr_figure.x;
  game.curr_figure.shape[1] = 0b11 << game.curr_figure.x;
  game.curr_figure.shape[2] = 0;
  game.curr_figure.shape[3] = 0;

  GameInfo_t game_2 = game;
  game_2.curr_figure.x--;
  for (int i = 0; i < 4; i++) {
    game_2.curr_figure.shape[i] >>= 1;
  }

  make_user_action(&game, 'd');
  eq_game_state(game, game_2);
}
END_TEST

START_TEST(make_user_action_8) {
  GameInfo_t game = init_game();

  game.curr_figure.size = 2;
  game.curr_figure.x = 1;
  game.curr_figure.shape[0] = 0b11 << game.curr_figure.x;
  game.curr_figure.shape[1] = 0b11 << game.curr_figure.x;
  game.curr_figure.shape[2] = 0;
  game.curr_figure.shape[3] = 0;

  GameInfo_t game_2 = game;

  make_user_action(&game, 'd');
  eq_game_state(game, game_2);
}
END_TEST

START_TEST(make_user_action_9) {
  GameInfo_t game = init_game();
  GameInfo_t game_2 = game;

  game_2.in_progress = 0;

  make_user_action(&game, 'q');
  eq_game_state(game, game_2);
}
END_TEST

START_TEST(make_user_action_10) {
  GameInfo_t game = init_game();
  GameInfo_t game_2 = game;

  game_2.pause = 1;

  make_user_action(&game, 'p');
  eq_game_state(game, game_2);
}
END_TEST

START_TEST(make_user_action_11) {
  GameInfo_t game = init_game();

  game.curr_figure.size = 2;
  game.curr_figure.x = 5;
  game.curr_figure.shape[0] = 0b11 << game.curr_figure.x;
  game.curr_figure.shape[1] = 0b11 << game.curr_figure.x;
  game.curr_figure.shape[2] = 0;
  game.curr_figure.shape[3] = 0;

  GameInfo_t game_2 = game;
  game_2.curr_figure.y = 18;

  make_user_action(&game, ' ');
  eq_game_state(game, game_2);
}
END_TEST

START_TEST(make_user_action_12) {
  GameInfo_t game = init_game();

  game.curr_figure.size = 2;
  game.curr_figure.x = 5;
  game.curr_figure.y = 18;
  game.curr_figure.shape[0] = 0b11 << game.curr_figure.x;
  game.curr_figure.shape[1] = 0b11 << game.curr_figure.x;
  game.curr_figure.shape[2] = 0;
  game.curr_figure.shape[3] = 0;

  GameInfo_t game_2 = game;

  make_user_action(&game, ' ');
  eq_game_state(game, game_2);
}
END_TEST

START_TEST(make_user_action_13) {
  GameInfo_t game = init_game();

  game.curr_figure.size = 2;
  game.curr_figure.x = 5;
  game.curr_figure.y = 18;
  game.curr_figure.shape[0] = 0b11 << game.curr_figure.x;
  game.curr_figure.shape[1] = 0b11 << game.curr_figure.x;
  game.curr_figure.shape[2] = 0;
  game.curr_figure.shape[3] = 0;

  GameInfo_t game_2 = game;

  make_user_action(&game, 'z');
  eq_game_state(game, game_2);
}
END_TEST

START_TEST(rotate_1) {
  GameInfo_t game = init_game();

  game.curr_figure.size = 4;
  game.curr_figure.x = 5;
  game.curr_figure.shape[0] = 0;
  game.curr_figure.shape[1] = 0;
  game.curr_figure.shape[2] = 0b1111 << game.curr_figure.x;
  game.curr_figure.shape[3] = 0;

  GameInfo_t game_2 = game;
  game_2.curr_figure.shape[0] = 0b0100 << 5;
  game_2.curr_figure.shape[1] = 0b0100 << 5;
  game_2.curr_figure.shape[2] = 0b0100 << 5;
  game_2.curr_figure.shape[3] = 0b0100 << 5;

  game.curr_figure = rotate(game.curr_figure);
  eq_game_state(game, game_2);
}
END_TEST

START_TEST(rotate_2) {
  GameInfo_t game = init_game();

  game.curr_figure.size = 2;
  game.curr_figure.x = 5;
  game.curr_figure.shape[0] = 0b0011 << game.curr_figure.x;
  game.curr_figure.shape[1] = 0b0011 << game.curr_figure.x;
  game.curr_figure.shape[2] = 0;
  game.curr_figure.shape[3] = 0;

  GameInfo_t game_2 = game;

  game.curr_figure = rotate(game.curr_figure);
  eq_game_state(game, game_2);
}
END_TEST

START_TEST(rotate_3) {
  GameInfo_t game = init_game();

  game.curr_figure.size = 3;
  game.curr_figure.x = 5;
  game.curr_figure.shape[0] = 0b0010 << game.curr_figure.x;
  game.curr_figure.shape[1] = 0b0011 << game.curr_figure.x;
  game.curr_figure.shape[2] = 0b0010 << game.curr_figure.x;
  game.curr_figure.shape[3] = 0;

  GameInfo_t game_2 = game;
  game_2.curr_figure.shape[1] = 0b0111 << 5;
  game_2.curr_figure.shape[2] = 0;

  game.curr_figure = rotate(game.curr_figure);
  eq_game_state(game, game_2);
}
END_TEST

START_TEST(place_figure_1) {
  GameInfo_t game = init_game();
  make_user_action(&game, 's');

  GameInfo_t game_2 = game;
  game_2.curr_figure = game.next_figure;
  for (int i = 0; i < 4; i++) {
    game_2.field[i + game.curr_figure.y] |= game.curr_figure.shape[i];
  }
  game_2.in_progress = 0;

  place_figure(&game);
  eq_game_state(game, game_2);
}
END_TEST

START_TEST(place_figure_2) {
  GameInfo_t game = init_game();

  GameInfo_t game_2 = game;
  game_2.curr_figure = game.next_figure;
  for (int i = 0; i < 4; i++) {
    game_2.field[i] |= game.curr_figure.shape[i];
  }
  game_2.in_progress = 0;

  place_figure(&game);
  eq_game_state(game, game_2);
}
END_TEST

START_TEST(delete_full_lines_1) {
  GameInfo_t game = init_game();

  GameInfo_t game_2 = game;
  game_2.score = 100;
  game_2.high_score = 100;

  game.field[19] = 0b111111111111;

  delete_full_lines(&game);
  eq_game_state(game, game_2);
}
END_TEST

START_TEST(delete_full_lines_2) {
  GameInfo_t game = init_game();

  GameInfo_t game_2 = game;
  game_2.score = 300;
  game_2.high_score = 300;

  game.field[18] = 0b111111111111;
  game.field[19] = 0b111111111111;

  delete_full_lines(&game);
  eq_game_state(game, game_2);
}
END_TEST

START_TEST(delete_full_lines_3) {
  GameInfo_t game = init_game();

  GameInfo_t game_2 = game;
  game_2.score = 700;
  game_2.high_score = 700;
  game_2.level = 1;
  game_2.delay = BASE_DELAY / (1.25);

  game.field[17] = 0b111111111111;
  game.field[18] = 0b111111111111;
  game.field[19] = 0b111111111111;

  delete_full_lines(&game);
  eq_game_state(game, game_2);
}
END_TEST

START_TEST(delete_full_lines_4) {
  GameInfo_t game = init_game();

  GameInfo_t game_2 = game;
  game_2.score = 1500;
  game_2.high_score = 1500;
  game_2.level = 2;
  game_2.delay = BASE_DELAY / (1.25 * 1.25);

  game.field[16] = 0b111111111111;
  game.field[17] = 0b111111111111;
  game.field[18] = 0b111111111111;
  game.field[19] = 0b111111111111;

  delete_full_lines(&game);
  eq_game_state(game, game_2);
}
END_TEST

int main() {
  Suite *s1 = suite_create("Core");
  TCase *tc_core = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  suite_add_tcase(s1, tc_core);

  tcase_add_test(tc_core, timer_shift_1);
  tcase_add_test(tc_core, timer_shift_2);

  tcase_add_test(tc_core, make_user_action_1);
  tcase_add_test(tc_core, make_user_action_2);
  tcase_add_test(tc_core, make_user_action_3);
  tcase_add_test(tc_core, make_user_action_4);
  tcase_add_test(tc_core, make_user_action_5);
  tcase_add_test(tc_core, make_user_action_6);
  tcase_add_test(tc_core, make_user_action_7);
  tcase_add_test(tc_core, make_user_action_8);
  tcase_add_test(tc_core, make_user_action_9);
  tcase_add_test(tc_core, make_user_action_10);
  tcase_add_test(tc_core, make_user_action_11);
  tcase_add_test(tc_core, make_user_action_12);
  tcase_add_test(tc_core, make_user_action_13);

  tcase_add_test(tc_core, rotate_1);
  tcase_add_test(tc_core, rotate_2);
  tcase_add_test(tc_core, rotate_3);

  tcase_add_test(tc_core, place_figure_1);
  tcase_add_test(tc_core, place_figure_2);

  tcase_add_test(tc_core, delete_full_lines_1);
  tcase_add_test(tc_core, delete_full_lines_2);
  tcase_add_test(tc_core, delete_full_lines_3);
  tcase_add_test(tc_core, delete_full_lines_4);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  srunner_free(sr);

  paint_tyan();

  return 0;
}

GameInfo_t init_game() {
  GameInfo_t game = {0};
  game.delay = BASE_DELAY;
  game.curr_figure = get_new_figure();
  game.next_figure = get_new_figure();
  game.in_progress = 1;
  game.pause = 0;

  for (int i = 0; i < HEIGHT; i++) {
    game.field[i] = EMPTY_LINE;
  }
  game.field[HEIGHT] = FULL_LINE;

  return game;
}

void eq_game_state(GameInfo_t game, GameInfo_t game_2) {
  ck_assert_int_eq(game.curr_figure.shape[0], game_2.curr_figure.shape[0]);
  ck_assert_int_eq(game.curr_figure.shape[1], game_2.curr_figure.shape[1]);
  ck_assert_int_eq(game.curr_figure.shape[2], game_2.curr_figure.shape[2]);
  ck_assert_int_eq(game.curr_figure.shape[3], game_2.curr_figure.shape[3]);

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