#include <stdio.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib,"ws2_32.lib")

#define BUFSIZE 255


void TCPClientSock()
{
	// ��ʼ��
	WSADATA wsaData;
	SOCKET hClient = { 0 };
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	// ������ʽ�׽���
	hClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// ���ӵ�������
	sockaddr_in addrServer = {0};
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(0x8888);
	inet_pton(AF_INET, "127.0.0.1", &addrServer.sin_addr.S_un);
	connect(hClient, (SOCKADDR*)&addrServer, sizeof(addrServer));

	// �շ�����
	char szBuff[BUFSIZE];
	recv(hClient, szBuff, strlen(szBuff), 0);
	printf("Server:%s\n", szBuff);

	char strSend[BUFSIZE] = { "How are you!" };
	send(hClient, strSend, strlen(strSend), 0);
	
	getchar();
	// ������
	closesocket(hClient);
	WSACleanup();
}

void UDPClientSock()
{
	char szBuf[BUFSIZE] = "haven connect";
	// ��ʼ��
	WSADATA wsaData = { 0 };
	SOCKET sockClient = { 0 };
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("WSAStartupʧ��\n");
		return;
	}

	// ���� UDP����
	sockClient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sockClient == INVALID_SOCKET)
	{
		printf("socket ʧ��\n");
		closesocket(sockClient);
		WSACleanup();
		return;
	}

	// ��  ��дIP�Ͷ˿�
	sockaddr_in addrSer = { 0 };
	addrSer.sin_family = AF_INET;
	addrSer.sin_port = htons(8888);
	inet_pton(addrSer.sin_family, "127.0.0.1", &addrSer.sin_addr.S_un);
	
	int serAddrLen = sizeof(sockaddr_in);
	int nRet = sendto(sockClient, szBuf, sizeof(szBuf), 0, (SOCKADDR*)&addrSer, serAddrLen);

	if (!nRet)
	{
		printf("sendtoʧ��\n");
		closesocket(sockClient);
		WSACleanup();
		return;
	}

	while (nRet)
	{
		printf("������Ҫ���͵�����:");
		scanf_s("%s", szBuf, 255);
		if (strcmp(szBuf, "exit") == 0) { break; }
		nRet = sendto(sockClient, szBuf, sizeof(szBuf), 0, (SOCKADDR*)&addrSer, serAddrLen);
	}

	//int nError = WSAGetLastError();

	// ������
	closesocket(sockClient);
	WSACleanup();
}

int main()
{
	UDPClientSock();
	return 0;
}