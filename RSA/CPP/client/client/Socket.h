#include <iostream>
#include <vector>
#include <string>

#include <WinSock2.h>
#include <WS2tcpip.h>
#include "targetver.h"
#include "stdafx.h"

#include "meth.h"

using namespace std;

class Socket
{
private:
	SOCKET clientSocket;
	int port = 55555;
	long long e, n;

	void setUpDll()
	{
		WSADATA wsaData;
		int wsaerr;
		WORD wVersionRequested = MAKEWORD(2, 2);
		wsaerr = WSAStartup(wVersionRequested, &wsaData);
		if (wsaerr != 0)
		{
			cout << "ERROR WinSock DLL not found" << endl;
		}
		else {
			cout << "WinSock DLL found" << endl;
			cout << wsaData.szSystemStatus << endl;
		}
	}

	void setupSocket() 
	{
		clientSocket = INVALID_SOCKET;
		clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (clientSocket == INVALID_SOCKET)
		{
			cout << "ERROR Socket setup failed" << endl;
			WSACleanup();
			exit(0);
		}
		else {
			cout << "Socket is up" << endl;
		}
	}
	
	void connectToSocket() 
	{
		sockaddr_in Service;
		Service.sin_family = AF_INET;
		InetPton(AF_INET, _T("127.0.0.1"), &Service.sin_addr.s_addr);
		Service.sin_port = htons(port);
		if (connect(clientSocket, (SOCKADDR*)&Service, sizeof(Service)) == SOCKET_ERROR)
		{
			cout << "Connect Failed" << endl;
			WSACleanup();
			exit(0);
		}
		else {
			cout << "Connected to the socket" << endl;
		}
	}
	
	void receivePublicKeys() 
	{
		char Buffer[20];
		int byteCount = recv(clientSocket, Buffer, 20, 0);
		if (byteCount > 0)
		{
			e = stoll(Buffer);
			cout << "e recieved: " << e << endl;
		}
		else {
			WSACleanup();
		}
		byteCount = recv(clientSocket, Buffer, 20, 0);
		if (byteCount > 0)
		{
			n = stoll(Buffer);
			cout << "n recieved: " << n << endl;
		}
		else 
		{
			WSACleanup();
		}
	}

public:
	Socket()
	{
		//set up DLL
		setUpDll();
		//setup the socket
		setupSocket();
		// connect to socket
		connectToSocket();
		// reciving the keys
		receivePublicKeys();
		cout << "=================================================================================================\n";
	}

	ll getN()
	{
		return n;
	}

	string Encrypt(string s)
	{
		string out = "";
		for (ll i = 0; i < s.length(); i++)
		{
			ll val = s[i];
			ll encrypted = fastModularPower((val), (e), n);
			out += to_string(encrypted);
			out += '-';
		}
		return out;
	}

	void sendMessage(string data) 
	{
		const char* s = data.c_str();
		char buffer[1000];
		strcpy_s(buffer, s);
		int byteCount = send(clientSocket, buffer, 1000, 0);
		if (byteCount > 0)
		{
			// do nothing
		}
		else {
			WSACleanup();
		}
	}
};