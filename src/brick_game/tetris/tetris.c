// конечный автомат?
// pause
// start game
// test
// makefile
// dvi
// dist

#include "tetris.h"

void timer_shift(board *game) {
  game->curr_figure.y++;

  if (collision(*game)) {
    game->curr_figure.y--;
    place_figure(game);
    delete_full_lines(game);
  }
}

void make_user_action(board *game, int ch) {
  if (ch == KEY_LEFT) {
    shift_left(&game->curr_figure);
    if (collision(*game)) shift_right(&game->curr_figure);

  } else if (ch == KEY_RIGHT) {
    shift_right(&game->curr_figure);
    if (collision(*game)) shift_left(&game->curr_figure);

  } else if (ch == KEY_DOWN) {
    game->curr_figure.y++;
    if (collision(*game)) game->curr_figure.y--;

  } else if (ch == KEY_UP) {
    board temp = *game;
    temp.curr_figure = rotate(game->curr_figure);
    if (!collision(temp)) game->curr_figure = temp.curr_figure;

  } else if (ch == 'q' || ch == 'Q' || ch == 185 || ch == 153) {  // йЙ
    game->in_progress = 0;

  } else if (ch == ' ') {
    while (!collision(*game)) {
      game->curr_figure.y++;
    }
    game->curr_figure.y--;
  }
}

int collision(board game) {
  int result = 0;

  for (int i = 0, j = game.curr_figure.y; i < 4; i++, j++) {
    if (game.field[j] & game.curr_figure.shape[i]) {
      result = 1;
    }
  }

  return result;
}

void shift_left(figure *fig) {
  for (int i = 0; i < 4; i++) {
    fig->shape[i] <<= 1;
  }

  ++fig->x;
}

void shift_right(figure *fig) {
  for (int i = 0; i < 4; i++) {
    fig->shape[i] >>= 1;
  }

  --fig->x;
}

figure rotate(figure f) {
  figure temp = f;

  if (f.size == 3) {
    for (int i = 0; i < 3; i++) {
      int bit = 1 << (f.x + i);

      temp.shape[i] = ((f.shape[0] & bit) << 2 | (f.shape[1] & bit) << 1 |
                       (f.shape[2] & bit));

      temp.shape[i] >>= i;
    }

  } else if (f.size == 4 && f.x > 0) {
    if (f.shape[0]) {
      temp.shape[0] = 0;
      temp.shape[1] = 0;
      temp.shape[2] = 15 << f.x;
      temp.shape[3] = 0;

    } else {
      int bit = 1 << (f.x + 2);
      for (int i = 0; i < 4; i++) {
        temp.shape[i] = bit;
      }
    }
  }

  return temp;
}

long long get_time() {
  struct timeval t;
  gettimeofday(&t, NULL);
  long long time = (long long)t.tv_sec * 1000;
  time += t.tv_usec / 1000;

  return time;
}

int timer(long long *prev_time, int delay) {
  int result = 1;
  long long int time = get_time();

  if (time - *prev_time >= delay) {
    *prev_time = time;
    result = 0;
  }

  return result;
}

void place_figure(board *game) {
  for (int i = 0; i < 4; i++) {
    int line = game->curr_figure.y;
    game->field[line + i] |= game->curr_figure.shape[i];
  }

  game->curr_figure = game->next_figure;
  game->next_figure = get_new_figure();
  if (collision(*game)) {
    game->in_progress = 0;
  }
}

void delete_full_lines(board *game) {
  int count = 0;

  for (int i = 0; i < HEIGHT; i++) {
    if (game->field[i] == FULL_LINE) {
      delete_one_line(game, i);
      count++;
    }
  }

  if (count == 1) {
    game->score += 100;
  } else if (count == 2) {
    game->score += 300;
  } else if (count == 3) {
    game->score += 700;
  } else if (count == 4) {
    game->score += 1500;
  }

  if (game->score > game->high_score) {
    game->high_score = game->score;
  }

  int level = game->score / 600;
  game->level = (level > 9) ? 9 : level;
  game->delay = BASE_DELAY / pow(1.25, game->level);
  timeout(game->delay);
}

void delete_one_line(board *game, int line_number) {
  for (int i = line_number; i > 0; i--) {
    game->field[i] = game->field[i - 1];
  }

  game->field[0] = EMPTY_LINE;
}

figure get_new_figure() {
  int fig_num = rand() % 7;
  figure fig = {0};

  if (fig_num == 0) {
    fig.size = 2;
    fig.x = 5;
    fig.shape[0] = 0b11 << fig.x;
    fig.shape[1] = 0b11 << fig.x;

  } else if (fig_num == 1) {
    fig.size = 3;
    fig.x = 4;
    fig.shape[0] = 0b100 << fig.x;
    fig.shape[1] = 0b111 << fig.x;

  } else if (fig_num == 2) {
    fig.size = 3;
    fig.x = 4;
    fig.shape[0] = 0b010 << fig.x;
    fig.shape[1] = 0b111 << fig.x;

  } else if (fig_num == 3) {
    fig.size = 3;
    fig.x = 4;
    fig.shape[0] = 0b001 << fig.x;
    fig.shape[1] = 0b111 << fig.x;

  } else if (fig_num == 4) {
    fig.size = 3;
    fig.x = 4;
    fig.shape[0] = 0b110 << fig.x;
    fig.shape[1] = 0b011 << fig.x;

  } else if (fig_num == 5) {
    fig.size = 3;
    fig.x = 4;
    fig.shape[0] = 0b011 << fig.x;
    fig.shape[1] = 0b110 << fig.x;

  } else if (fig_num == 6) {
    fig.size = 4;
    fig.x = 3;
    fig.shape[0] = 0b100 << fig.x;
    fig.shape[1] = 0b100 << fig.x;
    fig.shape[2] = 0b100 << fig.x;
    fig.shape[3] = 0b100 << fig.x;
  }

  return fig;
}