
// chiropracticDlg.h : ͷ�ļ�
//

#pragma once
#include"opencv2/opencv.hpp"
#include "afxwin.h"
#include"InitGdiplus.h"
#include "MyEdit.h"


enum drawTpye{ DRAW_LINE = 1, DRAW_DIAGNOSE, DRAW_LINE_MEASURE, DRAW_LINE_VERTICALLINE,DRAW_DIGU_LINE,DRAW_CIRCLE,DRAW_YAOZHUI_MEASURE,
	DRAW_BASE_LINE, DRAW_XIONGZHUI_MEASURE, DRAW_JINGZHUIZHENGMIAN_MEASURE, DRAW_JINGZHUIZHANGKOU_MEASURE
};
enum opType {DRAW_RECT = 1, DRAW_MEASURE,DIAG_QG ,DIAG_DG, DIAG_YZ, DIAG_YZJ,DIAG_XZ,DIAG_JZ,DIAG_HZ
};
typedef struct _logLnfo {
	cv::Point p[10];
	cv::Point center[5];
	double length[2];			//��������
	char text[3][20];			//���ֱ�ע���������ȡ���Ͻ���ȣ�
	int op;						//��������
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


// ��ת���ж�����
private:
	int m_rotateMethod;
	int m_curRotateStep;
	double m_dGrad_line_rotate;
	CString m_strYfc;		// R/L/-
	bool m_bHas_draw_yfc;
	cv::Point m_point_rotate[4];

// ͨ�ò���
private:
	bool m_bNeedSave;
	bool m_bCanCutPic;
	bool m_bDraw_rotate;
	int m_opType;
	int m_curStep;				// ��ǰ��������
	

	bool m_bLButtonDown; //��¼�Ƿ�����������
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
	int m_font_type_diag;				// ��Ͻ������������
	double m_font_scale_diag;			// ��Ͻ���������С
	int m_font_thick_diag;			// ��Ͻ��������
	CString *m_strHint;					// ������ʾ
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
// �㡢�ֶ����ò������
	CString m_strText;
	bool m_bPutText;
// һ���Ĺǰ���λ
//��������
private:
	CString m_strDiag_qg;			// �Ĺ���Ͻ��
	CString m_strHint_qg[20];		// �Ĺǲ�����ʾ
	double m_dGrad_gg_x_qg;				// �ɹ�ͷ��б��
	double m_dGrad_gg_y_qg;				// �ɹ�ͷ�ߴ�ֱ�ߵ�б��
	double m_dLength_wmg_l_qg;			// �����ǳ���
	double m_dLength_wmg_r_qg;
	double m_dLength;					// �ܹ����������������ߵľ���, ƫ���������Ϊ����ƫ�������Ҳ�Ϊ��
	//double m_dLlength_xiaguanjie;			// �¹ؽ�ͻӰ����
	//double m_dRlength_xiaguanjie;
	bool m_bDiag_dg_qg;					// �Ƿ�����������

///////////////////////////////////////////////////////////////////////////////////////
//�������ǰ���λ
private:
	CString m_strDiag_dg;				// ������Ͻ��
	CString m_strHint_dg[20];			// ���ǲ�����ʾ
	double m_dGrad_dg_x_dg;				// ����ˮƽ��б��
	double m_dGrad_dg_y_dg;				// ����ˮƽ�ߴ�ֱ�ߵ�б��
	//double m_grad_gugu_x;				// ����ǰ�涨��õ�
	double m_dLength_l_dg;				// �������߳���
	double m_dLength_r_dg;
	double m_dLength_xx_dg;			// ��������ƫλ
	double m_dThres_dg;				// ��������ƫλ��ֵ

	

///////////////////////////////////////////////////////////
// ��׵���
private:
	CString m_strHint_yz[20];											// ��׵������ʾ
	CString m_strDiag_yz[6];											// ��׵��Ͻ��
	int m_curDiag_yz;													// ��ǰ������ϵ���׵
	int m_curDiag_xie_yz;												// ��ǰШ����ϵĲ�������
	double m_dThres_xie_yz;												// Ш���п��ж���ֵ
	CString m_strBend_yz;												// ��׵����͹��
	bool m_bLuxs_yz[6];													// ��׵�Ƿ���λ
	bool m_bDraw_yfc_step;												// �Ƿ����ж�ԭ����Ĳ���
	int m_total_lux_yz;													// ����λ��׵����
	double m_dGrad_bj_yz[2];											// ��������ֱ��б�� [0]--��[1]--��
	double m_dBias_bj_yz[2];											// ��������ֱ��ƫ�� [0]--��[1]--��
	cv::Point m_point_cp_l_yz[6];										// ֱ������߽�ֱ�ߵĽ���
	cv::Point m_point_cp_r_yz[6];										// ֱ�����ұ߽�ֱ�ߵĽ��㣬5����׵��һ����׼��
	//
// ��������
private:
	
////////////////////////////////////////////////////////////
// ���������
private:
	double m_grad_yaozhuijiao_x;
	CString m_YaoDiJiao_diagnose;			// ��Ͻ��
	CString m_csYaoDiJiao_remind[20];		// �����ǲ�����ʾ
////////////////////////////////////////////////////////////
// ��׵���
private:
	CString m_strHint_xz[20];											// ��׵������ʾ
	CString m_strDiag_xz[13];											// ��׵��Ͻ��
	int m_curDiag_xz;													// ��ǰ������ϵ���׵
	int m_curDiag_xie_xz;												// ��ǰШ����ϵĲ�������
	double m_dThres_xie_xz;												// Ш���п��ж���ֵ
	CString m_strBend_xz;												// ��׵����͹��
	//bool m_bLuxs_xz[13];												// ��׵�Ƿ���λ
	int m_total_lux_xz;													// ����λ��׵����
	double m_dGrad_bj_xz[2];											// ��������ֱ��б�� [0]--��[1]--��
	double m_dBias_bj_xz[2];											// ��������ֱ��ƫ�� [0]--��[1]--��
	cv::Point m_point_cp_l_xz[13];										// ֱ������߽�ֱ�ߵĽ���
	cv::Point m_point_cp_r_xz[13];										// ֱ�����ұ߽�ֱ�ߵĽ��㣬12����׵��һ����׼��

///////////////////////////////////////////////////////////////////
// ���� ��׵
private:
	CString m_strHint_jz[20];											// ��׵������ʾ
	CString m_strDiag_jz[13];											// ��׵��Ͻ��
	int m_curDiag_jz;													// ��ǰ������ϵľ�׵
	int m_curDiag_step_jz;												// ��ǰ��ϵĲ�������
	double m_dThres_xie_jz;												// Ш���п��ж���ֵ
	CString m_strBend_jz;												// ��׵����͹��
	//bool m_bLuxs_jz[13];												// ��׵�Ƿ���λ
	int m_total_lux_jz;													// ����λ��׵����
	double m_dGrad_bj_jz[2];											// ��������ֱ��б�� [0]--��[1]--��
	double m_dBias_bj_jz[2];											// ��������ֱ��ƫ�� [0]--��[1]--��
	cv::Point m_point_cp_l_jz[13];										// ֱ������߽�ֱ�ߵĽ���
	cv::Point m_point_cp_r_jz[13];										// ֱ�����ұ߽�ֱ�ߵĽ���

// �׵
private:
	cv::Mat m_jzzcImg;													// ��׵����λƬ
	cv::Mat m_jzzkImg;													// ��׵�ſ�λƬ
	bool m_bHas_changed_img;											// �Ƿ���������ͼ��
	bool m_bHas_draw_step8;												// �Ƿ���Ҫ��step 8 ��������˵Ҫ����ͼ��
	double m_dThres_H_hz;												// 
	CString m_strHint_hz[20];											// �׵������ʾ
	CString m_strDiag_hz[13];											// �׵��Ͻ��
	double m_dGrad_czt_hz;
	double m_dBias_czt_hz;
	double m_dGrad_bj_hz[2];											// ��������ֱ��б�� [0]--��[1]--��
	double m_dBias_bj_hz[2];											// ��������ֱ��ƫ�� [0]--��[1]--��
	cv::Point m_point_cp_l_hz[5];										// ֱ������߽�ֱ�ߵĽ���
	cv::Point m_point_cp_r_hz[5];										// ֱ�����ұ߽�ֱ�ߵĽ��㣬
	cv::Point m_point_jzzk_bj_lt;												// ��׵�ſ�λƬ�ı߽�ֱ�ߵ�
	cv::Point m_point_jzzk_bj_lb;
	cv::Point m_point_jzzk_bj_rt;
	cv::Point m_point_jzzk_bj_rb;

// ��������
private:
	// ��������ֱ�ߵĽ���
	cv::Point intersect(cv::Point aa, cv::Point bb, cv::Point cc, cv::Point dd);
	// �ж�����ֱ���Ƿ��ཻ
	//bool intersect(CvPoint aa, CvPoint bb, CvPoint cc, CvPoint dd);
	 // �����ж�����ֱ���Ƿ�ƽ�У��Ƚ�б���Ƿ���ȣ�
	double determinant(double v1, double v2, double v3, double v4);
	// ���ߵ��ӳ���
	void  lineExt(double grad, cv::Point center, double lenth_lt, double lenth_rb, cv::Point &p_lt, cv::Point &p_rb);
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
	// ��ť�ؼ���ʼ��
	void initCtrlBtn(BOOL selBtn0, BOOL selBtn1);
	// ��ť�ؼ���۸ı�
	void changeCtrlBtn(INT selBtn = NULL, INT selBtn1 = NULL);
	// ��ת�жϺ���
	bool drawYfc(cv::Point pt);
	// 


// �������������ԵȲ���
public:
		double m_edit;
		CComboBox m_Combo;
		CComboBox m_Combo2;
		CMyEdit m_ctrlHint;
		CMyEdit m_logo;
		CMyEdit m_gallery;

		CMFCButtonEx m_button2;
		CMFCButtonEx m_button3;
		CMFCButtonEx m_button6;
		CMFCButtonEx m_button8;
		CMFCButtonEx m_button9;
		CMFCButtonEx m_button15;
		CMFCButtonEx m_button14;
		CMFCButtonEx m_button10;
		CMFCButtonEx m_button11;

		CMFCButtonEx m_button_op1;
		CMFCButtonEx m_button_op2;
		CMFCButtonEx m_button_op3;
		CMFCButtonEx m_button_op4;
		CMFCButtonEx m_button_op5;
		CMFCButtonEx m_button_op6;
		CMFCButtonEx m_button_op7;
		CMFCButtonEx m_button_op8;
		CMFCButtonEx m_button_op9;
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
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton6();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButtonOp1();
	afx_msg void OnBnClickedButtonOp2();
	afx_msg void OnBnClickedButtonOp3();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButtonOp4();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButtonOp5();
	afx_msg void OnBnClickedButtonOp6();
	afx_msg void OnBnClickedButtonOp7();
	afx_msg void OnCbnSelchangeCombo2();
};
