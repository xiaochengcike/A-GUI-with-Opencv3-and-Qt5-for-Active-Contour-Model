#pragma once
#include "XHyperLink.h"

// Help �Ի���

class Help : public CDialogEx
{
	DECLARE_DYNAMIC(Help)

public:
	Help(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Help();
	CStatic m_LinkStatic;
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Help };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	CXHyperLink m_ctrlWebStatic;
	CXHyperLink m_ctrlWebStatic1;
};
