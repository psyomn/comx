#include "archive_builder.h"
#include "archive_cbz.h"

namespace comx::core {
  std::unique_ptr<Archive> ArchiveBuilder::Build() {
    if (mPath.extension() == ".cbz") {
      return std::make_unique<ArchiveCBZ>(mPath);
    }

    throw std::runtime_error(Archive::UNKNOWN_FORMAT_EXCEPTION + ": " + mPath.string());
  }
}
