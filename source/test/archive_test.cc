/*
Copyright 2020 Simon (psyomn) Symeonidis

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "archive.h"
#include "archive_cbz.h"
#include "archive_builder.h"

#include "testing.h"
#include "debug.h"

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
  auto arch = LoadArchive("nope");
  return arch != nullptr;
}

int TestOpenSimpleArchive(void) {
  auto arch = LoadArchive("test/sample-comic.cbz");
  if (!arch) return 1;

  arch->Load();
  return arch->NumImages() == 8;
}

int TestListFilesInArchives(void) {
  auto arch = LoadArchive("test/sample-comic.cbz");
  if (!arch) return 1;
  arch->Load();

  const std::vector<std::string> actual = arch->PageNames();
  const std::vector<std::string> expected = {"000.png", "001.png", "002.png",
                                             "003.png", "004.png", "005.png",
                                             "006.png"};

  if (expected.size() != actual.size()) {
    std::cout << "sizes differ: expected: " << expected.size()
              << " actual size: " << actual.size() << std::endl;
    return 1;
  }

  if (actual != expected) {
    std::cout << "actual != expected" << std::endl;
    std::cout << "actual: " << std::endl;
    comx::utils::PrintVector(actual);

    std::cout << "expected: " << std::endl;
    comx::utils::PrintVector(expected);
  }

  return 0;
}

int TestFileSizeIsNotZero(void) {
  auto arch = LoadArchive("test/sample-comic.cbz");
  if (!arch) return 1;
  arch->Load();

  if (!arch->FileSize()) {
    std::cout << "file size should not be zero" << std::endl;
    return 1;
  }

  return 0;
}

int TestFileMetadata(void) {
  auto arch = LoadArchive("test/sample-comic.cbz");
  if (!arch) return 1;
  arch->Load();

  if (arch->Metadata() == "") {
    std::cout << "metadata was not successfully read from the archive" << std::endl;
    return 1;
  }

  const std::string expected = "THIS IS METADATA";
  const std::string actual = arch->Metadata();

  if (actual != expected) {
    std::cout << "expected: " << expected
              << " actual: " << actual
              << std::endl;
  }

  return 0;
}

int main(void) {
  return
    TestNonExistingArchiveThrows() |
    TestOpenSimpleArchive() |
    TestListFilesInArchives() |
    TestFileSizeIsNotZero() |
    TestFileMetadata();
}
