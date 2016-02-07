#include <cstdio>
#include <iostream>

class FileBuilder {
public:
  void do_speak()
  {
    std::string bar = "Generating Merlin";
    std::cout << bar << std::endl;
  }
};

extern "C" {

#include <gnumake.h>

  int plugin_is_GPL_compatible;

  char *generate_merlin(const char *func_name, int argc, char **argv)
  {
    (new FileBuilder)->do_speak();
    return NULL;
  }

  int hump_gmk_setup()
  {
    gmk_add_function("speak", (gmk_func_ptr)generate_merlin, 1, (unsigned int)1, 1);
    return 1;
  }

}
