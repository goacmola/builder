#ifndef __BUILDER_H__
#define __BUILDER_H__

#include <array>
#include <string>
#include <vector>

typedef enum warnings { All, Extra, Pedantic } WarningLevel;

typedef enum supported_compiler_list { GCC } Compilers;

typedef enum supported_systems_list { Windows, Linux } Systems;

typedef enum supported_architecture_list { x86, x86_64 } Architectures;

typedef enum supported_optimization_levels {
  None = -1,
  O0,
  O1,
  O2,
  O3,
  Ofast,
  Os,
  Og,
  Oz
} OptimizationLevel;

struct Builder {
private:
  Compilers compiler;
  Systems system;
  Architectures architecture;
  OptimizationLevel optimizationLevel;
  WarningLevel warningLevel;

  std::vector<std::string> files;
  std::string outputFile;

  std::vector<std::string> arguments;

  std::string argumentsToCommand();

public:
  Builder(Compilers compiler = GCC, Systems system = Linux,
          Architectures architecture = x86_64,
          OptimizationLevel optimizationLevel = None);

  void setCompiler(Compilers compiler);
  void setSystem(Systems system);
  void setArchitecture(Architectures architecture);
  void setOptimizationLevel(OptimizationLevel optimizationLevel);
  void setWarningLevel(WarningLevel warningLevel);

  void addFile(const std::string &dir);
  void addFile(const char *dir);

  void addFiles(const std::vector<std::string> &files);
  void addFiles(const std::vector<char *> files);
  void addFiles(const char **files, int size);

  void setOutputFile(const std::string &dir);
  void setOutputFile(const char *dir);

  void addArgument(const std::string &arg);
  void addArgument(const char *arg);

  void clearArguments();

  void Compile();
};

#endif // !__BUILDER_H__
