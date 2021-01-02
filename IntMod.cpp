#include <bits/stdc++.h>
using namespace std;

int64_t MOD = 1000000007;
struct IntMod {
  int64_t v;
  IntMod(int64_t v_) {v=v_%MOD;if(v<0)v+=MOD;}
  inline IntMod operator + (const IntMod& y) const {return {(v+y.v)%MOD};}
  inline IntMod operator - (const IntMod& y) const {return {(v-y.v+MOD)%MOD};}
  inline IntMod operator * (const IntMod& y) const {return {(v*y.v)%MOD};}
  inline IntMod pow(int64_t y) const {IntMod a(1),m(v);while(y!=0){if(y&1){a=a*m;}m=m*m;y>>=1;}return a;}
  bool operator==(const IntMod& y){return v==y.v;}
};
inline IntMod operator / (const IntMod& x, const IntMod& y) {return x * y.pow(MOD-2);}
ostream& operator<<(ostream& os, const IntMod& x){return os<<x.v;}

int main() {
    IntMod a = 10;
    IntMod b = 50;
    assert(a+b == IntMod(60));
    assert(a-b == IntMod(-40));
    assert(a*b == IntMod(500));
    assert(a/b == IntMod(400000003));
    assert(a/b == 1/IntMod(5));
    assert(a/b*b == a);

    assert(IntMod(2).pow(1000010) / IntMod(2).pow(1000000) == 1024);

    std::stringstream ss;
    ss << IntMod(1234);
    string s;
    ss >> s;
    assert(s == "1234");

    return 0;
}