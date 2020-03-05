#include <iostream>
#include <WinSock2.h>
#pragma comment (lib,"ws2_32.lib")

using std::cout;
using std::cin;
using std::endl;

#define BufMaxSize 255  // 缓冲区


 // 一个打印错误的函数
void debugLogString(char* logStr) { cout << logStr << WSAGetLastError() << endl; }


int main()
{
	char Buf[] = { 0 };
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData)) {
		debugLogString("WSAStartup error");
	}

	SOCKET hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (hSocket == SOCKET_ERROR)
	{
		debugLogString("hSocket error:");
		closesocket(hSocket);
	}

	SOCKADDR_IN sAddrSer = { 0 };
	sAddrSer.sin_family = AF_INET;
	sAddrSer.sin_addr.s_addr = htonl(ADDR_ANY);
	sAddrSer.sin_port = htons(8080);

	if (bind(hSocket, (SOCKADDR*)&sAddrSer, sizeof(sAddrSer)) == SOCKET_ERROR)
	{
		debugLogString("bind error:");
		closesocket(hSocket);
	}

	if (listen(hSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		debugLogString("listen error:");
		closesocket(hSocket);
	}

	fd_set readfds, writefds, exceptfds;
	FD_ZERO(&readfds);
	FD_ZERO(&writefds);
	FD_ZERO(&exceptfds);

	WSAAsyncSelect()

	return 0;
}