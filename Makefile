CC=gcc -fsanitize=address
PKGCONFIG = $(shell pkg-config --cflags --libs check)
CFLAGS=gcc -Wall -Wextra -Werror 
FILES = s21_viewer_func/*.c
OUT=exec
TESTFILES= tests/*.c 
GCOV_FLAGS=-fprofile-arcs -ftest-coverage
CHECKFLAGS=-lcheck 

all: install

s21_viewer.a:
	$(CFLAGS) -c $(FILES)
	ar -rc s21_viewer.a *.o
	rm -rf *.o

tests: test gcov_report

gcov_report:
	$(CC) -o exec $(GCOV_FLAGS) $(FILES) $(TESTFILES) $(PKGCONFIG)
	./$(OUT)
	lcov -capture --directory . --output-file main_coverage.info
	genhtml *.info -o ./gcov_report
	open ./gcov_report/index.html
	rm -rf *.gcda *.gcno *.info exec a.out

test:
	unzip test_file.zip 
	$(CC) $(FILES) $(TESTFILES) $(PKGCONFIG)

install: uninstall
	mkdir build
	cd build && cmake ../viewer
	make -C ./build/

uninstall:
	rm -Rf build/
	rm -rf viewer.tar.gz

dvi:
	open ../README.md

dist: install
	tar -czf viewer.tar.gz --directory=viewer/ .

style:
	clang-format -style=google -i s21_viewer_func/*.c s21_viewer_func/*.h
	clang-format -style=google -i tests/*.c tests/*.h
	clang-format -style=google -i viewer/*.h viewer/*.cpp

style_check:
	clang-format -style=google -n s21_viewer_func/*.c s21_viewer_func/*.h
	clang-format -style=google -n tests/*.c tests/*.h
	clang-format -style=google -n viewer/*.h viewer/*.cpp

clean: uninstall
	rm -rf gcov_report tests/*.o ./a.out *.o *.gcda *.gcno *.info exec s21_viewer.a ./test_file