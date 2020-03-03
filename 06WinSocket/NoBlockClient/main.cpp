#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

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
		debugLogString("Socket error:");
		closesocket(hSocket);
	}

	SOCKADDR_IN sAddrCli = { 0 };
	sAddrCli.sin_family = AF_INET;
	sAddrCli.sin_port = htons(8080);
	inet_pton(sAddrCli.sin_family, "127.0.0.1", &sAddrCli.sin_addr.S_un);
	int nLen = sizeof(sAddrCli);

	int nRet = connect(hSocket, (SOCKADDR*)&sAddrCli, nLen);
	if (nRet == SOCKET_ERROR)
	{
		debugLogString("connect error:");
		closesocket(hSocket);
	}
	nRet = send(hSocket, "have Connect", BufMaxSize, 0);

	while (nRet)
	{
		printf("请输入要发送的内容:");
		scanf_s("%s", Buf, 255);
		if (strcmp(Buf, "exit") == 0) { break; }
		nRet = send(hSocket,Buf,BufMaxSize,0);
	}

	return 0;
}