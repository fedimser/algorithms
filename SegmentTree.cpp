#include <bits/stdc++.h>
using namespace std;

template <class T>
class SegmentTree {
 private:
  vector<T> tree;
  vector<T> data;
  int N;

  inline T OP(T x, T y) { return x + y; }

  T count_sum(int tv, int tl, int tr, int l, int r) {
    l = max(l, tl);
    r = min(r, tr);
    if (l >= r) return T();
    if (l == tl && r == tr) return tree[tv];
    int tm = (tl + tr) / 2;
    return OP(count_sum(2 * tv, tl, tm, l, r),
              count_sum(2 * tv + 1, tm, tr, l, r));
  }

  void update_value(int tv, int tl, int tr, int idx, T new_val) {
    if (tl >= tr) return;
    if (tl == idx && tr == idx + 1) {
      tree[tv] = new_val;
      return;
    }
    int tm = (tl + tr) / 2;
    if (idx < tm)
      update_value(2 * tv, tl, tm, idx, new_val);
    else
      update_value(2 * tv + 1, tm, tr, idx, new_val);
    tree[tv] = OP(tree[2 * tv], tree[2 * tv + 1]);
  }

  T build(int tv, int tl, int tr) {
    if (tl >= tr) return T();
    if (tl + 1 == tr) return tree[tv] = data[tl];
    int tm = (tl + tr) / 2;
    return tree[tv] = OP(build(2 * tv, tl, tm), build(2 * tv + 1, tm, tr));
  }

 public:
  SegmentTree() : SegmentTree(vector<T>()) {}
  SegmentTree(int n) : SegmentTree(vector<T>(n)) {}
  SegmentTree(vector<T> data_) {
    data = data_;
    N = data.size();
    tree = vector<T>(4 * N);
    if (N > 0) build(1, 0, N);
  }

  void set(int idx, T new_value) {
    data[idx] = new_value;
    update_value(1, 0, N, idx, new_value);
  }

  T get(int idx) { return data[idx]; }

  // Counts sum [l, r).
  T sum(int l, int r) { return count_sum(1, 0, N, max(0, l), min(N, r)); }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  SegmentTree<int> st= SegmentTree<int>(vector<int>({0,1,2,3,4,5,6}));
  assert(st.sum(1, 6) == 15);

  return 0;
}
