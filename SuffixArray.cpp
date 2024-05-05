#include <bits/stdc++.h>
using namespace std;

// Returns permutation giving sort for cyclis shifts. O(nlogn).
// Optionally stores all intemediate equivalence classes in c_res.
vector<int> SortCyclicShifts(string const& s,
                             vector<vector<int>>* c_res = nullptr) {
  int n = s.size();
  if (n == 0) return {};
  const int alphabet = 256;
  vector<int> p(n), c(n), cnt(max(alphabet, n), 0);
  for (int i = 0; i < n; i++) cnt[s[i]]++;
  for (int i = 1; i < alphabet; i++) cnt[i] += cnt[i - 1];
  for (int i = 0; i < n; i++) p[--cnt[s[i]]] = i;
  c[p[0]] = 0;
  int classes = 1;
  for (int i = 1; i < n; i++) {
    if (s[p[i]] != s[p[i - 1]]) classes++;
    c[p[i]] = classes - 1;
  }
  if (c_res != nullptr) c_res->push_back(c);
  vector<int> pn(n), cn(n);
  for (int h = 0; (1 << h) < n; ++h) {
    for (int i = 0; i < n; i++) {
      pn[i] = p[i] - (1 << h);
      if (pn[i] < 0) pn[i] += n;
    }
    fill(cnt.begin(), cnt.begin() + classes, 0);
    for (int i = 0; i < n; i++) cnt[c[pn[i]]]++;
    for (int i = 1; i < classes; i++) cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i];
    cn[p[0]] = 0;
    classes = 1;
    for (int i = 1; i < n; i++) {
      pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
      pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << h)) % n]};
      if (cur != prev) ++classes;
      cn[p[i]] = classes - 1;
    }
    c.swap(cn);
    if (c_res != nullptr) c_res->push_back(c);
  }
  return p;
}

// Solves problems on fixed string using SA.
struct SAHelper {
  string s;
  int n;
  vector<vector<int>> c;
  SAHelper() = default;
  
  SAHelper(const string& s_) {
    s = s_ + '\1';
    n = s.size();
    SortCyclicShifts(s, &c);
  }

  int LongestCommonPrefix(int i, int j) {
    int ans = 0;
    for (int k = c.size() - 1; k >= 0; k--) {
      if (c[k][i % n] == c[k][j % n]) {
        ans += 1 << k;
        i += 1 << k;
        j += 1 << k;
      }
    }
    return ans;
  }
};

#include "debug.h"
int main() {
  assert(SortCyclicShifts("") == vector<int>({}));
  assert(SortCyclicShifts("a") == vector<int>({0}));
  assert(SortCyclicShifts("abc") == vector<int>({0, 1, 2}));
  assert(SortCyclicShifts("bac") == vector<int>({1, 0, 2}));
  assert(SortCyclicShifts("dabbb$") == vector<int>({5, 1, 4, 3, 2, 0}));
  assert(SortCyclicShifts("aaaaa\1") == vector<int>({5, 4, 3, 2, 1, 0}));
  assert(SortCyclicShifts("abb01ba01ba0b1a0b10aba01b111b0aaaaa01") ==
         vector<int>({35, 22, 3, 7,  29, 18, 15, 11, 17, 25, 26, 13, 36,
                      27, 23, 4, 8,  34, 21, 6,  14, 10, 33, 32, 31, 30,
                      19, 0,  2, 28, 16, 24, 12, 20, 5,  9,  1}));

  SAHelper sah("abacabac");
  assert(sah.LongestCommonPrefix(1, 5) == 3);
  assert(sah.LongestCommonPrefix(2, 6) == 2);
  assert(sah.LongestCommonPrefix(1, 2) == 0);
}
// Source: https://cp-algorithms.com/string/suffix-array.html