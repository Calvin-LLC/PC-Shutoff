#ifndef PCH_H_
#define PCH_H_

#define WIN32_LEAN_AND_MEAN // accept(ListenSocket, NULL, NULL); get rid of accept() in windows.h

#include <Windows.h>
#include <iostream>
#include <Winsock2.h>
#include <ws2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")

#define NO_CONSOLE_

#include "socket/socket.h"

#endif