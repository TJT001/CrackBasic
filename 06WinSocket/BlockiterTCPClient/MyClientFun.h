#pragma once
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment (lib,"ws2_32.lib")

using std::cout;
using std::cin;
using std::endl;
#define nBuffSize 512  // ������

// һ����ӡ����ĺ���
void debugLogString(char* logStr) { cout << logStr << WSAGetLastError() << endl; }

// ��ʼ��
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
	hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (hSocket == INVALID_SOCKET)
	{
		debugLogString("acceptSerFun-> socket error");
		return INVALID_SOCKET;
	}

	sockaddr_in sAddrCli = { 0 };
	sAddrCli.sin_family = AF_INET;
	sAddrCli.sin_port = htons(0x8888);
	inet_pton(AF_INET, "127.0.0.1", &sAddrCli.sin_addr.S_un);

	if (connect(hSocket, (sockaddr*)&sAddrCli, sizeof(sockaddr_in))
		== INVALID_SOCKET)
	{
		debugLogString("acceptSerFun-> socket error");
		return INVALID_SOCKET;
	}

	// ��������
	char szBuf[nBuffSize] = "haven connect";
	int nRet = send(hSocket, szBuf, nBuffSize, 0);

	if (!nRet)
	{
		printf("sendtoʧ��\n");
		closesocket(hSocket);
		WSACleanup();
	}

	while (nRet)
	{
		printf("������Ҫ���͵�����:");
		scanf_s("%s", szBuf, 255);
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
	}

}
