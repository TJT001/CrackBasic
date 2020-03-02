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
	char szBuf[BUFSIZE] = "haven connect";
	// 初始化
	WSADATA wsaData = { 0 };
	SOCKET sockClient = { 0 };
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("WSAStartup失败\n");
		return;
	}

	// 创建 UDP类型
	sockClient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sockClient == INVALID_SOCKET)
	{
		printf("socket 失败\n");
		closesocket(sockClient);
		WSACleanup();
		return;
	}

	// 绑定  填写IP和端口
	sockaddr_in addrSer = { 0 };
	addrSer.sin_family = AF_INET;
	addrSer.sin_port = htons(8888);
	inet_pton(addrSer.sin_family, "127.0.0.1", &addrSer.sin_addr.S_un);
	
	int serAddrLen = sizeof(sockaddr_in);
	int nRet = sendto(sockClient, szBuf, sizeof(szBuf), 0, (SOCKADDR*)&addrSer, serAddrLen);

	if (!nRet)
	{
		printf("sendto失败\n");
		closesocket(sockClient);
		WSACleanup();
		return;
	}

	while (nRet)
	{
		printf("请输入要发送的内容:");
		scanf_s("%s", szBuf, 255);
		if (strcmp(szBuf, "exit") == 0) { break; }
		nRet = sendto(sockClient, szBuf, sizeof(szBuf), 0, (SOCKADDR*)&addrSer, serAddrLen);
	}

	//int nError = WSAGetLastError();

	// 清理环境
	closesocket(sockClient);
	WSACleanup();
}

int main()
{
	UDPClientSock();
	return 0;
}