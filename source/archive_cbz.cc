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

#include "archive_cbz.h"

#include <libzippp.h>

namespace comx::core {
  // CBZ
  ArchiveCBZ::ArchiveCBZ(std::filesystem::path path) :
    Archive(path, 0, "", 0) {
  }

  ArchiveCBZ::~ArchiveCBZ() {
  }

  void ArchiveCBZ::Load() {
    mState = Archive::State::Loading;

    libzippp::ZipArchive zf(mPath);
    zf.open(libzippp::ZipArchive::READ_ONLY);
    std::vector<libzippp::ZipEntry> entries = zf.getEntries();

    mMetadata = zf.getComment();
    mNumImages = entries.size();
    mFileSize = std::filesystem::file_size(mPath);

    for (auto &e : entries) {
      mPageNames.push_back(e.getName());
    }

    mState = Archive::State::Loaded;
  }

}
