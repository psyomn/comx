#pragma once

#include "archive.h"

namespace comx::core {
  class ArchiveBuilder {
  public:
    explicit ArchiveBuilder(){};
    ~ArchiveBuilder(){};
    ArchiveBuilder(const ArchiveBuilder& other) = delete;
    ArchiveBuilder(ArchiveBuilder&& other) = delete;
    ArchiveBuilder& operator=(ArchiveBuilder other) = delete;

    inline ArchiveBuilder& Path(std::filesystem::path p) {
      mPath = p;
      return *this;
    }

    std::unique_ptr<Archive> Build();

  private:
    std::filesystem::path mPath;
  };
}
