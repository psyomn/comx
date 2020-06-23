#include "archive.h"

#include <cstdint>
#include <array>
#include "debug.h"

#include <libzippp.h>

namespace comx::core {
  const std::string ArchiveBuilder::UNKNOWN_FORMAT_EXCEPTION = "unknown format";
  const std::string ArchiveBuilder::BAD_FORMAT_EXCEPTION = "bad format";

  Archive::Archive(std::filesystem::path path,
                   std::uint32_t numImages,
                   std::string metadata,
                   std::uint32_t crc32)
    : mPath(path), mNumImages(numImages),
      mMetadata(metadata), mCRC32(crc32),
      mState(Archive::State::Init),
      mFileSize(0) {
  }

  Archive::~Archive() {
  }

  void Archive::Load() {
  }

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

    for (auto &e : entries) {}

    mState = Archive::State::Loaded;
  }
}
