#ifndef SOCKET_H_
#define SOCKET_H_

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

class c_socket {
private:
	WSADATA wsa_desc;
	struct addrinfo* result = NULL;
	struct addrinfo hints {};

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	int send_res{}, res{};
	char recvbuf[DEFAULT_BUFLEN]{};

public:
	c_socket();
	~c_socket();

	void wait_for_connection();
	void loop();

	bool alive = false;
};

#endif