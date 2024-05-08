// Debugging utils for competitive programming. (c) Dmytro Fedoriaka, 2024.
// This is intended to be included as header in local-only mode.
#include <iostream>
#include <map>
#include <vector>
#include <set>

template <class T1, class T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1,T2>& p) {
  os << "(" << p.first << "," << p.second << ")";
}

template <class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
  bool c = false;
  os << "[";
  for (const T& x : v) {
    if (c) {os << ",";} else {c = true;}
    os << x;
  }
  os << "]";
  return os;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& v) {
  bool c = false;
  os << "{";
  for (const T& x : v) {
    if (c) {os << ",";} else {c = true;}
    os << x;
  }
  os << "}";
  return os;
}

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::map<T1, T2>& m) {
  bool c = false;
  os << "{";
  for (const auto& x : m) {
    if (c) {os << ",";} else {c = true;}
    os << x.first << ":" << x.second;
  }
  os << "}";
  return os;
}

template <typename T>
void LOG(T&& v) {
  std::cout << v << std::endl;
}

template <typename T, typename... Ts>
void LOG(T&& v, Ts&&... r) {
  std::cout << v << " ";
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