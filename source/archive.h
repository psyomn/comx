#pragma once

#include <filesystem>
#include <cstdint>
#include <memory>
#include <vector>

namespace comx::core {
  class Archive {
  public:
    enum class State { Init, Loading, Loaded };
    explicit Archive(std::filesystem::path path,
                     std::uint32_t numImages,
                     std::string metadata,
                     std::uint32_t crc32);
    virtual ~Archive();
    Archive(const Archive& other) = delete;
    Archive(Archive&& other) = delete;
    Archive& operator=(Archive&& other) = delete;

    virtual void Load() = 0;

    inline std::uint32_t NumImages() const { return mNumImages; }
    inline std::string Metadata() const { return mMetadata; }
    inline std::uint32_t CRC32() const { return mCRC32; }
    inline const std::vector<std::string>& PageNames() const { return mPageNames; }
    inline std::size_t FileSize() const { return mFileSize; }
    inline State CurrentState() const { return mState; }

    static const std::string BAD_FORMAT_EXCEPTION;
    static const std::string UNKNOWN_FORMAT_EXCEPTION;

  protected:
    std::filesystem::path mPath;
    std::vector<std::string> mPageNames;
    std::uint32_t mNumImages;
    std::string mMetadata;
    std::uint32_t mCRC32;
    State mState;
    std::size_t mFileSize;
  };
}
