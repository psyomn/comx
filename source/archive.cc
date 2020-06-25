#include "archive.h"

#include <cstdint>
#include <array>
#include "archive.h"

namespace comx::core {
  const std::string Archive::UNKNOWN_FORMAT_EXCEPTION = "unknown format";
  const std::string Archive::BAD_FORMAT_EXCEPTION = "bad format";

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
}
