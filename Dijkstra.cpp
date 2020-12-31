#include <bits/stdc++.h>
using namespace std;

const int64_t INF = 1000000000;
struct Graph {
  int n;
  vector<vector<pair<int, int64_t>>> adj;
  vector<int64_t> d; // d[i] = min dist(s, i).
  vector<int> p; // prev vertex in path.
  
  Graph(int n_) {
  	n = n_;
  	adj.resize(n);
  }
  
  void addEdge(int x, int y, int64_t w) {
    assert(x>=0 && x<n && y>=0 && y<n && w<INF);
    adj[x].push_back({y, w});
    adj[y].push_back({x, w});
  }

  // s - start vertex. Complexity O (m*log(n)).
  void dijkstra(int s) {
    d.assign(n, INF);
    p.assign(n, -1);
	d[s] = 0;
	set<pair<int64_t, int>> q;
	q.insert({0, s});
	while (!q.empty()) {
	  int v = q.begin()->second;
	  q.erase(q.begin());
	  for (auto edge : adj[v]) {
	    int to = edge.first;
	    int len = edge.second;
        if (d[v] + len < d[to]) {
	      q.erase({d[to], to});
	      d[to] = d[v] + len; 
	      p[to] = v;
	      q.insert({d[to], to});
	    }
	  }
    }
  }
};

int main() {
    Graph g(5);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 3, 2);
    g.addEdge(0, 2, 4);
    g.addEdge(2, 3, 8);
    g.addEdge(0, 3, 16);
    g.addEdge(3, 4, 32);

    g.dijkstra(0);
    assert(g.d == (vector<int64_t> {0, 1, 4, 3, 35}));
    assert(g.p == (vector<int> {-1, 0, 0, 1, 3}));
    g.dijkstra(3);
    assert(g.d == (vector<int64_t> {3, 2, 7, 0, 32}));
    assert(g.p == (vector<int> {1, 3, 0, -1, 3}));
}