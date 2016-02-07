# -*- makefile -*-

.PHONY:all clean

flags := -shared -undefined dynamic_lookup -fPIC -std=c++14
libs := -lc++ -lfolly
src := hump.cpp
lib := hump.so

all:
	@clang++ ${flags} ${src} ${libs} -o ${lib}

example:all
	@make -C example

clean:
	@rm -rf *.{o,so}
	@rm -rf example/.merlin
