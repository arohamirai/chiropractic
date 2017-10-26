
// chiropracticDlg.h : ͷ�ļ�
//

#pragma once
#include"opencv2/opencv.hpp"
#include "afxwin.h"
#include"InitGdiplus.h"

#define DRAW_LINE 1
#define DRAW_RECT 2
#define DRAW_LABEL 3
#define DRAW_MEASURE 4

typedef struct _logLnfo {
	cv::Point p1;
	cv::Point p2;
	cv::Point center;
	int op;  //��������
	int step;
	char text[20];
}logInfo;


// CchiropracticDlg �Ի���
class CchiropracticDlg : public CDialogEx
{
// ����
public:
	CchiropracticDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHIROPRACTIC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();


private:
	cv::Mat m_loadImg; //��Ϊ���������Ź��ܣ�û�취��ֻ���ټ�һ����������ԭʼ�����ͼ��(��ʷ��������)
	cv::Mat m_srcImg;  // �ü���ͼ�����ڼ�¼���ñ�����ԭʼ����ͼ����ܲ���һ������֪Ϥ
	cv::Mat m_zoomImg; // ���ź��ͼ��

	//cv::Mat m_showImg; // ������ʾ
	cv::Mat m_maskImg; // ���ڼ�¼
	cv::Mat m_maskShowImg; // ������ʾ

	cv::Point m_p1, m_p2;  // ͼ������ϵ,���ڻ�ͼ
	cv::Point m_pp;			//���ڱ�ע
	cv::Point m_selP1;		// ѡȡģʽ��һ����
	cv::Point m_p[12];


	cv::vector<logInfo> m_vecLog;	 // ������־�����������ϵΪm_srcImg����ϵ
	cv::vector<logInfo> m_vecDelLog; // ��������


	REAL m_zoom;  //����ϵ��
	CRect m_Rect; //�Ի���ľ�������

	REAL m_imgX; //ͼƬ���Ͻ�X��ƫ����,����ڿؼ����Ͻ�
	REAL m_imgY; //ͼƬ���Ͻ�Y��ƫ����

	PointF m_PtStart;    //��������������¼��ǰ��m_imgX,m_imgY
	PointF m_mouseDown;  //����������ʱ�������ͼƬ�ؼ��е�λ�ã�

// ��������
private:
	bool m_bLButtonDown; //��¼�Ƿ�����������
	bool m_bDrawLine;
	bool m_bDrawRect;

	int m_ctrlWidth;
	int m_ctrlHeight;

	double m_dWidth;
	double m_dHeight;
	double m_dWidthScale;
	double m_dHeightScale;
////////////////////////////////////////////////////////////
	double m_gradient_x;		// �����ƽ��
	double m_gradient_y;
	double m_gradient_x1;
	double m_gradient_y1;

	double m_dLlength;
	double m_dRlength;
	double m_dLlength1;
	double m_dRlength1;
	double m_dLength;
	int m_curStep;				// ��ǰ��������
	std::string m_result;

// ��ͼ��ز���
	int m_l;			// �߿�
	cv::Scalar m_lineColor;	// �ߵ���ɫ
	cv::Point m_pd;			//�������߹ؼ���

// ��������
private:
	bool intersect(CvPoint aa, CvPoint bb, CvPoint cc, CvPoint dd);
	double determinant(double v1, double v2, double v3, double v4);
	void  lineExt(double grad, cv::Point center, double lenth_lt, double lenth_rb, cv::Point &p_l, cv::Point &p_r);
	cv::Point lineCrossDot(double grad, cv::Point p1, cv::Point p2);
	std::string WChar2Ansi(LPCWSTR pwszSrc);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton6();
	double m_edit;
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox m_Combo;
	afx_msg void OnBnClickedButton12();
	void Invalidate(BOOL bErase = 1);
	void Draw(CDC *pDC);
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton13();
};
