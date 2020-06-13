#include "archive.h"

#include <zlib.h>

namespace comx::core {
  const std::string Archive::BAD_FORMAT_EXCEPTION = "unknown format exception";

  Archive::Archive(std::filesystem::path path)
    : mPath(path), mChunkSize(16384) {
  }

  Archive::~Archive() {
  }

  void Archive::Load() {
    if (mPath.extension() == "cbz") {
      return;
    }

    throw std::runtime_error(BAD_FORMAT_EXCEPTION);
  }
}
