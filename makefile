CXX = g++
FLAGS = -std=c++17 -Wall -Werror -Wextra
SANITIZE = -fsanitize=address -pedantic
TARGETS = tests/tests.cc
GCOV = -fprofile-arcs -ftest-coverage -fPIC -pthread
GTEST = -lgtest -lgtest_main -L/opt/homebrew/Cellar/googletest/1.14.0/lib

all: test

test: clean
	${CXX} ${TARGETS} ${FLAGS} ${GCOV} ${GTEST} -o test -I/opt/homebrew/Cellar/googletest/1.14.0/include
	./test

test_asan: clean
	${CXX} ${FLAGS} ${SANITIZE} ${TARGETS} ${GTEST} -o test_asan -L/opt/homebrew/Cellar/googletest/1.14.0/include
	./test_asan


gcov_report: test
	mkdir report
	gcovr --html-details -o report/coverage.html
	open ./report/coverage.html

style:
	clang-format -style=Google -n *.h

clean:
	rm -rf *.o *.out *.gch *.dSYM *.gcov *.gcda *.gcno *.a *.css *.html *.info test test_asan report
.PHONY: test test_asan clean gcov_report style
