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
