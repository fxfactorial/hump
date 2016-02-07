extern "C" {

#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <gnumake.h>

  int plugin_is_GPL_compatible;

  char *ocaml_speaker(const char *func_name, int argc, char **argv)
  {
    printf("Called a custom make function!\n");
    return NULL;
  }

  int do_speak_gmk_setup()
  {
    printf("Started to create init\n");
    gmk_add_function("speak", (gmk_func_ptr)ocaml_speaker, 1, (unsigned int)1, 1);
    return 1;
  }

}
