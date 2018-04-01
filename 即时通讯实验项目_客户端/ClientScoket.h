#pragma once
#include<vector>
#define BUFMSG 2048//一次接收消息的最大字节数
//头部：通讯目的，包括匿名登录，聊天1v1聊天，注册，登录，添加好友，搜索好友，文件传输，查看聊天记录
enum CHATPURPOSE {
	ANONYMOUS = 1,
	CHAT,
	ONE2ONE,
	REGISTER,
	LOGIN,
	ADDFRIEND,
	SEARCHUSER,
	FILETRANS,
	MSGRECORD,
	UPDATEUSER
};
//聊天内容
//匿名的结构体
typedef struct _CHATANONYMOUS {
	DWORD dwLen;//匿名名称长度
	char buf[50];//匿名
}CHATANONYMOUS;

typedef struct _CHATCHAT {
	DWORD dwLen;//聊天内容长度
	char buf[1024];
}CHATCHAT;

//1v1结构体
typedef struct _CHATONE2ONE {
	CHAR szName[50];
	CHAR szContent[1024];
}CHATONE2ONE;

//注册结构体
typedef struct _CHATREGISTER {
	CHAR szName[50];
	CHAR szPwd[50];
}CHATREGISTER;

//登录结构体，服务器返回结果放在szName里
typedef struct _CHATLOGIN {
	CHAR szName[50];
	CHAR szPwd[50];
}CHATLOGIN;

//添加好友结构体
typedef struct _CHATADDFRIEND {
	CHAR szName[50];//自己姓名
	CHAR szFrd[50];//要添加好友姓名
}CHATADDFRIEND;

//搜索用户结构体
typedef struct _CHATSEARCHUSER {
	CHAR szName[50];//要搜索的用户名
}CHATSEARCHUSER;

//文件传输结构体
typedef struct _CHATFILETRANS {

}CHATFILETRANS;

//查看聊天记录结构体
typedef struct _CHATMSGRECORD {
	CHAR szFrom[50];
	CHAR szTo[50];
	CHAR szContent[1024];
}CHATMSGRECORD;

//更新在线用户列表
typedef struct _CHATUPDATEUSER {

};

//查看聊天

class CClientScoket
{
public:
	CClientScoket();
	~CClientScoket();
	//初始化客户端套接字，并尝试连接服务器
	bool ConnectServer(char* szIp, WORD port);
	//负责创建线程用来接收服务器的信息
	char* Recv();
	bool Send(CHATPURPOSE purpose, char*bufSend, DWORD dwLen);
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

