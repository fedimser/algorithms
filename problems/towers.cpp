// (c) Dmytro Fedoriaka, 2024.
// Problem: https://acmp.ru/index.asp?main=task&id_task=561
// Solution idea: https://blog.mitrichev.ch/2019/06/power-towers-solution.html
#include <bits/stdc++.h>
using namespace std;
#define int int64_t

struct Depoweriser {
  vector<pair<int, int> > v;
  Depoweriser() {
    v.resize(100);
    for (int i = 1; i <= 99; i++) v[i] = {i, 1};
    for (int i = 2; i <= 7; i++) v[i * i] = {i, 2};
    for (int i = 2; i <= 6; i++) v[1 << i] = {2, i};
    v[27] = {3, 3};
    v[81] = {3, 4};
  }
};
Depoweriser D;

double L[100];

// Represents number A^B = A^(10^logB).
struct TowerNumber {
  int A;
  double logB;

  TowerNumber(int A_, double logB_) {
    auto a = D.v[A_];
    A = a.first;
    logB = (A == 1 ? 0 : (L[a.second] + logB_));
  }

  inline TowerNumber BottomPow(int x) const { return TowerNumber(x, Log10()); }

  // 1,-1 - not equal, but close (0.1 < ratio < 10)
  // 2,-2 - not equal and not close.
  inline int CompareTo(const TowerNumber& other) const {
    double delta_logB = logB - other.logB;
    if (A == other.A && abs(delta_logB) < 1e-9) return 0;

    if (delta_logB >= 1) return 2;
    if (delta_logB <= -1) return -2;

    double beta = pow(10, delta_logB);
    double delta = beta * L[A] - L[other.A];

    if (other.logB <= 10) {
      double B2 = pow(10, other.logB);
      if (abs(B2 * delta) < 1) {
        return (delta > 0 ? 1 : -1);
      }
    }
    return (delta > 0 ? 2 : -2);
  }

  inline double Log10() const { return pow(10, logB) * L[A]; }
};

TowerNumber ONE(1, 0);
struct Tower {
  int idx;
  vector<int> t;

  void Read() {
    int n;
    cin >> n;
    n++;
    t.assign(n, 1);
    for (int i = 0; i < n; i++) {
      cin >> t[i];
    }
    for (int i = 0; i < n; i++) {
      if (t[i] == 1) {
        t.resize(i);
        break;
      }
    }
  }

  int CompareTo(const Tower& other) const {
    TowerNumber x = ONE, y = ONE;
    int n1 = t.size();
    int n2 = other.t.size();
    int n = max(n1, n2);
    int cmp;
    for (int i = n; i >= 0; i--) {
      if (i < n1) x = x.BottomPow(t[i]);
      if (i < n2) y = y.BottomPow(other.t[i]);
      cmp = x.CompareTo(y);
      if (cmp == 2 || cmp == -2) return cmp;
      if (cmp == 0 && x.Log10() > 2.37) {
        for (int j = i - 1; j >= 0; j--) {
          if (t[j] != other.t[j]) return (t[j] - other.t[j]);
        }
        return 0;
      }
    }
    return cmp;
  }

  bool operator<(const Tower& other) const { return CompareTo(other) < 0; }
};

void Solve() {
  for (int i = 1; i < 100; i++) L[i] = log10(i);

  int n;
  cin >> n;
  vector<Tower> t(n);
  for (int i = 0; i < n; i++) {
    t[i].idx = i + 1;
    t[i].Read();
  }

  sort(t.begin(), t.end());
  for (auto x : t) {
    cout << x.idx << " ";
  }
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  Solve();
  return 0;
}