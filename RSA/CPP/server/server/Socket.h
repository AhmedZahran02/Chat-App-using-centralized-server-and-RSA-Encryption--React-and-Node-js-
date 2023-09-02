#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <sstream>
#include <fstream>

#include <WinSock2.h>
#include <WS2tcpip.h>
#include "targetver.h"
#include "stdafx.h"

#include "meth.h"

using namespace std;
class Socket
{
private:
	SOCKET serverSocket, acceptSocket;
	int port = 55555;
	long long e, n, d;

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

	void bindSocket() 
	{
		sockaddr_in service;
		service.sin_family = AF_INET;
		InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
		service.sin_port = htons(port);
		if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
		{
			cout << "Bind Failed" << endl;
			closesocket(serverSocket);
			WSACleanup();
			exit(0);
		}
		else {
			cout << "Socket Binding is OK" << endl;
		}
	}

	void setupSocket() 
	{
		serverSocket = INVALID_SOCKET;
		serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (serverSocket == INVALID_SOCKET)
		{
			cout << "ERROR Socket setup failed" << endl;
			WSACleanup();
			exit(0);
		}
		else {
			cout << "Socket is up" << endl;
		}
	}

	void listenSocket() 
	{
		if (listen(serverSocket, 1) == SOCKET_ERROR)
		{
			cout << "Error listening on socket :" << WSAGetLastError() << endl;
		}
		else {
			cout << "Socket is Listening" << endl;
		}
	}

	void acceptConnection() 
	{
		acceptSocket = accept(serverSocket, NULL, NULL);
		if (acceptSocket == INVALID_SOCKET)
		{
			cout << "Accept Failed" << endl;
			WSACleanup();
			exit(-1);
		}
		cout << "Connection Accepted" << endl;
	}

	void sendPublicKeys()
	{
		string temp = to_string(e);
		const char* s = temp.c_str();
		char buffer[20];
		strcpy_s(buffer, s);
		int byteCount = send(acceptSocket, buffer, 20, 0);
		if (byteCount > 0)
		{
			cout << "e sent: " << e << endl;
		}
		else {
			WSACleanup();
		}
		temp = to_string(n);
		s = temp.c_str();
		strcpy_s(buffer, s);
		byteCount = send(acceptSocket, buffer, 20, 0);
		if (byteCount > 0)
		{
			cout << "n sent: " << n << endl;
		}
		else {
			WSACleanup();
		}
	}

	vector<long long> separateString(string buffer)
	{
		vector<long long> Message;
		int l = 0;
		for (int i = 0; i < buffer.size(); i++)
		{
			if (buffer[i] == '-')
			{
				Message.push_back(stoll(buffer.substr(l,i - l)));
				l = i + 1;
			}
		}
		return Message;
	}

	string decrypt(string s)
	{
		vector<long long> ans = separateString(s);
		string out = "";
		for (long long i = 0; i < (long long)ans.size(); i++)
		{
			ll dec = fastModularPower(ans[i], d, n);
			out += (char)dec;
		}
		return out;
	}

public:
	Socket(long long e, long long n, long long d)
	{
		this->e = e;
		this->n = n;
		this->d = d;
		//set up DLL
		setUpDll();
		//setup the socket
		setupSocket();
		// bind socket
		bindSocket();
		// listen on socket
		listenSocket();
		// accept connection
		acceptConnection();
		//send public keys 
		sendPublicKeys();
		cout << "=================================================================================================\n";
	}

	pair<string,string> receive() 
	{
		char buffer[1000];
		int byteCount = recv(acceptSocket, buffer, 1000, 0);

		// convert it to string to make it cooler
		string encrypted_text = "";
		int buff_len = strlen(buffer);

		for (int i = 0; i < buff_len;i++)
			encrypted_text += buffer[i];

		//some decyrepting stuff on the buffer
		string plainText = decrypt(encrypted_text);
		if (byteCount > 0)
		{
			//cout << "message after decryption : " << plainText << endl;
		}
		else {
			WSACleanup();
		}

		return { encrypted_text,plainText };
	}

};