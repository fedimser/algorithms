#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>

struct Edge {
  int from, to;
  int capacity;

  int capacity_cur;
  int flow;

  bool CanGo() { return flow < capacity_cur; }

  int ResidualCapacity() { return capacity_cur - flow; }
};

class Graph {
private:
  int vertex_count_;
  int edges_count_;
  std::vector<std::vector<int>> adj_list_;
  std::vector<Edge> edges_;

  std::vector<int> bfs_level_;
  std::vector<int> dfs_next_edge_;

  void AddEdgeInternal(int from, int to, int capacity) {
    Edge edge;
    edge.from = from;
    edge.to = to;
    edge.capacity = capacity;
    adj_list_[from].push_back(edges_.size());
    edges_.push_back(edge);
    edges_count_ = edges_.size();
  }

  bool DinicBfs() {
    bfs_level_.assign(vertex_count_, -1);
    std::queue<int> bfs_queue;
    bfs_queue.push(0);
    bfs_level_[0] = 0;

    while (!bfs_queue.empty() && bfs_level_[1] == -1) {
      int vx = bfs_queue.front();
      bfs_queue.pop();
      for (int edge_id : adj_list_[vx]) {
        int to = edges_[edge_id].to;
        if (edges_[edge_id].CanGo() && bfs_level_[to] == -1) {
          bfs_queue.push(to);
          bfs_level_[to] = bfs_level_[vx] + 1;
        }
      }
    }

    return (bfs_level_[1] != -1);
  }

  int DinicDfs(int vx, int flow) {
    if (flow == 0) {
      return 0;
    }
    if (vx == 1) {
      return flow;
    }

    int edges_count = adj_list_[vx].size();
    for (; dfs_next_edge_[vx] < edges_count; ++dfs_next_edge_[vx]) {
      int edge_id = adj_list_[vx][dfs_next_edge_[vx]];
      int to = edges_[edge_id].to;
      if (bfs_level_[to] == bfs_level_[vx] + 1 && edges_[edge_id].CanGo()) {
        int pushed =
            DinicDfs(to, std::min(flow, edges_[edge_id].ResidualCapacity()));
        if (pushed) {
          edges_[edge_id].flow += pushed;
          edges_[edge_id ^ 1].flow -= pushed;
          return pushed;
        }
      }
    }

    bfs_level_[vx] = -1;
    return false;
  }

  // Updates flow to maximal possible with capacities capacity_cur.
  void DinicFlow() {
    while (DinicBfs()) {
      dfs_next_edge_.assign(vertex_count_, 0);
      while (DinicDfs(0, INT_MAX)) {
      }
    }
  }

  int GetFlowSize() {
    int flow_size = 0;
    for (int edge_id : adj_list_[0]) {
      flow_size += edges_[edge_id].flow;
    }
    return flow_size;
  }

public:
  explicit Graph(int vertex_count) {
    vertex_count_ = vertex_count;
    edges_count_ = 0;
    adj_list_.resize(vertex_count_);
  }

  void AddEdge(int from, int to, int capacity_forward, int capacity_back) {
    AddEdgeInternal(from, to, capacity_forward);
    AddEdgeInternal(to, from, capacity_back);
  }

  int MaxFlow() {
    for (Edge &edge : edges_) {
      edge.capacity_cur = edge.capacity;
      edge.flow = 0;
    }

    DinicFlow();

    return GetFlowSize();
  }

  int MaxFlowWithScaling() {
    int mask = 1;
    for (Edge &edge : edges_) {
      while (mask < edge.capacity) {
        mask *= 2;
      }
      edge.flow = 0;
    }

    // Dinic with capacity scaling.
    while (mask != 0) {
      for (Edge &edge : edges_) {
        edge.flow *= 2;
        edge.capacity_cur = edge.capacity / mask;
      }
      DinicFlow();
      mask /= 2;
    }
    return GetFlowSize();
  }

  std::vector<std::pair<int, int>> GetCut() {
    assert(!DinicBfs());

    std::vector<std::pair<int, int>> ans;
    for (const Edge &edge : edges_) {
      if (bfs_level_[edge.from] != -1 && bfs_level_[edge.to] == -1 &&
          edge.flow > 0) {
        ans.push_back(std::make_pair(edge.from, edge.to));
      }
    }
    return ans;
  }
};

int main() {
  Graph gr(4);
  gr.AddEdge(0, 2, 2, 0);
  gr.AddEdge(0, 3, 3, 0);
  gr.AddEdge(2, 1, 3, 0);
  gr.AddEdge(3, 1, 2, 0);
  assert(gr.MaxFlow() == 4);
  return 0;
}
