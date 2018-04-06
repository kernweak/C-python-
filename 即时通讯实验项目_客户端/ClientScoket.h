#pragma once
#include<vector>
#include<fstream>
using namespace std;
#define BUFMSG 2048//������Ϣ����ֽ���
#define BUFCHAT 1024//����������󳤶�
#define BUFNAME 50 //��������ֽ���
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
	CHAR szName[BUFNAME];
	CHAR szContent[BUFCHAT];
}CHATFILETRANS;

//�鿴�����¼�ṹ��
typedef struct _CHATMSGRECORD {
	CHAR szFrom[50];
	CHAR szTo[50];
	CHAR szContent[1024];
}CHATMSGRECORD;

//���������û��б�
typedef struct _CHATUPDATEUSER {
	DWORD bAdd;//�Ǽ��뻹���˳�
	DWORD dwLen;//һ��ֻ����һ���û���
	CHAR buf[50];
}CHATUPDATEUSER;

//��������
typedef struct _CHATSEND {
	CHATPURPOSE m_type;
	union {
		char buf[BUFMSG];
		CHATANONYMOUS any;//����
		CHATCHAT chat;//����
		CHATONE2ONE o2o;//1v1
		CHATREGISTER reg;//ע��
		CHATLOGIN log;//��¼
		CHATADDFRIEND adf; //��Ӻ���
		CHATSEARCHUSER seu;//��������
		CHATFILETRANS trs;//�ļ�����
		CHATMSGRECORD rec;//�����¼
		CHATUPDATEUSER upd;//�����û��б�
	}m_content;
}CHATSEND;

//�鿴����

class CClientSocket
{
public:
	CClientSocket();
	~CClientSocket();
	//��ʼ���ͻ����׽��֣����������ӷ�����
	bool ConnectServer(char* szIp, WORD port);
	//���𴴽��߳��������շ���������Ϣ
	char* Recv();
	//BOOL Send(CHATPURPOSE purpose, char*bufSend, DWORD dwLen, SOCKET client = NULL);
	bool Send(CHATPURPOSE purpose, char*bufSend, DWORD dwLen,SOCKET client = NULL);
	bool Close();
private:
#define BUFNAME 50
	char m_bufRecv[BUFMSG] = {};
	fstream ReceiveFile;
	//recv function
	char* RecvForFiletrans();
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
	void SendForOne2One(char* bufSend, DWORD dwLen);
	void SendForRegister(char* bufSend, DWORD dwLen);
	void SendForLogin(char* bufSend, DWORD dwLen);
	void SendForAddFriend(char* bufSend, DWORD dwLen);
	void SendForSearchUser(char* bufSend, DWORD dwLen);
	void SendForGetMsgRecord(char* bufSend, DWORD dwLen);
	void SendForFiletrans(char* bufSend, DWORD dwLen,SOCKET client);
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

