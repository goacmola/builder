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

void Builder::Compile() {
  std::string command;
  std::string currPath = std::filesystem::current_path().string();

  if (compiler == GCC) {

    switch (architecture) {
    case x86_64:
      if (system == Linux)
        command = "x86_64-linux-gnu-gcc -m64";
      if (system == Windows)
        command = "x86_64-w64-mingw32-gcc";
      break;
    case x86:
      if (system == Linux)
        command = "x86_64-linux-gnu-gcc -m32";
      if (system == Windows)
        command = "i686-w64-mingw32-gcc";
      break;
    default:
      break;
    }
  }
  std::cout << command << std::endl;

  if (outputFile.size() != 0) {
    command += " -o " + currPath + "/" + outputFile;
  }

  switch (optimizationLevel) {
  case O0:
    command += " -O0";
    break;
  case O1:
    command += " -O1";
    break;
  case O2:
    command += " -O2";
    break;
  case O3:
    command += " -O3";
    break;
  case Ofast:
    command += " -Ofast";
    break;
  case Og:
    command += " -Og";
    break;
  case Oz:
    command += " -Oz";
    break;
  case Os:
    command += " -Os";
    break;
  case None:
  default:
    break;
  }

  if (files.empty())
    exit(1);
  for (auto &file : files)
    command += " " + currPath + "/" + file;

  std::cout << command << std::endl;
  sys(command.c_str());
}
