#include <filesystem>
#include <iostream>
#include <string>

#include "./header/builder.h"

auto (*sys)(const char *cmd) = system;

Builder::Builder(Compilers compiler, Systems system, Architectures architecture,
                 OptimizationLevel optimizationLevel)
    : compiler(compiler), system(system), architecture(architecture),
      optimizationLevel(optimizationLevel) {}

void Builder::setCompiler(Compilers compiler) { this->compiler = compiler; }

void Builder::setSystem(Systems system) { this->system = system; }

void Builder::setArchitecture(Architectures architecture) {
  this->architecture = architecture;
}

void Builder::setOptimizationLevel(OptimizationLevel optimizationLevel) {
  this->optimizationLevel = optimizationLevel;
}

void Builder::addFile(const std::string &dir) { files.push_back(dir); }

void Builder::addFiles(const std::vector<std::string> &files) {
  this->files.insert(this->files.end(), files.begin(), files.end());
}

void Builder::setOutputFile(const char *dir) { outputFile = dir; }

void Builder::addFile(const char *dir) { files.push_back(dir); }

void Builder::addFiles(const std::vector<char *> files) {
  this->files.insert(this->files.end(), files.begin(), files.end());
}

void Builder::setOutputFile(const std::string &dir) { outputFile = dir; }

void Builder::addFiles(const char **files, int size) {
  for (int i = 0; i < size; i++)
    this->files.push_back(files[i]);
}

void Builder::addArgument(const std::string &arg) {
  this->arguments.push_back(arg);
}
void Builder::addArgument(const char *arg) { this->arguments.push_back(arg); }

std::string Builder::argumentsToCommand() {
  std::string command = "";
  for (auto &arg : arguments)
    command += arg + " ";
  return command;
}

void Builder::clearArguments() { arguments.clear(); }

void Builder::Compile() {
  std::string currPath = std::filesystem::current_path().string();

  if (compiler == GCC) {
    switch (architecture) {
    case x86_64:
      if (system == Linux)
        addArgument("x86_64-linux-gnu-gcc -m64");
      if (system == Windows)
        addArgument("x86_64-w64-mingw32-gcc");
      break;
    case x86:
      if (system == Linux)
        addArgument("x86_64-linux-gnu-gcc -m32");
      if (system == Windows)
        addArgument("i686-w64-mingw32-gcc");
      break;
    default:
      break;
    }
  }

  if (outputFile.size() != 0)
    addArgument(" -o " + currPath + "/" + outputFile);

  switch (optimizationLevel) {
  case O0:
    addArgument(" -O0");
    break;
  case O1:
    addArgument(" -O1");
    break;
  case O2:
    addArgument(" -O2");
    break;
  case O3:
    addArgument(" -O3");
    break;
  case Ofast:
    addArgument(" -Ofast");
    break;
  case Og:
    addArgument(" -Og");
    break;
  case Oz:
    addArgument(" -Oz");
    break;
  case Os:
    addArgument(" -Os");
    break;
  case None:
  default:
    break;
  }

  if (files.empty())
    exit(1);
  for (auto &file : files)
    addArgument(" " + currPath + "/" + file);

  std::string command = argumentsToCommand();
  std::cout << command << std::endl;
  sys(command.c_str());
}
