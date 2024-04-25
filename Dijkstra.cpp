#include <bits/stdc++.h>
using namespace std;

const int64_t INF = 1000000000000000000;  // 10^18.
struct Graph {
  int n;
  vector<vector<pair<int, int64_t>>> adj;
  vector<int64_t> d;  // d[i] = min dist(s, i).
  vector<int> p;      // prev vertex in path.

  Graph(int n_) : n(n_), adj(n_){};

  void AddEdge(int x, int y, int64_t w) {
    assert(0 <= x && x < n);
    assert(0 <= y && y < n);
    assert(0 <= w && w < INF);
    adj[x].push_back({y, w});
    adj[y].push_back({x, w});
  }

  // s - start vertex. Complexity O (m*log(n)).
  void Dijkstra(int s) {
    d.assign(n, INF);
    p.assign(n, -1);
    d[s] = 0;
    priority_queue<pair<int64_t, int>> q;
    q.push({0, s});
    while (!q.empty()) {
      int64_t sd = -q.top().first;
      int v = q.top().second;
      q.pop();
      if (sd != d[v]) {
        continue;
      }
      for (const auto& edge : adj[v]) {
        int to = edge.first;
        int64_t new_d = d[v] + edge.second;
        if (new_d < d[to]) {
          d[to] = new_d;
          p[to] = v;
          q.push({-d[to], to});
        }
      }
    }
  }
};

int main() {
  Graph g(5);
  g.AddEdge(0, 1, 1);
  g.AddEdge(1, 3, 2);
  g.AddEdge(0, 2, 4);
  g.AddEdge(2, 3, 8);
  g.AddEdge(0, 3, 16);
  g.AddEdge(3, 4, 32);

  g.Dijkstra(0);
  assert(g.d == (vector<int64_t>{0, 1, 4, 3, 35}));
  assert(g.p == (vector<int>{-1, 0, 0, 1, 3}));
  g.Dijkstra(3);
  assert(g.d == (vector<int64_t>{3, 2, 7, 0, 32}));
  assert(g.p == (vector<int>{1, 3, 0, -1, 3}));

  Graph g2(3);
  g2.AddEdge(0, 1, INF - 5);
  g2.AddEdge(1, 2, 3);
  g2.Dijkstra(0);
  assert(g2.d == (vector<int64_t>{0, INF - 5, INF - 2}));
  assert(g2.p == (vector<int>{-1, 0, 1}));
}