#include <bits/stdc++.h>
using namespace std;

class FastMultiplier {
  const int64_t P1 = 2013265921;
  const int64_t P2 = 919601153;
  const int64_t R12 = 229239021;   // P1^-1 (mod P2)
  const int64_t ROOT1 = 195061667; // Primitive root of order(2^20) modulo P1.
  const int64_t ROOT2 = 611244703; // Primitive root of order(2^20) modulo P2.
  const int64_t MAX_SIZE = 1 << 20;

  int64_t P, ROOT, ROOT_REV;

  // (x^y) % p
  inline int64_t pow_mod(int64_t x, int64_t y, int64_t p) {
    int64_t ans = 1;
    int64_t m = x;
    while (y != 0) {
      if (y & 1)
        ans = (ans * m) % p;
      m = (m * m) % p;
      y >>= 1;
    }
    return ans;
  }

  // Returns such y, that 0<=y<p; (x*y)%p=1.
  // p must be prime !
  inline int64_t rev_mod(int64_t x, int64_t p) { return pow_mod(x, p - 2, p); }

  inline int64_t mod_signed(int64_t x, int64_t p) {
    int64_t ans = x % p;
    if (ans < 0)
      ans += p;
    return ans;
  }

  // Returns such a, that 0 <= a < P1*P2; a%P1 = a1, a%P2 = a2.
  // (Garner algorithm).
  inline int64_t restore(int64_t a1, int64_t a2) {
    int64_t x2 = mod_signed((a2 - a1) * R12, P2);
    return a1 + P1 * x2;
  }

  void prepare_fft(int index) {
    if (index == 1) {
      P = P1;
      ROOT = ROOT1;
      ROOT_REV = rev_mod(ROOT1, P1);
    } else {
      P = P2;
      ROOT = ROOT2;
      ROOT_REV = rev_mod(ROOT2, P2);
    }
  }

  inline void fft(vector<int64_t> &a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; ++i) {
      int bit = n >> 1;
      for (; j >= bit; bit >>= 1)
        j -= bit;
      j += bit;
      if (i < j)
        swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
      int64_t wlen = invert ? ROOT_REV : ROOT;
      for (int i = len; i < MAX_SIZE; i <<= 1) {
        wlen = (wlen * wlen) % P;
      }
      for (int i = 0; i < n; i += len) {
        int w = 1;
        for (int j = 0; j < len / 2; ++j) {
          int64_t u = a[i + j];
          int64_t v = (a[i + j + len / 2] * w) % P;
          a[i + j] = u + v < P ? u + v : u + v - P;
          a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + P;
          w = (w * wlen) % P;
        }
      }
    }
    if (invert) {
      int nrev = rev_mod(n, P);
      for (int i = 0; i < n; ++i) {
        a[i] = (a[i] * nrev) % P;
      }
    }
  }

public:
  // Removes all tailing zeros.
  inline void cut(vector<int64_t> &x) {
    int n = x.size() - 1;
    while (x[n] == 0 && n != 0)
      n--;
    x.resize(n + 1);
  }

  // Multiplies two polynomials modulo P1*P2 (P1*P2>1.85e18).
  vector<int64_t> multiply(const vector<int64_t> &x, const vector<int64_t> &y) {
    int x_size = x.size();
    int y_size = y.size();
    int res_min_size = x_size + y_size - 1;
    int n = 1;
    while (n < res_min_size)
      n <<= 1;
    assert(n <= MAX_SIZE);

    vector<int64_t> a1(n, 0);
    vector<int64_t> a2(n, 0);
    vector<int64_t> b1(n, 0);
    vector<int64_t> b2(n, 0);
    for (int i = 0; i < x_size; i++) {
      a1[i] = mod_signed(x[i], P1);
      a2[i] = mod_signed(x[i], P2);
    }
    for (int i = 0; i < y_size; i++) {
      b1[i] = mod_signed(y[i], P1);
      b2[i] = mod_signed(y[i], P2);
    }

    prepare_fft(1);
    fft(a1, false);
    fft(b1, false);
    prepare_fft(2);
    fft(a2, false);
    fft(b2, false);

    for (int i = 0; i < n; i++)
      a1[i] = (a1[i] * b1[i]) % P1;
    for (int i = 0; i < n; i++)
      a2[i] = (a2[i] * b2[i]) % P2;

    prepare_fft(1);
    fft(a1, true);
    prepare_fft(2);
    fft(a2, true);

    for (int i = 0; i < n; i++)
      a1[i] = restore(a1[i], a2[i]);
    cut(a1);
    return a1;
  }

  // Multiplies polynomials modulo P1 (2.01e9). Destroys data.
  inline vector<int64_t> multiply_fast(vector<int64_t> &x, vector<int64_t> &y) {
    int res_min_size = x.size() + y.size() - 1;
    int n = 1;
    while (n < res_min_size)
      n <<= 1;

    x.resize(n);
    y.resize(n);
    prepare_fft(1);
    fft(x, false);
    fft(y, false);

    for (int i = 0; i < n; i++)
      x[i] = (x[i] * y[i]) % P1;
    fft(x, true);
    cut(x);
    return x;
  }
};

int main() {
  FastMultiplier mult;
  vector<int64_t> a(10, 1);
  vector<int64_t> ans = mult.multiply(a, a);
  vector<int64_t> expected {1,2,3,4,5,6,7,8,9,10,9,8,7,6,5,4,3,2,1};
  assert(ans == expected);
  return 0;
}
