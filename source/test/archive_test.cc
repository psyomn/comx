#include "archive.h"
#include "testing.h"

#include <iostream>

using comx::testing::MISSING_FIXTURE;
using comx::core::Archive;
using comx::core::ArchiveCBZ;
using comx::core::ArchiveBuilder;

std::unique_ptr<Archive> LoadArchive(std::string name) {
  try {
    std::unique_ptr<Archive> archive = (ArchiveBuilder{}.Path(name).Build());
    return archive;
  } catch(std::exception& e) {
    return nullptr;
  }
}

int TestNonExistingArchiveThrows(void) {
  int badFormat = 0;
  auto arch = LoadArchive("nope");
  return !arch;
}

int TestOpenSimpleArchive(void) {
  auto arch = LoadArchive("test/sample-comic.cbz");
  if (!arch) return 1;
  return arch->NumImages() == 1;
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
