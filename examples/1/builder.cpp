#include "../../src/header/builder.h"

#include <string>
#include <vector>

int main() {
  Builder builder;

  builder.addFile("src/main.c");
  builder.setOutputFile("build/linux/main.out");
  builder.setArchitecture(x86_64);
  builder.setSystem(Linux);
  builder.setOptimizationLevel(O2);
  builder.Compile();

  builder.clearArguments();

  builder.setOutputFile("build/windows/main.exe");
  builder.setSystem(Windows);
  builder.Compile();
}
