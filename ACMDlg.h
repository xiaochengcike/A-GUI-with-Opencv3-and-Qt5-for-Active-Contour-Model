
// ACMDlg.h : 头文件
//

#pragma once
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

// CACMDlg 对话框
class CACMDlg : public CDialogEx
{
// 构造
public:
	CACMDlg(CWnd* pParent = NULL);	// 标准构造函数

	Mat Image;//原图
	Mat Image_;//原彩色图
	Mat image;//结果图
	Mat mask;//掩摹图
	uint ImgWidth;
	uint Imgheight;
	CString FileName;//图像名称
	BOOL IsInitialization;//初始化标志

	Mat IC_Img;//鼠标选点
	string MouseEvent;//鼠标事件
	vector<Point>ICPoint;
	int PIndex = 0;
	Mat Roipoly;

	BOOL IsExchange;//同向拟合标志
	BOOL IsPreFitting;//预拟合标志

	struct Parameters//声明一个结构体类型Parameters
	{
		uint num;
		float step;
		float epison;
		float nu;
		float mu;
		float lamda1;
		float lamda2;
		float sig;
		float lamda;
		float alfa;
		float weight;
		uint SE_radius;
		uint interval;
	} para;  

	struct Showing//声明一个结构体类型Show
	{
		uint linewidth;
		uint colorR;
		uint colorG;
		uint colorB;
	} Show;

	void ShowImage(Mat Img, UINT ID);//在MFC控件上显示图片
	void DrawContour(Mat LSF, Mat Img);//画轮廓
	Mat InitialContour();//传入初始轮廓
	void UpdataEdit_InitialContour();//更新EDIT
	void GetParameters();//得到模型参数
	void GetShow();//得到显示参数
	void Implement_ACM(CString ACM);//执行ACM主程序
	vector<Mat> Pre_Fitting(Mat Img, Mat Kernel);//预拟合函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ACM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpenimage();
	afx_msg void OnBnClickedCv();
	afx_msg void OnBnClickedRsf();
	afx_msg void OnBnClickedDrlse();
	afx_msg void OnEnChangeRow1();
	afx_msg void OnEnChangeRow2();
	afx_msg void OnEnChangeCollum1();
	afx_msg void OnEnChangeCollum2();
	afx_msg void OnBnClickedCircle();
	afx_msg void OnBnClickedRectangle();
	afx_msg void OnEnChangeCirclex();
	afx_msg void OnEnChangeCircley();
	afx_msg void OnEnChangeCircleradius();
	afx_msg void OnBnClickedDefault();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedMask();
	afx_msg void OnBnClickedClearall();
	afx_msg void OnBnClickedHelp();
	afx_msg void OnBnClickedLrcv();
	afx_msg void OnBnClickedLif();
	afx_msg void OnBnClickedLgif();
	afx_msg void OnBnClickedLgdf();
	afx_msg void OnBnClickedGml();

	CToolTipCtrl m_Mytip;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedInteractive();
	afx_msg void OnBnClickedSyntropicfitting();
	afx_msg void OnBnClickedPrefitting();
};
