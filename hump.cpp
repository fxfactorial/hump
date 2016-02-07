#include <cstdio>
#include <iostream>
#include <memory>

#include <folly/json.h>

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

  char *generate_project(const char *func_name, int argc, char **argv)
  {
    std::unique_ptr<FileBuilder> builder(new FileBuilder);

    builder->do_speak();
    return NULL;
  }

  int hump_gmk_setup()
  {
    gmk_add_function("generate_project",
		     (gmk_func_ptr)generate_project, 1, (unsigned int)1, 1);
    return 1;
  }

}
