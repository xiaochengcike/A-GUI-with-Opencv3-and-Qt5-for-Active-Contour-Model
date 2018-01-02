// Help.cpp : 实现文件
//

#include "stdafx.h"
#include "ACM.h"
#include "Help.h"
#include "afxdialogex.h"


// Help 对话框

IMPLEMENT_DYNAMIC(Help, CDialogEx)

Help::Help(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_Help, pParent)
{

}

Help::~Help()
{
}

void Help::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	CString help1;
	help1 = "This is a Graphical User Interface of Active Contour Model, including CV, RSF, DRLSE, LIF, LRCV, LGIF, LGDF, GMF model, and two improved methods.";
	GetDlgItem(IDC_HelpContent1)->SetWindowText(help1);

	CString help3;
	help3 = "This GUI is only for two-phase gray image segmentation. Please don't set parameters randomly, otherwise the program may be expired! For more information about the settting of parameters, please see Help.pdf. Note, this GUI may exists some bugs. If you find a serious bug or have any suggestion, please contact me through the Email below.";// http://www.escience.cn/people/dingkeyan/index.html
	GetDlgItem(IDC_HelpContent3)->SetWindowText(help3);

	DDX_Control(pDX, IDC_HelpContent2, m_ctrlWebStatic);
	m_ctrlWebStatic.SetWindowText(_T("Author: Keyan Ding"));
	m_ctrlWebStatic.SetURL(_T("https://www.researchgate.net/profile/Keyan_Ding2"));

	DDX_Control(pDX, IDC_HelpContent4, m_ctrlWebStatic1);
	m_ctrlWebStatic1.SetWindowText(_T("Email: dingkeyan93@outlook.com"));
	m_ctrlWebStatic1.SetURL(_T("mailto:dingkeyan93@outlook.com"));

}


BEGIN_MESSAGE_MAP(Help, CDialogEx)
END_MESSAGE_MAP()


// Help 消息处理程序
