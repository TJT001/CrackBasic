#pragma once
#include <iostream>
#include <WinSock2.h>
#pragma comment (lib,"ws2_32.lib")

using std::cout;
using std::cin;
using std::endl;
#define nBuffSize 512  // ������

// һ����ӡ����ĺ���
void debugLogString(char* logStr) { cout << logStr << WSAGetLastError() << endl; }

// ��ʼ��
BOOL initSocket(){
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		debugLogString("initSocket-> WSAStartup error");
	}
	return TRUE;
}

// �������ӣ��󶨺ͼ���
SOCKET bind_listen(int nBacklog)
{
	SOCKET hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (hSocket == SOCKET_ERROR)
	{
		debugLogString("hSocket error:");
	}

	SOCKADDR_IN sAddrSer = { 0 };
	sAddrSer.sin_family = AF_INET;
	sAddrSer.sin_addr.s_addr = htonl(ADDR_ANY);
	sAddrSer.sin_port = htons(0x8888);

	if (bind(hSocket, (SOCKADDR*)&sAddrSer, sizeof(sAddrSer)) == SOCKET_ERROR)
	{
		debugLogString("bind error:");
		closesocket(hSocket);
		return INVALID_SOCKET;
	} 

	if (listen(hSocket, nBacklog) == SOCKET_ERROR)
	{
		debugLogString("listen error:");
		closesocket(hSocket);
		return INVALID_SOCKET;
	}

	return hSocket;
}

// ����һ���ͻ��˵����Ӳ����ض�Ӧ���ӵ��׽���
SOCKET acceptConection(SOCKET socket)
{
	sockaddr_in sAddrConect = { 0 };
	int nAcceptLen = sizeof(sockaddr_in);
	if (accept(socket, (SOCKADDR*)&sAddrConect, &nAcceptLen)
		== INVALID_SOCKET)
	{
		debugLogString("acceptConect error:");
		return INVALID_SOCKET;
	}
	return socket;
}

// ����һ���ͻ��˵����ӣ�ʵ�ֽ��պͷ�������
BOOL clientConFun(SOCKET socket)
{
	char szBuf[nBuffSize] = { 0 };
	int nRetByte = 0;  // ���ص��ֽڳ���
	// ѭ������
	do {
		nRetByte = recv(socket, szBuf, nBuffSize, 0);
		if (nRetByte == SOCKET_ERROR)
		{
			debugLogString("clientConFun->recv error:");
			return FALSE;
		}
		else if(nRetByte != 0)
		{
			cout << "���յ�һ������:" << szBuf << endl;
			int nSend = 0;
			while (nSend < nRetByte){
				// �ѽ��յ����ٷ���ȥ
				int nTemp = send(socket, szBuf, nBuffSize, 0);
				if(nTemp > 0){
					nSend += nTemp;
				}
				else if(nTemp == SOCKET_ERROR){
					debugLogString("clientConFun->send error:");
					return FALSE;
				}
				else {
					// �����㣬��ʾ����û�б����ͳ�ȥ���ͻ��˱�����ر�
					debugLogString("clientConFun->send or close:");
				}
			}
		}
	} while (nRetByte != 0);

	return TRUE;
}


// �ر�����
BOOL closeConnect(SOCKET socket)
{
	// ���ȷ���һ��TCP FIN�ֶΣ���Է������Ѿ�������ݴ���
	if (shutdown(socket, SD_SEND) == SOCKET_ERROR)
	{
		debugLogString("closeConnect->shutdown error:");
		return FALSE;
	}

	char szBuf[nBuffSize] = { 0 };
	int nRetByte = 0;  // ���ص��ֽڳ���
	// ѭ������
	do {
		nRetByte = recv(socket, szBuf, nBuffSize, 0);
		if (nRetByte == SOCKET_ERROR)
		{
			debugLogString("clientConFun->recv error:");
			// return FALSE;
			break;
		}
		else if (nRetByte > 0)
		{
			debugLogString("closeConnect-> ����Ľ�������");
			// return FALSE;
			break;
		}
	} while (nRetByte != 0);

	if (closesocket(socket) == SOCKET_ERROR)
	{
		debugLogString("closeConnect->closesocket error:");
		return FALSE;
	}
	return TRUE;
}


// ����������

void MySerFun()
{
	SOCKET hSocket = bind_listen(3);
	if (hSocket == INVALID_SOCKET)
	{
		debugLogString("MySerFun->bind_listen error:");
		return;
	}

	while (true)
	{
		SOCKET sd = acceptConection(hSocket);
		if (sd == INVALID_SOCKET){
			debugLogString("MySerFun->acceptConection error:");
		}

		// �ͻ��˴���
		if (clientConFun(sd) == FALSE) {
			debugLogString("MySerFun->clientConFun error:");
		}

		// �ر�һ���ͻ�������
		if (closeConnect(sd) == FALSE) {
			break;
		}
	}
	
	if (closesocket(hSocket) == SOCKET_ERROR)
	{
		debugLogString("MySerFun->closesocket error:");
		return;
	}
}