// ACMDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ACM.h"
#include "ACMDlg.h"
#include "Help.h"
#include "afxdialogex.h"
#include "afxdialogex.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#include "CvvImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define pi 3.14159265

using namespace cv;
using namespace std;

// CACMDlg �Ի���

CACMDlg::CACMDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ACM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CACMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CACMDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OpenImage, &CACMDlg::OnBnClickedOpenimage)
	ON_BN_CLICKED(IDC_CV, &CACMDlg::OnBnClickedCv)
	ON_BN_CLICKED(IDC_RSF, &CACMDlg::OnBnClickedRsf)
	ON_BN_CLICKED(IDC_DRLSE, &CACMDlg::OnBnClickedDrlse)
	ON_EN_CHANGE(IDC_Row1, &CACMDlg::OnEnChangeRow1)
	ON_EN_CHANGE(IDC_Row2, &CACMDlg::OnEnChangeRow2)
	ON_EN_CHANGE(IDC_Collum1, &CACMDlg::OnEnChangeCollum1)
	ON_EN_CHANGE(IDC_Collum2, &CACMDlg::OnEnChangeCollum2)
	ON_BN_CLICKED(IDC_Circle, &CACMDlg::OnBnClickedCircle)
	ON_BN_CLICKED(IDC_Rectangle, &CACMDlg::OnBnClickedRectangle)
	ON_EN_CHANGE(IDC_CircleX, &CACMDlg::OnEnChangeCirclex)
	ON_EN_CHANGE(IDC_CircleY, &CACMDlg::OnEnChangeCircley)
	ON_EN_CHANGE(IDC_CircleRadius, &CACMDlg::OnEnChangeCircleradius)
	ON_BN_CLICKED(IDC_Default, &CACMDlg::OnBnClickedDefault)
	ON_BN_CLICKED(IDCANCEL, &CACMDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_Save, &CACMDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_Mask, &CACMDlg::OnBnClickedMask)
	ON_BN_CLICKED(IDC_ClearAll, &CACMDlg::OnBnClickedClearall)
	ON_BN_CLICKED(IDC_Help, &CACMDlg::OnBnClickedHelp)
	ON_BN_CLICKED(IDC_LRCV, &CACMDlg::OnBnClickedLrcv)
	ON_BN_CLICKED(IDC_LIF, &CACMDlg::OnBnClickedLif)
	ON_BN_CLICKED(IDC_LGIF, &CACMDlg::OnBnClickedLgif)
	ON_BN_CLICKED(IDC_LGDF, &CACMDlg::OnBnClickedLgdf)
	ON_BN_CLICKED(IDC_GML, &CACMDlg::OnBnClickedGml)
	ON_BN_CLICKED(IDC_Interactive, &CACMDlg::OnBnClickedInteractive)
	ON_BN_CLICKED(IDC_SyntropicFitting, &CACMDlg::OnBnClickedSyntropicfitting)
	ON_BN_CLICKED(IDC_PreFitting, &CACMDlg::OnBnClickedPrefitting)
END_MESSAGE_MAP()

// CACMDlg ��Ϣ�������
BOOL CACMDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	m_Mytip.Create(this);
	m_Mytip.AddTool(GetDlgItem(IDC_STATIC_Num), "The number of iterations");
	m_Mytip.AddTool(GetDlgItem(IDC_STATIC_Nu), "The coefficient of length term");
	m_Mytip.AddTool(GetDlgItem(IDC_Static_Step), "The iterative step");
	m_Mytip.AddTool(GetDlgItem(IDC_Static_Mu), "The coefficient of distance regularized term");
	m_Mytip.AddTool(GetDlgItem(IDC_Static_Sig), "The scale parameter of local region");
	m_Mytip.AddTool(GetDlgItem(IDC_STATIC_Epison), "The parameter of Dirac function");
	m_Mytip.AddTool(GetDlgItem(IDC_STATIC_InitialCoefficient), "The parameter of inital contour");
	m_Mytip.AddTool(GetDlgItem(IDC_STATIC_lamda), "The coefficient of edge term in DRLSE");
	m_Mytip.AddTool(GetDlgItem(IDC_STATIC_alfa), "The coefficient of area term in DRLSE");
	m_Mytip.AddTool(GetDlgItem(IDC_STATIC_weight), "The weight between GIF and LGF in LGIF");
	m_Mytip.AddTool(GetDlgItem(IDC_STATIC_SE), "The radius of disk structure element in GMF");
	m_Mytip.AddTool(GetDlgItem(IDC_STATIC_lamda1), "The coefficient of inner Energy");
	m_Mytip.AddTool(GetDlgItem(IDC_STATIC_lamda2), "The coefficient of outer Energy");
	m_Mytip.AddTool(GetDlgItem(IDC_Interactive), "Press Enter Key to stop choose");
	m_Mytip.AddTool(GetDlgItem(IDC_STATIC_Interval), "Showing every x iterations");

	m_Mytip.SetDelayTime(200); //�����ӳ�
	m_Mytip.SetTipTextColor(RGB(50, 50, 50)); //������ʾ�ı�����ɫ
	m_Mytip.SetTipBkColor(RGB(255, 255, 255)); //������ʾ��ı�����ɫ
	m_Mytip.Activate(TRUE); //�����Ƿ�������ʾ

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
void CACMDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CACMDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//��ʾ
BOOL CACMDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_MOUSEMOVE)
		m_Mytip.RelayEvent(pMsg);
	return CDialogEx::PreTranslateMessage(pMsg);
}

//-----------------------------------------------//
//NeumannBound����
void NeumannBoundCond(Mat& LSF)
{
	int w = LSF.cols - 1;
	int h = LSF.rows - 1;
	LSF.at<float>(0, 0) = LSF.at<float>(2, 2);
	LSF.at<float>(h, 0) = LSF.at<float>(h - 2, 2);
	LSF.at<float>(0, w) = LSF.at<float>(2, w - 2);
	LSF.at<float>(h, w) = LSF.at<float>(h - 2, w - 2);

	for (int i = 0; i <= w; i++)
	{
		LSF.at<float>(0, i) = LSF.at<float>(2, i);
		LSF.at<float>(h, i) = LSF.at<float>(h - 2, i);
	}
	for (int i = 0; i <= h; i++)
	{
		LSF.at<float>(i, 0) = LSF.at<float>(i, 2);
		LSF.at<float>(i, w) = LSF.at<float>(i, w - 2);
	}
}

//��������arctan����
Mat Mat_atan(Mat LSF)
{
	Mat dst(LSF.size(), LSF.type());
	for (int k = 0; k < LSF.rows; k++) //����
	{
		const float* inData = LSF.ptr<float>(k);
		float* outData = dst.ptr<float>(k);
		for (int i = 0; i < LSF.cols; i++)
			outData[i] = atan(inData[i]);
	}
	return dst;
}

//��������cos����
Mat Mat_cos(Mat LSF)
{
	Mat dst(LSF.size(), LSF.type());
	for (int k = 0; k < LSF.rows; k++) //����
	{
		const float* inData = LSF.ptr<float>(k);
		float* outData = dst.ptr<float>(k);
		for (int i = 0; i < LSF.cols; i++)
			outData[i] = cos(inData[i]);
	}
	return dst;
}

//�����log&sqrt����
Mat Mat_log_sqrt(Mat LSF)
{
	Mat dst(LSF.size(), LSF.type());
	for (int k = 0; k < LSF.rows; k++) //����
	{
		const float* inData = LSF.ptr<float>(k);
		float* outData = dst.ptr<float>(k);
		for (int i = 0; i < LSF.cols; i++)
			outData[i] = log(sqrt(inData[i]));
	}
	return dst;
}

//�����ݶ�
Mat gradient_x(Mat input)
{
	Mat Ix(input.size(), input.type());
	for (int ncol = 0; ncol < input.cols; ncol++)
	{
		for (int nrow = 0; nrow < input.rows; nrow++)
		{
			if (ncol == 0) {
				Ix.at<float>(nrow, ncol) = input.at<float>(nrow, 1) - input.at<float>(nrow, 0);
			}
			else if (ncol == input.cols - 1) {
				Ix.at<float>(nrow, ncol) = input.at<float>(nrow, ncol) - input.at<float>(nrow, ncol - 1);
			}
			else
				Ix.at<float>(nrow, ncol) = (input.at<float>(nrow, ncol + 1) - input.at<float>(nrow, ncol - 1)) / 2;
		}
	}
	return Ix;
}

Mat gradient_y(Mat input)
{
	Mat Iy(input.size(), input.type());
	for (int nrow = 0; nrow < input.rows; nrow++)
	{
		for (int ncol = 0; ncol < input.cols; ncol++)
		{
			if (nrow == 0) {
				Iy.at<float>(nrow, ncol) = input.at<float>(1, ncol) - input.at<float>(0, ncol);
			}
			else if (nrow == input.rows - 1) {
				Iy.at<float>(nrow, ncol) = input.at<float>(nrow, ncol) - input.at<float>(nrow - 1, ncol);
			}
			else
				Iy.at<float>(nrow, ncol) = (input.at<float>(nrow + 1, ncol) - input.at<float>(nrow - 1, ncol)) / 2;
		}
	}
	return Iy;
}

//��������
Mat curvature(Mat LSF)
{
	Mat Ix, Iy;
	Ix = gradient_x(LSF);
	Iy = gradient_y(LSF);
	Mat s;
	magnitude(Ix, Iy, s);//�ݶȵ�ģ
	Mat Nx = Ix / (s + 0.000001);
	Mat Ny = Iy / (s + 0.000001);
	Mat Nxx, Nyy;
	Nxx = gradient_x(Nx);
	Nyy = gradient_y(Ny);
	Mat cur = Nxx + Nyy;
	return cur;
}

//Exchange f1 and f2
void Exchange(Mat &f1, Mat &f2, BOOL IsExchange)
{
	if (IsExchange == FALSE)
		return;
	else
	{
		f1 = cv::min(f1, f2);
		f2 = cv::max(f1, f2);
	}
}

//Pre_Fitting
vector<Mat> CACMDlg::Pre_Fitting(Mat Img, Mat Kernel)
{
	uint r = (Kernel.cols - 1) / 2;
	Mat Im = Mat::zeros(Img.rows, Img.cols, CV_32FC1);
	Mat f1 = Mat::zeros(Img.rows, Img.cols, CV_32FC1);
	Mat f2 = Mat::zeros(Img.rows, Img.cols, CV_32FC1);

	for (int i = 0; i < Img.rows; i++)
	{
		for (int j = 0; j < Img.cols; j++)
		{
			Mat tmpM = Img(Rect(0, 0, Img.cols, Img.rows) & Rect(j - r, i - r, Kernel.cols, Kernel.rows));

			Scalar Sum = sum(tmpM);
			float Mean = Sum.val[0] / (tmpM.cols*tmpM.rows + 0.000001);
			Im.at<float>(i, j) = Mean;

			Mat tmp1 = (tmpM <= Mean) / 255;
			tmp1.convertTo(tmp1, CV_32FC1);
			Mat tmp11 = tmp1.mul(tmpM);
			Scalar Sum1 = sum(tmp11);
			f1.at<float>(i, j) = Sum1.val[0] / (float)(countNonZero(tmp1) + 0.000001);

			Mat tmp2 = (tmpM >= Mean) / 255;
			tmp2.convertTo(tmp2, CV_32FC1);
			Mat tmp22 = tmp2.mul(tmpM);
			Scalar Sum2 = sum(tmp22);
			f2.at<float>(i, j) = Sum2.val[0] / (float)(countNonZero(tmp2) + 0.000001);
		}
	}
	vector<Mat> Fit;
	Fit.push_back(Im);
	Fit.push_back(f1);
	Fit.push_back(f2);
	return Fit;
}

//CV
void CV(Mat& LSF, Mat Img, float mu, float nu, float epison, float step, float lamda1, float lamda2)
{
	NeumannBoundCond(LSF); //�߽�����

	Mat Drc = (epison / pi) / (epison*epison + LSF.mul(LSF)); //Dirac ����

	Mat Hea = 0.5*(1 + (2 / pi)*Mat_atan(LSF / epison)); //Heaviside ����

	Mat cur = curvature(LSF);//��������

	Mat Length = nu*Drc.mul(cur);//������

	//������
	Mat Lap;
	Laplacian(LSF, Lap, CV_32FC1);
	Mat Penalty = mu*(Lap - cur);

	//CV��
	Scalar S1;
	S1 = sum(Hea.mul(Img));
	Scalar S2;
	S2 = sum(Hea);
	float C1 = S1.val[0] / S2.val[0];
	Scalar S3;
	S3 = sum((1 - Hea).mul(Img));
	Scalar S4;
	S4 = sum((1 - Hea));
	float C2 = S3.val[0] / S4.val[0];
	Mat CVterm = Drc.mul((-lamda1 * (Img - C1).mul(Img - C1) + lamda2 * (Img - C2).mul(Img - C2)));

	//�������
	LSF = LSF + step*(Length + Penalty + CVterm);
}

//RSF
void RSF(Mat& LSF, Mat Img, Mat kernel, float mu, float nu, float epison, float step, int lambda1, int lambda2, BOOL IsExchange, Mat dataForce)
{
	NeumannBoundCond(LSF); //�߽�����

	Mat Drc = (epison / pi) / (epison*epison + LSF.mul(LSF)); //Dirac ����

	Mat Hea = 0.5*(1 + (2 / pi)*Mat_atan(LSF / epison)); //Heaviside ����

	Mat cur = curvature(LSF);//��������

	Mat Length = nu*Drc.mul(cur);//������

	//������
	Mat Lap;
	Laplacian(LSF, Lap, CV_32FC1);
	Mat Penalty = mu*(Lap - cur);

	//RSF��
	Mat RSFterm;
	if (dataForce.data != NULL)
		RSFterm = -Drc.mul(dataForce);
	else
	{
		Mat KIH;
		filter2D(Hea.mul(Img), KIH, -1, kernel);
		Mat KH;
		filter2D(Hea, KH, -1, kernel);
		Mat f1 = KIH / KH;

		Mat KIH1;
		filter2D((1 - Hea).mul(Img), KIH1, -1, kernel);
		Mat KH1;
		filter2D((1 - Hea), KH1, -1, kernel);
		Mat f2 = KIH1 / KH1;

		Exchange(f1, f2, IsExchange);

		Mat R1;
		R1 = (lambda1 - lambda2)*Img.mul(Img);
		Mat R2;
		filter2D(lambda1*f1 - lambda2*f2, R2, -1, kernel);
		Mat R3;
		filter2D(lambda1*f1.mul(f1) - lambda2*f2.mul(f2), R3, -1, kernel);
		RSFterm = -Drc.mul(R1 - 2 * R2.mul(Img) + R3);
	}
	//�������
	LSF = LSF + step*(Length + Penalty + RSFterm);
}

//DRLSE
void DRLSE(Mat& LSF, Mat Img, Mat g, float mu, float alfa, float lamda, float epison, float step)
{
	NeumannBoundCond(LSF); //�߽�����

	//Dirac ����
	Mat f = (0.5 / epison)*(1 + Mat_cos((pi / epison)*LSF));
	Mat b;
	inRange(LSF, -epison, epison, b);
	b.convertTo(b, CV_32FC1);
	Mat Drc = f.mul(b / 255);

	//��������
	Mat Ix, Iy;
	Ix = gradient_x(LSF);
	Iy = gradient_y(LSF);
	Mat s;
	magnitude(Ix, Iy, s);//�ݶ�ģ
	Mat Nx = Ix / (s + 0.000001);
	Mat Ny = Iy / (s + 0.000001);
	Mat Nxx, Nyy;
	Nxx = gradient_x(Nx);
	Nyy = gradient_y(Ny);
	Mat cur = Nxx + Nyy;

	//��Ե������
	Mat Gx, Gy;
	Gx = gradient_x(g);
	Gy = gradient_y(g);
	Mat Length_g = Drc.mul(Gx.mul(Nx) + Gy.mul(Ny) + g.mul(cur));

	//������
	Mat Lap;
	Laplacian(LSF, Lap, CV_32FC1);
	Mat Penalty = (Lap - cur);

	//�����Ե��
	Mat Area_g = Drc.mul(g);

	//�������
	LSF = LSF + step*(lamda* Length_g + mu*Penalty + alfa*Area_g);
}

//LRCV
void LRCV(Mat& LSF, Mat Img, Mat kernel, float mu, float nu, float epison, float step, int lambda1, int lambda2, BOOL IsExchange, Mat dataForce)
{
	NeumannBoundCond(LSF); //�߽�����

	Mat Drc = (epison / pi) / (epison*epison + LSF.mul(LSF)); //Dirac ����

	Mat Hea = 0.5*(1 + (2 / pi)*Mat_atan(LSF / epison)); //Heaviside ����

	Mat cur = curvature(LSF);//��������

	Mat Length = nu*Drc.mul(cur);//������

	//������
	Mat Lap;
	Laplacian(LSF, Lap, CV_32FC1);
	Mat Penalty = mu*(Lap - cur);

	//LRCV��
	Mat LRCVterm;
	if (dataForce.data != NULL)
		LRCVterm = -Drc.mul(dataForce);
	else
	{
		Mat KIH;
		filter2D(Hea.mul(Img), KIH, -1, kernel);
		Mat KH;
		filter2D(Hea, KH, -1, kernel);
		Mat f1 = KIH / KH;

		Mat KIH1;
		filter2D((1 - Hea).mul(Img), KIH1, -1, kernel);
		Mat KH1;
		filter2D((1 - Hea), KH1, -1, kernel);
		Mat f2 = KIH1 / KH1;

		Exchange(f1, f2, IsExchange);

		LRCVterm = -Drc.mul(lambda1*(Img - f1).mul(Img - f1) - lambda2*(Img - f2).mul(Img - f2));
	}

	//�������
	LSF = LSF + step*(Length + Penalty + LRCVterm);
}

//LIF
void LIF(Mat& LSF, Mat Img, Mat kernel, float mu, float nu, float epison, float step, BOOL IsExchange, Mat f1, Mat f2)
{
	NeumannBoundCond(LSF); //�߽�����

	Mat Drc = (epison / pi) / (epison*epison + LSF.mul(LSF)); //Dirac ����

	Mat Hea = 0.5*(1 + (2 / pi)*Mat_atan(LSF / epison)); //Heaviside ����

	Mat cur = curvature(LSF);//��������

	Mat Length = nu*Drc.mul(cur);//������

	//������
	Mat Lap;
	Laplacian(LSF, Lap, CV_32FC1);
	Mat Penalty = mu*(Lap - cur);

	//LIF��
	Mat LIFterm;
	if (f1.data != NULL & f2.data != NULL)
		LIFterm = Drc.mul((Img - f1.mul(Hea) - f2.mul(1 - Hea)).mul(f1 - f2));
	else
	{
		Mat KIH;
		filter2D(Hea.mul(Img), KIH, -1, kernel);
		Mat KH;
		filter2D(Hea, KH, -1, kernel);
		Mat f1 = KIH / KH;

		Mat KIH1;
		filter2D((1 - Hea).mul(Img), KIH1, -1, kernel);
		Mat KH1;
		filter2D((1 - Hea), KH1, -1, kernel);
		Mat f2 = KIH1 / KH1;

		Exchange(f1, f2, IsExchange);

		LIFterm = Drc.mul((Img - f1.mul(Hea) - f2.mul(1 - Hea)).mul(f1 - f2));
	}
	//�������
	LSF = LSF + step*(Length + Penalty + LIFterm);
}

//LGIF
void LGIF(Mat& LSF, Mat Img, Mat kernel, float mu, float nu, float epison, float step, int lambda1, int lambda2, float w)
{
	NeumannBoundCond(LSF); //�߽�����

	Mat Drc = (epison / pi) / (epison*epison + LSF.mul(LSF)); //Dirac ����

	Mat Hea = 0.5*(1 + (2 / pi)*Mat_atan(LSF / epison)); //Heaviside ����

	Mat cur = curvature(LSF);//��������

	Mat Length = nu*Drc.mul(cur);//������

	 //������
	Mat Lap;
	Laplacian(LSF, Lap, CV_32FC1);
	Mat Penalty = mu*(Lap - cur);

	//CV��
	Scalar S1;
	S1 = sum(Hea.mul(Img));
	Scalar S2;
	S2 = sum(Hea);
	float C1 = S1.val[0] / S2.val[0];
	Scalar S3;
	S3 = sum((1 - Hea).mul(Img));
	Scalar S4;
	S4 = sum((1 - Hea));
	float C2 = S3.val[0] / S4.val[0];
	Mat CVterm = Drc.mul((-lambda1 * (Img - C1).mul(Img - C1) + lambda1 * (Img - C2).mul(Img - C2)));

	//RSF��
	Mat KIH;
	filter2D(Hea.mul(Img), KIH, -1, kernel);
	Mat KH;
	filter2D(Hea, KH, -1, kernel);
	Mat f1 = KIH / KH;

	Mat KIH1;
	filter2D((1 - Hea).mul(Img), KIH1, -1, kernel);
	Mat KH1;
	filter2D((1 - Hea), KH1, -1, kernel);
	Mat f2 = KIH1 / KH1;

	Mat R1;
	R1 = (lambda1 - lambda2)*Img.mul(Img);
	Mat R2;
	filter2D(lambda1*f1 - lambda2*f2, R2, -1, kernel);
	Mat R3;
	filter2D(lambda1*f1.mul(f1) - lambda2*f2.mul(f2), R3, -1, kernel);
	Mat RSFterm = -Drc.mul(R1 - 2 * R2.mul(Img) + R3);

	//�������
	LSF = LSF + step*(Length + Penalty + (1 - w)*RSFterm + w*CVterm);
}

//GML
void GML(Mat& LSF, Mat Img, Mat GM, float mu, float nu, float epison, float step)
{
	NeumannBoundCond(LSF); //�߽�����

	Mat Drc = (epison / pi) / (epison*epison + LSF.mul(LSF)); //Dirac ����

	Mat Hea = 0.5*(1 + (2 / pi)*Mat_atan(LSF / epison)); //Heaviside ����

	Mat cur = curvature(LSF);//��������

	Mat Length = nu*Drc.mul(cur);//������

	//������
	Mat Lap;
	Laplacian(LSF, Lap, CV_32FC1);
	Mat Penalty = mu*(Lap - cur);

	//�������
	LSF = LSF + step*(Length + Penalty + Drc.mul(GM));
}

//LGDF
void LGDF(Mat& LSF, Mat Img, Mat kernel, float mu, float nu, float epison, float step, int lambda1, int lambda2, BOOL IsExchange, Mat f1, Mat f2)
{
	NeumannBoundCond(LSF); //�߽�����

	Mat Drc = (epison / pi) / (epison*epison + LSF.mul(LSF)); //Dirac ����

	Mat Hea = 0.5*(1 + (2 / pi)*Mat_atan(LSF / epison)); //Heaviside ����

	Mat cur = curvature(LSF);//��������

	Mat Length = nu*Drc.mul(cur);//������

								 //������
	Mat Lap;
	Laplacian(LSF, Lap, CV_32FC1);
	Mat Penalty = mu*(Lap - cur);

	//LGDF��
	Mat KIH;
	filter2D(Hea.mul(Img), KIH, -1, kernel);
	Mat KH;
	filter2D(Hea, KH, -1, kernel);
	Mat KI2;
	filter2D((Img.mul(Img)), KI2, -1, kernel);
	Mat KI2H;
	filter2D(Hea.mul(Img.mul(Img)), KI2H, -1, kernel);

	if (f1.data == NULL & f2.data == NULL)
	{
		f1 = KIH / KH;

		Mat KIH1;
		filter2D((1 - Hea).mul(Img), KIH1, -1, kernel);
		Mat KH1;
		filter2D((1 - Hea), KH1, -1, kernel);
		f2 = KIH1 / KH1;

		Exchange(f1, f2, IsExchange);
	}

	Mat KI;
	filter2D(Img, KI, -1, kernel);
	Mat Kone;
	filter2D(Mat::ones(Img.size(), CV_32FC1), Kone, -1, kernel);

	Mat Sigma1 = (KH.mul(f1.mul(f1)) - 2 * f1.mul(KIH) + KI2H) / KH + 0.000001;
	Mat Sigma2 = (Kone.mul(f2.mul(f2)) - KH.mul(f2.mul(f2)) - 2 * f2.mul(KI) + 2 * f2.mul(KIH) + KI2 - KI2H) / (Kone - KH) + 0.000001;

	Mat temp1 = (lambda1 - lambda2)*Kone*log(sqrt(2 * pi));

	Mat temp2;
	filter2D(lambda1*Mat_log_sqrt(Sigma1) - lambda2*Mat_log_sqrt(Sigma2) + lambda1*f1.mul(f1) / (2 * Sigma1) - lambda2*f2.mul(f2) / (2 * Sigma2), temp2, -1, kernel);

	Mat R1;
	filter2D(lambda2*f2 / Sigma2 - lambda1*f1 / Sigma1, R1, -1, kernel);
	Mat temp3 = Img.mul(R1);

	Mat R2;
	filter2D(lambda1 / (2 * Sigma1) - lambda2 / (2 * Sigma2), R2, -1, kernel);
	Mat temp4 = (Img.mul(Img)).mul(R2);

	Mat LGDFterm = -Drc.mul(temp1 + temp2 + temp3 + temp4);

	//�������
	LSF = LSF + step*(Length + Penalty + 30 * LGDFterm);
}

//��ͼƬ
void CACMDlg::OnBnClickedOpenimage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(true, _T("*.bmp"), NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image file(*.bmp;*.jpg)|*.bmp;*.jpg|All Files(*.*)|*.*|"), NULL);//����ѡ��ͼƬ�Ի���
	dlg.m_ofn.lpstrTitle = _T("Open Image");
	if (dlg.DoModal() != IDOK)
		return;
	CString m_strPicPath = dlg.GetPathName();//ͼ������·��
	FileName = dlg.GetFileName();//ͼ������
	m_strPicPath.Replace(_T("//"), _T("////"));
	string strPath; //·����CStringת��Ϊstring
	strPath = m_strPicPath.GetBuffer(0);
	Image_ = imread(strPath, 1);//����ԭ��ɫͼ��
	Image = imread(strPath, 0);//����ͼ��
	if (Image.data == NULL)
	{
		AfxMessageBox(_T("Failed��"));
		return;
	}
	else
	{
		GetDlgItem(IDC_State)->SetWindowText(m_strPicPath);
		ImgWidth = Image.cols;
		Imgheight = Image.rows;
		OnBnClickedDefault();//������ʼ��
		Mat InitialLSF = InitialContour();//Ĭ�ϳ�ʼ����
		Mat Img = Image_.clone();
		DrawContour(InitialLSF, Img);//��ʾ
	}
}

//�����ʼLSF
Mat CACMDlg::InitialContour()
{
	CString str;
	GetDlgItem(IDC_C0)->GetWindowText(str);
	int C0 = atoi(str.GetBuffer(0));
	Mat roi = Mat::ones(Image.size(), CV_32FC1);

	if (((CButton*)GetDlgItem(IDC_Rectangle))->GetCheck())
	{
		GetDlgItem(IDC_Row1)->GetWindowText(str);
		int Row1 = atoi(str.GetBuffer(0));
		GetDlgItem(IDC_Row2)->GetWindowText(str);
		int Row2 = atoi(str.GetBuffer(0));
		GetDlgItem(IDC_Collum1)->GetWindowText(str);
		int Collum1 = atoi(str.GetBuffer(0));
		GetDlgItem(IDC_Collum2)->GetWindowText(str);
		int Collum2 = atoi(str.GetBuffer(0));

		Point p1 = Point(Collum1, Row1);
		Point p2 = Point(Collum2, Row2);
		rectangle(roi, p1, p2, Scalar(0, 0, 0), -1, 8, 0);
	}

	if (((CButton*)GetDlgItem(IDC_Circle))->GetCheck())
	{
		GetDlgItem(IDC_CircleX)->GetWindowText(str);
		int CircleX = atoi(str.GetBuffer(0));
		GetDlgItem(IDC_CircleY)->GetWindowText(str);
		int CircleY = atoi(str.GetBuffer(0));
		GetDlgItem(IDC_CircleRadius)->GetWindowText(str);
		int CircleRadius = atoi(str.GetBuffer(0));

		Point center = Point(CircleX, CircleY);
		circle(roi, center, CircleRadius, Scalar(0, 0, 0), -1, 8, 0);
	}
	if (((CButton*)GetDlgItem(IDC_Mask))->GetCheck())
	{
		Mat r;
		threshold(mask, r, 128, 255, CV_THRESH_BINARY);//��ֵ�� 0-255
		r = r / 255;
		r.convertTo(roi, CV_32FC1);//ת������
	}
	if (((CButton*)GetDlgItem(IDC_Interactive))->GetCheck())
	{
		Mat r = 1 - Roipoly / 255;
		r.convertTo(roi, CV_32FC1);//ת������
	}
	Mat InitialLSF = C0 * 2 * (roi - 0.5);
	return InitialLSF;
}

//ģ�Ͳ�������
void  CACMDlg::GetParameters()
{
	CString str;
	GetDlgItem(IDC_Num)->GetWindowText(str);
	para.num = atoi(str.GetBuffer(0));

	GetDlgItem(IDC_Step)->GetWindowText(str);
	para.step = atof(str.GetBuffer(0));

	GetDlgItem(IDC_Epison)->GetWindowText(str);
	para.epison = atof(str.GetBuffer(0));

	GetDlgItem(IDC_Length)->GetWindowText(str);
	para.nu = atof(str.GetBuffer(0)) * 255 * 255;

	GetDlgItem(IDC_Penalty)->GetWindowText(str);
	para.mu = atof(str.GetBuffer(0));

	GetDlgItem(IDC_Lamda1)->GetWindowText(str);
	para.lamda1 = atof(str.GetBuffer(0));

	GetDlgItem(IDC_Lamda2)->GetWindowText(str);
	para.lamda2 = atof(str.GetBuffer(0));

	GetDlgItem(IDC_Lamda)->GetWindowText(str);
	para.lamda = atof(str.GetBuffer(0));

	GetDlgItem(IDC_Alfa)->GetWindowText(str);
	para.alfa = atof(str.GetBuffer(0));

	GetDlgItem(IDC_Sig)->GetWindowText(str);
	para.sig = atof(str.GetBuffer(0));

	GetDlgItem(IDC_Weight)->GetWindowText(str);
	para.weight = atof(str.GetBuffer(0));

	GetDlgItem(IDC_SE_Radius)->GetWindowText(str);
	para.SE_radius = atof(str.GetBuffer(0));

	GetDlgItem(IDC_interval)->GetWindowText(str);
	para.interval = atof(str.GetBuffer(0));
}

//��ʾ���ò���
void  CACMDlg::GetShow()
{
	CString str;

	GetDlgItem(IDC_LineWidth)->GetWindowText(str);
	Show.linewidth = atoi(str.GetBuffer(0));

	GetDlgItem(IDC_R)->GetWindowText(str);
	Show.colorR = atoi(str.GetBuffer(0));

	GetDlgItem(IDC_G)->GetWindowText(str);
	Show.colorG = atoi(str.GetBuffer(0));

	GetDlgItem(IDC_B)->GetWindowText(str);
	Show.colorB = atoi(str.GetBuffer(0));
}

//CVģ��
void CACMDlg::OnBnClickedCv()
{
	Implement_ACM("CV");
}

//RSFģ��
void CACMDlg::OnBnClickedRsf()
{
	Implement_ACM("RSF");
}

//DRLSEģ��
void CACMDlg::OnBnClickedDrlse()
{
	GetDlgItem(IDC_Step)->SetWindowText(_T("1"));
	GetDlgItem(IDC_Penalty)->SetWindowText(_T("0.2"));
	Implement_ACM("DRLSE");
}

//LRCVģ��
void CACMDlg::OnBnClickedLrcv()
{
	Implement_ACM("LRCV");
}

//LIFģ��
void CACMDlg::OnBnClickedLif()
{
	Implement_ACM("LIF");
}

//LGIFģ��
void CACMDlg::OnBnClickedLgif()
{
	Implement_ACM("LGIF");
}

//LGDFģ��
void CACMDlg::OnBnClickedLgdf()
{
	Implement_ACM("LGDF");
}

//GMLģ��
void CACMDlg::OnBnClickedGml()
{
	Implement_ACM("GML");
}

//ͬ�����
void CACMDlg::OnBnClickedSyntropicfitting()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (((CButton*)GetDlgItem(IDC_SyntropicFitting))->GetCheck())
	{
		((CButton*)GetDlgItem(IDC_PreFitting))->SetCheck(FALSE);
		GetDlgItem(IDC_RSF)->SetWindowText(_T("RSF(S)"));
		GetDlgItem(IDC_LIF)->SetWindowText(_T("LIF(S)"));
		GetDlgItem(IDC_LRCV)->SetWindowText(_T("LRCV(S)"));
		GetDlgItem(IDC_LGDF)->SetWindowText(_T("LGDF(S)"));
		IsExchange = TRUE;
		IsPreFitting = FALSE;
	}
	if (!((CButton*)GetDlgItem(IDC_SyntropicFitting))->GetCheck())
	{
		GetDlgItem(IDC_RSF)->SetWindowText(_T("RSF"));
		GetDlgItem(IDC_LIF)->SetWindowText(_T("LIF"));
		GetDlgItem(IDC_LRCV)->SetWindowText(_T("LRCV"));
		GetDlgItem(IDC_LGDF)->SetWindowText(_T("LGDF"));
		IsExchange = FALSE;
	}
}

//Ԥ���
void CACMDlg::OnBnClickedPrefitting()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (((CButton*)GetDlgItem(IDC_PreFitting))->GetCheck())
	{
		((CButton*)GetDlgItem(IDC_SyntropicFitting))->SetCheck(FALSE);
		GetDlgItem(IDC_RSF)->SetWindowText(_T("RSF(P)"));
		GetDlgItem(IDC_LIF)->SetWindowText(_T("LIF(P)"));
		GetDlgItem(IDC_LRCV)->SetWindowText(_T("LRCV(P)"));
		GetDlgItem(IDC_LGDF)->SetWindowText(_T("LGDF(P)"));
		IsExchange = FALSE;
		IsPreFitting = TRUE;
		GetDlgItem(IDC_Length)->SetWindowText(_T("0.01"));
	}
	if (!((CButton*)GetDlgItem(IDC_PreFitting))->GetCheck())
	{
		((CButton*)GetDlgItem(IDC_SyntropicFitting))->SetCheck(FALSE);
		GetDlgItem(IDC_RSF)->SetWindowText(_T("RSF"));
		GetDlgItem(IDC_LIF)->SetWindowText(_T("LIF"));
		GetDlgItem(IDC_LRCV)->SetWindowText(_T("LRCV"));
		GetDlgItem(IDC_LGDF)->SetWindowText(_T("LGDF"));
		IsPreFitting = FALSE;
	}
}

//ִ��ACM������
void CACMDlg::Implement_ACM(CString ACM)
{
	Mat Img, kernel, g, GM, dataForce, f1, f2;
	vector<Mat> Fit;
	Image.convertTo(Img, CV_32FC1);//ת������
	Mat LSF = InitialContour(); //�õ���ʼ����
	GetParameters();//�õ�����

	if (ACM == "RSF" | ACM == "LRCV" | ACM == "LIF" | ACM == "LGIF" | ACM == "LGDF")
	{
		Mat kernelX = getGaussianKernel(int(para.sig * 2) * 2 + 1, para.sig);
		kernel = kernelX * kernelX.t();
	}

	if ((IsPreFitting == TRUE) & (ACM == "RSF" | ACM == "LRCV" | ACM == "LIF" | ACM == "LGDF"))
	{
		Fit = Pre_Fitting(Img, kernel);
		filter2D(Fit[1], f1, -1, kernel);
		filter2D(Fit[2], f2, -1, kernel);
		if (ACM == "RSF")
		{
			Mat R1;
			R1 = (para.lamda1 - para.lamda2)*Img.mul(Img);
			Mat R2;
			filter2D(para.lamda1*f1 - para.lamda2*f2, R2, -1, kernel);
			Mat R3;
			filter2D(para.lamda1*f1.mul(f1) - para.lamda2*f2.mul(f2), R3, -1, kernel);
			dataForce = R1 - 2 * R2.mul(Img) + R3;
		}
		if (ACM == "LRCV")
			dataForce = para.lamda1*(Img - f1).mul(Img - f1) - para.lamda2*(Img - f2).mul(Img - f2);
	}

	if (ACM == "DRLSE")
	{
		Mat Img_;
		GaussianBlur(Img, Img_, Size(7, 7), 0, 0);
		Mat Ix, Iy;
		Ix = gradient_x(Img_);
		Iy = gradient_y(Img_);
		g = 1 / (1 + (Ix.mul(Ix) + Iy.mul(Iy))); //��Ե����
	}

	if (ACM == "GML")
	{
		Mat C1, C2;
		Mat element = getStructuringElement(MORPH_ELLIPSE, Size(para.SE_radius, para.SE_radius));
		morphologyEx(Img, C1, MORPH_DILATE, element);//������
		morphologyEx(Img, C2, MORPH_ERODE, element);//������
		GM = para.lamda1*(Img - C1).mul(Img - C1) - para.lamda2*(Img - C2).mul(Img - C2);
	}

	GetDlgItem(IDC_State)->SetWindowText(_T("Runing...Please keep waiting"));
	double start = clock();
	for (int n = 0; n < para.num; n++)
	{
		if (ACM == "CV")
			CV(LSF, Img, para.mu, para.nu, para.epison, para.step, para.lamda1, para.lamda2);//����
		if (ACM == "RSF")
			RSF(LSF, Img, kernel, para.mu, para.nu, para.epison, para.step, para.lamda1, para.lamda2, IsExchange, dataForce);//����
		if (ACM == "DRLSE")
			DRLSE(LSF, Img, g, para.mu, para.alfa, para.lamda, para.epison, para.step);//����
		if (ACM == "LRCV")
			LRCV(LSF, Img, kernel, para.mu, para.nu, para.epison, para.step, para.lamda1, para.lamda2, IsExchange, dataForce);//����
		if (ACM == "LIF")
			LIF(LSF, Img, kernel, para.mu, para.nu, para.epison, para.step, IsExchange, f1, f2);//����
		if (ACM == "LGIF")
			LGIF(LSF, Img, kernel, para.mu, para.nu, para.epison, para.step, para.lamda1, para.lamda2, para.weight);//����
		if (ACM == "GML")
			GML(LSF, Img, GM, para.mu, para.nu, para.epison, para.step);//����
		if (ACM == "LGDF")
			LGDF(LSF, Img, kernel, para.mu, para.nu, para.epison, para.step, para.lamda1, para.lamda2, IsExchange, f1, f2);//����

		if (n % para.interval == 0)
		{
			Mat Img = Image_.clone();
			DrawContour(LSF, Img);//��ʾ
		}
	}
	double stop = clock();
	double durationTime = ((double)(stop - start)) / CLK_TCK;
	CString str;
	str.Format("%.3lf", durationTime);
	GetDlgItem(IDC_State)->SetWindowText("Completed! Cost Time: " + str + "s");
}

//ϵͳȫ�����
void CACMDlg::OnBnClickedClearall()
{
	UINT Flag = MessageBox(_T("Are you sure to clear all��"), _T("Tip"), MB_YESNO | MB_ICONQUESTION);
	if (IDNO == Flag)
		return;

	GetDlgItem(IDC_State)->SetWindowText(_T("Please open the image!"));
	GetDlgItem(IDC_RSF)->SetWindowText(_T("RSF"));
	GetDlgItem(IDC_LIF)->SetWindowText(_T("LIF"));
	GetDlgItem(IDC_LRCV)->SetWindowText(_T("LRCV"));
	GetDlgItem(IDC_LGDF)->SetWindowText(_T("LGDF"));
	GetDlgItem(IDC_CV)->EnableWindow(FALSE);
	GetDlgItem(IDC_RSF)->EnableWindow(FALSE);
	GetDlgItem(IDC_DRLSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_LRCV)->EnableWindow(FALSE);
	GetDlgItem(IDC_LIF)->EnableWindow(FALSE);
	GetDlgItem(IDC_LGIF)->EnableWindow(FALSE);
	GetDlgItem(IDC_LGDF)->EnableWindow(FALSE);
	GetDlgItem(IDC_GML)->EnableWindow(FALSE);
	GetDlgItem(IDC_Rectangle)->EnableWindow(FALSE);
	GetDlgItem(IDC_Circle)->EnableWindow(FALSE);
	GetDlgItem(IDC_Mask)->EnableWindow(FALSE);
	GetDlgItem(IDC_Save)->EnableWindow(FALSE);
	GetDlgItem(IDC_Default)->EnableWindow(FALSE);
	GetDlgItem(IDC_ClearAll)->EnableWindow(FALSE);
	GetDlgItem(IDC_PreFitting)->EnableWindow(FALSE);
	GetDlgItem(IDC_SyntropicFitting)->EnableWindow(FALSE);

	GetDlgItem(IDC_Row1)->SetWindowText(_T(""));
	GetDlgItem(IDC_Row2)->SetWindowText(_T(""));
	GetDlgItem(IDC_Collum1)->SetWindowText(_T(""));
	GetDlgItem(IDC_Collum2)->SetWindowText(_T(""));
	GetDlgItem(IDC_CircleX)->SetWindowText(_T(""));
	GetDlgItem(IDC_CircleY)->SetWindowText(_T(""));
	GetDlgItem(IDC_CircleRadius)->SetWindowText(_T(""));

	GetDlgItem(IDC_Num)->SetWindowText(_T(""));
	GetDlgItem(IDC_Step)->SetWindowText(_T(""));
	GetDlgItem(IDC_C0)->SetWindowText(_T(""));
	GetDlgItem(IDC_Epison)->SetWindowText(_T(""));
	GetDlgItem(IDC_Length)->SetWindowText(_T(""));
	GetDlgItem(IDC_Penalty)->SetWindowText(_T(""));
	GetDlgItem(IDC_C0)->SetWindowText(_T(""));
	GetDlgItem(IDC_Lamda1)->SetWindowText(_T(""));
	GetDlgItem(IDC_Lamda2)->SetWindowText(_T(""));
	GetDlgItem(IDC_Sig)->SetWindowText(_T(""));
	GetDlgItem(IDC_Lamda)->SetWindowText(_T(""));
	GetDlgItem(IDC_Alfa)->SetWindowText(_T(""));
	GetDlgItem(IDC_Weight)->SetWindowText(_T(""));
	GetDlgItem(IDC_SE_Radius)->SetWindowText(_T(""));
	GetDlgItem(IDC_interval)->SetWindowText(_T(""));
	GetDlgItem(IDC_LineWidth)->SetWindowText(_T(""));
	GetDlgItem(IDC_R)->SetWindowText(_T(""));
	GetDlgItem(IDC_G)->SetWindowText(_T(""));
	GetDlgItem(IDC_B)->SetWindowText(_T(""));

	Mat Z = Mat::ones(1, 1, CV_8UC1) * 240;
	ShowImage(Z, IDC_ShowImg);
}

//�ָ�Ĭ�ϣ������Ͱ�ť��ʼ��
void CACMDlg::OnBnClickedDefault()
{
	IsExchange = 0;

	GetDlgItem(IDC_CV)->EnableWindow(TRUE);
	GetDlgItem(IDC_RSF)->EnableWindow(TRUE);
	GetDlgItem(IDC_DRLSE)->EnableWindow(TRUE);
	GetDlgItem(IDC_LRCV)->EnableWindow(TRUE);
	GetDlgItem(IDC_LIF)->EnableWindow(TRUE);
	GetDlgItem(IDC_LGIF)->EnableWindow(TRUE);
	GetDlgItem(IDC_LGDF)->EnableWindow(TRUE);
	GetDlgItem(IDC_GML)->EnableWindow(TRUE);
	GetDlgItem(IDC_Circle)->EnableWindow(TRUE);
	GetDlgItem(IDC_Rectangle)->EnableWindow(TRUE);
	GetDlgItem(IDC_Mask)->EnableWindow(TRUE);
	GetDlgItem(IDC_Interactive)->EnableWindow(TRUE);
	GetDlgItem(IDC_Default)->EnableWindow(TRUE);
	GetDlgItem(IDC_Save)->EnableWindow(TRUE);
	GetDlgItem(IDC_ClearAll)->EnableWindow(TRUE);
	GetDlgItem(IDC_PreFitting)->EnableWindow(TRUE);
	GetDlgItem(IDC_SyntropicFitting)->EnableWindow(TRUE);

	GetDlgItem(IDC_RSF)->SetWindowText(_T("RSF"));
	GetDlgItem(IDC_LIF)->SetWindowText(_T("LIF"));
	GetDlgItem(IDC_LRCV)->SetWindowText(_T("LRCV"));
	GetDlgItem(IDC_LGDF)->SetWindowText(_T("LGDF"));

	IsInitialization = FALSE;
	CString str;
	str.Format("%d", uint(Imgheight*0.25));
	GetDlgItem(IDC_Row1)->SetWindowText(str);
	str.Format("%d", uint(Imgheight*0.75));
	GetDlgItem(IDC_Row2)->SetWindowText(str);
	str.Format("%d", uint(ImgWidth*0.25));
	GetDlgItem(IDC_Collum1)->SetWindowText(str);
	str.Format("%d", uint(ImgWidth*0.75));
	GetDlgItem(IDC_Collum2)->SetWindowText(str);

	str.Format("%d", uint(ImgWidth*0.5));
	GetDlgItem(IDC_CircleX)->SetWindowText(str);
	str.Format("%d", uint(Imgheight*0.5));
	GetDlgItem(IDC_CircleY)->SetWindowText(str);
	str.Format("%d", uint(ImgWidth*0.25));
	GetDlgItem(IDC_CircleRadius)->SetWindowText(str);

	IsInitialization = TRUE;

	OnBnClickedRectangle();

	GetDlgItem(IDC_Num)->SetWindowText(_T("200"));
	GetDlgItem(IDC_Step)->SetWindowText(_T("0.1"));
	GetDlgItem(IDC_C0)->SetWindowText(_T("2"));
	GetDlgItem(IDC_Epison)->SetWindowText(_T("1"));
	GetDlgItem(IDC_Length)->SetWindowText(_T("0.003"));
	GetDlgItem(IDC_Penalty)->SetWindowText(_T("2"));
	GetDlgItem(IDC_Lamda1)->SetWindowText(_T("1"));
	GetDlgItem(IDC_Lamda2)->SetWindowText(_T("1"));
	GetDlgItem(IDC_Sig)->SetWindowText(_T("3"));
	GetDlgItem(IDC_Lamda)->SetWindowText(_T("10"));
	GetDlgItem(IDC_Alfa)->SetWindowText(_T("-5"));
	GetDlgItem(IDC_Weight)->SetWindowText(_T("0.05"));
	GetDlgItem(IDC_SE_Radius)->SetWindowText(_T("13"));
	GetDlgItem(IDC_interval)->SetWindowText(_T("10"));
	GetDlgItem(IDC_LineWidth)->SetWindowText(_T("1"));
	GetDlgItem(IDC_R)->SetWindowText(_T("255"));
	GetDlgItem(IDC_G)->SetWindowText(_T("0"));
	GetDlgItem(IDC_B)->SetWindowText(_T("0"));

	((CButton*)GetDlgItem(IDC_PreFitting))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_SyntropicFitting))->SetCheck(FALSE);
	IsExchange = FALSE;
	IsPreFitting = FALSE;
}

//������
void CACMDlg::DrawContour(Mat LSF, Mat Img)
{
	Mat src = (LSF < 0); //�ȵõ���ֵͼ
	vector <vector<Point> > contours;
	vector <Vec4i> hierarchy;
	GetShow();
	findContours(src, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);
	drawContours(Img, contours, -1, Scalar(Show.colorB, Show.colorG, Show.colorR), Show.linewidth);
	ShowImage(Img, IDC_ShowImg);//��ʾ
	image = Img.clone(); //���ڱ���
}

//��MFC��ʾͼƬ
void CACMDlg::ShowImage(Mat Img, UINT ID)
{
	IplImage *img;
	img = &IplImage(Img);
	CDC* pDC = GetDlgItem(ID)->GetDC();
	HDC hDC = pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	SetRect(rect, rect.left, rect.top, rect.right, rect.bottom);
	CvvImage cimg;
	cimg.CopyOf(img);
	cimg.DrawToHDC(hDC, &rect);
	ReleaseDC(pDC);
}

//����ͼƬ
void CACMDlg::OnBnClickedSave()
{
	if (image.data != NULL)
	{
		CString imageResult;
		//�����Ի���ѡ��·��
		CFileDialog fileDlg(FALSE, "", FileName, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, "*.bmp", this);
		if (fileDlg.DoModal() == IDOK)
			imageResult = fileDlg.GetPathName();
		else
			return;
		string strPath = imageResult.GetBuffer(0);//·����CStringת��Ϊstring
		image.convertTo(image, CV_8UC1);
		imwrite(strPath, image);
	}
	else
		AfxMessageBox(_T("Failed��"));
}

//EDIT��ֵ�ı�ʱ����
void CACMDlg::OnEnChangeRow1()
{
	UpdataEdit_InitialContour();
}

void CACMDlg::OnEnChangeRow2()
{
	UpdataEdit_InitialContour();
}

void CACMDlg::OnEnChangeCollum1()
{
	UpdataEdit_InitialContour();
}

void CACMDlg::OnEnChangeCollum2()
{
	UpdataEdit_InitialContour();
}

void CACMDlg::OnEnChangeCirclex()
{
	UpdataEdit_InitialContour();
}

void CACMDlg::OnEnChangeCircley()
{
	UpdataEdit_InitialContour();
}

void CACMDlg::OnEnChangeCircleradius()
{
	UpdataEdit_InitialContour();
}

void CACMDlg::UpdataEdit_InitialContour()
{
	if (IsInitialization == TRUE)
	{
		Mat Img = Image_.clone();
		Mat InitialLSF = InitialContour();
		DrawContour(InitialLSF, Img);//��ʾ��ʱ��ʼ����
	}
}

//ѡ��Radio Button
void CACMDlg::OnBnClickedCircle()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	((CButton*)GetDlgItem(IDC_Rectangle))->SetCheck(FALSE); //��ѡ��
	GetDlgItem(IDC_Row1)->EnableWindow(FALSE);
	GetDlgItem(IDC_Row2)->EnableWindow(FALSE);
	GetDlgItem(IDC_Collum1)->EnableWindow(FALSE);
	GetDlgItem(IDC_Collum2)->EnableWindow(FALSE);

	((CButton*)GetDlgItem(IDC_Circle))->SetCheck(TRUE); //ѡ��
	GetDlgItem(IDC_CircleX)->EnableWindow(TRUE);
	GetDlgItem(IDC_CircleY)->EnableWindow(TRUE);
	GetDlgItem(IDC_CircleRadius)->EnableWindow(TRUE);

	((CButton*)GetDlgItem(IDC_Mask))->SetCheck(FALSE); //��ѡ��
	((CButton*)GetDlgItem(IDC_Interactive))->SetCheck(FALSE); //��ѡ��

	UpdataEdit_InitialContour();
}

void CACMDlg::OnBnClickedRectangle()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	((CButton*)GetDlgItem(IDC_Rectangle))->SetCheck(TRUE); //ѡ��
	GetDlgItem(IDC_Row1)->EnableWindow(TRUE);
	GetDlgItem(IDC_Row2)->EnableWindow(TRUE);
	GetDlgItem(IDC_Collum1)->EnableWindow(TRUE);
	GetDlgItem(IDC_Collum2)->EnableWindow(TRUE);

	((CButton*)GetDlgItem(IDC_Circle))->SetCheck(FALSE); //��ѡ��
	GetDlgItem(IDC_CircleX)->EnableWindow(FALSE);
	GetDlgItem(IDC_CircleY)->EnableWindow(FALSE);
	GetDlgItem(IDC_CircleRadius)->EnableWindow(FALSE);

	((CButton*)GetDlgItem(IDC_Mask))->SetCheck(FALSE); //��ѡ��
	((CButton*)GetDlgItem(IDC_Interactive))->SetCheck(FALSE); //��ѡ��

	UpdataEdit_InitialContour();
}

void CACMDlg::OnBnClickedMask()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	((CButton*)GetDlgItem(IDC_Rectangle))->SetCheck(FALSE);
	GetDlgItem(IDC_Row1)->EnableWindow(FALSE);
	GetDlgItem(IDC_Row2)->EnableWindow(FALSE);
	GetDlgItem(IDC_Collum1)->EnableWindow(FALSE);
	GetDlgItem(IDC_Collum2)->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_Circle))->SetCheck(FALSE);
	GetDlgItem(IDC_CircleX)->EnableWindow(FALSE);
	GetDlgItem(IDC_CircleY)->EnableWindow(FALSE);
	GetDlgItem(IDC_CircleRadius)->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_Interactive))->SetCheck(FALSE);

	CFileDialog dlg(true, _T("*.bmp"), NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image file(*.bmp;*.jpg)|*.bmp;*.jpg|All Files(*.*)|*.*|"), NULL);//����ѡ��ͼƬ�Ի���
	dlg.m_ofn.lpstrTitle = _T("Open Mask Image");
	if (dlg.DoModal() != IDOK)
		return;
	CString m_strPicPath = dlg.GetPathName();//ͼ������·��
	m_strPicPath.Replace(_T("//"), _T("////"));
	string strPath; //·����CStringת��Ϊstring
	strPath = m_strPicPath.GetBuffer(0);
	mask = imread(strPath, 0);//����ͼ��

	if (mask.data == NULL)
		AfxMessageBox(_T("Failed��"));
	else if (mask.size() != Image.size())
		AfxMessageBox(_T("The size of mask image is not equal to original image!"));
	else
		UpdataEdit_InitialContour();
}

void on_mouse(int event, int x, int y, int flags, void *ustc)//event����¼����ţ�x,y������꣬flags��ק�ͼ��̲����Ĵ���??
{
	if (event == CV_EVENT_LBUTTONDOWN)//������£���ȡ����
	{
		CACMDlg* pThis = (CACMDlg*)ustc;

		char temp[20];
		pThis->ICPoint.push_back(Point(x, y));
		sprintf(temp, "(%d,%d)", x, y);
		putText(pThis->IC_Img, temp, pThis->ICPoint[pThis->PIndex], FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0));//�ڴ�������ʾ����
		if (pThis->PIndex == 0)
			circle(pThis->IC_Img, pThis->ICPoint[0], 1, Scalar(0, 0, 255));
		else
			line(pThis->IC_Img, pThis->ICPoint[pThis->PIndex - 1], pThis->ICPoint[pThis->PIndex], Scalar(0, 0, 255));
		imshow(pThis->MouseEvent, pThis->IC_Img);
		pThis->PIndex++;
		Sleep(200);

		if ((char)waitKey(0) == '\r') //����
		{
			destroyWindow(pThis->MouseEvent);

			int s = pThis->ICPoint.size();
			Point root_points[1][20];
			for (int i = 0; i < s; i++)
				root_points[0][i] = pThis->ICPoint[i];
			const Point* ppt[1] = { root_points[0] };
			int npt[] = { s };
			Mat Zero = Mat::zeros(pThis->Image.size(), CV_8UC1);
			fillPoly(Zero, ppt, npt, 1, Scalar(255), 1);

			pThis->Roipoly = Zero.clone();
			pThis->UpdataEdit_InitialContour();//����ʼ����
			pThis->PIndex = 0;
			pThis->ICPoint.clear();
		}
	}
}
void CACMDlg::OnBnClickedInteractive()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	((CButton*)GetDlgItem(IDC_Rectangle))->SetCheck(FALSE);
	GetDlgItem(IDC_Row1)->EnableWindow(FALSE);
	GetDlgItem(IDC_Row2)->EnableWindow(FALSE);
	GetDlgItem(IDC_Collum1)->EnableWindow(FALSE);
	GetDlgItem(IDC_Collum2)->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_Circle))->SetCheck(FALSE);
	GetDlgItem(IDC_CircleX)->EnableWindow(FALSE);
	GetDlgItem(IDC_CircleY)->EnableWindow(FALSE);
	GetDlgItem(IDC_CircleRadius)->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_Mask))->SetCheck(FALSE);

	MouseEvent = "Choose Initial Contour";
	namedWindow(MouseEvent);//����һ������
	imshow(MouseEvent, Image);
	Image_.copyTo(IC_Img);
	setMouseCallback(MouseEvent, on_mouse, this);//��������¼��Ļص�����
}

//Help
void CACMDlg::OnBnClickedHelp()
{
	Help  help;
	if (IDOK == help.DoModal())
	{
	}
}

//�˳�
void CACMDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UINT Flag = MessageBox(_T("Are you sure to exit��"), _T("Tip"), MB_YESNO | MB_ICONQUESTION);
	if (IDNO == Flag)
		return;
	CDialogEx::OnCancel();
}