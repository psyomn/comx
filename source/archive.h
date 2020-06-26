/*
Copyright 2020 Simon (psyomn) Symeonidis

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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
