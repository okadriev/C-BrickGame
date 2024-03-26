CFLAGS = -Wall -Wextra -Werror -std=c11 -g
VLGRND = valgrind --tool=memcheck --leak-check=yes --show-leak-kinds=all --track-origins=yes -s

all: clear install

install: clear clean
	@gcc $(CFLAGS) -c brick_game/tetris/tetris.c -o tetris.o -lm
	@ar rcs tetris.a tetris.o
	@ranlib tetris.a
	@gcc $(CFLAGS) brick_game/brick_game.c gui/cli/interface.c -o tetris -L. -l:tetris.a -lncurses -lm
	@rm -rf *.o

uninstall:
	@rm -rf tetris tetris.a brick_game/tetris/high_score.txt

dvi:
	@xelatex -output-directory=build build/documentation.tex

dist: install
	@tar -czvf $(DIST_NAME)  Makefile brick_game gui test

run:
	@./tetris

clean:
	@rm -rf *.o

clear:
	@clear

# all: 
# 	@clear
# 	@gcc $(CFLAGS) brick_game/tetris/tetris.c gui/cli/interface.c -lncurses -lm 
# 	@./a.out
# 	@-rm ./a.out