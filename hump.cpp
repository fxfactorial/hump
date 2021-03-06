#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include <fstream>

#include <folly/json.h>
#include <folly/dynamic.h>

#include <folly/Format.h>
#include <folly/FileUtil.h>

std::string getcwd_string(void)
{
   char buff[PATH_MAX];
   getcwd(buff, PATH_MAX);
   std::string cwd(buff);
   return cwd;
}

class Project_builder {
private:
  folly::dynamic project_spec = nullptr;

public:
  Project_builder(const std::string package_json_path)
  {
    std::string load_pkg_desc;
    if (!folly::readFile(package_json_path.data(), load_pkg_desc)) {
      exit(-1);
    }
    project_spec = folly::parseJson(load_pkg_desc);
  }

  void make_merlin_file()
  {
    std::ofstream merlin_file;
    std::string merlin_gen_file_path =
      folly::sformat("{}/.merlin", getcwd_string ());

    merlin_file.open(merlin_gen_file_path, std::ios::out);
    merlin_file << "PKG ";

    for (auto& pkg : project_spec["dependencies"].keys()) {
      merlin_file << pkg << " ";
    }
    merlin_file << std::endl;
    merlin_file.close();
  }

  void make_opam_file()
  {
    std::ofstream opam_file;
    std::string opam_gen_file_path =
      folly::sformat("{}/opam", getcwd_string());
    opam_file.open(opam_gen_file_path, std::ios::out);
    opam_file << "opam-version: \"1.2\"" << "\n"
	      << "name: " << project_spec["name"] << "\n"
	      << "version: " << project_spec["version"] << "\n"
	      << "license: " << project_spec["license"] << "\n"
	      << std::endl;
    opam_file.close();
  }

};

class Code_builder {

public:
  Code_builder(const std::string package_json_path)
  {
    std::cout << "Spoken from code builder\n";
  }

};

extern "C" {

#include <gnumake.h>

  int plugin_is_GPL_compatible;

  char *generate_project(const char *func_name, int argc, char **argv)
  {
    std::string package_json(*argv);
    std::unique_ptr<Project_builder> builder(new Project_builder(package_json));

    builder->make_merlin_file();
    builder->make_opam_file();
    return NULL;
  }

  char *build_project(const char *func_name, int argc, char **argv)
  {
    std::string package_json(*argv);
    std::unique_ptr<Code_builder> builder(new Code_builder(package_json));

    return NULL;
  }

  int hump_gmk_setup()
  {
    gmk_add_function("generate_project",
		     (gmk_func_ptr)generate_project, 1, (unsigned int)1, 1);
    gmk_add_function("build_project",
		     (gmk_func_ptr)build_project, 1, (unsigned int)1, 1);
    return 1;
  }

}
