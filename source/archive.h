#pragma once

// http://zlib.net/zlib_how.html

#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#  include <fcntl.h>
#  include <io.h>
#  define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
#else
#  define SET_BINARY_MODE(file)
#endif

#include <filesystem>

namespace comx::core {
  class Archive {
  public:
    Archive(std::filesystem::path path);
    ~Archive();
    Archive(const Archive& other) = delete;
    Archive(Archive&& other) = delete;

    void Load();

    static const std::string BAD_FORMAT_EXCEPTION;

  private:
    std::filesystem::path mPath;
    const std::size_t mChunkSize;
  };
}
