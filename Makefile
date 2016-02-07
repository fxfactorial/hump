# -*- makefile -*-

.PHONY:all clean

flags := -shared -undefined dynamic_lookup -fPIC
libs := -lc++
src := hump.cpp
lib := hump.so

all:
	@clang++ ${flags} ${src} ${libs} -o ${lib}

example:all
	@make -C example

clean:
	@rm -rf *.{o,so}
