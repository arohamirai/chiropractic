
// chiropracticDlg.h : ͷ�ļ�
//

#pragma once
#include"opencv2/opencv.hpp"
#include "afxwin.h"
#include"InitGdiplus.h"
#include "MyEdit.h"


enum drawTpye{ DRAW_LINE = 1, DRAW_DIAGNOSE, DRAW_LINE_MEASURE, DRAW_LINE_VERTICALLINE,DRAW_DIGU_LINE,DRAW_CIRCLE,DRAW_YAOZHUI_MEASURE,
	DRAW_BASE_LINE
};
enum opType {DRAW_RECT = 1, DRAW_MEASURE,DIAG_QIAGU ,DIAG_DIGU, DIAG_YAOZHUI, DIAG_YAODIJIAO
};
typedef struct _logLnfo {
	//cv::Point p1;
	//cv::Point p2;
	//cv::Point p3;
	//cv::Point p4;
	cv::Point p[10];		// p[0~1] ����ֱ�ߣ�p[2~3]������
	cv::Point center[5];
	//cv::Point center1;		 // ��ֱ��ʱ��ȡ�ؼ���
	//cv::Point center2;		// ����Բ����ע�����֡���Ͻ����������λ�á�
	double length[2];				//��������
	char text[3][20];			//���ֱ�ע���������ȡ���Ͻ���ȣ�
	int op;					//��������
	int step;
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


// ͨ�ò���
private:
	bool m_bNeedSave;
	int m_opType;
	bool m_bLButtonDown; //��¼�Ƿ�����������
	int m_curStep;				// ��ǰ��������

	int m_ctrlWidth;	// ͼ��ʵ�ʳ���(mm)
	int m_ctrlHeight;
	double m_dWidthScale;	// ��������(mm/����)
	double m_dHeightScale;

	cv::Mat m_loadImg; //��Ϊ���������Ź��ܣ�û�취��ֻ���ټ�һ����������ԭʼ�����ͼ��(��ʷ��������)
	cv::Mat m_srcImg;  // �ü���ͼ�����ڼ�¼���ñ�����ԭʼ����ͼ����ܲ���һ������֪Ϥ
	cv::Mat m_zoomImg; // ���ź��ͼ��
	cv::Mat m_maskImg; // ���ڼ�¼
	cv::Mat m_maskShowImg; // ������ʾ

	cv::Point m_p1, m_p2;  // ͼ������ϵ,���ڻ�ͼ
	cv::Point m_gp[30];		// ����ʱ���õ��ĵ�
	cv::vector<logInfo> m_vecLog;	 // ������־
	cv::vector<logInfo> m_vecDelLog; // ��������

	// ��ͼ��ز���
	int m_circleRadius;
	int m_lineWidth;						// �ߵĿ��
	cv::Scalar m_maskColor;					// �ɰ���ɫ
	cv::Scalar m_lineColor;					// �ߵ���ɫ
	cv::Scalar m_circleColor;				// СԲ�����ɫ
	cv::Scalar m_infoColor;					// CTƬ��Ϣ��������ɫ;
	cv::Scalar m_diagnoseColor;				// ��Ͻ��������ɫ
	cv::Scalar m_measureColor;				// ��Ƭʱ������ֵ����ɫ
	int m_fontTypeOfInfo;					// CTƬ��Ϣ��������
	double m_dFontSizeOfInfo;				// CTƬ��Ϣ�����С
	int m_fontThicknessOfInfo;				// CTƬ��Ϣ������
	int m_fontTypeOfMeasure;				// ��Ƭʱ������ֵ����������
	double m_dFontSizeOfMeasure;			// ��Ƭʱ������ֵ�������С
	int m_fontThicknessOfMeasure;			// ��Ƭʱ������ֵ��������
	int m_fontTypeOfDiagnose;				// ��Ͻ������������
	double m_dFontSizeOfDiagnose;			// ��Ͻ���������С
	int m_fontThicknessOfDiagnose;			// ��Ͻ��������
	CString *m_csRemind;					// ������ʾ
// ��������
	REAL m_zoom;  //����ϵ��
	//CRect m_Rect; //�Ի���ľ�������
	REAL m_imgX; //ͼƬ���Ͻ�X��ƫ����,����ڿؼ����Ͻ�
	REAL m_imgY; //ͼƬ���Ͻ�Y��ƫ����
	PointF m_PtStart;    //��������������¼��ǰ��m_imgX,m_imgY
	PointF m_mouseDown;  //����������ʱ�������ͼƬ�ؼ��е�λ�ã�
///////////////////////////////////////////////////////////
// DRAW_MEASURE
	int m_recordFirstPoint; // �Ƿ��¼�˵�һ����

////////////////////////////////////////////////////////////////////////////////
// һ���Ĺǰ���λ
//��������
private:
	double m_grad_gugu_x;				// �ɹ�ͷ��б��
	double m_grad_gugu_y;				// �ɹ�ͷ�ߴ�ֱ�ߵ�б��
	double m_dLlength_wuminggu;			// �����ǳ���
	double m_dRlength_wuminggu;
	double m_dLength;					// �ܹ����������������ߵľ���, ƫ���������Ϊ����ƫ�������Ҳ�Ϊ��
	double m_dLlength_xiaguanjie;			// �¹ؽ�ͻӰ����
	double m_dRlength_xiaguanjie;

	CString m_qiagu_diagnose;			// �Ĺ���Ͻ��
// ��������
private:
	CString m_csQiagu_remind[20];		// �Ĺǲ�����ʾ

///////////////////////////////////////////////////////////////////////////////////////
//�������ǰ���λ
private:
	double m_grad_digu_x;				// ����ˮƽ��б��
	double m_grad_digu_y;				// ����ˮƽ�ߴ�ֱ�ߵ�б��
	//double m_grad_gugu_x;				// ����ǰ�涨��õ�

	double m_dLlength_digu;				// �������߳���
	double m_dRlength_digu;
	double m_dDigu_down;				// ��������ƫλ

	CString m_digu_diagnose;			// ������Ͻ��
// ��������
private:
	CString m_csDigu_remind[20];		// ���ǲ�����ʾ

///////////////////////////////////////////////////////////
// ��׵���
private:
	double m_grad[2];									// ��������ֱ��б�� [0]--��[1]--��
	double m_bias[2];									// ��������ֱ��ƫ�� [0]--��[1]--��
	std::vector<std::vector<cv::Point>> m_vecCpPoint;	// ֱ����߽�ֱ�ߵĽ���
	std::vector<std::vector<double>> m_vecMeasure;		// �ؾ�
	std::vector<std::vector<cv::Point>> m_vecCpPointDel;	// ֱ����߽�ֱ�ߵĽ���
	std::vector<std::vector<double>> m_vecMeasureDel;		// �ؾ�

	std::vector<CString> m_yaozhui_diagnose;			// ��׵��Ͻ��
// ��������
private:
	CString m_csaoZhui_remind[20];		// ��׵������ʾ
	CString m_csYaoZhui_remind[20];		// ��׵������ʾ

// ���������
private:
	double m_grad_yaozhuijiao_x;
	CString m_YaoDiJiao_diagnose;			// ��Ͻ��
	CString m_csYaoDiJiao_remind[20];		// ��׵������ʾ
////////////////////////////////////////////////////////////
// ��������
private:
	// ��������ֱ�ߵĽ���
	cv::Point intersect(cv::Point aa, cv::Point bb, cv::Point cc, cv::Point dd);
	// �ж�����ֱ���Ƿ��ཻ
	//bool intersect(CvPoint aa, CvPoint bb, CvPoint cc, CvPoint dd);
	 // �����ж�����ֱ���Ƿ�ƽ�У��Ƚ�б���Ƿ���ȣ�
	double determinant(double v1, double v2, double v3, double v4);
	// ���ߵ��ӳ���
	void  lineExt(double grad, cv::Point center, double lenth_lt, double lenth_rb, cv::Point &p_l, cv::Point &p_r);
	// �����ֱ�ߵĴ�ֱ��
	cv::Point lineCrossDot(double grad, cv::Point p1, cv::Point p2);
	// ��ȡ*.dcm��CTƬ��OpenCV֧�ָ�ʽ
	bool dcm2Mat(const char* const fileName, cv::Mat &mat);
	// �ַ���ת��
	std::string WChar2Ansi(LPSTR pwszSrc);
	// ��Ϻ���
	CString diagnose(int op_type, cv::Point &pose);
	// ��ʼ��������
	void initParam();
	// �����ʾ��䣬�Ե�ǰ����������и���
	void remindColor();

public:
		double m_edit;
		CComboBox m_Combo;
		CMyEdit m_remind1;
public:
	void Invalidate(BOOL bErase = 1);
	void Draw(CDC *pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton10();
	//afx_msg void OnBnClickedButton5();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton6();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnCbnSelchangeCombo1();
	//afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButtonOp1();
	afx_msg void OnBnClickedButtonOp2();
	afx_msg void OnBnClickedButtonOp3();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButtonOp4();
};
