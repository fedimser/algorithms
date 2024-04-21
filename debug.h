// Debugging utils for competitive programming. (c) Dmytro Fedoriaka, 2024.
// This is intended to be included as header in local-only mode.
#include <iostream>
#include <vector>
#include <map>

template <typename T>
void DebugPrint(T &&v) {
  std::cout << v;
}

template <typename T>
void DebugPrint(std::vector<T> &v) {
  bool c = false;
  std::cout << "[";
  for (T &x : v) {
    std::cout << x;
    if (c) std::cout << ","; else c=1;
  }
  std::cout << "]";
}

template <typename T1, typename T2>
void DebugPrint(std::map<T1, T2> &m){
  bool c = false;
  std::cout << "{";
  for (const auto &x : m)  {
    std::cout << x.first << ":" << x.second;
    if (c) std::cout << ","; else c=1;
  }
  std::cout << "}";
}

template <typename T>
void LOG(T &&v){
  DebugPrint(v);
  std::cout << std::endl;
}

template <typename T, typename... Ts>
void LOG(T &&v, Ts &&...r){
  DebugPrint(v);
  std::cout << " ";
  LOG(std::forward<Ts>(r)...);
}
