#include "MyTCPFun.h"

/***********************

 ��������ʽ

************************/

int main()
{
	// ��ʼ��
	initSocket();

	// ҵ�����ݴ���
	MySerFun();

	// �ͷ���Դ
	WSACleanup();

	getchar();
	return 0;
}