#include <stdio.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib,"ws2_32.lib")

#define BUFSIZE 255


void TCPClientSock()
{
	// 初始化
	WSADATA wsaData;
	SOCKET hClient = { 0 };
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	// 建立流式套接字
	hClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// 连接到服务器
	sockaddr_in addrServer = {0};
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(0x8888);
	inet_pton(AF_INET, "127.0.0.1", &addrServer.sin_addr.S_un);
	connect(hClient, (SOCKADDR*)&addrServer, sizeof(addrServer));

	// 收发数据
	char szBuff[BUFSIZE];
	recv(hClient, szBuff, strlen(szBuff), 0);
	printf("Server:%s\n", szBuff);

	char strSend[BUFSIZE] = { "How are you!" };
	send(hClient, strSend, strlen(strSend), 0);
	
	getchar();
	// 清理环境
	closesocket(hClient);
	WSACleanup();
	
}

void UDPClientSock()
{
	char szBuf[BUFSIZE] = {"123456789"};
	// 初始化
	WSADATA wsaData = { 0 };
	SOCKET sockClient = { 0 };
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	// 创建 UDP类型
	int nRet = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (nRet == INVALID_SOCKET)
	{
		printf("socket 失败\n");
		return;
	}

	// 绑定  填写IP和端口
	sockaddr_in addrClient;
	addrClient.sin_family = AF_INET;
	addrClient.sin_port = htons(0x8080);
	addrClient.sin_addr.s_addr = inet_pton(addrClient.sin_family,"127.0.0.1",&addrClient.sin_addr.S_un);
	

	sockaddr_in ServerAddr = { 0 };
	int clientAddrLen = sizeof(addrClient);
	// recvfrom(sockServer, szBuf, 512, 0, (SOCKADDR*)&ClientAddr, &clientAddrLen);
	sendto(sockClient, szBuf, BUFSIZE, 0, (SOCKADDR*)&ServerAddr, clientAddrLen);
	getchar();
	printf(szBuf);
	printf("发送成功\n");

	closesocket(sockClient);
	WSACleanup();
}

int main()
{
	UDPClientSock();
	return 0;
}