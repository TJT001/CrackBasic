#include "MyTCPFun.h"

/***********************

 阻塞迭代式

************************/

int main()
{
	// 初始化
	initSocket();

	// 业务数据处理
	MySerFun();

	// 释放资源
	WSACleanup();

	getchar();
	return 0;
}