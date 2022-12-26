#include <bits/stdc++.h>
using namespace std;

int64_t MOD = 1000000007;
struct IntMod {
  int64_t v;
  IntMod() : v(0) {}
  IntMod(int64_t v_) : v(v_%MOD) {if(v<0)v+=MOD;}
  IntMod(const IntMod& v_) : v(v_.v) {} 
  inline IntMod operator + (const IntMod& y) const {IntMod a(*this); a+=y; return a;}
  inline IntMod operator - (const IntMod& y) const {IntMod a(*this); a-=y; return a;}
  inline IntMod operator * (const IntMod& y) const {return {(v*y.v)%MOD};}
  inline IntMod pow(int64_t y) const {IntMod a(1),m(v);while(y!=0){if(y&1){a=a*m;}m=m*m;y>>=1;}return a;}
  inline IntMod inverse() const {return pow(MOD-2);}
  bool operator == (const IntMod& y){return v==y.v;}
  inline void operator += (const IntMod& y) {(v+=y.v)>=MOD && (v-=MOD);}
  inline void operator -= (const IntMod& y) {(v-=y.v)<0 && (v+=MOD);} 
  inline void operator *= (const IntMod& y) {v*=y.v; v%=MOD;}
};
inline IntMod operator / (const IntMod& x, const IntMod& y) {return x * y.inverse();}
ostream& operator<<(ostream& os, const IntMod& x){return os<<x.v;}

struct BinCoefs {
  vector<IntMod> facts,inv_facts;
  BinCoefs(int max_n) {facts = vector<IntMod>(max_n+1);inv_facts = vector<IntMod>(max_n+1);facts[0]=inv_facts[0]=1;for(int i=1;i<=max_n;i++){facts[i] = facts[i-1] * i;inv_facts[i] = facts[i].inverse();}}
  IntMod C(int n, int m) {if(m<0 || m > n) return 0;return facts[n] * inv_facts[m] * inv_facts[n-m];}
  IntMod fact(int n) {return facts[n];}
};
BinCoefs BC(100);


int main() {  
    IntMod a = 10;
    IntMod b = 50;
    assert(a+b == IntMod(60));
    assert(a-b == IntMod(-40));
    assert(a*b == IntMod(500));
    assert(a/b == IntMod(400000003));
    assert(a/b == 1/IntMod(5));
    assert(a/b*b == a);

    assert(a.inverse() == IntMod(700000005));
    assert(b.inverse() == IntMod(140000001));
    assert(a.inverse().inverse() == a);

    assert(IntMod(2).pow(1000010) / IntMod(2).pow(1000000) == 1024);

    a = IntMod(-2);
    a += IntMod(4);
    assert(a==2);
    a += IntMod(MOD-5);
    assert(a==-3);
    a -= IntMod(97);
    assert(a==-100);
    a*=-1;
    assert(a==100);
    a*=100000000;
    assert(a==999999937);

    std::stringstream ss;
    ss << IntMod(1234);
    string s;
    ss >> s;
    assert(s == "1234");

    assert(BC.C(10,0) == 1);
    assert(BC.C(10,1) == 10);
    assert(BC.C(10,3) == 120);
    assert(BC.C(10,5) == 252);
    assert(BC.C(10,11) == 0);
    assert(BC.C(100,40) == 213157642);
    assert(BC.C(100,40) == 213157642);
    assert(BC.fact(0) == 1);
    assert(BC.fact(5) == 120);
    assert(BC.fact(100) == 437918130);

    return 0;
}
