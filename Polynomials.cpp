#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct Poly {
  vector<T> a;
  Poly() : a({0}) {}
  Poly(T a0) : a({a0}) {}
  Poly(const Poly<T>& other) : a(other.a) {}
  Poly(const initializer_list<T>& a) : a(vector<T>(a)) {}
  Poly(const vector<T>& a_) : a(a_) {if(a.empty())a.push_back(0);normalize();}
  inline T coef(size_t i) {return i>=a.size() ? 0 : a[i];}
  inline void operator += (const Poly<T>& other) {
    int n = min(a.size(), other.a.size());
    for(int i=0;i<n;i++) {a[i]+=other.a[i];}
    for(int i=n;i<other.a.size();i++)a.push_back(other.a[i]);
    normalize();
  }
  inline Poly<T> operator + (const Poly<T>& y) const {Poly<T> ans(a);ans+=y; return ans;}
  inline void operator *= (const T& y) {for(T& x: a)x *= y;}
  inline Poly<T> operator * (const T& y) const {Poly<T> ans(a);ans*=y; return ans;}
  bool operator == (const Poly<T>& other){
    if(other.a.size()!=a.size())return false;
    for(int i=0;i<a.size();i++)if(a[i]!=other.a[i])return false;
    return true;
  }
  // Multiply by (x-x0).
  inline void MultByBinomial(T x0) {int d=deg();a.push_back(a[d]);for(int i=d;i>=1;i--)a[i]=a[i-1]-x0*a[i];a[0]*=(x0*-1);}
  // Multiply by x^p.
  inline void ShiftLeft(int p) {
	  if(p==0 || (a.size()==1 && a[0]==0))return;
	  reverse(a.begin(), a.end());a.resize(a.size()+p);reverse(a.begin(), a.end());
  }
  // Adds delta * x^i.
  void AddCoef(int i, T delta) {while(deg()<i)a.push_back(0);a[i]+=delta;normalize();}
  inline int deg() const {return a.size()-1;}
  inline T eval(T x) const {T ans = a[0],xi=x;for(int i=1;i<a.size();i++){ans+=(xi*a[i]);xi*=x;}return ans;}
  void normalize(){while(a.size()>1 && a[a.size()-1]==0)a.pop_back();}
};
template <typename T> Poly<T> operator*(const T& x, const Poly<T>& y){return y*x;}
template <typename T> ostream& operator<<(ostream& os, const Poly<T>& x){
  int d = x.deg();os<<x.a[d]<<"x^"<<d;
  for(int i=d-1;i>=1;i--){if(x.a[i]!=0){os<<"+"<<x.a[i]<<"x^"<<i;}}if(x.a[0]!=0)os<<"+"<<x.a[0];return os;
}

template <typename T>
struct Interpolator { // Uses Newton Polynomials.
  vector<T> x,a;
  Poly<T> basis=vector<T>(1,T(1)), res=vector<T>(0);
  void Add(T xk, T yk) {
    x.push_back(xk);
    int k = a.size();
    vector<T> a1(k+1);
    a1[0]=yk;
    for(int i=1;i<=k;i++)a1[i]=(a1[i-1]-a[i-1])/(xk-x[k-i]);
    a=a1;
    res += (basis*a[k]);
    basis.MultByBinomial(xk);
  }
  Poly<T> result() {return res;}
};



int main() {
  // Test polynomial operations.
  Poly<int> p = {1,2,3};  
  p.ShiftLeft(2);
  assert(p == Poly<int>({0,0,1,2,3}));
  p.AddCoef(10, 2);
  assert(p == Poly<int>({0,0,1,2,3,0,0,0,0,0,2})); 
  p.MultByBinomial(-1);
  assert(p == Poly<int>({0,0,1,3,5,3,0,0,0,0,2,2}));
  Poly<int> p1 = {1,2};  
  Poly<int> p2 = {1,2,3};   
  assert(p1+p1 == Poly<int>({2,4}));
  assert(p1+p2 == Poly<int>({2,4,3}));
  assert(p2*10 == Poly<int>({10,20,30}));
  assert(10*p2 == Poly<int>({10,20,30}));
  stringstream ss;ss<<p2;string s; ss >> s;
  assert(s == "3x^2+2x^1+1");

  p2.ShiftLeft(2);
  assert(p2 == Poly<int>({0,0,1,2,3}));

  // Test interpolation.
  Interpolator<double> ip;
  ip.Add(0,1);
  assert(ip.result() == Poly<double>({1.0}));
  ip.Add(2,129);
  assert(ip.result() == Poly<double>({1, 64}));
  ip.Add(3,547);
  ip.Add(4,1593);
  ip.Add(6,7465);
  ip.Add(10,54321);
  assert(ip.result() == Poly<double>({1,2,3,4,5}));
  ip.Add(11,78915);
  assert(ip.result() == Poly<double>({1,2,3,4,5}));

  return 0;
}