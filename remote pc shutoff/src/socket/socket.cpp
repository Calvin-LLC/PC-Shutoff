#include "../pch.h"

c_socket::c_socket() {
	// init winsock dll
	res = WSAStartup(MAKEWORD(2, 2), &wsa_desc);

	// if theres a result then it failed
	if (res) {
#ifndef NO_CONSOLE_
		printf("wsa startup failed : %d\n", res);
#endif
		return;
	}

	// specifiers for our winsocket server https://learn.microsoft.com/en-us/windows/win32/api/ws2def/ns-ws2def-addrinfoa
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_INET;			// type of request (ipv4)
	hints.ai_protocol = IPPROTO_TCP;	// protocol
	hints.ai_socktype = SOCK_STREAM;	// so that we don't have to setup some things ourselves

	// get information about the server addr and port
	res = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (res) {
#ifndef NO_CONSOLE_
		printf("getaddrinfo failed with error: %d\n", res);
#endif
		return;
	}

	// create the listen socket
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
#ifndef NO_CONSOLE_
		printf("socket failed with error: %ld\n", WSAGetLastError());
#endif
		return;
	}

	// setup the listen socket
	res = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (res == SOCKET_ERROR) {
#ifndef NO_CONSOLE_
		printf("bind failed with error: %d\n", WSAGetLastError());
#endif
		return;
	}

	freeaddrinfo(result);
}

c_socket::~c_socket() {
	if (ListenSocket != INVALID_SOCKET) {
		closesocket(ListenSocket);
	}

	if (ClientSocket != INVALID_SOCKET) {
		res = shutdown(ClientSocket, SD_SEND);
		if (res == SOCKET_ERROR) {
#ifndef NO_CONSOLE_
			printf("shutdown failed with error: %d\n", WSAGetLastError());
#endif
			closesocket(ClientSocket);
		}
	}
	WSACleanup();
}

void c_socket::wait_for_connection() {
#ifndef NO_CONSOLE_
	printf("waiting for client connection\n");
#endif

	// Check if the socket is in the listening state
	if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
#ifndef NO_CONSOLE_
		printf("listen failed with error: %d\n", WSAGetLastError());
#endif
		return;
	}

	// wait to connect to a client
	while (true) {
		ClientSocket = accept(ListenSocket, NULL, NULL);

		if (ClientSocket != INVALID_SOCKET) {
#ifndef NO_CONSOLE_
			printf("connected to a client\n");
#endif
			break;
		}
		else {
#ifndef NO_CONSOLE_
			printf("accept failed with error: %d\n", WSAGetLastError());
#endif
			Sleep(100);
		}
	}

	alive = true;

	// No longer need server socket
	closesocket(ListenSocket);
}

void c_socket::loop() {
	// recieve information from the client
	res = recv(ClientSocket, recvbuf, DEFAULT_BUFLEN, 0);

	// if we've recieved anything
	if (res > 0) {
		// shutdown windows
		Beep(300, 500); // let me know that it worked
		system("shutdown -s -t 0");
		
		alive = false;
	}
	
	else if (res == 0) {} // if nothing is sent

	else {
#ifndef NO_CONSOLE_
		printf("recv failed with error: %d\n", WSAGetLastError());
#endif
	}
}
