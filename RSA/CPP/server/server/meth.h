#include <iostream>
#include <math.h>
#include <vector>
using namespace std;
#define ll long long
#define ull unsigned long long

ull gcd(ull a, ull b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

ll GCD(ll a, ll b, vector<ll>& Quotients) // prepare qoutients array for modular inverse table
{
	if (b == 0)
		return a;
	ll q = a / b, r = a % b;
	Quotients.push_back(q);
	return GCD(b, r, Quotients);
}


ll calc_e(ll start, ll end)
{
	ll phiN = end;
	end = phiN - 1;
	while (true)
	{
		ll x = rand() % 100;
		if (x > 3)
		{
			if (gcd(start, phiN) == 1)
			{
				return start;
			}
			start++;
		}
		else {
			if (gcd(end, phiN) == 1)
			{
				return end;
			}
			end--;
		}
	}
}


ll rotateNumber(ll x, ll mod) // make mod positive
{
	if (x >= 0)
		return x;

	ll cycles = llabs(x) / mod;
	x += mod * (cycles + 1);
	return x;
}


ll modularInverse(ll a, ll n)
{
	vector<ll> Quotients, X;

	if (GCD(a, n, Quotients) != 1)
		return 0; // doesn't exist

	X.push_back(1), X.push_back(0);

	for (ll i = 0; i < Quotients.size() - 1; i++)
	{
		ll nextX = X[i] - X[i + 1] * Quotients[i];
		X.push_back(nextX);
	}

	return rotateNumber(*X.rbegin(), n);
}



tuple<ll, ll, ll> generateKey(ll p, ll q)
{
	ll n = p * q;
	ll phiN = (p - 1) * (q - 1);
	ll e = calc_e(2, phiN);
	ll d = modularInverse(e, phiN);
	return { e,n,d };
}

ll mulMod(ll a, ll b, ll m) 
{
	if (m == 0) 
		return a * b;

	ll r = 0;

	while (a > 0) 
	{
		if (a & 1)
			if ((r += b) > m) r %= m;
		
		a >>= 1;
		if ((b <<= 1) > m) b %= m;
	}
	return r;
}

ll fastModularPower(ll a, ll n, ll m) {
	ll r = 1;

	while (n > 0) 
	{
		if (n & 1)
			r = mulMod(r, a, m);
		
		a = mulMod(a, a, m);
		
		n >>= 1;
	}
	return r;
}

bool isPrime(ll n)
{
	for (ll i = 2; i * i <= n; i++)
	{
		if (n % i == 0)
			return false;
	}
	return true;
}
