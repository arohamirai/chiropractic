
// chiropracticDlg.h : ͷ�ļ�
//

#pragma once
#include"opencv2/opencv.hpp"
#include "afxwin.h"
#include"InitGdiplus.h"
#include "MyEdit.h"


// ��ͼ����
enum drawTpye {
	DRAW_LINE = 1, DRAW_DIAGNOSE, DRAW_LINE_MEASURE, DRAW_DIGU_SPX, DRAW_DI1, DRAW_LINE_VERTICALLINE, DRAW_DIGU_LINE, DRAW_CIRCLE, DRAW_YAOZHUI_MEASURE,
	DRAW_BASE_LINE, DRAW_XIONGZHUI_MEASURE, DRAW_JINGZHUIZHENGMIAN_MEASURE, DRAW_JINGZHUIZHANGKOU_MEASURE
};
// �������ͣ�����Ϊ����ȡͼƬ������������ϣ���׵��ϣ���������ϣ���׵��ϣ���׵��ϣ��׵��ϣ�������
enum opType {DRAW_RECT = 1,DIAG_GP, DIAG_YZ, DIAG_YDJ,DIAG_XZ,DIAG_JZ,DIAG_HZ, DIAG_ZG
};

// ������Ϣ��¼�ṹ��
typedef struct _logLnfo {
	cv::Point p[10];			//	�ؼ���
	cv::Point center[5];		//	�������ĵ�
	char text[3][20];			//	���ֱ�ע���������ȡ���Ͻ���ȣ�
	int op;						//	��������
	int step;					// �ǵڼ�������
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


// ԭ�����ж�����
private:
	int m_yfcMethod;					// ԭ�����жϷ���
	int m_curYfcStep;					// ԭ��������ڼ���
	double m_dGrad_line_yfc;			// ������Ҫ��¼��ֱ��б��
	CString m_strYfc;					// ԭ�����жϽ����R/L/-
	bool m_bHas_draw_yfc;				// �Ƿ����ԭ�������
	cv::Point m_point_yfc[4];			// ԭ���໭��ʱ��Ҫ����ĵ�

// ͨ�ò���
private:
	bool m_bNeedSave;					// �Ƿ���Ҫ���棬ֻҪ�޸Ĺ�ͼ�񣬸�ֵ��Ӧ��Ϊtrue
	bool m_bCanCutPic;					// �Ƿ������ȡͼƬ������ֻ�ڻ�δʵ�ʻ�Ƭʱ�����ֵΪtrue
	int m_opType;						// ��Ƭ�������ͣ���ȡͼƬ��������ϡ���׵��ϡ���׵�����......
	int m_curStep;						// ��ϲ�����һ��
	
	bool m_bLButtonDown;				//��¼�Ƿ�����������
	int m_ctrlWidth;					// ͼ��ʵ�ʿ��(mm)
	int m_ctrlHeight;					// ͼ��ʵ�ʳ���(mm)
	double m_dwidth_scale;				// ��ȷ����������(mm/����)
	double m_dheight_scale;				// ���ȷ����������(mm/����)

	cv::Mat m_loadImg;					//��Ϊ���������Ź��ܣ�û�취��ֻ���ټ�һ����������ԭʼ�����ͼ��(��ʷ��������)
	cv::Mat m_srcImg;					// �ü���ͼ�����ڼ�¼���ñ�����ԭʼ����ͼ�� m_loadImg ���ܲ���һ������֪Ϥ
	cv::Mat m_zoomImg;					// ���ź��ͼ��
	cv::Mat m_maskImg;					// ���ߵĲ�������¼�����ͼ���ϣ������OpenCV����ģ���ܵ��ӵ�m_srcImgͼ���ϣ����ڼ�¼
	cv::Mat m_maskShowImg;				// ����ʵʱ���߲������

	cv::Point m_p1, m_p2;				// ͼ������ϵ,���ڽ�ȡͼƬ����Ҫ��ͬʱ��OnLButtonDown()��OnLButtonUp()�������ȡ�ĵ�
	cv::Point m_gPoint[50];				// ��ϲ���ʱ��Ҫ��¼�ĵ�
	cv::vector<logInfo> m_vecLog;		// ������־�����ڳ���
	cv::vector<logInfo> m_vecDelLog;	// �������Ĳ�������������
	cv::vector<logInfo> m_vecLog_yfc;		// ����ԭ���⳷��������
	cv::vector<logInfo> m_vecDelLog_yfc;	// ����ԭ���⳷��������

	// ��ͼ��ز���
	int m_circleRadius;						// СԲ��İ뾶
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
	int m_font_type_measure;				// ��Ƭʱ������ֵ����������
	double m_dfont_scale_measure;			// ��Ƭʱ������ֵ�������С
	int m_font_thick_measure;				// ��Ƭʱ������ֵ��������
	int m_font_type_diag;					// ��Ͻ������������
	double m_dfont_scale_diag;				// ��Ͻ���������С
	int m_font_thick_diag;					// ��Ͻ��������
	CString *m_strHint;						// ������ʾָ�룬�Բ�ͬ����ϲ������ͣ�ָ���Ӧ�Ĳ�����ʾ�������
	CString m_strYfcHint[6][20];			// ԭ�����ж���ʾ���

	// ͼ��������ر���
	REAL m_zoom;							// ����ϵ��
	REAL m_imgX;							// ͼƬ���Ͻ�X��ƫ����,����ڿؼ����Ͻ�
	REAL m_imgY;							// ͼƬ���Ͻ�Y��ƫ����
	PointF m_PtStart;						// ��������������¼��ǰ��m_imgX,m_imgY
	PointF m_mouseDown;						// ����������ʱ�������ͼƬ�ؼ��е�λ�ã�
///////////////////////////////////////////////////////////
	double l_l, l_r;
////////////////////////////////////////////////////////////////////////////////
// һ���������λ���Ĺǡ����ǣ�
private:
	CString m_strDiag_qg;				// �Ĺ���Ͻ��
	CString m_strHint_gp[20];			// �Ĺǲ�����ʾ
	double m_dGrad_gg_x_qg_gp;				// �ɹ�ͷ��б��
	double m_dGrad_gg_y_qg_gp;				// �ɹ�ͷ�ߴ�ֱ�ߵ�б��
	double m_dLength_wmg_l_qg_gp;			// �������ǳ���
	double m_dLength_wmg_r_qg_gp;			// �������ǳ���
	double m_dLength_qg_gp;					// �ܹ����������������ߵľ���, ƫ���������Ϊ����ƫ�������Ҳ�Ϊ��
	bool m_bDiag_dg_gp;					// �Ƿ�����������
private:
	CString m_strDiag_dg_gp;				// ������Ͻ��
	double m_dGrad_dg_x_dg_gp;				// ����ˮƽ��б��
	double m_dGrad_dg_y_dg_gp;				// ����ˮƽ�ߴ�ֱ�ߵ�б��
	double m_dLength_l_dg_gp;				// �����߳���
	double m_dLength_r_dg_gp;				// �����߳���
	double m_dLength_xx_dg_gp;				// ��������ƫλ����
	double m_dThres_dg_gp;					// ��������ƫλ�趨��ֵ


///////////////////////////////////////////////////////////
// ��׵���
private:
	CString m_strHint_yz[20];											// ��׵������ʾ
	CString m_strDiag_yz[6];											// ��׵��Ͻ��
	int m_curDiag_yz;													// ��ǰ������ϵ���׵
	int m_curDiag_xie_yz;												// ��ǰШ����ϵĲ�������
	double m_dThres_xie_yz;												// Ш���п��ж��趨��ֵ
	CString m_strBend_yz;												// ��׵����͹��
	bool m_bLuxs_yz[6];													// ��׵�Ƿ���λ
	bool m_bDraw_yfc_step_yz;											// �Ƿ����ж�ԭ����Ĳ���
	int m_total_lux_yz;													// ����λ��׵����
	double m_dGrad_bj_yz[2];											// ��������ֱ��б�� [0]--��[1]--��
	double m_dBias_bj_yz[2];											// ��������ֱ��ƫ�� [0]--��[1]--��
	cv::Point m_point_cp_l_yz[6];										// ֱ������߽�ֱ�ߵĽ���
	cv::Point m_point_cp_r_yz[6];										// ֱ�����ұ߽�ֱ�ߵĽ��㣬5����׵��һ����׼��

	
////////////////////////////////////////////////////////////
// ���������
private:
	double m_grad_yaozhuijiao_x;			// ֱ��б��
	CString m_YaoDiJiao_diagnose;			// ��Ͻ��
	CString m_csYaoDiJiao_remind[20];		// �����ǲ�����ʾ
////////////////////////////////////////////////////////////
// ��׵���
private:
	CString m_strHint_xz[20];											// ��׵������ʾ
	CString m_strDiag_xz[20];											// ��׵��Ͻ��
	int m_curDiag_xz;													// ��ǰ������ϵ���׵
	int m_curDiag_xie_xz;												// ��ǰШ����ϵĲ�������
	
	CString m_strBend_xz;												// ��׵����͹��
	//bool m_bLuxs_xz[13];												// ��׵�Ƿ���λ
	int m_total_xz;														// ����λ��׵����
	double m_dGrad_bj_xz[2];											// ��������ֱ��б�� [0]--��[1]--��
	double m_dBias_bj_xz[2];											// ��������ֱ��ƫ�� [0]--��[1]--��
	cv::Point m_point_cp_l_xz[20];										// ֱ������߽�ֱ�ߵĽ���
	cv::Point m_point_cp_r_xz[20];										// ֱ�����ұ߽�ֱ�ߵĽ��㣬12����׵��һ����׼��

	CString m_strYfc_xz[20];											// ԭ�����ж�����׺1~12~L1��׵��0���ã���ͬ��
	CString m_strXie_xz[20];											// Ш�ο��ڳ���
	bool m_bHas_more_xz_xz;												// �Ƿ��г���12������׵
	bool m_bDraw_L1_xz;													// �Ƿ�L1��׵
	double m_bHas_draw_dd_line_xz;										// �Ƿ��Ѿ���������ˮƽ��
	double m_dGrad_dg_xz;												// ����ˮƽ�ߵ�б��
	double m_dThres_xie_xz;												// Ш���п��ж���ֵ
	void diagXz();														//��׵���

///////////////////////////////////////////////////////////////////
// ���� ��׵
private:
	CString m_strHint_jz[20];											// ��׵������ʾ
	CString m_strDiag_jz[13];											// ��׵��Ͻ��
	int m_curDiag_cw_jz;												// ��λƬ�ϵ�ǰ������ϵľ�׵
	int m_curDiag_zw_jz;												// ��λƬ�ϵ�ǰ������ϵľ�׵
	int m_curDiag_step_cw_jz;											// ��λƬ�ϵ�ǰ��ϵĲ�������
	int m_curDiag_step_zw_jz;											// ��λƬ�ϵ�ǰ��ϵĲ�������
	double m_dThres_xie_zw_jz;											// Ш���п��ж���ֵ
	CString m_strBend_jz;												// ��׵����͹��
	int m_total_lux_jz;													// ����λ��׵����
	double m_dGrad_cwbj_jz[2];											// ��λƬ����������ֱ��б�� [0]--��[1]--��
	double m_dBias_cwbj_jz[2];											// ��λƬ����������ֱ��ƫ�� [0]--��[1]--��
	double m_dGrad_zwbj_jz[2];											// ��λƬ����������ֱ��б�� [0]--��[1]--��
	double m_dBias_zwbj_jz[2];											// ��λƬ����������ֱ��ƫ�� [0]--��[1]--��
	cv::Point m_point_cp_cw_l_jz[13];									// ��λƬ��ֱ������߽�ֱ�ߵĽ���
	cv::Point m_point_cp_cw_r_jz[13];									// ��λƬ��ֱ�����ұ߽�ֱ�ߵĽ���
	cv::Point m_point_cp_zw_l_jz[13];									// ��λƬ��ֱ������߽�ֱ�ߵĽ���
	cv::Point m_point_cp_zw_r_jz[13];									// ��λƬ��ֱ�����ұ߽�ֱ�ߵĽ���
	CString m_strYfc_jz[8];												// ��׵ԭ����
	CString m_strXie_zw_jz[10];
	void diagJz();														// ��׵���

// �ߡ� �׵
private:
	CString m_strHint_hz[20];											// �׵������ʾ
	CString m_strDiag_hz;												// �׵��Ͻ��
	cv::Mat m_jzzcImg_hz;												// ��׵����λƬ
	cv::Mat m_jzzkImg_hz;												// ��׵�ſ�λƬ
	bool m_bHas_changed_img_hz;											// �Ƿ���������ͼ��
	bool m_bHas_draw_step8_hz;											// �Ƿ���Ҫ��step 8 ��������˵Ҫ����ͼ��
	double m_dGrad_czt_hz;												// ��״ͻ
	double m_dBias_czt_hz;
	double m_dGrad_bj_hz[2];											// ��������ֱ��б�� [0]--��[1]--��
	double m_dBias_bj_hz[2];											// ��������ֱ��ƫ�� [0]--��[1]--��
	cv::Point m_point_cp_l_hz[5];										// ֱ������߽�ֱ�ߵĽ���
	cv::Point m_point_cp_r_hz[5];										// ֱ�����ұ߽�ֱ�ߵĽ��㣬
	cv::Point m_point_jzzk_bj_hz[4];									// ��׵�ſ�λƬ�ı߽�ֱ��
	void diagHz();

// �ˡ� ���
	cv::Mat m_jzzcImg_zg;												// ��׵����λƬ
	cv::Mat m_jzzkImg_zg;												// ��׵�ſ�λƬ
	bool m_bHas_changed_img_zg;											// �Ƿ���������ͼ��
	bool m_bHas_draw_step12_zg;											// �Ƿ���Ҫ��step 8 ��������˵Ҫ����ͼ��
	double m_dThres_H_zg;												// 
	CString m_strHint_zg[20];											// ��ǲ�����ʾ
	CString m_strDiag_zg;												// �����Ͻ��
	double m_dGrad_czt_zg;												// ��״ͻ
	double m_dBias_czt_zg;
	double m_dGrad_bj_zg[2];											// ��������ֱ��б�� [0]--��[1]--��
	double m_dBias_bj_zg[2];											// ��������ֱ��ƫ�� [0]--��[1]--��
	cv::Point m_point_cp_l_zg[10];										// ֱ������߽�ֱ�ߵĽ���
	cv::Point m_point_cp_r_zg[10];										// ֱ�����ұ߽�ֱ�ߵĽ��㣬
	cv::Point m_point_jzzk_bj_zg[4];									// ��׵�ſ�λƬ�ı߽�ֱ�ߵ�

	void diagZg();

// ��������
private:
	// ��������ֱ�ߵĽ���
	cv::Point intersect(const cv::Point aa, const cv::Point bb, const cv::Point cc, const cv::Point dd);
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
	//std::string WChar2Ansi(LPSTR pwszSrc);
	// ��Ϻ���
	//CString diagnose(int op_type, cv::Point &pose);
	// ��ʼ��������
	void initParam();
	// �����ʾ��䣬�Ե�ǰ����������и���
	void remindColor();
	// ԭ�����жϺ���
	bool drawYfc(cv::Point pt);
	// 


// �������������ԵȲ���
public:
		double m_edit;
		CComboBox m_Combo;
		CComboBox m_Combo2;
		CMyEdit m_ctrlHint;
		CMyEdit m_logo;
public:
	void Invalidate(BOOL bErase = 1);
	void Draw(CDC *pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton3();
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
	afx_msg void OnBnClickedButtonOp3();
	afx_msg void OnBnClickedCancel();

	afx_msg void OnBnClickedButtonOp4();
	afx_msg void OnBnClickedButtonOp5();
	afx_msg void OnBnClickedButtonOp6();
	afx_msg void OnBnClickedButtonOp7();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnBnClickedButtonOp8();
	afx_msg void OnBnClickedButton16();
};
