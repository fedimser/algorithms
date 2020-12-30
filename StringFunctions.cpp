#include <bits/stdc++.h>
using namespace std;

// p[i]: max length such that s[0...]=s[...i].
vector<int> PrefixFunction(const string& str) {
    int length = str.length();
    vector<int> pf = vector<int>(length, 0);
    for (int i = 1; i < length; ++i) {
        int brdr = pf[i-1];
        while (brdr && str[i] != str[brdr]) brdr = pf[brdr-1];
        brdr += (str[i] == str[brdr]);
        pf[i] = brdr;
    }
    return pf;
}

// z[i]: max length such that s[0...]=s[i...].
vector<int> ZFunction(const string& str) {
    int len = str.length();
    vector<int> zf(len, 0);
    int left = 0, right = 0;
    for (int i = 1; i < len; ++i) {
        zf[i] = std::max((int)0, std::min(right - i, zf[i - left]));
        while (i + zf[i] < len && str[zf[i]] == str[i + zf[i]]) zf[i]++;
        if (i + zf[i] >= right) { left = i; right = i + zf[i]; }
    }
    zf[0] = len;
    return zf;
}




void checkString(const string& s) {
    int n = s.length();

    vector<int> pf = PrefixFunction(s);
    assert(pf.size() == n);
    for(int i=0; i<n; i++) {
        int p = pf[i];
        assert(p<i+1);
        for(int j=0;j<p;j++) assert(s[j]==s[i-p+1+j]);
    }

    vector<int> zf = ZFunction(s);
    assert(zf.size() == n);
    for(int i=0; i<n; i++) {
        int z = zf[i];
        for(int j=0;j<z;j++) assert(s[j]==s[i+j]);
        assert(i+z==n || s[z]!=s[i+z]);
    }
}


int main() {
    checkString("a");
    checkString("abacaba");
    checkString("gkljhgsdfkljhghkjhuihhhhhhhddhhhsadhfjsghjgkhjgkskjgfshjg");
}