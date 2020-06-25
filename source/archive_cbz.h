#pragma once

#include "archive.h"

namespace comx::core {
  class ArchiveCBZ : public Archive {
  public:
    explicit ArchiveCBZ(std::filesystem::path path);
    ~ArchiveCBZ();
    ArchiveCBZ(const ArchiveCBZ& other) = delete;
    ArchiveCBZ(const ArchiveCBZ&& other) = delete;
    ArchiveCBZ& operator=(ArchiveCBZ other) = delete;

    void Load() override;
  private:
    unsigned char* mIn;
    unsigned char* mOut;
  };
}
