
// chiropracticDlg.h : 头文件
//

#pragma once
#include"opencv2/opencv.hpp"
#include "afxwin.h"
#include"InitGdiplus.h"
#include "MyEdit.h"


// 画图类型
enum drawTpye {
	DRAW_LINE = 1, DRAW_DIAGNOSE, DRAW_LINE_MEASURE, DRAW_DIGU_SPX, DRAW_DI1, DRAW_LINE_VERTICALLINE, DRAW_DIGU_LINE, DRAW_CIRCLE, DRAW_YAOZHUI_MEASURE,
	DRAW_BASE_LINE, DRAW_XIONGZHUI_MEASURE, DRAW_JINGZHUIZHENGMIAN_MEASURE, DRAW_JINGZHUIZHANGKOU_MEASURE
};
// 操作类型，依次为：截取图片操作；骨盆诊断；腰椎诊断；腰骶角诊断；胸椎诊断；颈椎诊断；寰椎诊断；枕骨诊断
enum opType {DRAW_RECT = 1,DIAG_GP, DIAG_YZ, DIAG_YDJ,DIAG_XZ,DIAG_JZ,DIAG_HZ, DIAG_ZG
};

// 操作信息记录结构体
typedef struct _logLnfo {
	cv::Point p[10];			//	关键点
	cv::Point center[5];		//	各种中心点
	char text[3][20];			//	文字标注（测量长度、诊断结果等）
	int op;						//	操作类型
	int step;					// 是第几步操作
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


// 原发侧判定参数
private:
	int m_yfcMethod;					// 原发侧判断方法
	int m_curYfcStep;					// 原发侧操作第几步
	double m_dGrad_line_yfc;			// 可能需要记录的直线斜率
	CString m_strYfc;					// 原发侧判断结果：R/L/-
	bool m_bHas_draw_yfc;				// 是否完成原发侧诊断
	cv::Point m_point_yfc[4];			// 原发侧画线时需要保存的点

// 通用参数
private:
	bool m_bNeedSave;					// 是否需要保存，只要修改过图像，该值就应该为true
	bool m_bCanCutPic;					// 是否允许截取图片操作，只在还未实际画片时允许该值为true
	int m_opType;						// 画片操作类型：截取图片、骨盆诊断、腰椎诊断、腰椎角诊断......
	int m_curStep;						// 诊断操作下一步
	
	bool m_bLButtonDown;				//记录是否按下了鼠标左键
	int m_ctrlWidth;					// 图像实际宽度(mm)
	int m_ctrlHeight;					// 图像实际长度(mm)
	double m_dwidth_scale;				// 宽度方向比例因子(mm/像素)
	double m_dheight_scale;				// 长度方向比例因子(mm/像素)

	cv::Mat m_loadImg;					//因为加入了缩放功能，没办法，只能再加一个变量保存原始载入的图像(历史遗留问题)
	cv::Mat m_srcImg;					// 裁剪后图像，用于记录，该变量与原始载入图像 m_loadImg 可能并不一样，请知悉
	cv::Mat m_zoomImg;					// 缩放后的图像
	cv::Mat m_maskImg;					// 画线的操作都记录在这幅图像上，最后用OpenCV的掩模功能叠加到m_srcImg图像上，用于记录
	cv::Mat m_maskShowImg;				// 用于实时画线操作结果

	cv::Point m_p1, m_p2;				// 图像坐标系,用于截取图片等需要在同时在OnLButtonDown()和OnLButtonUp()函数间获取的点
	cv::Point m_gPoint[50];				// 诊断操作时需要记录的点
	cv::vector<logInfo> m_vecLog;		// 操作日志，用于撤销
	cv::vector<logInfo> m_vecDelLog;	// 被撤销的操作，用于重做
	cv::vector<logInfo> m_vecLog_yfc;		// 用于原发测撤销与重做
	cv::vector<logInfo> m_vecDelLog_yfc;	// 用于原发测撤销与重做

	// 画图相关参数
	int m_circleRadius;						// 小圆点的半径
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
	int m_font_type_measure;				// 划片时测量的值得字体类型
	double m_dfont_scale_measure;			// 划片时测量的值得字体大小
	int m_font_thick_measure;				// 划片时测量的值得字体宽度
	int m_font_type_diag;					// 诊断结果的字体类型
	double m_dfont_scale_diag;				// 诊断结果的字体大小
	int m_font_thick_diag;					// 诊断结果字体宽度
	CString *m_strHint;						// 操作提示指针，对不同的诊断操作类型，指向对应的操作提示语句数组
	CString m_strYfcHint[6][20];			// 原发测判断提示语句

	// 图像缩放相关变量
	REAL m_zoom;							// 缩放系数
	REAL m_imgX;							// 图片左上角X轴偏移量,相对于控件左上角
	REAL m_imgY;							// 图片左上角Y轴偏移量
	PointF m_PtStart;						// 按下鼠标左键，记录当前的m_imgX,m_imgY
	PointF m_mouseDown;						// 按下鼠标左键时，鼠标在图片控件中的位置；
///////////////////////////////////////////////////////////
	double l_l, l_r;
////////////////////////////////////////////////////////////////////////////////
// 一、骨盆半脱位（髂骨、骶骨）
private:
	CString m_strDiag_qg;				// 髂骨诊断结果
	CString m_strHint_gp[20];			// 髂骨操作提示
	double m_dGrad_gg_x_qg_gp;				// 股骨头线斜率
	double m_dGrad_gg_y_qg_gp;				// 股骨头线垂直线的斜率
	double m_dLength_wmg_l_qg_gp;			// 左无名骨长度
	double m_dLength_wmg_r_qg_gp;			// 右无名骨长度
	double m_dLength_qg_gp;					// 耻骨联合中线与中心线的距离, 偏中心线左侧为负，偏中心线右侧为正
	bool m_bDiag_dg_gp;					// 是否继续诊断骶骨
private:
	CString m_strDiag_dg_gp;				// 骶骨诊断结果
	double m_dGrad_dg_x_dg_gp;				// 骶骨水平线斜率
	double m_dGrad_dg_y_dg_gp;				// 骶骨水平线垂直线的斜率
	double m_dLength_l_dg_gp;				// 左翼垂线长度
	double m_dLength_r_dg_gp;				// 右翼垂线长度
	double m_dLength_xx_dg_gp;				// 骶骨向下偏位长度
	double m_dThres_dg_gp;					// 骶骨向下偏位设定阈值


///////////////////////////////////////////////////////////
// 腰椎诊断
private:
	CString m_strHint_yz[20];											// 腰椎操作提示
	CString m_strDiag_yz[6];											// 腰椎诊断结果
	int m_curDiag_yz;													// 当前正在诊断的腰椎
	int m_curDiag_xie_yz;												// 当前楔形诊断的操作步骤
	double m_dThres_xie_yz;												// 楔形切口判断设定阈值
	CString m_strBend_yz;												// 腰椎侧弯凸侧
	bool m_bLuxs_yz[6];													// 腰椎是否脱位
	bool m_bDraw_yfc_step_yz;											// 是否到了判断原发测的步骤
	int m_total_lux_yz;													// 半脱位腰椎总数
	double m_dGrad_bj_yz[2];											// 左右两条直线斜率 [0]--左，[1]--右
	double m_dBias_bj_yz[2];											// 左右两条直线偏置 [0]--左，[1]--右
	cv::Point m_point_cp_l_yz[6];										// 直线与左边界直线的交点
	cv::Point m_point_cp_r_yz[6];										// 直线与右边界直线的交点，5条腰椎，一条基准线

	
////////////////////////////////////////////////////////////
// 腰骶角诊断
private:
	double m_grad_yaozhuijiao_x;			// 直线斜率
	CString m_YaoDiJiao_diagnose;			// 诊断结果
	CString m_csYaoDiJiao_remind[20];		// 腰骶角操作提示
////////////////////////////////////////////////////////////
// 胸椎诊断
private:
	CString m_strHint_xz[20];											// 胸椎操作提示
	CString m_strDiag_xz[20];											// 胸椎诊断结果
	int m_curDiag_xz;													// 当前正在诊断的胸椎
	int m_curDiag_xie_xz;												// 当前楔形诊断的操作步骤
	
	CString m_strBend_xz;												// 胸椎侧弯凸侧
	//bool m_bLuxs_xz[13];												// 胸椎是否脱位
	int m_total_xz;														// 半脱位胸椎总数
	double m_dGrad_bj_xz[2];											// 左右两条直线斜率 [0]--左，[1]--右
	double m_dBias_bj_xz[2];											// 左右两条直线偏置 [0]--左，[1]--右
	cv::Point m_point_cp_l_xz[20];										// 直线与左边界直线的交点
	cv::Point m_point_cp_r_xz[20];										// 直线与右边界直线的交点，12条胸椎，一条基准线

	CString m_strYfc_xz[20];											// 原发测判定（下缀1~12~L1腰椎，0弃用，下同）
	CString m_strXie_xz[20];											// 楔形开口朝向
	bool m_bHas_more_xz_xz;												// 是否有超过12条的胸椎
	bool m_bDraw_L1_xz;													// 是否画L1腰椎
	double m_bHas_draw_dd_line_xz;										// 是否已经做出骶骨水平线
	double m_dGrad_dg_xz;												// 骶骨水平线的斜率
	double m_dThres_xie_xz;												// 楔形切口判断阈值
	void diagXz();														//胸椎诊断

///////////////////////////////////////////////////////////////////
// 六、 颈椎
private:
	CString m_strHint_jz[20];											// 颈椎操作提示
	CString m_strDiag_jz[13];											// 颈椎诊断结果
	int m_curDiag_cw_jz;												// 侧位片上当前正在诊断的颈椎
	int m_curDiag_zw_jz;												// 正位片上当前正在诊断的颈椎
	int m_curDiag_step_cw_jz;											// 侧位片上当前诊断的操作步骤
	int m_curDiag_step_zw_jz;											// 正位片上当前诊断的操作步骤
	double m_dThres_xie_zw_jz;											// 楔形切口判断阈值
	CString m_strBend_jz;												// 颈椎侧弯凸侧
	int m_total_lux_jz;													// 半脱位颈椎总数
	double m_dGrad_cwbj_jz[2];											// 侧位片上左右两条直线斜率 [0]--左，[1]--右
	double m_dBias_cwbj_jz[2];											// 侧位片上左右两条直线偏置 [0]--左，[1]--右
	double m_dGrad_zwbj_jz[2];											// 正位片上左右两条直线斜率 [0]--左，[1]--右
	double m_dBias_zwbj_jz[2];											// 正位片上左右两条直线偏置 [0]--左，[1]--右
	cv::Point m_point_cp_cw_l_jz[13];									// 侧位片上直线与左边界直线的交点
	cv::Point m_point_cp_cw_r_jz[13];									// 侧位片上直线与右边界直线的交点
	cv::Point m_point_cp_zw_l_jz[13];									// 正位片上直线与左边界直线的交点
	cv::Point m_point_cp_zw_r_jz[13];									// 正位片上直线与右边界直线的交点
	CString m_strYfc_jz[8];												// 颈椎原发测
	CString m_strXie_zw_jz[10];
	void diagJz();														// 颈椎诊断

// 七、 寰椎
private:
	CString m_strHint_hz[20];											// 寰椎操作提示
	CString m_strDiag_hz;												// 寰椎诊断结果
	cv::Mat m_jzzcImg_hz;												// 颈椎正侧位片
	cv::Mat m_jzzkImg_hz;												// 颈椎张口位片
	bool m_bHas_changed_img_hz;											// 是否载入了新图像
	bool m_bHas_draw_step8_hz;											// 是否需要做step 8 步，还是说要载入图像
	double m_dGrad_czt_hz;												// 齿状突
	double m_dBias_czt_hz;
	double m_dGrad_bj_hz[2];											// 左右两条直线斜率 [0]--左，[1]--右
	double m_dBias_bj_hz[2];											// 左右两条直线偏置 [0]--左，[1]--右
	cv::Point m_point_cp_l_hz[5];										// 直线与左边界直线的交点
	cv::Point m_point_cp_r_hz[5];										// 直线与右边界直线的交点，
	cv::Point m_point_jzzk_bj_hz[4];									// 颈椎张口位片的边界直线
	void diagHz();

// 八、 枕骨
	cv::Mat m_jzzcImg_zg;												// 颈椎正侧位片
	cv::Mat m_jzzkImg_zg;												// 颈椎张口位片
	bool m_bHas_changed_img_zg;											// 是否载入了新图像
	bool m_bHas_draw_step12_zg;											// 是否需要做step 8 步，还是说要载入图像
	double m_dThres_H_zg;												// 
	CString m_strHint_zg[20];											// 枕骨操作提示
	CString m_strDiag_zg;												// 枕骨诊断结果
	double m_dGrad_czt_zg;												// 齿状突
	double m_dBias_czt_zg;
	double m_dGrad_bj_zg[2];											// 左右两条直线斜率 [0]--左，[1]--右
	double m_dBias_bj_zg[2];											// 左右两条直线偏置 [0]--左，[1]--右
	cv::Point m_point_cp_l_zg[10];										// 直线与左边界直线的交点
	cv::Point m_point_cp_r_zg[10];										// 直线与右边界直线的交点，
	cv::Point m_point_jzzk_bj_zg[4];									// 颈椎张口位片的边界直线点

	void diagZg();

// 辅助函数
private:
	// 计算两条直线的交点
	cv::Point intersect(const cv::Point aa, const cv::Point bb, const cv::Point cc, const cv::Point dd);
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
	//std::string WChar2Ansi(LPSTR pwszSrc);
	// 诊断函数
	//CString diagnose(int op_type, cv::Point &pose);
	// 初始化各变量
	void initParam();
	// 针对提示语句，对当前步骤的语句进行高亮
	void remindColor();
	// 原发侧判断函数
	bool drawYfc(cv::Point pt);
	// 


// 界面美化，调试等参数
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
