#include "Socket.h"
using namespace std;

#define MAX_CHARACTER 128
#define defaultP 43
#define defaultQ 79
#define MAXPQDIGITS 9


void getInput(ll& p, ll& q);
void printEncryptedData(string s);

int main() {
	srand(1);
	// read p,q from txt file
	ll p, q;
	getInput(p, q);
	//generate Key
	ll e, n, d;
	tie(e, n, d) = generateKey(p, q); //{e,n,d} of your life :)
	// start the connection
	Socket Connection(e,n,d);
	// receive
	while (true)
	{
		string Enc, Plain;
		tie(Enc,Plain) = Connection.receive();
		cout << "Received Encrypted message : ";
		printEncryptedData(Enc);
		cout << "Decrypted Successfully : " << Plain << endl;
		cout << "Decryption Done Using The Following p & q : " << p << " " << q << endl;
		cout<<"=================================================================================================\n";
	}

	system("pause");
	WSACleanup();
	return 0;
}

void parseNextLine(string s, ll& n, ll Default)
{
	if (s[0] == '-')
	{
		cout << "negative values are not allowed...\n resetting to the default value\n";
		n = Default;
		return;
	}

	if (s.size() - 1 > MAXPQDIGITS)
	{
		cout << "nice try overflowing the buffer.. but no :P\n";
		n = Default;
		return;
	}

	try
	{
		n = stoll(s);
	}
	catch (exception e)
	{
		cout << "bro why u bully my code give me numbers\n";
		n = Default;
	}
}

void getInput(ll& p, ll& q) 
{
	fstream fin;
	fin.open("input.txt", ios::in);

	p = defaultP;
	q = defaultQ;

	if (fin.is_open())
	{
		string s; bool qTurn = 0;
		while (getline(fin, s))
		{
			if (s.size() == 0)
				continue;

			if (qTurn)
				parseNextLine(s, q, defaultQ);
			else
				parseNextLine(s, p, defaultP), qTurn = true;
		}
		fin.close();

		ll n = p * q;

		bool coversAscii = n > MAX_CHARACTER;
		bool causeOverflow = n < 0 || p < 0 || q < 0;
		bool arePrimes = isPrime(p) && isPrime(q);

		if ( !coversAscii || causeOverflow || !arePrimes ) // overflow detected
		{
			cout << "p,q values maybe invalid...\n";
			cout << "resetting to default values\n";
			p = defaultP;
			q = defaultQ;
		}
	}
}

void printEncryptedData(string s) {
	for (ll i = 0; i < s.length(); i++)
	{
		if (s[i] == '-')
		{
			continue;
		}
		cout << s[i];
	}
	cout << endl;
}



