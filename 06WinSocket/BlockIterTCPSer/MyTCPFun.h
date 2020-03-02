#pragma once
#include <iostream>
#include <WinSock2.h>
#pragma comment (lib,"ws2_32.lib")

using std::cout;
using std::cin;
using std::endl;
#define nBuffSize 512  // 缓冲区

// 一个打印错误的函数
void debugLogString(char* logStr) { cout << logStr << WSAGetLastError() << endl; }

// 初始化
BOOL initSocket(){
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		debugLogString("initSocket-> WSAStartup error");
	}
	return TRUE;
}

// 处理连接，绑定和监听
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

// 接收一个客户端的连接并返回对应连接的套接字
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

// 处理一个客户端的连接，实现接收和发送数据
BOOL clientConFun(SOCKET socket)
{
	char szBuf[nBuffSize] = { 0 };
	int nRetByte = 0;  // 返回的字节长度
	// 循环处理
	do {
		nRetByte = recv(socket, szBuf, nBuffSize, 0);
		if (nRetByte == SOCKET_ERROR)
		{
			debugLogString("clientConFun->recv error:");
			return FALSE;
		}
		else if(nRetByte != 0)
		{
			cout << "接收到一条数据:" << szBuf << endl;
			int nSend = 0;
			while (nSend < nRetByte){
				// 把接收到的再发回去
				int nTemp = send(socket, szBuf, nBuffSize, 0);
				if(nTemp > 0){
					nSend += nTemp;
				}
				else if(nTemp == SOCKET_ERROR){
					debugLogString("clientConFun->send error:");
					return FALSE;
				}
				else {
					// 返回零，表示数据没有被发送出去，客户端被意外关闭
					debugLogString("clientConFun->send or close:");
				}
			}
		}
	} while (nRetByte != 0);

	return TRUE;
}


// 关闭连接
BOOL closeConnect(SOCKET socket)
{
	// 首先发送一个TCP FIN分段，向对方表明已经完成数据传送
	if (shutdown(socket, SD_SEND) == SOCKET_ERROR)
	{
		debugLogString("closeConnect->shutdown error:");
		return FALSE;
	}

	char szBuf[nBuffSize] = { 0 };
	int nRetByte = 0;  // 返回的字节长度
	// 循环处理
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
			debugLogString("closeConnect-> 错误的接收数据");
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


// 服务器主体

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

		// 客户端处理
		if (clientConFun(sd) == FALSE) {
			debugLogString("MySerFun->clientConFun error:");
		}

		// 关闭一个客户端连接
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