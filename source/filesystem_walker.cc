#include "filesystem_walker.h"

namespace comx::core {
  FilesystemWalker::FilesystemWalker(std::string path,
                                     std::optional<std::string> extension)
    : mPath(path), mDirIt(path), mExtension(extension) {
  }

  FilesystemWalker::~FilesystemWalker() {
  }

  std::optional<std::string> FilesystemWalker::NextFile() {
    std::filesystem::path ret;

    for (;;) {
      if (!HasNext()) return {};

      ret = *(mDirIt);
      mDirIt++;

      if (!std::filesystem::is_regular_file(ret))
        continue;

      if (!mExtension)
        return ret.string();

      if (ret.extension() == mExtension)
        return ret.string();
    }

    return ret.string();
  }

  bool FilesystemWalker::HasNext() const {
    return mDirIt != std::filesystem::end(mDirIt);
  }
}
