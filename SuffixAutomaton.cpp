#include <bits/stdc++.h>
using namespace std;

class SuffixAutomaton {
  struct State {int len, link; map<char, int> next;};
 public:
  vector<State> st;
  int sz, last;
  SuffixAutomaton(const string& s) {
  	st.resize(2*s.length() + 10);
	st[0].len = 0; st[0].link = -1;
	sz = 1;	last = 0;
	for(char c: s) sa_extend(c);
  }

  // Returns -1 if transition doesn't exist, otherwise state id.
  // Root has id 1.
  int go(int sid, char c) const {
  	auto it = st[sid].next.find(c);
  	return (it==st[sid].next.end())?-1:(it->second);
  }

  bool contains_substring(const string& s) const {
    int sid = 0;
    for (char c: s) {sid = go(sid, c);if(sid == -1) return false;}
    return true;
  }

 private:
  void sa_extend(char c) {
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    int p = last;
    while (p != -1 && !st[p].next.count(c)) {
        st[p].next[c] = cur;
        p = st[p].link;
    }
    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            st[clone].next = st[q].next;
            st[clone].link = st[q].link;
            while (p != -1 && st[p].next[c] == q) {
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
  }
};

int main() {
    string s = "abacababadbacab71528756yutwyurtre000000";
    SuffixAutomaton sa(s);

    assert(sa.contains_substring(""));
    assert(sa.contains_substring(s));
    assert(sa.contains_substring("a"));
    assert(sa.contains_substring("aba"));
    assert(sa.contains_substring("dbacab7"));
    assert(sa.contains_substring("000000"));

    assert(!sa.contains_substring(s + "#"));
    assert(!sa.contains_substring("#"));
    assert(!sa.contains_substring("0000000"));
    assert(!sa.contains_substring("cabb"));
}