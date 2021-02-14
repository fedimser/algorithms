#include <bits/stdc++.h>
using namespace std;

/*
This is universal version of Segment Tree which supports:
  - Adding on range.
  - Setting on range.
  - Querying sum on range.
  - Querying max on range.
*/

class SegmentTree {
 private:
  vector<int64_t> tree_sum; // Sum on segment.
  vector<int64_t> tree_max; // Max on segment.
  vector<char> upd_type;    // Update type: 0-none,1-set,2-add.
  vector<int64_t> upd_val;
  int N;

  inline void pushUpdSet(int tv, int64_t val) {
    upd_type[tv]=1;upd_val[tv] = val;
  }
  inline void pushUpdAdd(int tv, int64_t val) {
    if(upd_type[tv]==0){upd_type[tv]=2;upd_val[tv]=val;}
    else upd_val[tv]+=val;
  }
  inline void pushData(int tv, int tl, int tr) {
    if (upd_type[tv] == 0) return;
    int tm = (tl+tr)/2;
    if (upd_type[tv] == 1) {
        tree_sum[2*tv]=(tm-tl)*upd_val[tv];
        tree_sum[2*tv+1]=(tr-tm)*upd_val[tv];
        tree_max[2*tv]=tree_max[2*tv+1]=upd_val[tv];
        pushUpdSet(2*tv, upd_val[tv]);
        pushUpdSet(2*tv+1, upd_val[tv]);
    } else {
        tree_sum[2*tv]+=(tm-tl)*upd_val[tv];
        tree_sum[2*tv+1]+=(tr-tm)*upd_val[tv];
        tree_max[2*tv]+=upd_val[tv];
        tree_max[2*tv+1]+=upd_val[tv];
        pushUpdAdd(2*tv, upd_val[tv]);
        pushUpdAdd(2*tv+1, upd_val[tv]);
    }
    upd_type[tv]=0;
  }
  void updRange(int tv, int tl, int tr, int l, int r, char type, int64_t val) {
    l = max(l, tl);
    r = min(r, tr);
    if (l >= r) return;
    if (l == tl && r == tr) {
      if (type==1) {
        pushUpdSet(tv, val);
        tree_sum[tv] = (r-l)*val;
        tree_max[tv] = val;
      } else {
        pushUpdAdd(tv, val);
        tree_sum[tv] += (r-l)*val;
        tree_max[tv] += val;
      }
      return;
    }
    pushData(tv, tl, tr);
    int tm = (tl + tr) / 2;
    updRange(2 * tv, tl, tm, l, r, type, val);
    updRange(2 * tv + 1, tm, tr, l, r, type, val);
    tree_sum[tv] = tree_sum[2*tv] + tree_sum[2*tv+1];
    tree_max[tv] = max(tree_max[2*tv], tree_max[2*tv+1]);
  }
  int64_t getSum(int tv, int tl, int tr, int l, int r) {
    l = max(l, tl);
    r = min(r, tr);
    if (l >= r) return 0;
    if (l == tl && r == tr) return tree_sum[tv];
    pushData(tv, tl, tr);
    int tm = (tl + tr) / 2;
    return getSum(2 * tv, tl, tm, l, r) + getSum(2 * tv + 1, tm, tr, l, r);
  }
  int64_t getMax(int tv, int tl, int tr, int l, int r) {
    l = max(l, tl);
    r = min(r, tr);
    if (l >= r) return LLONG_MIN;
    if (l == tl && r == tr) return tree_max[tv];
    pushData(tv, tl, tr);
    int tm = (tl + tr) / 2;
    return max(getMax(2 * tv, tl, tm, l, r), getMax(2 * tv + 1, tm, tr, l, r));
  }
  void init(int n) {
    N = n;int sz=1; while(sz<2*N)sz<<=1;
    tree_sum.resize(sz); tree_max.resize(sz);
    upd_type.assign(sz, 0); upd_val.assign(sz, 0);
  }
  void build(int tv, int tl, int tr, const vector<int64_t>& data) {
    if (tl >= tr) return;
    if (tl + 1 == tr) {tree_sum[tv] = tree_max[tv] = data[tl]; return;}
    int tm = (tl + tr) / 2;
    build(2*tv, tl, tm, data);
    build(2*tv+1, tm, tr, data);
    tree_sum[tv] = tree_sum[2*tv] + tree_sum[2*tv+1];
    tree_max[tv] = max(tree_max[2*tv], tree_max[2*tv+1]);
  }
 public:
  SegmentTree() {}
  SegmentTree(int N) {init(N);}
  SegmentTree(const vector<int64_t>& data_) {
    init(data_.size());
    if (N > 0) build(1, 0, N, data_);
  }
  int64_t getSum(int l, int r) { return getSum(1, 0, N, l, r); }
  int64_t getMax(int l, int r) { return getMax(1, 0, N, l, r); }
  int64_t get(int i) { return getSum(i, i+1); }
  void setRange(int l, int r, int val) { updRange(1, 0, N, l, r, 1, val); }
  void addRange(int l, int r, int delta) { updRange(1, 0, N, l, r, 2, delta); }
  void set(int pos, int val) { updRange(1, 0, N, pos, pos+1, 1, val); }
};


// Testing code starts here.
struct Mock {
  vector<int64_t> a;
  Mock(const vector<int64_t>& data_) : a(data_) {}
  int64_t getSum(int l, int r) { int64_t ans=0; for(int i=l;i<r;i++) ans+= a[i]; return ans; }
  int64_t getMax(int l, int r) { int64_t ans=LLONG_MIN; for(int i=l;i<r;i++) ans = max(ans, a[i]); return ans; }
  int64_t get(int pos) { return a[pos]; }
  void setRange(int l, int r, int val) { for(int i=l;i<r;i++) a[i] = val; }
  void addRange(int l, int r, int delta) { for(int i=l;i<r;i++) a[i] += delta; }
  void set(int pos, int val) { a[pos] = val; }
};

void test(int N) {
    vector<int64_t> data(N);
    for(int i=0;i<N;i++) data[i] = rand();
    SegmentTree st(data);
    Mock mock(data);
    for(int i=0; i < N; i++) {
        assert(st.get(i) == data[i]);
    }

    for(int i=0;i<1000;i++) {
        int l = rand() % (N);
        int r = l + rand() % (N - l + 1);
        assert(0<=l && l<N && l<=r && r<=N);
        int val = rand();
        int mode = rand() % 6;
        if (mode == 0) {
          assert(st.getSum(l, r) == mock.getSum(l, r));
        } else if (mode == 1) {
          assert(st.getMax(l, r) == mock.getMax(l, r));
        } else if (mode == 2) {
          assert(st.get(l) == mock.get(l));
        } else if (mode == 3) {
            st.setRange(l, r, val);
            mock.setRange(l, r, val);
        } else if (mode == 4) {
            st.addRange(l, r, val);
            mock.addRange(l, r, val);
        } else if (mode == 5) {
            st.set(l, val);
            mock.set(l, val);
        }
    }
}

int main() {
  test(1);
  test(2);
  test(10);
  test(100);
  test(127);
  test(128);
  test(129);
  test(500);

  return 0;
}
