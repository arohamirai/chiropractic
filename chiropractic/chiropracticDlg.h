
// chiropracticDlg.h : 头文件
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
	cv::Point p[10];		// p[0~1] 正常直线，p[2~3]测量线
	cv::Point center[5];
	//cv::Point center1;		 // 画直线时所取关键点
	//cv::Point center2;		// 保存圆、标注线文字、诊断结果文字所在位置。
	double length[2];				//测量长度
	char text[3][20];			//文字标注（测量长度、诊断结果等）
	int op;					//操作类型
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


// 通用参数
private:
	bool m_bNeedSave;
	int m_opType;
	bool m_bLButtonDown; //记录是否按下了鼠标左键
	int m_curStep;				// 当前操作步骤

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
	int m_fontTypeOfDiagnose;				// 诊断结果的字体类型
	double m_dFontSizeOfDiagnose;			// 诊断结果的字体大小
	int m_fontThicknessOfDiagnose;			// 诊断结果字体宽度
	CString *m_csRemind;					// 操作提示
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
// 一、髂骨半脱位
//正经变量
private:
	double m_grad_gugu_x;				// 股骨头线斜率
	double m_grad_gugu_y;				// 股骨头线垂直线的斜率
	double m_dLlength_wuminggu;			// 无名骨长度
	double m_dRlength_wuminggu;
	double m_dLength;					// 耻骨联合中线与中心线的距离, 偏中心线左侧为负，偏中心线右侧为正
	double m_dLlength_xiaguanjie;			// 下关节突影长度
	double m_dRlength_xiaguanjie;

	CString m_qiagu_diagnose;			// 髂骨诊断结果
// 辅助变量
private:
	CString m_csQiagu_remind[20];		// 髂骨操作提示

///////////////////////////////////////////////////////////////////////////////////////
//二、骶骨半脱位
private:
	double m_grad_digu_x;				// 骶骨水平线斜率
	double m_grad_digu_y;				// 骶骨水平线垂直线的斜率
	//double m_grad_gugu_x;				// 利用前面定义好的

	double m_dLlength_digu;				// 两根垂线长度
	double m_dRlength_digu;
	double m_dDigu_down;				// 骶骨向下偏位

	CString m_digu_diagnose;			// 骶骨诊断结果
// 辅助变量
private:
	CString m_csDigu_remind[20];		// 骶骨操作提示

///////////////////////////////////////////////////////////
// 腰椎诊断
private:
	double m_grad[2];									// 左右两条直线斜率 [0]--左，[1]--右
	double m_bias[2];									// 左右两条直线偏置 [0]--左，[1]--右
	std::vector<std::vector<cv::Point>> m_vecCpPoint;	// 直线与边界直线的交点
	std::vector<std::vector<double>> m_vecMeasure;		// 截距
	std::vector<std::vector<cv::Point>> m_vecCpPointDel;	// 直线与边界直线的交点
	std::vector<std::vector<double>> m_vecMeasureDel;		// 截距

	std::vector<CString> m_yaozhui_diagnose;			// 腰椎诊断结果
// 辅助变量
private:
	CString m_csaoZhui_remind[20];		// 腰椎操作提示
	CString m_csYaoZhui_remind[20];		// 腰椎操作提示

// 腰骶角诊断
private:
	double m_grad_yaozhuijiao_x;
	CString m_YaoDiJiao_diagnose;			// 诊断结果
	CString m_csYaoDiJiao_remind[20];		// 腰椎操作提示
////////////////////////////////////////////////////////////
// 辅助函数
private:
	// 计算两条直线的交点
	cv::Point intersect(cv::Point aa, cv::Point bb, cv::Point cc, cv::Point dd);
	// 判断两条直线是否相交
	//bool intersect(CvPoint aa, CvPoint bb, CvPoint cc, CvPoint dd);
	 // 用于判断两条直线是否平行（比较斜率是否相等）
	double determinant(double v1, double v2, double v3, double v4);
	// 做线的延长线
	void  lineExt(double grad, cv::Point center, double lenth_lt, double lenth_rb, cv::Point &p_l, cv::Point &p_r);
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
