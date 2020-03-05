#include <iostream>
#include <WinSock2.h>
#pragma comment (lib,"ws2_32.lib")

using std::cout;
using std::cin;
using std::endl;

#define BufMaxSize 255  // ������

/**************************
 *						  *
 *ע�ͣ�  �����߼����Ż�     *
 *						  *
 **************************/


// һ����ӡ����ĺ���
void debugLogString(char* logStr) { cout << logStr << WSAGetLastError() << endl; }


int main()
{
	char Buf[] = { 0 };
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData)){
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

	int iMode = 1; // 1��ʾ������, 0��ʾ����
	int nRet = ioctlsocket(hSocket, FIONBIO, (u_long FAR *)&iMode);

	if (nRet)
	{
		debugLogString("ioctlsocket error:");
		closesocket(hSocket);
	}

	sockaddr_in addrCli = { 0 };
	SOCKET ClicSock = { 0 };
	int nCliAddrLen = sizeof(sockaddr_in);
	
	while (true)
	{
		// ���տͻ��˵�����  һֱ��������
		SOCKET ClicSock = accept(hSocket, (sockaddr*)&addrCli, &nCliAddrLen);
		if (ClicSock == INVALID_SOCKET)
		{
			int nError = GetLastError();
			if (nError == WSAEWOULDBLOCK){   // ��������
				Sleep(100);
				continue;
			}
			else{
				debugLogString("accept error:");
				closesocket(ClicSock);
				closesocket(hSocket);
				WSACleanup();
			}
		}
		else
		{
			memset(Buf, 0, BufMaxSize);
			int nRet = recv(ClicSock, Buf, BufMaxSize, 0);
			if (SOCKET_ERROR == nRet)
			{
				int nError = GetLastError();
				if (nError == WSAEWOULDBLOCK | Buf == "")  // ��������
				{
					Sleep(100);
					continue;
				}
				else if (nError == WSAETIMEDOUT || nError == WSAENETDOWN)
				{
					debugLogString("recv error:");
					closesocket(ClicSock);
					closesocket(hSocket);
					WSACleanup();
				}
			}
			cout << "���յ�������:" << Buf << endl;
		}

	}

	return 0;
}