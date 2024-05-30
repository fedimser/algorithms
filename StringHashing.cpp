#include <bits/stdc++.h>
using namespace std;
 
constexpr char MIN_CHAR='a', MAX_CHAR='z';
constexpr int64_t P1 = 29, P1_REV = 827709889, M1 = 1200179339;
constexpr int64_t P2 = 31, P2_REV = 234768588, M2 = 1039689461;
static_assert((P1*P1_REV)%M1==1);
static_assert((P2*P2_REV)%M2==1);
static_assert(MAX_CHAR-MIN_CHAR+2<=P1);
static_assert(MAX_CHAR-MIN_CHAR+2<=P2);
typedef pair<int64_t, int64_t> Hash;
std::ostream& operator<<(std::ostream& os, const Hash& h) {
  return os << h.first << ";" << h.second;
}
 
struct StringHashes {
  vector<int64_t> h1,h2;
  Hash SubstrHash(int l, int r) const;   // [l,r).
  int Length() const {return h1.size()-1; }
};
 
struct Hasher {
  vector<int64_t> p1,p2,r1,r2;
  Hasher(int N): p1(N+1),p2(N+1),r1(N+1),r2(N+1) {
    p1[0]=p2[0]=r1[0]=r2[0]=1;
    for(int i=1;i<=N;i++) {
      p1[i] = (p1[i-1]*P1)%M1; p2[i] = (p2[i-1]*P2)%M2;
      r1[i] = (r1[i-1]*P1_REV)%M1; r2[i] = (r2[i-1]*P2_REV)%M2;       
    }    
  }
  Hash GetHash(const string& s) const {
    int64_t h1 = 0, h2 = 0;
    int n = s.size();
    for(int i=0; i<n; ++i) {
      int64_t c = 1 + (s[i] - MIN_CHAR);
      h1 = (h1+p1[i]*c)%M1;
      h2 = (h2+p2[i]*c)%M2;
    }
    return make_pair(h1, h2);
  }  
  StringHashes GetHashes(const string& s) const {
    StringHashes ans;
    int n = s.size();
    ans.h1.resize(n+1);
    ans.h2.resize(n+1);    
    ans.h1[0]=ans.h2[0]=0;
    int64_t h1 = 0, h2 = 0;
    for(int i=0; i<n; ++i) {
      int64_t c = 1 + (s[i] - MIN_CHAR);
      h1 = (h1+p1[i]*c)%M1;
      h2 = (h2+p2[i]*c)%M2;
      ans.h1[i+1]=h1;
      ans.h2[i+1]=h2;
    }
    return ans;
  }
};
Hasher HH(2000007);
 
Hash StringHashes::SubstrHash(int l, int r) const {   
  int64_t a1 = (M1+h1[r]-h1[l])*HH.r1[l];
  int64_t a2 = (M2+h2[r]-h2[l])*HH.r2[l];
  return make_pair(a1%M1, a2%M2);
}




int main() {
    string s = "abacabaqabacaba"; // len=15.
    StringHashes sh = HH.GetHashes(s);
    assert(HH.GetHash(s) == sh.SubstrHash(0, 15));
    assert(sh.SubstrHash(0, 1) == Hash(1LL, 1LL));
    assert(sh.SubstrHash(1, 2) == Hash(2LL, 2LL));
    assert(sh.SubstrHash(0, 3) == sh.SubstrHash(4, 7));
    assert(sh.SubstrHash(0, 7) == sh.SubstrHash(8, 15));
    assert(sh.SubstrHash(0, 7) != sh.SubstrHash(1, 8));
}