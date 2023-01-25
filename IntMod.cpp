#include <bits/stdc++.h>
using namespace std;

int64_t MOD = 1000000007;
struct IntMod {
  int64_t v;
  IntMod() : v(0) {}
  IntMod(int64_t v_) : v(v_) {if((uint64_t)v>=(uint64_t)MOD){v%=MOD;if(v<0)v+=MOD;}}
  IntMod(const IntMod& v_) : v(v_.v) {}
  inline IntMod operator + (const IntMod& y) const {IntMod a(*this); a+=y; return a;}
  inline IntMod operator - (const IntMod& y) const {IntMod a(*this); a-=y; return a;}
  inline IntMod operator * (const IntMod& y) const {return {v*y.v};}
  inline IntMod pow(int64_t y) const {IntMod a(1),m(v);while(y!=0){if(y&1){a=a*m;}m=m*m;y>>=1;}return a;}
  inline IntMod inverse() const {
    int64_t g=MOD,r=v,x=0,y=1;
    while(r!=0){int64_t q=g/r;g%=r;swap(g,r);x-=q*y;swap(x,y);}
    return IntMod(x+(x<0)*MOD);
  }
  bool operator == (const IntMod& y) const {return v==y.v;}
  bool operator != (const IntMod& y) const {return v!=y.v;}
  inline void operator += (const IntMod& y) {(v+=y.v)>=MOD && (v-=MOD);}
  inline void operator -= (const IntMod& y) {(v-=y.v)<0 && (v+=MOD);}
  inline void operator *= (const IntMod& y) {v*=y.v; v%=MOD;}
};
inline IntMod operator / (const IntMod& x, const IntMod& y) {return x * y.inverse();}
ostream& operator<<(ostream& os, const IntMod& x){return os<<x.v;}

struct BinCoefs {
  vector<IntMod> fact_,inv_,inv_fact_;
  BinCoefs(int N) {
    fact_.resize(N+1);inv_.resize(N+1);inv_fact_.resize(N+1);
    fact_[0]=inv_fact_[0]=fact_[1]=inv_[1]=inv_fact_[1]=1;
    for(int i=2;i<=N;i++){fact_[i]=fact_[i-1]*i;inv_[i]=inv_[MOD%i]*IntMod(MOD - MOD/i);inv_fact_[i] = inv_fact_[i-1]*inv_[i];}
  }
  inline IntMod fact(int n) {return fact_[n];}
  inline IntMod inv(int n) {return inv_[n];}
  inline IntMod inv_fact(int n) {return inv_fact_[n];}
  inline IntMod C(int n, int m) {if(m<0 || m > n) return 0;return fact_[n] * inv_fact_[m] * inv_fact_[n-m];}
};
BinCoefs BC(100007);

struct Pow2 {
  vector<int> p;
  Pow2(int N){p.resize(N+1);p[0]=1;for(int i=1;i<=N;i++){p[i]=p[i-1]<<1;if(p[i]>MOD)p[i]-=MOD;}}
  IntMod operator()(int n) {return IntMod(p[n]);}
};
Pow2 P2(100007);

// Fits P(i)=y_i (i=0..N). Returns f(x). Complexity O(n).
IntMod LagrangeInterpolation(vector<IntMod> y, IntMod x){
  int N = y.size()-1;assert(N<=BC.fact_.size()-1);
  vector<IntMod> L(N+1,1), R(N+1,1);
  for(int i=0;i<N;i++)L[i+1]=L[i]*(x-i);
  for(int i=N;i>0;i--)R[i-1]=R[i]*(x-i);
  IntMod ans=0;
  for(int i=0;i<=N;i++){IntMod t=y[i]*L[i]*R[i]*BC.inv_fact(i)*BC.inv_fact(N-i);if ((N-i)%2==0) ans+=t; else ans-=t;}
  return ans;
}


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
    assert(!(a!=999999937));
    assert(a!=5);

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

    assert(P2(10) == 1024);
    assert(P2(12345) == IntMod(2).pow(12345));

    assert(LagrangeInterpolation({0,1,4}, 25) == 625);

    return 0;
}
