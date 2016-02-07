# -*- makefile -*-

.PHONY:all clean

all:
	@clang++ -shared -undefined dynamic_lookup \
	-fPIC do_speak.cpp -o do_speak.so

load do_speak.so

show_off:
	${speak 123}

clean:
	@rm -rf *.{cmi,cmt,cmi,cmx,o,cmo,so}
