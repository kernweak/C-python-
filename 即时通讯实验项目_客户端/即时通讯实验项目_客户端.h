
// ��ʱͨѶʵ����Ŀ_�ͻ���.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// C��ʱͨѶʵ����Ŀ_�ͻ���App: 
// �йش����ʵ�֣������ ��ʱͨѶʵ����Ŀ_�ͻ���.cpp
//

class C��ʱͨѶʵ����Ŀ_�ͻ���App : public CWinApp
{
public:
	C��ʱͨѶʵ����Ŀ_�ͻ���App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern C��ʱͨѶʵ����Ŀ_�ͻ���App theApp;