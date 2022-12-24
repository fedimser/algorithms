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
  vector<int64_t> Divisors(int64_t x) const {
    vector<int64_t> ans;if (x > N) {int64_t sqrt_x = ceil(sqrt(x));for(int p: primes) {if (p>sqrt_x) break;if (x%p==0) {reduce(x,p,ans);sqrt_x = ceil(sqrt(x));if(x<=N)break;}}if (x > N) {ans.push_back(x); return ans;}}while(x!=1) reduce(x, e[x], ans);return ans;
  }
  // Prime divisors of x with multiplicity. Ascending. 1<=x<=N^2.
  vector<pair<int64_t, int64_t>> Factors(int64_t x) const {
    vector<pair<int64_t, int64_t>> ans;if (x > N) {int64_t sqrt_x = ceil(sqrt(x));for(int p: primes) {if (p>sqrt_x) break;if (x%p==0) {reduce(x,p,ans);sqrt_x = ceil(sqrt(x));if(x<=N)break;}}if (x > N) {ans.push_back({x, 1}); return ans;}}while(x!=1) reduce(x, e[x], ans);return ans;
  }
};

void TestPrimes(const Primes& p, int64_t n, vector<int64_t> true_prime_divisors) {
    assert(p.IsPrime(n) == (true_prime_divisors.size()==1 && true_prime_divisors[0]==n));

    vector<int64_t> divisors = p.Divisors(n);
    vector<pair<int64_t,int64_t>> factors = p.Factors(n);

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
    Primes p(1000000);
    assert(p.primes.size() == 78498);
    assert(p.primes[0] == 2);
    assert(p.primes[1000] == 7927);
    assert(p.primes[78497] == 999983);

    TestPrimes(p, 1, {});
    TestPrimes(p, 2, {2});
    TestPrimes(p, 3, {3});
    TestPrimes(p, 4, {2});
    TestPrimes(p, 5, {5});
    TestPrimes(p, 6, {2,3});
    TestPrimes(p, 7, {7});
    TestPrimes(p, 8, {2});
    TestPrimes(p, 9, {3});
    TestPrimes(p, 10, {2,5});
    TestPrimes(p, 20, {2,5});
    TestPrimes(p, 36, {2,3});
    TestPrimes(p, 77, {7,11});
    TestPrimes(p, 100, {2,5});
    TestPrimes(p, 121, {11});
    TestPrimes(p, 7927, {7927});
    TestPrimes(p, 30030, {2,3,5,7,11,13});
    TestPrimes(p, 67500, {2,3,5});
    TestPrimes(p, 707960, {2,5,11,1609});
    TestPrimes(p, 1000000, {2,5});
    TestPrimes(p, 1000001, {101,9901});
    TestPrimes(p, 21999626, {2,11,999983});
    TestPrimes(p, 967983544, {2,11,999983});
    TestPrimes(p, 1000000007, {1000000007});
    TestPrimes(p, 999966000289, {999983});
    TestPrimes(p, 999999999999, {3,7,11,13,37,101,9901});
    TestPrimes(p, 1000000000000, {2,5});

    return 0;
}