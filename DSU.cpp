#include <bits/stdc++.h>

class DSU {
	std::vector<int> p;
public:
	DSU() {}
	DSU(int n): p(n){std::iota(p.begin(),p.end(),0);}	
	int Get(int v){if(v==p[v])return v;return p[v]=Get(p[v]);}
	void Union(int a, int b){a=Get(a);b=Get(b);if(a==b)return;if(rand()%2){p[b]=a;}else{p[a]=b;}}
  int operator[](int i){return Get(i);}
};

int main() {
  DSU dsu(1000);
  assert(dsu[0]==0);
  assert(dsu[999]==999);
  dsu.Union(1, 2);
  dsu.Union(20, 25);
  dsu.Union(40, 45);
  dsu.Union(2, 40);
  assert(dsu[1]!=dsu[25]);
  dsu.Union(45, 25);
  assert(dsu[1]==dsu[25]);
  return 0;
}
