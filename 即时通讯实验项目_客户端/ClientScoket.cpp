#include "stdafx.h"
#include "ClientScoket.h"
#include <WS2tcpip.h>
CClientSocket::CClientSocket()
{
}


CClientSocket::~CClientSocket()
{
}

bool CClientSocket::ConnectServer(char * szIp, WORD port)
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
	//servAddr.sin_addr.s_addr = inet_addr(szIp);
	inet_pton(AF_INET, szIp, &servAddr.sin_addr);
	//szIp = inet_ntop(AF_INET, &servAddr.sin_addr.s_addr, str, sizeof(str));
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


char * CClientSocket::Recv()
{
	CHATSEND ct = {};

	if (SOCKET_ERROR == recv(m_sClient, (char*)&ct, sizeof(CHATSEND), NULL)) {
		printf("recv error!\n");
		return nullptr;
	}
	m_pObjChatRecv = &ct;
	switch (ct.m_type) {
	case ANONYMOUS:
		return RecvForAnonumous();
	case CHAT:
		return RecvForChat();
		break;
	case ONE2ONE:
		return RecvForOne2One();
		break;
	case REGISTER:
		return RecvForRegister();
	case LOGIN:
		return RecvForLogin();
//case ADDFRIEND:
//	return RecvForAddFriend();
//case SEARCHUSER:
//	return RecvForSearchUser();
//case FILETRANS:
//	break;
//case MSGRECORD:
//	return RecvForGetMsgRecord();
	case UPDATEUSER:
		return RecvForUpdataUserList();
	default:
		break;
	}
	return nullptr;
}

bool CClientSocket::Send(CHATPURPOSE purpose, char * bufSend, DWORD dwLen)
{
	switch (purpose)
	{
	case ANONYMOUS:
		SendForAnonymous(bufSend, dwLen);
		break;
	case CHAT:
		SendForChat(bufSend, dwLen);
		break;
	case ONE2ONE:
		SendForOne2One(bufSend, dwLen);
		break;
	case REGISTER:
		SendForRegister(bufSend,dwLen);
		break;
	case LOGIN:
		SendForLogin(bufSend, dwLen);
		break;
//case ADDFRIEND:
//	SendForAddFriend(bufSend, dwLen);
//	break;
//case SEARCHUSER:
//	SendForSearchUser(bufSend, dwLen);
//	break;
//case FILETRANS:
//	break;
//case MSGRECORD:
//	SendForGetMsgRecord(bufSend, dwLen);
//	break;
	case UPDATEUSER:
		break;
	default:
		break;
	}
	return false;
}

bool CClientSocket::Close()
{
	WSACleanup();
	closesocket(m_sClient);
	return true;
}

char * CClientSocket::RecvForAnonumous()
{
	sprintf_s(m_bufRecv, BUFMSG, "%s���������ң�\n", m_pObjChatRecv->m_content.any.buf);
	return m_bufRecv;
}

char * CClientSocket::RecvForChat()
{
	for (int i = 0;i < m_pObjChatRecv->m_content.chat.dwLen;i++) {
		m_pObjChatRecv->m_content.chat.buf[i] ^= 15;
	}
	strcpy_s(m_bufRecv, m_pObjChatRecv->m_content.chat.buf);
	return m_bufRecv;
}

char * CClientSocket::RecvForUpdataUserList()
{
	//���û����룬���µ��û��б���
	m_pObjUpdate = new CHATUPDATEUSER;
	memcpy_s(m_pObjUpdate, sizeof(CHATUPDATEUSER), &m_pObjChatRecv->m_content.upd, sizeof(CHATUPDATEUSER));
	return nullptr;
}

char * CClientSocket::RecvForOne2One()
{//���û����룬���µ��û��б���
	m_pObjOne2One = new CHATONE2ONE;
	memcpy_s(m_pObjOne2One, sizeof(CHATONE2ONE), &m_pObjChatRecv->m_content.o2o, sizeof(CHATONE2ONE));
		return nullptr;
}

char * CClientSocket::RecvForRegister()
{
	if (!strcmp(m_pObjChatRecv->m_content.log.szName, "ע��ɹ�!")) {
		return "ע��ɹ���";

	}
	else {
		return nullptr;
	}
	
}

char * CClientSocket::RecvForLogin()
{
	if (!strcmp(m_pObjChatRecv->m_content.log.szName, "��¼�ɹ�!")) {
		return "��¼�ɹ���";

	}
	else {
		return nullptr;
	}
}

void CClientSocket::SendForAnonymous(char * bufSend, DWORD dwLen)
{
	CHATSEND ct = { ANONYMOUS };
	//���� ����+�ǳ�
	strcpy_s(ct.m_content.chat.buf, bufSend);
	ct.m_content.chat.dwLen = dwLen;
	send(m_sClient, (char*)&ct, sizeof(ct), NULL);
}

void CClientSocket::SendForChat(char * bufSend, DWORD dwLen)
{
	CHATSEND ct = { CHAT };
	//���� ���ȼ�����������
	strcpy_s(ct.m_content.chat.buf, m_szName);
	strcpy_s(ct.m_content.chat.buf, ":");
	strcpy_s(ct.m_content.chat.buf, bufSend);
	ct.m_content.chat.dwLen = strlen(ct.m_content.chat.buf) + 1;
	//����
	for (int i = 0;i < ct.m_content.any.dwLen;i++) {
		ct.m_content.chat.buf[i] ^= 15;
	}
	send(m_sClient, (char*)&ct, sizeof(ct), NULL);
}

void CClientSocket::SendForOne2One(char * bufSend, DWORD dwLen)
{
	CHATSEND ct = { ONE2ONE };
	char* nextToken = nullptr;
	char* szContext = strtok_s(bufSend, ":", &nextToken);
	memcpy_s(ct.m_content.o2o.szName, nextToken - bufSend, bufSend, nextToken - bufSend);
	memcpy_s(ct.m_content.o2o.szContent, strlen(nextToken), nextToken, strlen(nextToken));
	send(m_sClient, (char*)&ct, sizeof(ct), NULL);

}

void CClientSocket::SendForRegister(char * bufSend, DWORD dwLen)
{
	CHATSEND ct = { REGISTER };
	char* pwd = nullptr;
	strtok_s(bufSend, ":", &pwd);
	memcpy_s(ct.m_content.reg.szName, pwd - bufSend, bufSend, pwd - bufSend);
	memcpy_s(ct.m_content.reg.szPwd, strlen(pwd), pwd, strlen(pwd));
	send(m_sClient, (char*)&ct, sizeof(ct), NULL);
}
void CClientSocket::SendForLogin(char * bufSend, DWORD dwLen)
{
	CHATSEND ct = { LOGIN };
	char* pwd = nullptr;
	strtok_s(bufSend, ":", &pwd);
	memcpy_s(ct.m_content.log.szName, pwd - bufSend, bufSend, pwd - bufSend);
	memcpy_s(ct.m_content.log.szPwd, strlen(pwd), pwd, strlen(pwd));
	send(m_sClient, (char*)&ct, sizeof(ct), NULL);
}
