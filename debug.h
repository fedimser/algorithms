// Debugging utils for competitive programming. (c) Dmytro Fedoriaka, 2024.
// This is intended to be included as header in local-only mode.
#include <iostream>
#include <map>
#include <vector>

template <typename T>
void DebugPrint(T &&v) {
  std::cout << v;
}

template <typename T>
void DebugPrint(std::vector<T> &v) {
  bool c = false;
  std::cout << "[";
  for (T &x : v) {
    if (c) {
      std::cout << ",";
    } else {
      c = true;
    }
    std::cout << x;
  }
  std::cout << "]";
}

template <typename T1, typename T2>
void DebugPrint(std::map<T1, T2> &m) {
  bool c = false;
  std::cout << "{";
  for (const auto &x : m) {
    if (c) {
      std::cout << ",";
    } else {
      c = true;
    }
    std::cout << x.first << ":" << x.second;
  }
  std::cout << "}";
}

template <typename T>
void LOG(T &&v) {
  DebugPrint(v);
  std::cout << std::endl;
}

template <typename T, typename... Ts>
void LOG(T &&v, Ts &&...r) {
  DebugPrint(v);
  std::cout << " ";
  LOG(std::forward<Ts>(r)...);
}

std::chrono::time_point<std::chrono::system_clock> __start_time =
    std::chrono::system_clock::now();

void ResetTime() { __start_time = std::chrono::system_clock::now(); }

void LogTime(std::string message) {
  auto diff = std::chrono::system_clock::now() - __start_time;
  auto diff_ms = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
  std::cout << message << " " << diff_ms.count() << "ms" << std::endl;
}