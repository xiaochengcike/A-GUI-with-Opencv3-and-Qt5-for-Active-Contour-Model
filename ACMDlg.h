
// ACMDlg.h : ͷ�ļ�
//

#pragma once
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

// CACMDlg �Ի���
class CACMDlg : public CDialogEx
{
// ����
public:
	CACMDlg(CWnd* pParent = NULL);	// ��׼���캯��

	Mat Image;//ԭͼ
	Mat Image_;//ԭ��ɫͼ
	Mat image;//���ͼ
	Mat mask;//��ġͼ
	uint ImgWidth;
	uint Imgheight;
	CString FileName;//ͼ������
	BOOL IsInitialization;//��ʼ����־

	Mat IC_Img;//���ѡ��
	string MouseEvent;//����¼�
	vector<Point>ICPoint;
	int PIndex = 0;
	Mat Roipoly;

	BOOL IsExchange;//ͬ����ϱ�־
	BOOL IsPreFitting;//Ԥ��ϱ�־

	struct Parameters//����һ���ṹ������Parameters
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

	struct Showing//����һ���ṹ������Show
	{
		uint linewidth;
		uint colorR;
		uint colorG;
		uint colorB;
	} Show;

	void ShowImage(Mat Img, UINT ID);//��MFC�ؼ�����ʾͼƬ
	void DrawContour(Mat LSF, Mat Img);//������
	Mat InitialContour();//�����ʼ����
	void UpdataEdit_InitialContour();//����EDIT
	void GetParameters();//�õ�ģ�Ͳ���
	void GetShow();//�õ���ʾ����
	void Implement_ACM(CString ACM);//ִ��ACM������
	vector<Mat> Pre_Fitting(Mat Img, Mat Kernel);//Ԥ��Ϻ���

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ACM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
