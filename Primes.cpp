#include <bits/stdc++.h>
using namespace std;

vector<int64_t> primesUpTo(int64_t n) {
  vector<bool> e(n+1);vector<int64_t> a;
  for(int i=2;i<=n;i++)if(!e[i]){a.push_back(i);for(int j=2*i;j<=n;j+=i)e[j]=1;}
  return a;
}

int main() {
    vector<int64_t> primes = primesUpTo(1000000);
    assert(primes.size() == 78498);
    assert(primes[0] == 2);
    assert(primes[1000] == 7927);
    assert(primes[78497] == 999983);
    return 0;
}