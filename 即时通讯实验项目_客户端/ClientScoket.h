#pragma once
#include<vector>
class CClientScoket
{
public:
	CClientScoket();
	~CClientScoket();
	//初始化客户端套接字，并尝试连接服务器
	bool ConnectServer(char* szIp, WORD port);
	//负责创建线程用来接收服务器的信息
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
	//保存聊天记录使用
	HANDLE m_hEvent = 0;
	vector<CHATMSGRECORD> m_vecMsgRecord;
	//客户端套接字
	SOCKET m_sClient = NULL;
	//新用户加入或退出聊天室用到
	CHATUPDATEUSER *m_pObjUpdate = nullptr;
	//1v1聊天的时候
	CHATONE2ONE *m_pObjOne2One = nullptr;
	//当前客户端的用户名
	char m_szName[BUFNAME] = {};
	CHATSEND *m_pObjChatRecv;
private:

};

