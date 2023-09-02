#include <iostream>
#include <math.h>
#include <vector>
#include <chrono>

using namespace std;
#define ull unsigned long long
#define ll long long


#define startTime auto start = chrono::high_resolution_clock::now();
#define endTime auto end = chrono::high_resolution_clock::now();
#define deltaTime chrono::duration_cast<chrono::microseconds>(end - start).count()

ll rotateNumber(ll x, ll mod) // make mod positive
{
	if (x >= 0)
		return x;

	ll cycles = llabs(x) / mod;
	x += mod * (cycles + 1);
	return x;
}

int numberLength(ll n)
{
	return floor(log2(n)) + 1;
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

ll GCD(ll a, ll b, vector<ll>& Quotients) // prepare qoutients array for modular inverse table
{
	if (b == 0)
		return a;
	ll q = a / b, r = a % b;
	Quotients.push_back(q);
	return GCD(b, r, Quotients);
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

ll gcd(ll a, ll b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}