#include <iostream>

#include "filesystem_walker.h"

int TestWalkingSimpleDirStructure() {
  comx::core::FilesystemWalker walker{".", {}};
  while (walker.HasNext()) {
    std::optional<std::string> filename = walker.NextFile();
    if (filename) std::cout << filename.value() << std::endl;
    else std::cout << "none found" << std::endl;
  }
  return 0;
}

int TestWalkingWithExtension() {
  comx::core::FilesystemWalker walker(".", "cbx");
  while (walker.HasNext()) {
    std::optional<std::string> filename = walker.NextFile();
    if (filename) std::cout << filename.value() << std::endl;
    else std::cout << "none found" << std::endl;
  }
  return 0;
}

int main(void) {
  return
    TestWalkingSimpleDirStructure() |
    TestWalkingWithExtension();
}
