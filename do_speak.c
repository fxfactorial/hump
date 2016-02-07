#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <gnumake.h>
#include <caml/mlvalues.h>
#include <caml/callback.h>
#include <caml/memory.h>
#include <caml/alloc.h>

int plugin_is_GPL_compatible;

char *ocaml_speaker(const char *func_name, int argc, char **argv)
{
  char *answer =
    String_val(caml_callback(*caml_named_value("speak"), Val_unit));

  printf("Speaking and got: %s\n", answer);
  char *buf = gmk_alloc(strlen(answer) + 1);
  strcpy(buf, answer);
  /* receive_arg */
  return buf;
}

int do_speak_gmk_setup()
{
  printf("Getting Called by Make\n");
  char **argv = {"/home/Edgar/foo", NULL};
  /* caml_startup(argv); */
  printf("Called caml_startup\n");
  gmk_add_function("speak", ocaml_speaker, 1, (unsigned int)1, 1);
  return 1;
}
