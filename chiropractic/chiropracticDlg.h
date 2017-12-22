
// chiropracticDlg.h : 头文件
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
	double length[2];			//测量长度
	char text[3][20];			//文字标注（测量长度、诊断结果等）
	int op;						//操作类型
	int step;
}logInfo;


// CchiropracticDlg 对话框
class CchiropracticDlg : public CDialogEx
{
// 构造
public:
	CchiropracticDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHIROPRACTIC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();


// 旋转侧判定参数
private:
	int m_rotateMethod;
	int m_curRotateStep;
	double m_dGrad_line_rotate;
	CString m_strYfc;		// R/L/-
	bool m_bHas_draw_yfc;
	cv::Point m_point_rotate[4];

// 通用参数
private:
	bool m_bNeedSave;
	bool m_bCanCutPic;
	bool m_bDraw_rotate;
	int m_opType;
	int m_curStep;				// 当前操作步骤
	

	bool m_bLButtonDown; //记录是否按下了鼠标左键
	int m_ctrlWidth;	// 图像实际长宽(mm)
	int m_ctrlHeight;
	double m_dWidthScale;	// 比例因子(mm/像素)
	double m_dHeightScale;

	cv::Mat m_loadImg; //因为加入了缩放功能，没办法，只能再加一个变量保存原始载入的图像(历史遗留问题)
	cv::Mat m_srcImg;  // 裁剪后图像，用于记录，该变量与原始载入图像可能并不一样，请知悉
	cv::Mat m_zoomImg; // 缩放后的图像
	cv::Mat m_maskImg; // 用于记录
	cv::Mat m_maskShowImg; // 用于显示

	cv::Point m_p1, m_p2;  // 图像坐标系,用于画图
	cv::Point m_gp[30];		// 操作时会用到的点
	cv::vector<logInfo> m_vecLog;	 // 操作日志
	cv::vector<logInfo> m_vecDelLog; // 用于重做

	// 画图相关参数
	int m_circleRadius;
	int m_lineWidth;						// 线的宽度
	cv::Scalar m_maskColor;					// 蒙版颜色
	cv::Scalar m_lineColor;					// 线的颜色
	cv::Scalar m_circleColor;				// 小圆点的颜色
	cv::Scalar m_infoColor;					// CT片信息的文字颜色;
	cv::Scalar m_diagnoseColor;				// 诊断结果字体颜色
	cv::Scalar m_measureColor;				// 划片时测量的值的颜色
	int m_fontTypeOfInfo;					// CT片信息字体类型
	double m_dFontSizeOfInfo;				// CT片信息字体大小
	int m_fontThicknessOfInfo;				// CT片信息字体宽度
	int m_fontTypeOfMeasure;				// 划片时测量的值得字体类型
	double m_dFontSizeOfMeasure;			// 划片时测量的值得字体大小
	int m_fontThicknessOfMeasure;			// 划片时测量的值得字体宽度
	int m_font_type_diag;				// 诊断结果的字体类型
	double m_font_scale_diag;			// 诊断结果的字体大小
	int m_font_thick_diag;			// 诊断结果字体宽度
	CString *m_strHint;					// 操作提示
// 辅助变量
	REAL m_zoom;  //缩放系数
	//CRect m_Rect; //对话框的矩形区域
	REAL m_imgX; //图片左上角X轴偏移量,相对于控件左上角
	REAL m_imgY; //图片左上角Y轴偏移量
	PointF m_PtStart;    //按下鼠标左键，记录当前的m_imgX,m_imgY
	PointF m_mouseDown;  //按下鼠标左键时，鼠标在图片控件中的位置；
///////////////////////////////////////////////////////////
// DRAW_MEASURE
	int m_recordFirstPoint; // 是否记录了第一个点

////////////////////////////////////////////////////////////////////////////////
// 零、手动放置测量结果
	CString m_strText;
	bool m_bPutText;
// 一、髂骨半脱位
//正经变量
private:
	CString m_strDiag_qg;			// 髂骨诊断结果
	CString m_strHint_qg[20];		// 髂骨操作提示
	double m_dGrad_gg_x_qg;				// 股骨头线斜率
	double m_dGrad_gg_y_qg;				// 股骨头线垂直线的斜率
	double m_dLength_wmg_l_qg;			// 无名骨长度
	double m_dLength_wmg_r_qg;
	double m_dLength;					// 耻骨联合中线与中心线的距离, 偏中心线左侧为负，偏中心线右侧为正
	//double m_dLlength_xiaguanjie;			// 下关节突影长度
	//double m_dRlength_xiaguanjie;
	bool m_bDiag_dg_qg;					// 是否继续诊断骶骨

///////////////////////////////////////////////////////////////////////////////////////
//二、骶骨半脱位
private:
	CString m_strDiag_dg;				// 骶骨诊断结果
	CString m_strHint_dg[20];			// 骶骨操作提示
	double m_dGrad_dg_x_dg;				// 骶骨水平线斜率
	double m_dGrad_dg_y_dg;				// 骶骨水平线垂直线的斜率
	//double m_grad_gugu_x;				// 利用前面定义好的
	double m_dLength_l_dg;				// 两根垂线长度
	double m_dLength_r_dg;
	double m_dLength_xx_dg;			// 骶骨向下偏位
	double m_dThres_dg;				// 骶骨向下偏位阈值

	

///////////////////////////////////////////////////////////
// 腰椎诊断
private:
	CString m_strHint_yz[20];											// 腰椎操作提示
	CString m_strDiag_yz[6];											// 腰椎诊断结果
	int m_curDiag_yz;													// 当前正在诊断的腰椎
	int m_curDiag_xie_yz;												// 当前楔形诊断的操作步骤
	double m_dThres_xie_yz;												// 楔形切口判断阈值
	CString m_strBend_yz;												// 腰椎侧弯凸侧
	bool m_bLuxs_yz[6];													// 腰椎是否脱位
	bool m_bDraw_yfc_step;												// 是否到了判断原发测的步骤
	int m_total_lux_yz;													// 半脱位腰椎总数
	double m_dGrad_bj_yz[2];											// 左右两条直线斜率 [0]--左，[1]--右
	double m_dBias_bj_yz[2];											// 左右两条直线偏置 [0]--左，[1]--右
	cv::Point m_point_cp_l_yz[6];										// 直线与左边界直线的交点
	cv::Point m_point_cp_r_yz[6];										// 直线与右边界直线的交点，5条腰椎，一条基准线
	//
// 辅助变量
private:
	
////////////////////////////////////////////////////////////
// 腰骶角诊断
private:
	double m_grad_yaozhuijiao_x;
	CString m_YaoDiJiao_diagnose;			// 诊断结果
	CString m_csYaoDiJiao_remind[20];		// 腰骶角操作提示
////////////////////////////////////////////////////////////
// 胸椎诊断
private:
	CString m_strHint_xz[20];											// 胸椎操作提示
	CString m_strDiag_xz[13];											// 胸椎诊断结果
	int m_curDiag_xz;													// 当前正在诊断的胸椎
	int m_curDiag_xie_xz;												// 当前楔形诊断的操作步骤
	double m_dThres_xie_xz;												// 楔形切口判断阈值
	CString m_strBend_xz;												// 胸椎侧弯凸侧
	//bool m_bLuxs_xz[13];												// 胸椎是否脱位
	int m_total_lux_xz;													// 半脱位胸椎总数
	double m_dGrad_bj_xz[2];											// 左右两条直线斜率 [0]--左，[1]--右
	double m_dBias_bj_xz[2];											// 左右两条直线偏置 [0]--左，[1]--右
	cv::Point m_point_cp_l_xz[13];										// 直线与左边界直线的交点
	cv::Point m_point_cp_r_xz[13];										// 直线与右边界直线的交点，12条胸椎，一条基准线

///////////////////////////////////////////////////////////////////
// 六、 颈椎
private:
	CString m_strHint_jz[20];											// 颈椎操作提示
	CString m_strDiag_jz[13];											// 颈椎诊断结果
	int m_curDiag_jz;													// 当前正在诊断的颈椎
	int m_curDiag_step_jz;												// 当前诊断的操作步骤
	double m_dThres_xie_jz;												// 楔形切口判断阈值
	CString m_strBend_jz;												// 颈椎侧弯凸侧
	//bool m_bLuxs_jz[13];												// 颈椎是否脱位
	int m_total_lux_jz;													// 半脱位颈椎总数
	double m_dGrad_bj_jz[2];											// 左右两条直线斜率 [0]--左，[1]--右
	double m_dBias_bj_jz[2];											// 左右两条直线偏置 [0]--左，[1]--右
	cv::Point m_point_cp_l_jz[13];										// 直线与左边界直线的交点
	cv::Point m_point_cp_r_jz[13];										// 直线与右边界直线的交点

// 寰椎
private:
	cv::Mat m_jzzcImg;													// 颈椎正侧位片
	cv::Mat m_jzzkImg;													// 颈椎张口位片
	bool m_bHas_changed_img;											// 是否载入了新图像
	bool m_bHas_draw_step8;												// 是否需要做step 8 步，还是说要载入图像
	double m_dThres_H_hz;												// 
	CString m_strHint_hz[20];											// 寰椎操作提示
	CString m_strDiag_hz[13];											// 寰椎诊断结果
	double m_dGrad_czt_hz;
	double m_dBias_czt_hz;
	double m_dGrad_bj_hz[2];											// 左右两条直线斜率 [0]--左，[1]--右
	double m_dBias_bj_hz[2];											// 左右两条直线偏置 [0]--左，[1]--右
	cv::Point m_point_cp_l_hz[5];										// 直线与左边界直线的交点
	cv::Point m_point_cp_r_hz[5];										// 直线与右边界直线的交点，
	cv::Point m_point_jzzk_bj_lt;												// 颈椎张口位片的边界直线点
	cv::Point m_point_jzzk_bj_lb;
	cv::Point m_point_jzzk_bj_rt;
	cv::Point m_point_jzzk_bj_rb;

// 辅助函数
private:
	// 计算两条直线的交点
	cv::Point intersect(cv::Point aa, cv::Point bb, cv::Point cc, cv::Point dd);
	// 判断两条直线是否相交
	//bool intersect(CvPoint aa, CvPoint bb, CvPoint cc, CvPoint dd);
	 // 用于判断两条直线是否平行（比较斜率是否相等）
	double determinant(double v1, double v2, double v3, double v4);
	// 做线的延长线
	void  lineExt(double grad, cv::Point center, double lenth_lt, double lenth_rb, cv::Point &p_lt, cv::Point &p_rb);
	// 求点与直线的垂直点
	cv::Point lineCrossDot(double grad, cv::Point p1, cv::Point p2);
	// 读取*.dcm的CT片到OpenCV支持格式
	bool dcm2Mat(const char* const fileName, cv::Mat &mat);
	// 字符串转换
	std::string WChar2Ansi(LPSTR pwszSrc);
	// 诊断函数
	CString diagnose(int op_type, cv::Point &pose);
	// 初始化各变量
	void initParam();
	// 针对提示语句，对当前步骤的语句进行高亮
	void remindColor();
	// 按钮控件初始化
	void initCtrlBtn(BOOL selBtn0, BOOL selBtn1);
	// 按钮控件外观改变
	void changeCtrlBtn(INT selBtn = NULL, INT selBtn1 = NULL);
	// 旋转判断函数
	bool drawYfc(cv::Point pt);
	// 


// 界面美化，调试等参数
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
