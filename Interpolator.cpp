#include <bits/stdc++.h>
using namespace std;



template <typename T>
struct Poly {
  vector<T> a;
  Poly() : a({0}) {}
  Poly(const Poly<T>& other) : a(other.a) {}
  Poly(const vector<T>& a_) : a(a_) {if(a.empty())a.push_back(0);normalize();}
  inline void operator += (const Poly<T>& other) {
    int n = min(a.size(), other.a.size());
    for(int i=0;i<n;i++) {a[i]+=other.a[i];}
    for(int i=n;i<other.a.size();i++)a.push_back(other.a[i]);
    normalize();
  }
  inline void operator *= (const T& y) {for(T& x: a)x *= y;}
  inline Poly<T> operator * (const T& y) const {Poly<T> ans(a);ans*=y; return ans;}
  inline Poly<T> operator + (const T& y) const {Poly<T> ans(a);ans*=y; return ans;}
  bool operator == (const Poly<T>& other){
    if(other.a.size()!=a.size())return false;
    for(int i=0;i<a.size();i++)if(a[i]!=other.a[i])return false;
    return true;
  }

  // Multiply by (x-x0).
  inline void MultByBinomial(T x0) {int d=deg();a.push_back(a[d]);for(int i=d;i>=1;i--)a[i]=a[i-1]-x0*a[i];a[0]*=(x0*-1);}
  inline int deg() const {return a.size()-1;}
  inline T eval(T x) const {T ans = a[0],xi=x;for(int i=1;i<a.size();i++){ans+=(xi*a[i]);xi*=x;}return ans;}
  void normalize(){while(a.size()>1 && a[a.size()-1]==0)a.pop_back();}
};
template <typename T> ostream& operator<<(ostream& os, const Poly<T>& x){os<<"[";for(const T& k:x.a)os<<k<<" ";os<<"]"; return os;}


template <typename T>
struct Interpolator { // Uses Newton Polynomials.
  vector<T> x,a;
  Poly<T> basis=vector<T>(1,T(1)), result=vector<T>(0);
  void Add(T xk, T yk) {
    x.push_back(xk);
    int k = a.size();
    vector<T> a1(k+1);
    a1[0]=yk;
    for(int i=1;i<=k;i++)a1[i]=(a1[i-1]-a[i-1])/(xk-x[k-i]);
    a=a1;
    result += (basis*a[k]);
    basis.MultByBinomial(xk);
  }
};



int main() {
  Interpolator<double> ip;
  ip.Add(0,1);
  assert(ip.result == Poly<double>({1}));
  ip.Add(2,129);
  assert(ip.result == Poly<double>({1, 64}));
  ip.Add(3,547);
  ip.Add(4,1593);
  ip.Add(6,7465);
  ip.Add(10,54321);
  assert(ip.result == Poly<double>({1,2,3,4,5}));
  ip.Add(11,78915);
  assert(ip.result == Poly<double>({1,2,3,4,5}));

  return 0;
}