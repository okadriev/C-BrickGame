SHELL = /bin/bash
CFLAGS = -Wall -Wextra -Werror -std=c11 -g
VLGRND = valgrind --tool=memcheck --leak-check=yes --show-leak-kinds=all --track-origins=yes -s
TFLAGS = -lcheck -lsubunit -lm
GFLAGS = -fprofile-arcs -ftest-coverage

all: clear install run

install: clear clean
	@gcc $(CFLAGS) -c brick_game/tetris/tetris.c -o tetris.o -lm
	@ar rcs tetris.a tetris.o
	@ranlib tetris.a
	@gcc $(CFLAGS) brick_game/brick_game.c gui/cli/interface.c -o tetris -L. -l:tetris.a -lncurses -lm
	@rm -rf *.o

uninstall:
	@rm -rf *.o tetris tetris.a brick_game/tetris/high_score.txt coverage_report

clean:
	@rm -rf *.o tetris.a coverage_report build/*.gz build/*.aux build/*n.log build/*.out build/*.pdf

dvi:
	@xelatex -output-directory=build build/documentation.tex

dist: install
	@tar -czvf build/brick_game.tar.gz Makefile brick_game gui

test: install
	@gcc $(CFLAGS) -c brick_game/tetris/test.c
	@gcc $(CFLAGS) test.o -o test.out -L. -l:tetris.a $(TFLAGS)
#	@./test.out
	@$(VLGRND) ./test.out
	@rm -rf *.o test.out

gcov_report: clear clean
	@gcc $(CFLAGS) -c brick_game/tetris/tetris.c $(GFLAGS) -lm
	@ar rcs tetris.a tetris.o
	@ranlib tetris.a 
	@gcc $(CFLAGS) -o gcov_r $(GFLAGS) brick_game/tetris/test.c -L. -l:tetris.a $(TFLAGS)
	@mkdir -p coverage_report
	@./gcov_r
	@gcovr -r . --html --html-details -o coverage_report/index.html --exclude '.*test.*'
	@rm -rf *.o *.gcno *.gcda *.gcov gcov_r

run:
	@./tetris

clear:
	@clear

# установка enumitem: sudo apt-get install texlive-latex-extra
# установка gcovr: sudo apt install gcovr
# установка ncurses: sudo apt-get install libncurses5-dev libncursesw5-dev
# установка xelatex: sudo apt-get install texlive-latex-extra (если не работает прописать в маке абсолютный путь)