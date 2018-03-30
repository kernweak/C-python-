#pragma once
#include<vector>
class CClientScoket
{
public:
	CClientScoket();
	~CClientScoket();
	//��ʼ���ͻ����׽��֣����������ӷ�����
	bool ConnectServer(char* szIp, WORD port);
	//���𴴽��߳��������շ���������Ϣ
	char* Recv();
	bool Send(CHATPURPSE purpose, char*bufSend, DWORD dwLen);
	bool Close();
private:
#define BUFNAME 50
	char m_bufRecv[BUFMSG] = {};
	//recv function
	char* RecvForAnonumous();
	char* RecvForChat();
	char* RecvForUpdataUserList();
	char* RecvForOne2One();
	char* RecvForRegister();
	char* RecvForLogin();
	char* RecvForAddFriend();
	char* RecvForSearchUser();
	char* RecvForGetMsgRecord();
	//send function
	void SendForAnonymous(char* bufSend, DWORD dwLen);
	void SendForChat(char* bufSend, DWORD dwLen);
	void SendForOne2One(char* vufSend, DWORD dwLen);
	char* SendForRegister();
	char* SendForLogin();
	char* SendForAddFriend();
	char* SendForSearchUser();
	char* SendForGetMsgRecord();
public:
	//���������¼ʹ��
	HANDLE m_hEvent = 0;
	vector<CHATMSGRECORD> m_vecMsgRecord;
	//�ͻ����׽���
	SOCKET m_sClient = NULL;
	//���û�������˳��������õ�
	CHATUPDATEUSER *m_pObjUpdate = nullptr;
	//1v1�����ʱ��
	CHATONE2ONE *m_pObjOne2One = nullptr;
	//��ǰ�ͻ��˵��û���
	char m_szName[BUFNAME] = {};
	CHATSEND *m_pObjChatRecv;
private:

};

