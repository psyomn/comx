#include "archive.h"

#include <iostream>

int TestNonExistingArchiveThrows(void) {
  using namespace comx::core;

  Archive nope("nope");
  int badFormat = 0;

  try {
    nope.Load();
  } catch(std::exception& e) {
    // bad format is expected behavior
    badFormat = !(e.what() == Archive::BAD_FORMAT_EXCEPTION);
  }
  return badFormat;
}

int TestOpenSimpleArchive(void) {
  return 0;
}

int TestListFilesInArchives(void) {
  return 0;
}

int main(void) {
  return
    TestNonExistingArchiveThrows() |
    TestOpenSimpleArchive() |
    TestListFilesInArchives();
}
