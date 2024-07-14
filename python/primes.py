import math
import random

def pow_mod(x, y, p):
  a,x=1,x%p 
  while (y > 0):
    if (y & 1): a = (a * x) % p
    y = y>>1
    x = (x * x) % p
  return a 

def miller_test(d, n, a):
  x = pow_mod(a, d, n)
  if (x == 1 or x == n - 1): return True;
  while (d != n - 1):
    x = (x * x) % n
    d *= 2
    if (x == 1): return False
    if (x == n - 1): return True
  return False
 
def is_prime(n, trials=10):
  if n<=4: return (n==2 or n==3)
  d = n - 1
  while d % 2 == 0: d //= 2  # n = 2^r * d + 1 (r >= 1).
  return all(miller_test(d, n, 2+random.randint(1,n-4)) for _ in range(trials))

def pollard_rho(n, seed=0, f=lambda x: x**2 + 1):
  x, y, d = seed, seed, 1
  while d == 1:
    x = f(x) % n
    y = f(f(y)) % n
    d = math.gcd((x - y) % n, n)
  return d

def factorize(x):
  assert x <= 10**18
  f = []
  for d in range(2, 10**6): # Must be limit**(1/3).
    if d*d > x: break
    if x%d==0:
      ctr = 0
      while x%d==0: 
        x//=d
        ctr+=1
      f.append((d, ctr))
  if x == 1: return f
  if is_prime(x): return f + [(x, 1)]
  while True:
    d1 = pollard_rho(x, seed = random.randint(0, x-1))
    if d1 <=1 or d1>=x: continue
    d2 = x // d1
    if d1 > d2: d1, d2 = d2, d1 
    return f + ([(d1,2)] if d1==d2 else [(d1, 1), (d2, 1)])

assert factorize(216) == [(2,3), (3,3)]
assert factorize(920663414723656061) == [(920663414723656061,1)]
assert factorize(329103252131530141) == [(509452343,1),(645994187,1)]
assert factorize(786550534649646649) == [(886876843,2)]
print("primes.py OK")