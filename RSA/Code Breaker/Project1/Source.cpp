#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

typedef long long ll;

using namespace std;


int main()
{
	ifstream in("in.txt");
	ofstream res("res.txt");
	ofstream time("time.csv");


	while (!in.eof())
	{
		string s;
		in >> s;
		if (s.size() > 18)
		{
			cout << "nice try overflowing the stack but no :P \n";
			continue;
		}
		
		ll n = stoll(s);

		if (n % 2 == 0)
		{
			res << 2 << " " << n / 2 << " " << endl;
			time << n << "," << 0 << endl;
			continue;
		}


		auto start = std::chrono::high_resolution_clock::now();
		for (ll i = 3; i * i <= n; i += 2)
		{
			if (n % i == 0)
			{
				auto end = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);


				res << i << " " << n / i << " " << endl;
				time << n << "," << duration.count() << endl;
				break;
			}
		}
	}

	return 0;
}