#include <bits/stdc++.h>
using namespace std;

struct TwoSat {
  int n;
  vector<vector<int>> adj, adj_t;
  vector<bool> used;
  vector<int> order, comp;
  vector<bool> assignment;  // Solution will be here (if satisifiable).

  TwoSat(int n_) {
    n = 2 * n_;
    adj.resize(n);
    adj_t.resize(n);
  }

  void AddImplication(bool negate1, int v1, bool negate2, int v2) {
    assert(0 <= v1 && v1 < n / 2);
    assert(0 <= v2 && v2 < n / 2);
    v1 = 2 * v1 + (negate1 ? 1 : 0);
    v2 = 2 * v2 + (negate2 ? 1 : 0);
    adj[v1].push_back(v2);
    adj_t[v2].push_back(v1);
  }

  void AddDisjunction(bool negate1, int v1, bool negate2, int v2) {
    AddImplication(!negate1, v1, negate2, v2);
    AddImplication(!negate2, v2, negate1, v1);
  }

  bool Solve() {
    order.clear();
    used.assign(n, false);
    for (int i = 0; i < n; ++i) {
      if (!used[i]) dfs1(i);
    }

    comp.assign(n, -1);
    for (int i = 0, j = 0; i < n; ++i) {
      int v = order[n - i - 1];
      if (comp[v] == -1) dfs2(v, j++);
    }

    assignment.assign(n / 2, false);
    for (int i = 0; i < n; i += 2) {
      if (comp[i] == comp[i + 1]) return false;
      assignment[i / 2] = comp[i] > comp[i + 1];
    }
    return true;
  }

  void dfs1(int v) {
    used[v] = true;
    for (int u : adj[v]) {
      if (!used[u]) dfs1(u);
    }
    order.push_back(v);
  }

  void dfs2(int v, int cl) {
    comp[v] = cl;
    for (int u : adj_t[v]) {
      if (comp[u] == -1) dfs2(u, cl);
    }
  }
};

#include "debug.h"
int main() {
    // Test 1: satisifiable formula (a|!b)&(!a|b)&(!a|!b)&(a|c).
    TwoSat ts1(3);
    ts1.AddDisjunction(false, 0, true, 1);
    ts1.AddDisjunction(true, 0, false, 1);
    ts1.AddDisjunction(true, 0, true, 1);
    ts1.AddDisjunction(false, 0, false, 2);
    // Solution: a=false,b=false,c=true.
    assert(ts1.Solve() == true);
    assert(ts1.assignment == vector<bool>({false, false, true}));

    // Test 2: satisifiable formula (a|a).
    TwoSat ts2(1);
    ts2.AddDisjunction(false, 0, false, 0);
    assert(ts2.Solve() == true);
    assert(ts2.assignment == vector<bool>({true}));

    // Test 3: not satisifiable formula (a|a)&(!a|!a)
    TwoSat ts3(1);
    ts3.AddDisjunction(false, 0, false, 0);
    ts3.AddDisjunction(true, 0, true, 0);
    assert(ts3.Solve() == false);
}
// Source: https://cp-algorithms.com/graph/2SAT.html
