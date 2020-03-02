#include <stdio.h>
#include <WinSock2.h>
#include <ws2tcpip.h>

#pragma comment(lib,"ws2_32.lib") // ����Socket2��ͷ�ļ�

#define BUFSIZE 255

void TCPServSock()
{
	WSADATA wsaData;
	SOCKET hServer = { 0 };
	WORD vVersion = MAKEWORD(2, 2);

	if (WSAStartup(vVersion, &wsaData))
	{
		printf("WSAStartup\n");
		return ;
	}

	// ���ڴ�������ָ���ķ����ṩ�߽��а�  tcp����
	hServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (hServer == INVALID_SOCKET)
	{
		printf("socket ʧ��\n");
	}

	
	sockaddr_in addrServer = { 0 };
	addrServer.sin_family = AF_INET;
	//addrServer.sin_port = htons(0x8888);
	addrServer.sin_addr.s_addr = htonl(INADDR_ANY);
	inet_pton(AF_INET, "127.0.0.1", &addrServer.sin_addr.S_un);

	// ��
	int nRet = bind(hServer, (sockaddr*)&addrServer, sizeof(addrServer));
	if (nRet == SOCKET_ERROR)
	{
		printf("bindʧ��\n");
		closesocket(hServer);
		WSACleanup();
		return;
	}

	// ����
	nRet = listen(hServer, 2); //����˭��������ɵĿͻ�������
	// int nError = WSAGetLastError();

	/*if (nRet = SOCKET_ERROR)
	{
		printf("listenʧ��\n");
		closesocket(hServer);
		WSACleanup();
		return;
	}*/

	// �������Կͻ��˵�����
	SOCKET hClient;
	sockaddr_in addrClient = { 0 };
	int nLen = sizeof(addrClient);


	// �������Կͻ��˵�����
	hClient = accept(hServer, (sockaddr*)&addrClient, &nLen);
	if (INVALID_SOCKET == hClient)
	{
		printf("accept ʧ��\n");
		closesocket(hServer);
		WSACleanup();
		return;
	}

	char szBuf[BUFSIZE];

	// ѭ�����տͻ��˵�����
	while (true)
	{
		memset(szBuf, 0, BUFSIZE);
		nRet = recv(hClient, szBuf, BUFSIZE, 0);
		if (nRet == SOCKET_ERROR)
		{
			printf("recv ʧ��\n");
			closesocket(hServer);
			WSACleanup();
			return;
		}

		char sPrintfBuf[BUFSIZE];
		sprintf_s(sPrintfBuf, "IP:%s,���յ���Ϣ:%s", 
			inet_ntop(addrClient.sin_family,&addrClient.sin_addr,szBuf,sizeof(szBuf)), szBuf);
		// sprintf_s(sPrintfBuf, "IP:%s,���յ���Ϣ:%s", inet_ntop((INT)addrClient.sin_addr,));
		printf(sPrintfBuf);

		// ���͸��ͻ��˵�����
		if (strcmp(szBuf, "close") == 0)
		{
			nRet = send(hClient, "close", strlen("close"), 0);
			break;
		}
		else
		{
			sprintf_s(sPrintfBuf, "�Ѿ����յ������Ϣ��%s", szBuf);
			nRet = recv(hClient, sPrintfBuf, strlen(sPrintfBuf), 0);
			if (SOCKET_ERROR == nRet)
			{
				printf("send ����\n");
				closesocket(hClient);
				closesocket(hServer);
				WSACleanup();
				return;
			}
		}
	}

	closesocket(hClient);
	closesocket(hServer);
	WSACleanup();
}


void UDPServerSock()
{
	char szBuf[BUFSIZE];
	// ��ʼ��
	WSADATA wsaData = { 0 };
	SOCKET sockServer = { 0 };
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("WSAStartupʧ��\n");
	}

	// ���� UDP���� -> SOCK_DGRAM
	sockServer = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sockServer == INVALID_SOCKET)
	{
		printf("socket ʧ��\n");
		return;
	}


	// ��  ��дIP�Ͷ˿�
	sockaddr_in addrSer = { 0 };
	
	addrSer.sin_family = AF_INET;
	addrSer.sin_port = htons(8888);
	// inet_pton(addrSer.sin_family, "127.0.0.1", &addrSer.sin_addr.S_un);
	addrSer.sin_addr.s_addr = htonl(ADDR_ANY);
	//addrSer.sin_addr.s_addr = inet_addr("127.0.0.1");
	int nAddrLen = sizeof(sockaddr_in);
	int nRet = bind(sockServer, (SOCKADDR*)&addrSer, nAddrLen);
	int nError = WSAGetLastError();

	if (nRet == SOCKET_ERROR)
	{
		printf("bind ʧ��\n");
	}

	sockaddr_in ClientAddr = { 0 };
	int clientAddrLen = sizeof(sockaddr_in);
	nRet = recvfrom(sockServer, szBuf, 512, 0, (SOCKADDR*)&ClientAddr, &clientAddrLen);

	while (nRet)
	{	
		printf("�ѽ���:%s\n",szBuf);
		recvfrom(sockServer, szBuf, 512, 0, (SOCKADDR*)&ClientAddr, &clientAddrLen);
	}

	// ������
	closesocket(sockServer);
	WSACleanup();
}

int main()
{
	UDPServerSock();
	return 0;
}


/*  ����Ҫ��ע�Ľṹ��
	typedef struct sockaddr_in {

	 #if(_WIN32_WINNT < 0x0600)
		short   sin_family;
	 #else //(_WIN32_WINNT < 0x0600)
		ADDRESS_FAMILY sin_family;
	 #endif //(_WIN32_WINNT < 0x0600)

		USHORT sin_port;
		IN_ADDR sin_addr;
		CHAR sin_zero[8];
	} SOCKADDR_IN, *PSOCKADDR_IN;


	typedef struct in_addr {
		union {
				struct { UCHAR s_b1,s_b2,s_b3,s_b4; } S_un_b;
				struct { USHORT s_w1,s_w2; } S_un_w;
				ULONG S_addr;
		} S_un;
	#define s_addr  S_un.S_addr    // can be used for most tcp & ip code
	#define s_host  S_un.S_un_b.s_b2    // host on imp
	#define s_net   S_un.S_un_b.s_b1    // network
	#define s_imp   S_un.S_un_w.s_w2    // imp
	#define s_impno S_un.S_un_b.s_b4    // imp #
	#define s_lh    S_un.S_un_b.s_b3    // logical host
	} IN_ADDR, *PIN_ADDR, FAR *LPIN_ADDR
	*/