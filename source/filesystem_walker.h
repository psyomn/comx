#pragma once

#include <string>
#include <filesystem>
#include <optional>

namespace comx::core {
  class FilesystemWalker {
  public:
    FilesystemWalker(std::string path, std::optional<std::string> ext);
    ~FilesystemWalker();
    FilesystemWalker(const FilesystemWalker&) = delete;
    FilesystemWalker(FilesystemWalker&&) = delete;

    bool HasNext() const;
    std::optional<std::string> NextFile();

  private:
    std::string mPath;
    std::optional<std::string> mExtension;
    std::filesystem::recursive_directory_iterator mDirIt;
  };
}
