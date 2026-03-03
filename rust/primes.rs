struct Primes {
    n: i64,
    e: Vec<i64>,
    primes: Vec<i64>,
}

impl Primes {
    fn new(n_: i64) -> Self {
        let mut e = vec![0; (n_ + 1) as usize];
        let mut primes = Vec::new();
        for i in 2..=n_ {
            if e[i as usize] == 0 {
                primes.push(i);
                let mut j = i;
                while j <= n_ {
                    if e[j as usize] == 0 {
                        e[j as usize] = i;
                    }
                    j += i;
                }
            }
        }
        Primes { n: n_, e, primes }
    }

    /// Check if x is prime. Works for x > n.
    fn is_prime(&self, x: i64) -> bool {
        if x <= self.n {
            return self.e[x as usize] == x;
        }
        let sqrt_x = (x as f64).sqrt().ceil() as i64;
        self.primes
            .iter()
            .take_while(|&&p| p <= sqrt_x)
            .all(|&p| x % p != 0)
    }

    /// Prime divisors of x. No repeats. Ascending. 1<=x<=N^2.
    fn prime_divisors(&self, mut x: i64) -> Vec<i64> {
        let mut ans = Vec::new();
        for &p in &self.primes {
            if p * p > x {
                break;
            }
            if x % p == 0 {
                ans.push(p);
                while x % p == 0 {
                    x /= p;
                }
            }
        }
        if x > 1 {
            ans.push(x);
        }
        ans
    }

    /// Prime divisors of x with multiplicity. Ascending. 1<=x<=N^2.
    fn factors(&self, mut x: i64) -> Vec<(i64, i64)> {
        let mut ans = Vec::new();
        for &p in &self.primes {
            if p * p > x {
                break;
            }
            if x % p == 0 {
                let mut count = 0;
                while x % p == 0 {
                    x /= p;
                    count += 1;
                }
                ans.push((p, count));
            }
        }
        if x > 1 {
            ans.push((x, 1));
        }
        ans
    }

    /// Number of integers 0<x<=n such that gcd(x,n)=1. 1<=x<=N^2.
    fn totient(&self, mut n: i64) -> i64 {
        for p in self.prime_divisors(n) {
            n = n / p * (p - 1);
        }
        n
    }
}

fn test_primes(pr: &Primes, n: i64, true_prime_divisors: Vec<i64>) {
    assert!(pr.is_prime(n) == (true_prime_divisors.len() == 1 && true_prime_divisors[0] == n));

    let divisors = pr.prime_divisors(n);
    let factors = pr.factors(n);

    assert_eq!(divisors.len(), true_prime_divisors.len());
    assert_eq!(factors.len(), true_prime_divisors.len());

    let mut val = 1;
    for (i, &p) in true_prime_divisors.iter().enumerate() {
        assert_eq!(divisors[i], p);
        assert_eq!(factors[i].0, p);
        for _ in 0..factors[i].1 {
            val *= p;
        }
    }
    assert_eq!(val, n);
}

fn main() {
    let pr = Primes::new(1_000_000);
    assert_eq!(pr.primes.len(), 78498);
    assert_eq!(pr.primes[0], 2);
    assert_eq!(pr.primes[1000], 7927);
    assert_eq!(pr.primes[78497], 999_983);

    test_primes(&pr, 1, vec![]);
    test_primes(&pr, 2, vec![2]);
    test_primes(&pr, 3, vec![3]);
    test_primes(&pr, 4, vec![2]);
    test_primes(&pr, 5, vec![5]);
    test_primes(&pr, 6, vec![2, 3]);
    test_primes(&pr, 7, vec![7]);
    test_primes(&pr, 8, vec![2]);
    test_primes(&pr, 9, vec![3]);
    test_primes(&pr, 10, vec![2, 5]);
    test_primes(&pr, 20, vec![2, 5]);
    test_primes(&pr, 36, vec![2, 3]);
    test_primes(&pr, 77, vec![7, 11]);
    test_primes(&pr, 100, vec![2, 5]);
    test_primes(&pr, 121, vec![11]);
    test_primes(&pr, 7927, vec![7927]);
    test_primes(&pr, 30030, vec![2, 3, 5, 7, 11, 13]);
    test_primes(&pr, 67500, vec![2, 3, 5]);
    test_primes(&pr, 707960, vec![2, 5, 11, 1609]);
    test_primes(&pr, 1_000_000, vec![2, 6]);
    test_primes(&pr, 1_000_001, vec![101, 9901]);
    test_primes(&pr, 21_999_626, vec![2, 11, 999_983]);
    test_primes(&pr, 967_983_544, vec![2, 11, 999_983]);
    test_primes(&pr, 1_000_000_007, vec![1_000_000_007]);
    test_primes(&pr, 999_966_000_289, vec![999_983]);
    test_primes(&pr, 999_999_999_999, vec![3, 7, 11, 13, 37, 101, 9901]);
    test_primes(&pr, 1_000_000_000_000, vec![2, 5]);

    assert_eq!(pr.totient(1), 1);
    assert_eq!(pr.totient(2), 1);
    assert_eq!(pr.totient(6), 2);
    assert_eq!(pr.totient(30030), 5760);
    assert_eq!(pr.totient(1_000_000_007), 1_000_000_006);
}
