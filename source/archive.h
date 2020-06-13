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
#include <cstdint>
#include <memory>

namespace comx::core {
  class Archive {
  public:
    Archive(std::filesystem::path path,
            std::uint32_t numImages,
            std::string metadata,
            std::uint32_t crc32);
    virtual ~Archive();
    Archive(const Archive& other) = delete;
    Archive(Archive&& other) = delete;

    virtual void Load() = 0;

    inline std::uint32_t NumImages() { return mNumImages; }
    inline std::string Metadata() { return mMetadata; }
    inline std::uint32_t CRC32() { return mCRC32; }

  protected:
    std::filesystem::path mPath;
    const std::size_t mChunkSize;

    std::uint32_t mNumImages;
    std::string mMetadata;
    std::uint32_t mCRC32;
  };

  // Different archive types bellow
  class ArchiveCBZ: public Archive {
  public:
    ArchiveCBZ(std::filesystem::path path);
    ~ArchiveCBZ();
    ArchiveCBZ(const ArchiveCBZ& other) = delete;
    ArchiveCBZ(const ArchiveCBZ&& other) = delete;

    void Load() override;
  private:
  };

  class ArchiveBuilder {
  public:
    ArchiveBuilder(){};
    ~ArchiveBuilder(){};
    ArchiveBuilder(const ArchiveBuilder& other) = delete;
    ArchiveBuilder(ArchiveBuilder&& other) = delete;

    inline ArchiveBuilder& Path(std::filesystem::path p) {
      mPath = p;
      return *this;
    }

    std::unique_ptr<Archive> Build() {
      if (mPath.extension() == ".cbz") {
        return std::make_unique<ArchiveCBZ>(mPath);
      }

      throw std::runtime_error(UNKNOWN_FORMAT_EXCEPTION + ": " + mPath.string());
    }

  static const std::string BAD_FORMAT_EXCEPTION;
  static const std::string UNKNOWN_FORMAT_EXCEPTION;

  private:
    std::filesystem::path mPath;
  };
}
