
// ACM.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CACMApp: 
// �йش����ʵ�֣������ ACM.cpp
//

class CACMApp : public CWinApp
{
public:
	CACMApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CACMApp theApp;