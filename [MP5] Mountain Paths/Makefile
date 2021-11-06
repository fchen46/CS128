CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++20 -g -fstandalone-debug -Wall -Wextra -Werror -pedantic $(INCLUDES)

exec: bin/exec
tests: bin/tests

bin/exec: ./src/driver.cc ./src/color.cc ./src/elevation_dataset.cc ./src/grayscale_image.cc ./src/path_image.cc ./src/path.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/tests: ./tests/tests.cc obj/catch.o ./src/color.cc ./src/elevation_dataset.cc ./src/grayscale_image.cc ./src/path_image.cc ./src/path.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

obj/catch.o: tests/catch.cc
	$(CXX) $(CXXFLAGS) -c $^ -o $@

.DEFAULT_GOAL := tests
.PHONY: clean exec tests

clean:
	rm -fr bin/* obj/*
