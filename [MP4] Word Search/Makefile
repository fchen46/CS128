CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++20 -g -fstandalone-debug -Wall -Wextra -Werror -pedantic $(INCLUDES)

exec: bin/exec
tests: bin/tests

bin/exec: src/driver.cc src/CharPositions.cc src/WordLocation.cc src/WordSearchSolver.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/tests: obj/catch.o tests/tests.cc src/CharPositions.cc src/WordLocation.cc src/WordSearchSolver.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

obj/catch.o: tests/catch.cc
	$(CXX) $(CXXFLAGS) -c $^ -o $@

.DEFAULT_GOAL := exec
.PHONY: clean

clean:
	rm -f bin/*
