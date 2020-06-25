#pragma once

#include <iostream>
#include <vector>
#include <string>

namespace comx::utils {
  inline void PrintVector(const std::vector<std::string>& vec) {
    std::cout << "[";
    for (auto &e : vec) std::cout << e << " ";
    std::cout << "]" << std::endl;;
  }
}
