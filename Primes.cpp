#include <bits/stdc++.h>
using namespace std;

struct Primes {
  int64_t N;
  vector<int64_t> e, primes;
  Primes(int64_t N_) {N = N_;e.assign(N+1,0);for(int i=2;i<=N;i++)if(e[i]==0){primes.push_back(i);for(int j=i;j<=N;j+=i)if(!e[j])e[j]=i;}}
  inline static void reduce(int64_t& x, int p, vector<int64_t>& ans) {ans.push_back(p); x/=p; while(x%p==0)x/=p;}
  inline static void reduce(int64_t& x, int p, vector<pair<int64_t, int64_t>>& ans) {int ctr=1; x/=p; while(x%p==0){x/=p;ctr++;} ans.push_back({p, ctr});}

  bool IsPrime(int64_t x) const {
    if(x>N) {int64_t sqrt_x = ceil(sqrt(x));for(int p: primes) {if (p>sqrt_x) break;if (x%p==0) return false;}return true;}return e[x]==x;
  }
  // Prime divisors of x. No repeats. Ascending. 1<=x<=N^2.
  vector<int64_t> PrimeDivisors(int64_t x) const {
    vector<int64_t> ans;if (x > N) {int64_t sqrt_x = ceil(sqrt(x));for(int p: primes) {if (p>sqrt_x) break;if (x%p==0) {reduce(x,p,ans);sqrt_x = ceil(sqrt(x));if(x<=N)break;}}if (x > N) {ans.push_back(x); return ans;}}while(x!=1) reduce(x, e[x], ans);return ans;
  }
  // Prime divisors of x with multiplicity. Ascending. 1<=x<=N^2.
  vector<pair<int64_t, int64_t>> Factors(int64_t x) const {
    vector<pair<int64_t, int64_t>> ans;if (x > N) {int64_t sqrt_x = ceil(sqrt(x));for(int p: primes) {if (p>sqrt_x) break;if (x%p==0) {reduce(x,p,ans);sqrt_x = ceil(sqrt(x));if(x<=N)break;}}if (x > N) {ans.push_back({x, 1}); return ans;}}while(x!=1) reduce(x, e[x], ans);return ans;
  }
  // Number of integers 0<x<=n such that gcd(x,n)=1. 1<=x<=N^2.
  int Totient(int n) {for(int p: PrimeDivisors(n))n=(p-1)*(n/p);return n;}
};
Primes PR(1000000);

void TestPrimes(int64_t n, vector<int64_t> true_prime_divisors) {
    assert(PR.IsPrime(n) == (true_prime_divisors.size()==1 && true_prime_divisors[0]==n));

    vector<int64_t> divisors = PR.PrimeDivisors(n);
    vector<pair<int64_t,int64_t>> factors = PR.Factors(n);

    assert(divisors.size()==true_prime_divisors.size());
    assert(factors.size()==true_prime_divisors.size());
    int64_t val=1;
    for(int i=0;i<factors.size();i++) {
        int p = true_prime_divisors[i];
        assert(divisors[i]==p);
        assert(factors[i].first==p);
        for(int j=0;j<factors[i].second;++j)val*=p;
    }
    assert(val==n);
}

int main() {
    assert(PR.primes.size() == 78498);
    assert(PR.primes[0] == 2);
    assert(PR.primes[1000] == 7927);
    assert(PR.primes[78497] == 999983);

    TestPrimes(1, {});
    TestPrimes(2, {2});
    TestPrimes(3, {3});
    TestPrimes(4, {2});
    TestPrimes(5, {5});
    TestPrimes(6, {2,3});
    TestPrimes(7, {7});
    TestPrimes(8, {2});
    TestPrimes(9, {3});
    TestPrimes(10, {2,5});
    TestPrimes(20, {2,5});
    TestPrimes(36, {2,3});
    TestPrimes(77, {7,11});
    TestPrimes(100, {2,5});
    TestPrimes(121, {11});
    TestPrimes(7927, {7927});
    TestPrimes(30030, {2,3,5,7,11,13});
    TestPrimes(67500, {2,3,5});
    TestPrimes(707960, {2,5,11,1609});
    TestPrimes(1000000, {2,5});
    TestPrimes(1000001, {101,9901});
    TestPrimes(21999626, {2,11,999983});
    TestPrimes(967983544, {2,11,999983});
    TestPrimes(1000000007, {1000000007});
    TestPrimes(999966000289, {999983});
    TestPrimes(999999999999, {3,7,11,13,37,101,9901});
    TestPrimes(1000000000000, {2,5});

    assert(PR.Totient(1) == 1);
    assert(PR.Totient(2) == 1);
    assert(PR.Totient(6) == 2);
    assert(PR.Totient(30030) == 5760);
    assert(PR.Totient(1000000007) == 1000000006);

    return 0;
}