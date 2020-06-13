#include "archive.h"

#include <zlib.h>
#include "debug.h"

namespace comx::core {
  const std::string ArchiveBuilder::UNKNOWN_FORMAT_EXCEPTION = "unknown format";
  const std::string ArchiveBuilder::BAD_FORMAT_EXCEPTION = "bad format";

  Archive::Archive(std::filesystem::path path,
                   std::uint32_t numImages,
                   std::string metadata,
                   std::uint32_t crc32)
    : mPath(path), mChunkSize(16384), mNumImages(numImages),
      mMetadata(metadata), mCRC32(crc32) {
  }

  Archive::~Archive() {
  }

  void Archive::Load() {
  }

  // CBZ
  ArchiveCBZ::ArchiveCBZ(std::filesystem::path path) :
    Archive(path, 0, "", 0) {
    mNumImages = 0;
    mMetadata = "";
    mCRC32 = 0;
  }

  ArchiveCBZ::~ArchiveCBZ() {
  }

  void ArchiveCBZ::Load() {
    std::cout << "todo" << std::endl;
  }
}
