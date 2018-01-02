#pragma once
#include "XHyperLink.h"

// Help 对话框

class Help : public CDialogEx
{
	DECLARE_DYNAMIC(Help)

public:
	Help(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Help();
	CStatic m_LinkStatic;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Help };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	CXHyperLink m_ctrlWebStatic;
	CXHyperLink m_ctrlWebStatic1;
};
