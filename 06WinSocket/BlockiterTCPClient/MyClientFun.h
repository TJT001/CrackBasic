#pragma once
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string.h>

#pragma comment (lib,"ws2_32.lib")

using std::cout;
using std::cin;
using std::endl;
#define nBuffSize 255  // 缓冲区

// 一个打印错误的函数
void debugLogString(char* logStr) { cout << logStr << WSAGetLastError() << endl; }

// 初始化
BOOL initSocket() {
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		debugLogString("initSocket-> WSAStartup error");
	}
	return TRUE;
}

SOCKET acceptSerFun(SOCKET hSocket)
{
	char szBuf[nBuffSize] = { 0 };
	hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (hSocket == INVALID_SOCKET)
	{
		debugLogString("acceptSerFun-> socket error");
		return INVALID_SOCKET;
	}

	sockaddr_in sAddrCli = { 0 };
	sAddrCli.sin_family = AF_INET;
	sAddrCli.sin_port = htons(8080);
	inet_pton(AF_INET, "127.0.0.1", &sAddrCli.sin_addr.S_un);

	int nRet = connect(hSocket, (sockaddr*)&sAddrCli, sizeof(sockaddr_in));
	
	if (nRet == SOCKET_ERROR)
	{
		debugLogString("acceptSerFun-> connect error");
		return INVALID_SOCKET;
	}

	// 发送数据
	strcpy_s(szBuf, "haven connect");
	nRet = send(hSocket, szBuf, nBuffSize, 0);

	if (!nRet)
	{
		debugLogString("acceptSerFun-> send error");
		closesocket(hSocket);
		WSACleanup();
	}

	while (nRet)
	{
		printf("请输入要发送的内容:");
		scanf_s("%s", szBuf, 255);

		// exit退出
		if (strcmp(szBuf, "exit") == 0) { break; }
		send(hSocket, szBuf, nBuffSize, 0);
	}

	return hSocket;
}

void MyClientFun()
{
	SOCKET cliSocket = { 0 };
	initSocket();
	if (acceptSerFun(cliSocket) == INVALID_SOCKET)
	{
		debugLogString("MyClientFun-> acceptSerFun error");
		closesocket(cliSocket);
		WSACleanup();
	}

}
