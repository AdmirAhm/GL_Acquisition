#pragma once
#include "ws_base.h"
#include <iostream>
#include <fo/FileOperations.h>
#include <cnt/StringBuilder.h>
#include <mu/mu.h>
#include <future>
#include "..\global.h"
class server : public ws_base
{
protected:

	void handleClient()
	{
		sockaddr clientAdr;

		SOCKET clientSocket = acceptConnection(clientAdr);
		if (clientSocket == INVALID_SOCKET)
			return;
		isconnected = true;

		try
		{
			while (true)
			{
				td::String message = receiveMsg(clientSocket);
				setMessage(message);
				if (close_server) {
					closesocket(clientSocket);
					return;
				}
			}
		}
		catch (...)
		{
			closesocket(clientSocket);
			return;

		}
		
	}

	void shutdownClient(SOCKET client, int how)
	{
		int iRes = shutdown(client, how);
		if (iRes != 0)
		{
			throw std::runtime_error("WinSock error");
		}
	}



	SOCKET acceptConnection(sockaddr& client)
	{
		std::memset(&client, 0, sizeof client);
		int clientAdrSize = sizeof client;
		return accept(_socket, &client, &clientAdrSize);
	}

public:

	void initAndListenForConnections(td::String port, protocol protocol)
	{
		try
		{

			WSADATA wsa = initWSA();

			addrinfo* result = nullptr, hints;
			std::memset(&hints, 0, sizeof(addrinfo));
			hints.ai_family = AF_INET;
			hints.ai_socktype = protocol == protocol::TCP ? SOCK_STREAM : SOCK_DGRAM;
			hints.ai_protocol = protocol == protocol::TCP ? IPPROTO_TCP : IPPROTO_UDP;
			hints.ai_flags = AI_PASSIVE;

			getAdrInfo(nullptr, port.c_str(), &hints);
		
			initSocket();

			bindSocketToAddress();

			listenSocket(SOMAXCONN);

			
			struct sockaddr_in sock;
			char hostn[30];
			gethostname(hostn, sizeof(hostn));
			struct hostent* phe = gethostbyname(hostn);

			struct in_addr addr;
			for (int i = 0; phe->h_addr_list[i] != 0; ++i) {
				memcpy(&addr, phe->h_addr_list[i], sizeof(struct in_addr));
				int x = 0;
			}

			int namelen= sizeof(sock);
			getsockname(_socket, (struct sockaddr*) & sock, &namelen);
			auto x1=ntohs(sock.sin_addr.S_un.S_addr);


			cnt::StringBuilder sb;
			for (int i = 2; i <= 5; i++) {
				int br = 0;
				switch (i) {
				case 2:
					br=addr.S_un.S_un_b.s_b1;
					break;
				case 3:
					br=addr.S_un.S_un_b.s_b2;
					break;
				case 4:
					br=addr.S_un.S_un_b.s_b3;
					break;
				case 5:
					br=addr.S_un.S_un_b.s_b4;
					break;
				}
				char b1[2] = { (char)((br % 10) + '0'), '\0' };
				char b2[2] = { (char)(((br/10) % 10) + '0'), '\0' };
				char b3[2] = { (char)((br/100) + '0'), '\0' };
				td::String str;
				cnt::StringBuilder sb2;
				if (b3[0] != '0') sb2.appendCString(b3);
				if (b3[0] != '0' || b2[0] != '0') sb2.appendCString(b2);
				sb2.appendCString(b1);
				sb2.getString(str);
				sb.appendString(str);
				if (i != 5) sb.appendCString(".");
			}
			sb.getString(ip);
			if (close_server) {
				closesocket(_socket);
				return;
				
			}
			while (true)
			{

				handleClient();
				if (close_server) {
					closesocket(_socket);
					return;
				}
			}
		}
		catch (...)
		{
			//std::cout << "WinSock error code: " << WSAGetLastError();
			freeaddrinfo(_adrInfo);
			closesocket(_socket);
			WSACleanup();
		}
	}

	server()
	{
	}

};