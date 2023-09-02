#include "Socket.h"
#include <fstream>
using namespace std;

void printEncryptedData(string s) 
{
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



int main() {
	Socket Connection;
	ll n = Connection.getN();
	ofstream timeMeasurements("time.csv", ios::app);

	while (true)
	{
		string message;
		cout << "enter your message : ";
		getline(cin, message);
		message = message.substr(0, 500); // trim the first 500 characters only to prevent overflow
		
		startTime;
		string encrypted_data = Connection.Encrypt(message);
		endTime;
		cout << deltaTime << " us" << endl;
		timeMeasurements << numberLength(n) << "," << deltaTime << endl;

		Connection.sendMessage(encrypted_data);
		printEncryptedData(encrypted_data);
		cout << "sent !!" << endl;
		cout << "=================================================================================================\n";
	}
	//end
	system("pause");
	WSACleanup();
	return 0;
}