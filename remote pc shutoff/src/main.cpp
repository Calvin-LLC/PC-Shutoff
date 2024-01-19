#include "pch.h"

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd) {
	c_socket socket;
	
	// wait for our app to connect
	socket.wait_for_connection();

	for (;socket.alive;Sleep(1)) {
		socket.loop();
	}

	return 1;
}