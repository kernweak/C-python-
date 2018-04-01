#pragma once
#include<vector>
#define BUFMSG 2048//һ�ν�����Ϣ������ֽ���
//ͷ����ͨѶĿ�ģ�����������¼������1v1���죬ע�ᣬ��¼����Ӻ��ѣ��������ѣ��ļ����䣬�鿴�����¼
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
//��������
//�����Ľṹ��
typedef struct _CHATANONYMOUS {
	DWORD dwLen;//�������Ƴ���
	char buf[50];//����
}CHATANONYMOUS;

typedef struct _CHATCHAT {
	DWORD dwLen;//�������ݳ���
	char buf[1024];
}CHATCHAT;

//1v1�ṹ��
typedef struct _CHATONE2ONE {
	CHAR szName[50];
	CHAR szContent[1024];
}CHATONE2ONE;

//ע��ṹ��
typedef struct _CHATREGISTER {
	CHAR szName[50];
	CHAR szPwd[50];
}CHATREGISTER;

//��¼�ṹ�壬���������ؽ������szName��
typedef struct _CHATLOGIN {
	CHAR szName[50];
	CHAR szPwd[50];
}CHATLOGIN;

//��Ӻ��ѽṹ��
typedef struct _CHATADDFRIEND {
	CHAR szName[50];//�Լ�����
	CHAR szFrd[50];//Ҫ��Ӻ�������
}CHATADDFRIEND;

//�����û��ṹ��
typedef struct _CHATSEARCHUSER {
	CHAR szName[50];//Ҫ�������û���
}CHATSEARCHUSER;

//�ļ�����ṹ��
typedef struct _CHATFILETRANS {

}CHATFILETRANS;

//�鿴�����¼�ṹ��
typedef struct _CHATMSGRECORD {
	CHAR szFrom[50];
	CHAR szTo[50];
	CHAR szContent[1024];
}CHATMSGRECORD;

//���������û��б�
typedef struct _CHATUPDATEUSER {

};

//�鿴����

class CClientScoket
{
public:
	CClientScoket();
	~CClientScoket();
	//��ʼ���ͻ����׽��֣����������ӷ�����
	bool ConnectServer(char* szIp, WORD port);
	//���𴴽��߳��������շ���������Ϣ
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

