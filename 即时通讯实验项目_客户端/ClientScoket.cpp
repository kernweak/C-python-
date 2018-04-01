#include "stdafx.h"
#include "ClientScoket.h"


CClientScoket::CClientScoket()
{
}


CClientScoket::~CClientScoket()
{
}

bool CClientScoket::ConnectServer(char * szIp, WORD port)
{
	//1.��ʼ���׽��ֶ�̬��
	WSADATA wsd;
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0) {
		return false;
	}
	//��鷵�صĿ��Ƿ���2.2
	if (LOBYTE(wsd.wVersion) != 2 || HIBYTE(wsd.wHighVersion) != 2) {
		WSACleanup();
		return false;
	}
	//2.�����׽���
	m_sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_sClient == INVALID_SOCKET) {
		WSACleanup();
		return false;
	}
	//3.���÷�������ַ
	SOCKADDR_IN servAddr = {};//��������ַ
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(szIp);
	servAddr.sin_port = htons((short)port);
	//6.���ӷ�����
	//SOCKERT sService;//��������������׽���
	int nRetValue = connect(m_sClient, (sockaddr*)&servAddr, sizeof(SOCKADDR_IN));
	if (nRetValue == SOCKET_ERROR) {
		closesocket(m_sClient);
		m_sClient = NULL;
		WSACleanup();
		return false;
	}
	return true;
}


bool CClientScoket::Close()
{
	WSACleanup();
	closesocket(m_sClient);
	return true;
}

