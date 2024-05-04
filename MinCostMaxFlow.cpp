#include <bits/stdc++.h>
using namespace std;
// Source: https://cp-algorithms.com/graph/min_cost_flow.html

const int INF = 1e9;
struct Edge {
  int from, to, capacity, cost;
};

struct Graph {
  int N;
  vector<Edge> edges;
  vector<vector<int>> adj, cost, capacity;

  Graph(int N_) : N(N_){};

  // Cost is PER UNIT OF FLOW!
  void AddEdge(int from, int to, int capacity, int cost) {
    assert(0 <= from && from < N && 0 <= to && to < N);
    edges.push_back(Edge{from, to, capacity, cost});
  }

  void ShortestPaths(int n, int v0, vector<int>& d, vector<int>& p) {
    d.assign(n, INF);
    d[v0] = 0;
    vector<bool> inq(n, false);
    queue<int> q;
    q.push(v0);
    p.assign(n, -1);

    while (!q.empty()) {
      int u = q.front();
      q.pop();
      inq[u] = false;
      for (int v : adj[u]) {
        if (capacity[u][v] > 0 && d[v] > d[u] + cost[u][v]) {
          d[v] = d[u] + cost[u][v];
          p[v] = u;
          if (!inq[v]) {
            inq[v] = true;
            q.push(v);
          }
        }
      }
    }
  }

  // Finds max flow s->t with flow <=K, of those - flow with min cost.
  // If K=INF, finds minimum-cost maximum-flow.
  // Returns (flow, cost).
  pair<int, int> MinCostFlow(int K, int s, int t) {
    assert(0 <= s && s < N && 0 <= t && t < N);
    adj.assign(N, vector<int>());
    cost.assign(N, vector<int>(N, 0));
    capacity.assign(N, vector<int>(N, 0));
    for (Edge e : edges) {
      adj[e.from].push_back(e.to);
      adj[e.to].push_back(e.from);
      cost[e.from][e.to] = e.cost;
      cost[e.to][e.from] = -e.cost;
      capacity[e.from][e.to] = e.capacity;
    }

    int flow = 0;
    int cost = 0;
    vector<int> d, p;
    while (flow < K) {
      ShortestPaths(N, s, d, p);
      if (d[t] == INF) break;

      // Find max flow on that path.
      int f = K - flow;
      int cur = t;
      while (cur != s) {
        f = min(f, capacity[p[cur]][cur]);
        cur = p[cur];
      }

      // Apply flow.
      flow += f;
      cost += f * d[t];
      cur = t;
      while (cur != s) {
        capacity[p[cur]][cur] -= f;
        capacity[cur][p[cur]] += f;
        cur = p[cur];
      }
    }

    return make_pair(flow, cost);
  }
};

int main() {
  Graph gr(4);
  gr.AddEdge(0, 1, 2, 0);
  gr.AddEdge(1, 2, 3, 1);
  gr.AddEdge(0, 2, 6, 100);
  gr.AddEdge(0, 3, 3, 0);
  gr.AddEdge(3, 2, 2, 10);

  assert(gr.MinCostFlow(0, 0, 2) == make_pair(0, 0));
  assert(gr.MinCostFlow(2, 0, 2) == make_pair(2, 2));
  assert(gr.MinCostFlow(5, 0, 2) == make_pair(5, 122));
  assert(gr.MinCostFlow(INF, 0, 2) == make_pair(10, 622));  
  return 0;
}
