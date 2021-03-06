
// chiropracticDlg.h : 头文件
//

#pragma once
#include"opencv2/opencv.hpp"
#include "afxwin.h"
#include"InitGdiplus.h"

#define DRAW_LINE 0
#define DRAW_RECT 1
#define DRAW_LABEL 2
#define DRAW_MEASURE 3

typedef struct _logLnfo {
	/*CvPoint p1;
	CvPoint p2;*/
	cv::Point p1;
	cv::Point p2;
	cv::Point center;
	int op;  //操作类型
	char text[20];
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


private:
	cv::Mat m_loadImg; //因为加入了缩放功能，没办法，只能再加一个变量保存原始载入的图像(历史遗留问题)
	cv::Mat m_srcImg;  // 裁剪后图像，用于记录，该变量与原始载入图像可能并不一样，请知悉
	cv::Mat m_zoomImg; // 缩放后的图像

	//cv::Mat m_showImg; // 用于显示
	cv::Mat m_maskImg; // 用于记录
	cv::Mat m_maskShowImg; // 用于显示

	cv::Point m_p1, m_p2;  // 图像坐标系,用于画图



	cv::vector<logInfo> m_vecLog;	 // 操作日志，保存的坐标系为m_srcImg坐标系
	cv::vector<logInfo> m_vecDelLog; // 用于重做
	cv::vector<logInfo> m_vecMeasure; // 用于测量
	logInfo m_stuLog;					// 用于记录测量信息

	double m_dScale;	//缩放比例

	REAL m_zoom;  //缩放系数
	CRect m_Rect; //对话框的矩形区域

	REAL m_imgX; //图片左上角X轴偏移量,相对于控件左上角
	REAL m_imgY; //图片左上角Y轴偏移量

	PointF m_PtStart;    //按下鼠标左键，记录当前的m_imgX,m_imgY
	PointF m_mouseDown;  //按下鼠标左键时，鼠标在图片控件中的位置；

// 辅助变量
private:
	bool m_bLButtonDown; //记录是否按下了鼠标左键
	bool m_bDrawLine;
	bool m_bDrawRect;
	bool m_bDrawLabel;
	bool m_bDel;
	bool m_bMeasure;
	bool m_bPutText;

	int m_ctrlWidth;
	int m_ctrlHeight;

	double m_dWidth;
	double m_dHeight;
	double m_dWidthScale;
	double m_dHeightScale;

// 辅助函数
private:
	bool intersect(CvPoint aa, CvPoint bb, CvPoint cc, CvPoint dd);
	double determinant(double v1, double v2, double v3, double v4);
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
};
