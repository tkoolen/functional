#include <vector>
#include <iostream>

template <typename T>
inline bool isMonotonic(const std::vector<T>& values) {
  for (size_t i = 1; i < values.size(); i++) {
    if (values[i] < values[i - 1]) {
      std::cout << "values[i]: " << values[i] << ", values[i - 1]: " << values[i - 1] << std::endl;
      return false;
    }
  }
  return true;
}