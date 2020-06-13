#pragma once

namespace comx::testing {
  inline std::string MISSING_FIXTURE() {
    return
      "there seems to be a missing fixture for the tests\n"
      "make sure that cmake is indeed copying certain files into\n"
      "the build directory\n";
  }
}
