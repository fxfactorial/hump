.PHONY:all clean

# all:
# 	ocamlopt speak_ocaml.ml do_speak.c  \
# 	-ccopt -undefined -ccopt dynamic_lookup \
# 	-ccopt -fPIC \
# 	-output-obj -o do_speak.so

# load ./do_speak.so

all:
	ocamlopt -c speak_ocaml.ml
	ocamlopt -output-obj -o caml_code.o speak_ocaml.cmx
	clang -I`ocamlc -where` -c do_speak.c -o do_speak.o

	clang -shared -undefined dynamic_lookup -fPIC -L`ocamlc -where` -ldl \
	-lasmrun do_speak.o caml_code.o -o do_speak.so

show_off:
	echo "Speaker?"
	${speak 123}

clean:
	@rm -rf *.{cmi,cmt,cmi,cmx,o,cmo,so}
