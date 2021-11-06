CXX=clang++
INCLUDES=-Iincludes/
CXX_FLAGS=-std=c++20 -g -fstandalone-debug -Wall -Wextra -Werror -pedantic $(INCLUDES)

exec: bin/exec
tests: bin/tests

bin/exec: src/main.cc src/seam_carver.cc src/image_ppm.cc includes/image_ppm.hpp includes/seam_carver.hpp
	${CXX} ${CXX_FLAGS} src/main.cc src/seam_carver.cc src/image_ppm.cc -o bin/exec

bin/tests: tests/tests.cc obj/catch.o src/seam_carver.cc src/image_ppm.cc includes/image_ppm.hpp includes/seam_carver.hpp
	${CXX} ${CXX_FLAGS} obj/catch.o tests/tests.cc src/seam_carver.cc src/image_ppm.cc -o bin/tests

obj/catch.o: tests/catch.cc
	$(CXX) $(CXX_FLAGS) -c $^ -o $@

.DEFAULT_GOAL := tests
.PHONY: clean exec tests

clean:
	rm -fr bin/* obj/*