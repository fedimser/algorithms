#include <bits/stdc++.h>
using namespace std;

template<class T>
struct FenwickTree {
    vector<T> bit;int n;
    FenwickTree(int n) {this->n=n;bit.assign(n, 0);}
    FenwickTree(vector<T> a) : FenwickTree(a.size()) {for (size_t i = 0; i < a.size(); i++)add(i, a[i]);}
    T sum__(int r) {T ret = 0;for (;r>=0;r=(r&(r+1))-1)ret+=bit[r];return ret;}
    T sum(int l, int r) {  // [l,r)
      assert(0<=l && l<=r && r<=n);
      return sum__(r-1) - (l==0?0:sum__(l-1));
    }
    void add(int idx, T delta) {for (; idx < n; idx = idx | (idx + 1))bit[idx] += delta;}
};

int main() {
    FenwickTree<int> ft(100);
    assert(ft.sum(0,100)==0);

    ft.add(0, 1);
    ft.add(1, 100);ft.add(1, -98);
    ft.add(2, 4);
    assert(ft.sum(0,1)==1);
    assert(ft.sum(1,2)==2);
    assert(ft.sum(2,3)==4);
    assert(ft.sum(0,2)==3);
    assert(ft.sum(1,3)==6);
    assert(ft.sum(0,3)==7);

    ft.add(10, 12);
    ft.add(20, 15);
    assert(ft.sum(10,20)==12);
    assert(ft.sum(10,21)==27);

    ft.add(99, 1000);
    assert(ft.sum(0,99)==34);
    assert(ft.sum(0,100)==1034);

    return 0;
}