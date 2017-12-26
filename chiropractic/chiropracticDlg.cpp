
// chiropracticDlg.cpp : 实现文件
//
/*
窗口坐标：
屏幕坐标：
控件坐标：
*/
#include "stdafx.h"
#include "chiropractic.h"
#include "chiropracticDlg.h"
#include "afxdialogex.h"

#include"Parameter.h"
#include"CvvImage.h"
#include"InputName.h"
#include"math.h"
#include "InputText.h"
#include"InputYZ.h"
#include"RotateSee.h"
#include "Bend.h"

#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */
#include "dcmtk/ofstd/ofstdinc.h"

#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmdata/cmdlnarg.h"
#include "dcmtk/ofstd/ofconapp.h"
#include "dcmtk/dcmdata/dcuid.h"       /* for dcmtk version name */
#include "dcmtk/dcmjpeg/djdecode.h"    /* for dcmjpeg decoders */
#include "dcmtk/dcmjpeg/dipijpeg.h"    /* for dcmimage JPEG plugin */

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib,"iphlpapi.lib")
#pragma comment(lib, "netapi32.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define WIDTHBYTES(bits) ((DWORD)(((bits)+31) & (~31)) / 8)

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CchiropracticDlg 对话框



CchiropracticDlg::CchiropracticDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CHIROPRACTIC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CchiropracticDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_COMBO1, m_Combo);
	DDX_Control(pDX, IDC_COMBO2, m_Combo2);
	DDX_Control(pDX, IDC_REMIND1, m_ctrlHint);
	DDX_Control(pDX, IDC_STATIC_LOGO, m_logo);
	DDX_Control(pDX, IDC_STATIC_GALLERY, m_gallery);
	DDX_Control(pDX, IDC_BUTTON2, m_button2);
	DDX_Control(pDX, IDC_BUTTON3, m_button3);
	DDX_Control(pDX, IDC_BUTTON6, m_button6);
	DDX_Control(pDX, IDC_BUTTON8, m_button8);
	DDX_Control(pDX, IDC_BUTTON9, m_button9);
	DDX_Control(pDX, IDC_BUTTON15, m_button15);
	DDX_Control(pDX, IDC_BUTTON14, m_button14);
	DDX_Control(pDX, IDC_BUTTON10, m_button10);
	DDX_Control(pDX, IDC_BUTTON11, m_button11);

	DDX_Control(pDX, IDC_BUTTON_OP1, m_button_op1);
	DDX_Control(pDX, IDC_BUTTON_OP2, m_button_op2);
	DDX_Control(pDX, IDC_BUTTON_OP3, m_button_op3);
	DDX_Control(pDX, IDC_BUTTON_OP4, m_button_op4);
	DDX_Control(pDX, IDC_BUTTON_OP5, m_button_op5);
	DDX_Control(pDX, IDC_BUTTON_OP6, m_button_op6);
	DDX_Control(pDX, IDC_BUTTON_OP7, m_button_op7);
	//DDX_Control(pDX, IDC_BUTTON_OP8, m_button_op);

}

BEGIN_MESSAGE_MAP(CchiropracticDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CchiropracticDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CchiropracticDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CchiropracticDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CchiropracticDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CchiropracticDlg::OnBnClickedButton4)
	//ON_BN_CLICKED(IDC_BUTTON5, &CchiropracticDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CchiropracticDlg::OnBnClickedButton6)
	//ON_BN_CLICKED(IDC_BUTTON7, &CchiropracticDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CchiropracticDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CchiropracticDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CchiropracticDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CchiropracticDlg::OnBnClickedButton11)
	//ON_BN_CLICKED(IDC_BUTTON12, &CchiropracticDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON_OP1, &CchiropracticDlg::OnBnClickedButtonOp1)
	ON_BN_CLICKED(IDC_BUTTON_OP2, &CchiropracticDlg::OnBnClickedButtonOp2)
	ON_BN_CLICKED(IDC_BUTTON_OP3, &CchiropracticDlg::OnBnClickedButtonOp3)
	ON_BN_CLICKED(IDC_BUTTON13, &CchiropracticDlg::OnBnClickedButton13)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEWHEEL()
	ON_BN_CLICKED(IDCANCEL, &CchiropracticDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON15, &CchiropracticDlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON_OP4, &CchiropracticDlg::OnBnClickedButtonOp4)
	ON_BN_CLICKED(IDC_BUTTON14, &CchiropracticDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON_OP5, &CchiropracticDlg::OnBnClickedButtonOp5)
	ON_BN_CLICKED(IDC_BUTTON_OP6, &CchiropracticDlg::OnBnClickedButtonOp6)
	ON_BN_CLICKED(IDC_BUTTON_OP7, &CchiropracticDlg::OnBnClickedButtonOp7)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CchiropracticDlg::OnCbnSelchangeCombo2)
END_MESSAGE_MAP()
// CchiropracticDlg 消息处理程序
BOOL CchiropracticDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	// TODO: 在此添加额外的初始化代码
	// 参数初始化
	initParam();
	// 尺寸
	m_Combo.AddString(_T("14x17"));
	m_Combo.AddString(_T("7x8.5"));
	m_Combo.AddString(_T("手动输入尺寸..."));
	// 默认14x17尺寸
	int nIndex = m_Combo.FindStringExact(0, _T("14x17"));
	if (nIndex != CB_ERR)
		m_Combo.SetCurSel(nIndex);
	// 未载入图像前，禁止选择
	GetDlgItem(IDC_COMBO1)->EnableWindow(FALSE);
	// 旋转侧判定方法
	m_Combo2.AddString(_T("请选择"));
	m_Combo2.AddString(_T("手动输入"));
	m_Combo2.AddString(_T("测量椎体棘突中央到椎体边缘的距离"));
	m_Combo2.AddString(_T("测量椎体椎弓根影横经"));
	m_Combo2.AddString(_T("测量椎体下关节突影"));
	nIndex = m_Combo2.FindStringExact(0, _T("请选择"));
	if (nIndex != CB_ERR)
		m_Combo2.SetCurSel(nIndex);
	// 初始时，禁止选择
	//GetDlgItem(IDC_COMBO2)->EnableWindow(FALSE);
	// 更新下尺度变量
	//OnCbnSelchangeCombo1();
	// logo 文字
	m_logo.SetBkColor(RGB(0x23,0xce,0xc0));
	m_logo.SetForeColor(RGB(0xff, 0xff, 0xff));
	//GetDlgItem(IDC_STATIC_LOGO)->SetWindowPos(NULL, 0, 0, 100, 32, SWP_NOMOVE);
	m_logo.SetTextFont(200, _T("黑体"));
	m_logo.SetWindowText(_T(" 天化之美划片科技"));
	m_ctrlHint.SetBkColor(RGB(0xe1, 0xee, 0xe3));
	m_ctrlHint.SetForeColor(RGB(0x41, 0x8c, 0x4d));
	m_ctrlHint.SetTextFont(150, _T("宋体"));
	m_ctrlHint.SetWindowText(_T("请先加载图像！"));
	// 设置图片控件尺寸
	m_ctrlWidth = 1000;
	m_ctrlHeight = 750;
	GetDlgItem(IDC_PICTURE)->SetWindowPos(NULL, 0, 0, m_ctrlWidth, m_ctrlHeight, SWP_NOMOVE); //固定大小的窗口
	GetDlgItem(IDC_REMIND1)->SetWindowPos(NULL, 0, 0, m_ctrlWidth,32, SWP_NOMOVE);
	initCtrlBtn(TRUE,TRUE);
	//Invalidate();
	//OnPaint();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
void CchiropracticDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}
// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
void CchiropracticDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);

		Invalidate();
	}
	else
	{
		CPaintDC dc(this); // 用于绘制的设备上下文
		CRect rect;
		GetClientRect(&rect);
		dc.FillSolidRect(rect, RGB(0xff, 0xff, 0xff));   //设置为绿色背景
		m_gallery.SetBkColor(RGB(0xdf, 0xee, 0xed));
		CDialogEx::OnPaint();
		GetDlgItem(IDC_PICTURE)->ShowWindow(SW_SHOW);

	}	
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CchiropracticDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
// 更换图片
void CchiropracticDlg::OnBnClickedButton2()
{
	changeCtrlBtn(IDC_BUTTON2);
	// TODO: 在此添加控件通知处理程序代码
	if (m_bNeedSave)
	{
		INT_PTR ret = MessageBox(_T("当前诊断尚未保存，是否保存？"),_T("提示！"),MB_YESNO);
		if (ret == IDOK)
		{
			OnBnClickedButton11();		// 保存
			m_bNeedSave = false;
			return;
		}		
	}
	CFileDialog dlg(
		TRUE, NULL,//_T("*.bmp|*.jpeg"),
		NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		NULL,//_T("image files (*.bmp; *.jpg;*.png) |*.bmp; *.jpg;*.jpeg;*.jge;*.png; ||"),
		NULL
	);                                        // 选项图片的约定
	dlg.m_ofn.lpstrTitle = _T("Open Image");    // 打开文件对话框的标题名
	if (dlg.DoModal() != IDOK)                    // 判断是否获得图片
		return;

	CString mPath = dlg.GetPathName();            // 获取图片路径
	
	/*int len = WideCharToMultiByte(CP_ACP, 0, mPath, -1, NULL, 0, NULL, NULL);
	char *ptxtTemp = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, mPath, -1, ptxtTemp, len, NULL, NULL);*/
	char *ptxtTemp = mPath.GetBuffer(mPath.GetLength()); //文件完整路径
	CString fileExt = dlg.GetFileExt();// 文件后缀名
	if (fileExt == _T("png") || fileExt == _T("jpg") || fileExt == _T("bmp"))
	{
		m_loadImg = imread(ptxtTemp, CV_LOAD_IMAGE_UNCHANGED);    // 读取图片
	}
	else
	{
		bool ret = dcm2Mat(ptxtTemp, m_loadImg);
		if (!ret)
		{
			MessageBox(_T("载入图像失败，请检查文件的合法性！"));
			return;
		}
	}
	//delete[] ptxtTemp;

	if (m_loadImg.empty())                                    // 判断是否成功载入图片
		return;
	m_srcImg = m_loadImg.clone(); // 为什么这么用，看头文件
	m_zoomImg = m_loadImg.clone();
	
	m_maskImg.create(m_srcImg.size(), CV_8UC1); // 掩膜图像
	m_maskShowImg.create(m_srcImg.size(), CV_8UC1); // 内部temp掩膜图像
	m_maskImg.setTo(0);
	m_maskShowImg.setTo(0);
	Invalidate();

	// 默认载入17*14图像
	double w, h; //实际尺寸(mm或英寸)
	w = 17 * 25.4;
	h = 14 * 25.4;
	m_dwidth_scale = w / m_srcImg.cols;
	m_dheight_scale = h / m_srcImg.rows;
	// 允许调整尺寸
	GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);
	m_ctrlHint.SetWindowText(_T("请选择操作类型！"));

}
/*
* 求两直线交点
* aa,bb,cc,dd分别为两直线上的两个点
* 算法原理：http://dec3.jlu.edu.cn/webcourse/t000096/graphics/chapter5/01_2.html
*/
cv::Point CchiropracticDlg::intersect(cv::Point aa, cv::Point bb, cv::Point cc, cv::Point dd)
{
	// 判断两条直线是否平行， delta=0，表示两线段重合或平行
	double delta = determinant(bb.x - aa.x, cc.x - dd.x, bb.y - aa.y, cc.y - dd.y);
	
	if (delta <= (1e-6) && delta >= -(1e-6))   
	{
		return cv::Point(0,0);
	}
	// 以下用于线段，非直线
	//double namenda = determinant(cc.x - aa.x, cc.x - dd.x, cc.y - aa.y, cc.y - dd.y) / delta;
	//if (namenda>1 || namenda<0)
	//{
	//	return cv::Point(0, 0);
	//}
	//double miu = determinant(bb.x - aa.x, cc.x - aa.x, bb.y - aa.y, cc.y - aa.y) / delta;
	//if (miu>1 || miu<0)
	//{
	//	return cv::Point(0, 0);
	//}
	//计算直线斜率和偏置
	double k0, k1, b0, b1;
	k0 = (aa.y - bb.y) / (aa.x - bb.x + 10e-8);
	b0 = ((aa.y + bb.y) - k0 * (aa.x + bb.x)) / 2;
	k1 = (cc.y - dd.y) / (cc.x - dd.x + 10e-8);
	b1 = ((cc.y + dd.y) - k1 * (cc.x + dd.x)) / 2;

	double x, y;
	x = -(b1 - b0) / (k1 - k0);
	y = (-(b1 - b0)*(k1 + k0) / (k1 - k0) + b1 + b0) / 2;
	return cv::Point(x, y);
}
double CchiropracticDlg::determinant(double v1, double v2, double v3, double v4)
{
	return (v1*v4 - v2*v3);
}
// 选取
void CchiropracticDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_srcImg.empty())
	{
		MessageBox(_T("请先载入图像！"));
		return;
	}	
	OnRButtonDown(NULL, NULL);
	m_opType = DRAW_RECT;
	changeCtrlBtn(IDC_BUTTON3);
	return;
}
// 画线
void CchiropracticDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_srcImg.empty())
	{
		MessageBox(_T("请先载入图像！"));
		return;
	}
	OnRButtonDown(NULL, NULL);
	//m_bDrawLine = true;
	//remindColor();
	return;
}
// 清屏
void CchiropracticDlg::OnBnClickedButton10()
{
	//// TODO: 在此添加控件通知处理程序代码
	//OnRButtonDown(NULL, NULL);
	changeCtrlBtn(IDC_BUTTON10);
	m_maskImg.setTo(0);
	m_maskShowImg.setTo(0);
	cv::vector<logInfo>().swap(m_vecLog);
	cv::vector<logInfo>().swap(m_vecDelLog);
	m_curStep = 0;
	remindColor();
	Invalidate();
}
// 右键取消
void CchiropracticDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_opType = -1;
	CDialogEx::OnRButtonDown(nFlags, point);
}
// 更换图片
void CchiropracticDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	OnRButtonDown(NULL, NULL);
	if (m_srcImg.empty())
	{
		MessageBox(_T("尚未载入图片,请载入！"));
		return;
	}
		
	CParameter dlg;
	INT_PTR ret = dlg.DoModal();
	if (ret != IDOK)
		return;
	int w = dlg.m_dWidth;
	int h = dlg.m_dHeight;

	m_dwidth_scale = w / m_srcImg.cols;
	m_dheight_scale = h / m_srcImg.rows;
	return;
}
void CchiropracticDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	m_imgX = 0;
	m_imgY = 0;
	m_zoom = 1;
	changeCtrlBtn(IDC_BUTTON6);
	Invalidate();
}
void CchiropracticDlg::OnLButtonDown(UINT nFlags, CPoint point)//这些坐标总是相对于窗口的左上角
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bLButtonDown = true;
	CRect rect;
	GetDlgItem(IDC_PICTURE)->GetWindowRect(rect);		// 得到的是控件相对于左上角的位置
	ScreenToClient(&rect);								// 得到的是控件相对于程序窗口左上角的位置

	// 不在控件中，返回
	if (!PtInRect(&rect, point))
		return;
	// 不在图片中，则返回
	cv::Point pt;
	pt.x = point.x - rect.left; // 求相对于控件的坐标
	pt.y = point.y - rect.top;
	pt.x = pt.x / m_zoom - m_imgX;	// 求相对于图像的坐标
	pt.y = pt.y / m_zoom - m_imgY;
	if (pt.x < 0 || pt.y < 0 || pt.x > m_srcImg.cols || pt.y > m_srcImg.rows)
		return;

	// 截图模式，记录下初始点
	if (m_opType == DRAW_RECT)
	{
		m_p1 = pt;
		//m_p1.x = point.x - rect.left;
		//m_p1.y = point.y - rect.top;
		//m_p1.x = m_p1.x / m_zoom - m_imgX;
		//m_p1.y = m_p1.y / m_zoom - m_imgY;
	}
	// 手动测量模式
	if (m_opType == DRAW_MEASURE)
	{
		/*++m_recordFirstPoint;
		m_p1 = pt;*/
	}

	if (nFlags & MK_LBUTTON && (m_opType == -1))
	{
			m_mouseDown.X = point.x;
			m_mouseDown.Y = point.y;
			m_PtStart.X = m_imgX;
			m_PtStart.Y = m_imgY;

			m_p1 = pt;
			//m_p1.x = point.x - rect.left;
			//m_p1.y = point.y - rect.top;
			//m_p1.x = m_p1.x / m_zoom - m_imgX;
			//m_p1.y = m_p1.y / m_zoom - m_imgY;
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}
void CchiropracticDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rect;
	GetDlgItem(IDC_PICTURE)->GetWindowRect(rect);		// 得到的是控件相对于左上角的位置
	ScreenToClient(&rect);								// 得到的是控件相对于程序窗口左上角的位置

														// 不在控件中，返回
	if (!PtInRect(&rect, point))
		return;
	// 不在图片中，则返回
	cv::Point pt;
	pt.x = point.x - rect.left; // 求相对于控件的坐标
	pt.y = point.y - rect.top;
	pt.x = pt.x / m_zoom - m_imgX;	// 求相对于图像的坐标
	pt.y = pt.y / m_zoom - m_imgY;
	if (pt.x < 0 || pt.y < 0 || pt.x > m_srcImg.cols || pt.y > m_srcImg.rows)
		return;

	m_maskImg.copyTo(m_maskShowImg);// 将已完成的步骤载入
	if (m_bPutText)
	{
		cv::putText(m_maskShowImg, m_strText.GetBuffer(), pt, m_font_type_measure, m_dfont_scale_measure, m_maskColor, m_font_thick_measure);
		Invalidate();
		//CDialogEx::OnMouseMove(nFlags, point);
		return;  // 如果是放置诊断结果，就不要再往下做了
	}
	if ((m_opType == DRAW_RECT) && m_bLButtonDown)		//区域选择
	{
		int r = 1;
		cv::rectangle(m_maskShowImg, m_p1, pt, cv::Scalar(255), r);
		Invalidate();
	}
	else if (m_opType == DRAW_MEASURE)
	{
		if (m_recordFirstPoint == 0) // 第一点都没记录
		{
			cv::circle(m_maskShowImg, pt, m_circleRadius, m_maskColor, -1);
		}
		else
		{
			// 第一点已经记录时，m_recordFirstPoint == 1
			m_p2 = pt;
			//画直线
			cv::circle(m_maskShowImg, m_p1, m_circleRadius, m_maskColor, -1);
			cv::circle(m_maskShowImg, m_p2, m_circleRadius, m_maskColor, -1);
			cv::line(m_maskShowImg, m_p1, m_p2, m_lineColor, m_lineWidth);
			double w = m_dwidth_scale * std::sqrt((m_p2.x - m_p1.x)*(m_p2.x - m_p1.x));
			double h = m_dheight_scale * std::sqrt((m_p2.y - m_p1.y)*(m_p2.y - m_p1.y));
			double length = std::sqrt(w*w + h*h);
			char text[20] = { 0 };
			sprintf_s(text, "%.1fmm", length);
			// 计算放置位置
			cv::Point center = cv::Point((m_p2.x + m_p1.x) / 2, (m_p2.y + m_p1.y) / 2);
			int baseline = 0;
			cv::Size sz_wh = cv::getTextSize(text, m_font_type_measure, m_dfont_scale_measure, m_font_thick_measure, &baseline);
			cv::Point pose = cv::Point(center.x - sz_wh.width / 2, center.y);
			// 放置结果
			cv::putText(m_maskShowImg, text, pose, m_font_type_measure, m_dfont_scale_measure, m_maskColor, m_font_thick_measure);
		}
	}
	else if (m_opType == DIAG_QG)			// 髂骨诊断
	{
		cv::circle(m_maskShowImg, pt, 3, m_maskColor, -1);
		if (m_curStep == 1 )
		{
			cv::line(m_maskShowImg, m_gp[0], pt, m_maskColor, m_lineWidth);
		}
	}	
	else if (m_opType == DIAG_DG )		// 骶骨诊断
	{
		cv::circle(m_maskShowImg, pt, 3, m_maskColor, -1);
		if (m_curStep == 1 || m_curStep == 4)
		{
			cv::line(m_maskShowImg, m_gp[m_curStep-1], pt, m_maskColor, m_lineWidth);
		}
	}
	// 无操作，移动模式
	else if (nFlags && MK_LBUTTON  && (m_opType == -1))
	{
		REAL deltaX = point.x - m_mouseDown.X; //x轴方向偏移
		REAL deltaY = point.y - m_mouseDown.Y; //y轴方向偏移

		m_imgX = (m_PtStart.X + (deltaX / m_zoom)); //在原始图像中X坐标偏移，这里计算的是在原始图片中的位移，原因在上面已经说明，全局的仿射变换会影响实际的位移
		m_imgY = (m_PtStart.Y + (deltaY / m_zoom)); //在原始图像中Y坐标偏移
	}
	Invalidate();
	CDialogEx::OnMouseMove(nFlags, point);
}
void CchiropracticDlg::OnLButtonUp(UINT nFlags, CPoint point) //相对于窗口左上角的
{
	m_bLButtonDown = false;
	if (m_srcImg.empty())
		return;
	CRect rectBox;
	CWnd *pWnd = GetDlgItem(IDC_PICTURE);
	pWnd->GetWindowRect(&rectBox);  // 得到的是控件相对于左上角的位置
	ScreenToClient(&rectBox);// 得到的是控件相对于程序窗口左上角的位置
	// 不在控件中，返回
	if (!PtInRect(&rectBox, point) && point != CPoint(0,0))
		return;
	// 不在图片中，则返回
	cv::Point pt;
	pt.x = point.x - rectBox.left; // 求相对于控件的坐标
	pt.y = point.y - rectBox.top;
	pt.x = pt.x / m_zoom - m_imgX;	// 求相对于图像的坐标
	pt.y = pt.y / m_zoom - m_imgY;
	if (point != CPoint(0, 0))
	{
		if (pt.x < 0 || pt.y < 0 || pt.x > m_srcImg.cols || pt.y > m_srcImg.rows)
			return;
	}
	// 零、截图操作
	if (m_opType == DRAW_RECT)
	{
		m_p2 = pt;
		// m_p2位于m_p1 左上角
		if (m_p1.x > m_p2.x && m_p1.y > m_p2.y)
		{
			// 左上角和右下角两点坐标互换
			cv::Point t;
			t = m_p1;
			m_p1 = m_p2;
			m_p2 = t;
		}
		// m_p2位于m_p1 左下角
		else if (m_p1.x > m_p2.x && m_p1.y < m_p2.y)
		{
			cv::Point t1, t2;
			t1.x = m_p2.x;
			t1.y = m_p1.y;
			t2.x = m_p1.x;
			t2.y = m_p2.y;

			m_p1 = t1;
			m_p2 = t2;
		}
		// m_p2位于m_p1 右上角
		else if (m_p1.x < m_p2.x && m_p1.y > m_p2.y)
		{
			cv::Point t1, t2;
			t1.x = m_p1.x;
			t1.y = m_p2.y;
			t2.x = m_p2.x;
			t2.y = m_p1.y;
			m_p1 = t1;
			m_p2 = t2;
		}
		// m_p2位于m_p1 右下角
		else if (m_p1.x < m_p2.x && m_p1.y < m_p2.y)
		{
			m_p2 = pt;
		}
		cv::Rect rect;
		rect.x = m_p1.x;
		rect.y = m_p1.y;
		rect.width = m_p2.x - m_p1.x;
		rect.height = m_p2.y - m_p1.y;

		m_srcImg(rect).copyTo(m_srcImg);   // 获取选取区域
		resize(m_maskImg, m_maskImg, m_srcImg.size());
		m_maskImg.setTo(0);
		resize(m_maskShowImg, m_maskShowImg, m_maskImg.size());
		m_maskShowImg.setTo(0);
	}

	//===============================================================================================================
	// 一、髂骨半脱位
	else if (m_opType == DIAG_QG && m_curStep < 20) // 操作从0到11
	{
		// 0、1 基准线
		if (m_curStep == 0)
		{
			m_gp[0] = pt;
			cv::circle(m_maskImg, pt, m_circleRadius, m_maskColor, -1);
			++m_curStep;
			m_bNeedSave = true;
		}
		else if (m_curStep == 1)
		{
			m_gp[1] = pt;
			cv::circle(m_maskImg, pt, m_circleRadius, m_maskColor, -1);

			m_dGrad_gg_x_qg = double(m_gp[0].y - m_gp[1].y) / (m_gp[0].x - m_gp[1].x + 10e-8); // 求斜率
			m_dGrad_gg_y_qg = -1.0f / (m_dGrad_gg_x_qg + 10e-8);
			cv::line(m_maskImg, m_gp[0], m_gp[1], m_maskColor, m_lineWidth);

			logInfo log = { 0 };    // 写入日志
			log.p[0] = m_gp[0];
			log.p[1] = m_gp[1];
			log.op = DRAW_LINE;
			log.step = m_curStep;
			m_vecLog.push_back(log);
			++m_curStep;
			m_bNeedSave = true;
		}
		// 左高
		else if (m_curStep == 2)
		{
			m_gp[2] = pt;
			cv::circle(m_maskImg, pt, m_circleRadius, m_maskColor, -1);

			lineExt(m_dGrad_gg_x_qg, pt, pt.x, (m_srcImg.cols/2 - pt.x)/2, m_p1, m_p2);  // 左边
			cv::line(m_maskImg, m_p1, m_p2, m_maskColor, m_lineWidth);

			logInfo log = { 0 };    // 写入日志
			log.p[0] = m_p1;
			log.p[1] = m_p2;
			log.center[0] = m_gp[2]; // 保存关键点
			log.op = DRAW_LINE;
			log.step = m_curStep;
			m_vecLog.push_back(log);
			++m_curStep;
			m_bNeedSave = true;
		}
		// 左底
		else if (m_curStep == 3)
		{
			m_gp[3] = pt;
			cv::circle(m_maskImg, pt, m_circleRadius, m_maskColor, -1);

			lineExt(m_dGrad_gg_x_qg, pt, pt.x, (m_srcImg.cols / 2 - pt.x) / 2, m_p1, m_p2);
			cv::line(m_maskImg, m_p1, m_p2, m_maskColor, m_lineWidth);

			logInfo log = { 0 };    // 写入日志
			// 求交点
			cv::Point dot;
			dot = lineCrossDot(m_dGrad_gg_x_qg, pt, m_gp[2]);   // 直线外点与直线的交点
			cv::line(m_maskImg, m_gp[2], dot, m_maskColor, m_lineWidth);
			// 计算测量长度
			double length = m_dheight_scale * std::sqrt((m_gp[2].x - dot.x)*(m_gp[2].x - dot.x) + (m_gp[2].y - dot.y)*(m_gp[2].y - dot.y));
			// 保存测量结果
			sprintf_s(log.text[0], "%.1fmm", length);
			// 显示测量结果
			cv::Point center = cv::Point(m_gp[2].x, (m_gp[2].y + pt.y) * 2 / 3);
			cv::putText(m_maskImg, log.text[0], center, m_font_type_measure, m_dfont_scale_measure, m_maskColor,m_font_thick_measure);

			m_dLength_wmg_l_qg = length;

			// 保存标注信息
			// p[0~1] 正常直线，p[2~3]测量线
			// center[0] 画直线时所取关键点，center[1] 测量线文字放置位置
			log.p[0] = m_p1;
			log.p[1] = m_p2;
			log.p[2] = m_gp[2];
			log.p[3] = dot;
			log.center[0] = m_gp[3]; // 保存关键点
			log.center[1] = center; // 保存关键点
			log.length[0] = length;
			log.op = DRAW_LINE_MEASURE;
			log.step = m_curStep;
			m_vecLog.push_back(log);
			++m_curStep;
			m_bNeedSave = true;
		}
		// 右高
		else if (m_curStep == 4)
		{
			m_gp[4] = pt;
			cv::circle(m_maskImg, pt, m_circleRadius, m_maskColor, -1);

			lineExt(m_dGrad_gg_x_qg, pt, (pt.x - m_srcImg.cols / 2) / 2, m_srcImg.cols - pt.x, m_p1, m_p2);
			cv::line(m_maskImg, m_p1, m_p2, m_maskColor, m_lineWidth);

			logInfo log = { 0 };    // 写入日志
			log.p[0] = m_p1;
			log.p[1] = m_p2;
			log.center[0] = m_gp[4];
			log.op = DRAW_LINE;
			log.step = m_curStep;
			m_vecLog.push_back(log);
			++m_curStep;
			m_bNeedSave = true;
		}
		// 右底
		else if (m_curStep == 5)
		{
			m_gp[5] = pt;
			cv::circle(m_maskImg, pt, m_circleRadius, m_maskColor, -1);

			lineExt(m_dGrad_gg_x_qg, pt, (pt.x - m_srcImg.cols / 2) / 2, m_srcImg.cols - pt.x, m_p1, m_p2);
			cv::line(m_maskImg, m_p1, m_p2, m_maskColor, m_lineWidth);

			logInfo log = { 0 };    // 写入日志
			// 标注
			cv::Point dot;
			dot = lineCrossDot(m_dGrad_gg_x_qg, pt, m_gp[4]);
			cv::line(m_maskImg, m_gp[4], dot, m_maskColor, m_lineWidth);

			double length = m_dheight_scale * std::sqrt((m_gp[4].x - dot.x)*(m_gp[4].x - dot.x) + (m_gp[4].y - dot.y)*(m_gp[4].y - dot.y));
			sprintf_s(log.text[0], "%.1fmm", length);
			cv::Point center = cv::Point(m_gp[4].x, (m_gp[4].y + pt.y) * 2 / 3);
			cv::putText(m_maskImg, log.text[0], center, m_font_type_measure, m_dfont_scale_measure, m_maskColor, m_font_thick_measure);
			m_dLength_wmg_r_qg = length;

			// 保存标注信息
			// p[0~1] 正常直线，p[2~3]测量线
			// center[0] 画直线时所取关键点，center[1] 测量线文字放置位置
			log.p[0] = m_p1;
			log.p[1] = m_p2;
			log.p[2] = m_gp[4];
			log.p[3] = dot;
			log.center[0] = m_gp[5]; // 保存关键点
			log.center[1] = center; // 保存关键点
			log.length[0] = length;
			log.op = DRAW_LINE_MEASURE;
			log.step = m_curStep;
			m_vecLog.push_back(log);
			++m_curStep;
			m_bNeedSave = true;
		}
		// 竖1
		else if (m_curStep == 6)
		{
			m_gp[6] = pt;
			cv::circle(m_maskImg, pt, m_circleRadius, m_maskColor, -1);

			if (m_dGrad_gg_y_qg >0)
				lineExt(m_dGrad_gg_y_qg, pt, m_srcImg.rows / 20, m_srcImg.rows - pt.y, m_p1, m_p2);
			else
				lineExt(m_dGrad_gg_y_qg, pt, m_srcImg.rows - pt.y, m_srcImg.rows / 20, m_p1, m_p2);
			cv::line(m_maskImg, m_p1, m_p2, m_maskColor, m_lineWidth);

			logInfo log = { 0 };    // 写入日志
			log.p[0] = m_p1;
			log.p[1] = m_p2;
			log.center[0] = m_gp[6];
			log.op = DRAW_LINE;
			log.step = m_curStep;
			m_vecLog.push_back(log);
			++m_curStep;
			m_bNeedSave = true;
		}
		// 竖2
		else if (m_curStep == 7)
		{
			m_gp[7] = pt;
			cv::circle(m_maskImg, pt, m_circleRadius, m_maskColor, -1);

			if (m_dGrad_gg_y_qg >0)
				lineExt(m_dGrad_gg_y_qg, pt, m_srcImg.rows/20, m_srcImg.rows - pt.y, m_p1, m_p2);
			else
				lineExt(m_dGrad_gg_y_qg, pt, m_srcImg.rows - pt.y, m_srcImg.rows / 20, m_p1, m_p2);
			cv::line(m_maskImg, m_p1, m_p2, m_maskColor, m_lineWidth);

			logInfo log = { 0 };    // 写入日志
			// 标注
			cv::Point dot;
			dot = lineCrossDot(m_dGrad_gg_y_qg, m_gp[6], pt);
			double length = m_dheight_scale * std::sqrt((pt.x - dot.x)*(pt.x - dot.x) + (pt.y - dot.y)*(pt.y - dot.y));
			cv::line(m_maskImg, pt, dot, m_maskColor, m_lineWidth);

			sprintf_s(log.text[0], "%.1fmm", length);
			cv::Point center;
			if(m_gp[7].x < dot.x)		//耻骨联合中线偏左
			{
				int baseline = 0;
				cv::Size sz_wh = cv::getTextSize(log.text[0], m_font_type_measure, m_dfont_scale_measure, m_font_thick_measure, &baseline);
				center = cv::Point(m_gp[7].x - sz_wh.width, m_gp[7].y + sz_wh.height/2);
			}
			else						//耻骨联合中线偏右,或相等
			{
				center = cv::Point(m_gp[7].x, m_gp[7].y);
			}
			cv::putText(m_maskImg, log.text[0], center, m_font_type_measure, m_dfont_scale_measure, m_maskColor, m_font_thick_measure);

			if (m_gp[7].x < dot.x)  // 负数表示偏左，正数表示偏右
				m_dLength = 0 - length;
			else
				m_dLength = length;
			// 保存标注信息
			// p[0~1] 正常直线，p[2~3]测量线
			// center[0] 画直线时所取关键点，center[1] 测量线文字放置位置
			log.p[0] = m_p1;
			log.p[1] = m_p2;
			log.p[2] = m_gp[7];
			log.p[3] = dot;
			log.center[0] = m_gp[7];
			log.center[1] = center; // 保存关键点
			log.length[0] = length;
			log.op = DRAW_LINE_MEASURE;
			log.step = m_curStep;
			m_vecLog.push_back(log);
			++m_curStep;
			m_bNeedSave = true;
		}
		// 判断原发侧
		else if (m_curStep == 8)
		{
			//旋转侧判定
			if (m_bHas_draw_yfc == false)		// 启动旋转判定步骤
			{
				if (m_rotateMethod == 0)
				{
					MessageBox(_T("请选择原发测判定方法。"));
					return;
				}
				drawYfc(pt);
				if(m_bHas_draw_yfc == false)
					return;
			}
			// 进行诊断
			double delta_wmg = m_dLength_wmg_l_qg - m_dLength_wmg_r_qg;
			if (m_strYfc == _T("R"))//原发侧为右侧
			{
				if (delta_wmg > 0)		//右侧为AS
				{
					if (m_dLength < 0)
						m_strDiag_qg.Format(_T("AS%.1fIn%.1f"), delta_wmg, -m_dLength);
					else
						m_strDiag_qg.Format(_T("AS%.1fEx%.1f"), delta_wmg, m_dLength);
				}
				else//右侧为PI
				{
					if (m_dLength < 0)
						m_strDiag_qg.Format(_T("PI%.1fIn%.1f"), -delta_wmg, -m_dLength);
					else
						m_strDiag_qg.Format(_T("PI%.1fEx%.1f"), -delta_wmg, m_dLength);
				}
				
			}
			else if (m_strYfc == _T("L"))//原发侧为左侧
			{
				if (delta_wmg > 0)		//左侧为PI
				{
					if (m_dLength < 0)
						m_strDiag_qg.Format(_T("PI%.1fEx%.1f"), delta_wmg, -m_dLength);
					else
						m_strDiag_qg.Format(_T("PI%.1fIn%.1f"), delta_wmg, m_dLength);
				}
				else//左侧为AS
				{
					if (m_dLength < 0)
						m_strDiag_qg.Format(_T("AS%.1fEx%.1f"), -delta_wmg, -m_dLength);
					else
						m_strDiag_qg.Format(_T("AS%.1fIn%.1f"), -delta_wmg, m_dLength);
				}
			}
			// 放置诊断
			cv::Point center_diag_qg;
			if (m_strYfc == _T("L"))
			{
				center_diag_qg = cv::Point(0, m_srcImg.rows / 2);
			}
			else if(m_strYfc == _T("R"))
			{
				int baseline = 0;
				cv::Size sz_wh = cv::getTextSize(m_strDiag_qg.GetBuffer(), m_font_type_diag, m_font_scale_diag, m_font_thick_diag, &baseline);
				center_diag_qg = cv::Point(m_srcImg.cols, m_srcImg.rows / 2);
				center_diag_qg.x = center_diag_qg.x - sz_wh.width;
			}
			cv::putText(m_maskImg, m_strDiag_qg.GetBuffer(), center_diag_qg, m_font_type_diag, m_font_scale_diag, m_maskColor, m_font_thick_diag);
			Invalidate();
			m_curStep++;
			m_bNeedSave = true;
			m_bHas_draw_yfc = false;
			INT_PTR ret = MessageBox(_T("是否继续诊断骶骨？"),_T("提示"),MB_YESNO);
			if (ret == IDYES)
			{
				m_bDiag_dg_qg = true;
			}
			else
			{
				m_bDiag_dg_qg = false;
			}

		}
		// 9.10骶骨水平线
		else if (m_curStep == 9 && m_bDiag_dg_qg == true)
		{
			m_gp[9] = pt;
			cv::circle(m_maskImg, pt, m_circleRadius, m_maskColor, -1);
			m_curStep++;
			m_bNeedSave = true;
		}
		else if (m_curStep == 10)
		{
			m_gp[10] = pt;
			m_dGrad_dg_x_dg = double(m_gp[10].y - m_gp[9].y) / (m_gp[10].x - m_gp[9].x + 10e-8); // 求斜率
			m_dGrad_dg_y_dg = -1.0f / (m_dGrad_dg_x_dg + 10e-8);
			// 1. 做骶骨水平线
			cv::Point lineExt_l, lineExt_r;
			lineExt(m_dGrad_dg_x_dg, m_gp[9], m_gp[9].x / 2, 0, m_p1, m_p2);
			lineExt_l = m_p1;
			lineExt(m_dGrad_dg_x_dg, m_gp[10], 0, (m_srcImg.cols - m_gp[10].x) / 2, m_p1, m_p2);
			lineExt_r = m_p2;
			// 画出骶骨水平线和点
			cv::circle(m_maskImg, m_gp[9], m_circleRadius, m_maskColor, -1);
			cv::circle(m_maskImg, m_gp[10], m_circleRadius, m_maskColor, -1);
			cv::line(m_maskImg, lineExt_l, lineExt_r, m_lineColor, m_lineWidth);
			// 侧向下偏位
			// 3. 过骶沟较高点做股骨头线的平行线
			// 过较低骶沟点做股骨头线的平行线的垂直线
			cv::Point line_xx_l, line_xx_r, dot_xx_top,dot_xx_bot;
			if (m_gp[9].y >= m_gp[10].y)  //左侧偏下，右侧偏上
			{
				// 过m_gp[10]做股骨头线的平行线
				// 延长线向左延长
				lineExt(m_dGrad_gg_x_qg, m_gp[10], m_gp[10].x - (lineExt_l.x + m_gp[9].x) / 2, 0, m_p1, m_p2);
				line_xx_l = m_p1;
				line_xx_r = m_gp[10];
				dot_xx_top = lineCrossDot(m_dGrad_gg_x_qg, line_xx_l, m_gp[9]);
				dot_xx_bot = m_gp[9];
			}
			else if (m_gp[9].y < m_gp[10].y)  //左侧偏上，右侧偏下
			{
				// 过m_gp[9]做股骨头线的平行线，
				// 延长线向右延长
				lineExt(m_dGrad_gg_x_qg, m_gp[9], 0, (lineExt_r.x + m_gp[10].x) / 2 - m_gp[9].x, m_p1, m_p2);
				line_xx_l = m_gp[9];
				line_xx_r = m_p2;
				dot_xx_top = lineCrossDot(m_dGrad_gg_x_qg, line_xx_l, m_gp[10]);
				dot_xx_bot = m_gp[10];
			}
			cv::line(m_maskImg, line_xx_l, line_xx_r, m_maskColor, m_lineWidth);
			cv::line(m_maskImg, dot_xx_top, dot_xx_bot, m_maskColor, m_lineWidth);
			// 计算向下偏位距离
			int xx_x = std::abs(dot_xx_top.x - dot_xx_bot.x);
			int xx_y = std::abs(dot_xx_top.y - dot_xx_bot.y);
			m_dLength_xx_dg = std::sqrt(m_dwidth_scale*xx_x *xx_x + m_dheight_scale *xx_y*xx_y);
			//计算放置位置
			char text_xx[20];
			sprintf_s(text_xx, "%.1fmm", m_dLength_xx_dg);
			int baseline = 0;
			cv::Size sz_wh = cv::getTextSize(text_xx, m_font_type_measure, m_dfont_scale_measure, m_font_thick_measure, &baseline);
			cv::Point center_xx;
			center_xx.x = dot_xx_top.x - sz_wh.width / 2;
			center_xx.y = dot_xx_top.y - sz_wh.height / 2;
			cv::putText(m_maskImg, text_xx, center_xx, m_font_type_measure, m_dfont_scale_measure, m_maskColor, m_font_thick_measure);

			m_curStep++;
			m_bNeedSave = true;

			// 为胸椎诊断设置标志位
			m_bHas_draw_dd_line_xz = true;
			m_dGrad_dg_xz = m_dGrad_dg_x_dg;
		}
		// 11 左侧骶翼垂直线
		else if (m_curStep == 11)
		{
			m_gp[11] = pt;
			cv::Point dot;
			// 求左垂线与骶骨水平线的垂直点
			dot = lineCrossDot(m_dGrad_dg_x_dg, m_gp[10], m_gp[11]);
			//求从dot点延长线
			//if (m_dGrad_dg_y_dg >0)	// top 在左边
			lineExt(m_dGrad_dg_y_dg, dot, 0, m_gp[0].y - dot.y, m_p1, m_p2);
			//else                    // top 在右边
			//lineExt(m_dGrad_dg_y_dg, dot, m_gp[0].y - dot.y, 0, m_p1, m_p2);
			// 画出直线
			cv::circle(m_maskImg, m_gp[11], m_circleRadius, m_maskColor, -1);
			cv::line(m_maskImg, m_p1, m_p2, m_maskColor, m_lineWidth);

			m_curStep++;
			m_bNeedSave = true;
		}
		// 12 右侧骶翼垂直线
		else if (m_curStep == 12)
		{
			m_gp[12] = pt;
			cv::Point dot;
			// 求右垂线与骶骨水平线的垂直点
			dot = lineCrossDot(m_dGrad_dg_x_dg, m_gp[10], m_gp[12]);
			//求从dot点延长线
			//if (m_dGrad_dg_y_dg >0)	// top 在左边
			lineExt(m_dGrad_dg_y_dg, dot, 0, m_gp[0].y - dot.y, m_p1, m_p2);
			//else                    // top 在右边
			//lineExt(m_dGrad_dg_y_dg, dot, m_gp[0].y - dot.y, 0, m_p1, m_p2);
			// 画出直线
			cv::circle(m_maskImg, m_gp[12], m_circleRadius, m_maskColor, -1);
			cv::line(m_maskImg, m_p1, m_p2, m_maskColor, m_lineWidth);

			m_curStep++;
			m_bNeedSave = true;
		}
		// 13 骶1结点垂直线
		else if (m_curStep == 13)
		{
			m_gp[13] = pt;
			cv::Point dot;
			// 求骶1结点与骶骨水平线的垂直点
			dot = lineCrossDot(m_dGrad_dg_x_dg, m_gp[9], m_gp[13]);
			//求从dot点延长线
			lineExt(m_dGrad_dg_y_dg, dot, 0, m_gp[0].y - dot.y, m_p1, m_p2);
			cv::circle(m_maskImg, m_gp[12], m_circleRadius, m_maskColor, -1);
			cv::line(m_maskImg, m_p1, m_p2, m_maskColor, m_lineWidth);
			// 骶1结点到左右倆垂线的垂直点
			cv::Point dot_l, dot_r;
			dot_l = lineCrossDot(m_dGrad_dg_y_dg, m_gp[11], m_gp[13]);
			dot_r = lineCrossDot(m_dGrad_dg_y_dg, m_gp[12], m_gp[13]);
			int delta_x_l = std::abs(m_gp[13].x - dot_l.x);
			int delta_y_l = std::abs(m_gp[13].y - dot_l.y);
			int delta_x_r = std::abs(m_gp[13].x - dot_r.x);
			int delta_y_r = std::abs(m_gp[13].y - dot_r.y);
			m_dLength_l_dg = std::sqrt(m_dwidth_scale * delta_x_l*delta_x_l + m_dheight_scale * delta_y_l * delta_y_l);
			m_dLength_r_dg = std::sqrt(m_dwidth_scale * delta_x_r*delta_x_r + m_dheight_scale * delta_y_r * delta_y_r);
			// 放置测量
			char text_l_dg[20], text_r_dg[20];
			cv::Point center_l_dg, center_r_dg;
			sprintf_s(text_l_dg, "%.1fmm", m_dLength_l_dg);
			sprintf_s(text_r_dg, "%.1fmm", m_dLength_r_dg);
			center_l_dg = cv::Point((m_gp[13].x + dot_l.x)/2, (m_gp[13].y + dot_l.y) / 2);
			center_r_dg = cv::Point((m_gp[13].x + dot_r.x) / 2, (m_gp[13].y + dot_r.y) / 2);
			int baseline = 0;
			cv::Size sz_wh_l = cv::getTextSize(text_l_dg, m_font_type_measure, m_dfont_scale_measure, m_font_thick_measure, &baseline);
			cv::Size sz_wh_r = cv::getTextSize(text_r_dg, m_font_type_measure, m_dfont_scale_measure, m_font_thick_measure, &baseline);
			center_l_dg = cv::Point(center_l_dg.x - sz_wh_l.width / 2, center_l_dg.y - sz_wh_l.height / 2);
			center_r_dg = cv::Point(center_r_dg.x - sz_wh_r.width / 2, center_r_dg.y - sz_wh_r.height / 2);
			cv::putText(m_maskImg, text_l_dg, center_l_dg, m_font_type_measure, m_dfont_scale_measure, m_maskColor, m_font_thick_measure);
			cv::putText(m_maskImg, text_r_dg, center_r_dg, m_font_type_measure, m_dfont_scale_measure, m_maskColor, m_font_thick_measure);
			// 下诊断
			double delta_dg = std::abs(m_dLength_l_dg - m_dLength_r_dg);
			CString strYfc = _T("");
			//bool isok = true;
			if (delta_dg >= 7)	// 骶骨需要矫正
			{
				//isok = false;
				if (m_dLength_l_dg < m_dLength_r_dg)		// 右边为原发测
				{
					strYfc = _T("R");
					m_strDiag_dg.Format(_T("P%.1fI%.1f-R"), delta_dg, m_dLength_xx_dg);
				}
				// 左边为原发测
				else
				{
					strYfc = _T("L");
					m_strDiag_dg.Format(_T("P%.1fI%.1f-L"), delta_dg, m_dLength_xx_dg);
				}
			}
			else if (delta_dg > 4 && delta_dg < 7)		// 人工判断是否有向下偏位
			{

				bool has_xx;
				INT_PTR ret = MessageBox(_T("两侧距离只差介于4mm到6mm之间，是否有向下偏位？"), _T("提示"), MB_YESNO);
				if (ret == IDYES)
				{
					has_xx = true;
				}
				else
				{
					has_xx = false;
				}
				if (m_dLength_l_dg < m_dLength_r_dg)		// 右边为原发测
				{
					if(has_xx)
						m_strDiag_dg.Format(_T("P%.1fI%.1f-R"), delta_dg, m_dLength_xx_dg);
					else
						m_strDiag_dg.Format(_T("P%.1f-R"), delta_dg);
				}
				// 左边为原发测
				else
				{
					if (has_xx)
						m_strDiag_dg.Format(_T("P%.1fI%.1f-L"), delta_dg, m_dLength_xx_dg);
					else
						m_strDiag_dg.Format(_T("P%.1f-L"), delta_dg);
				}
			}
			// 骶骨没有问题
			else
			{
				m_strDiag_dg = _T("");
			}
			// 计算放置位置
			cv::Point center_diag_dg;
			if (delta_dg > 4)
			{
				if (m_dLength_l_dg < m_dLength_r_dg)		// 右边为原发测
				{
					center_diag_dg = cv::Point(m_srcImg.cols, m_srcImg.rows / 2);
					int baseline = 0;
					cv::Size sz_wh = cv::getTextSize(m_strDiag_dg.GetBuffer(), m_font_type_diag, m_font_scale_diag, m_font_thick_diag, &baseline);
					center_diag_dg.x = center_diag_dg.x - sz_wh.width;
					center_diag_dg.y = center_diag_dg.y - 2*sz_wh.height;//防止与髂骨诊断重合
				}
				else
				{
					center_diag_dg = cv::Point(0, m_srcImg.rows / 2);
					int baseline = 0;
					cv::Size sz_wh = cv::getTextSize(m_strDiag_dg.GetBuffer(), m_font_type_diag, m_font_scale_diag, m_font_thick_diag, &baseline);
					//center_diag_dg.x = center_diag_dg.x - sz_wh.width;
					center_diag_dg.y = center_diag_dg.y - 2*sz_wh.height;//防止与髂骨诊断重合
				}
			}
			cv::putText(m_maskImg, m_strDiag_dg.GetBuffer(), center_diag_dg, m_font_type_diag, m_font_scale_diag, m_maskColor,m_font_thick_diag);

			m_curStep++;
			m_bNeedSave = true;
		}

		//有新操作后就不能再返回了
		cv::vector<logInfo>().swap(m_vecDelLog);
		remindColor();
	} /* 一、髂骨半脱位 */
//===============================================================================================================
	// 三、腰椎诊断
	else if (m_opType == DIAG_YZ && m_curStep < 20)
	{
		// 先确定左右直线边界
		// 0、1左边界
		if (m_curStep == 0)
		{
			m_gp[0] = pt;
			cv::circle(m_maskImg, m_gp[0], m_circleRadius, m_maskColor, -1);
			m_curStep++;
		}
		else if (m_curStep == 1)
		{
			m_gp[1] = pt;
			cv::circle(m_maskImg, m_gp[1], m_circleRadius, m_maskColor, -1);
			cv::line(m_maskImg, m_gp[0], m_gp[1], m_maskColor, m_lineWidth);
			//计算直线斜率和偏置
			m_dGrad_bj_yz[0] = (m_gp[1].y - m_gp[0].y) / (m_gp[1].x - m_gp[0].x + 10e-8);
			m_dBias_bj_yz[0] = ((m_gp[1].y + m_gp[0].y) - m_dGrad_bj_yz[0] * (m_gp[1].x + m_gp[0].x)) / 2;
			//写入操作
			logInfo log = { 0 };
			log.p[0] = m_gp[0];
			log.p[1] = m_gp[1];
			log.op = DRAW_LINE;
			log.step = m_curStep;
			m_vecLog.push_back(log);
			m_curStep++;
		}
		// 2、3右边界
		else if (m_curStep == 2)
		{
			m_gp[2] = pt;
			cv::circle(m_maskImg, m_gp[2], m_circleRadius, m_maskColor, -1);
			m_curStep++;
		}
		else if (m_curStep == 3)
		{
			m_gp[3] = pt;
			cv::circle(m_maskImg, m_gp[3], m_circleRadius, m_maskColor, -1);
			cv::line(m_maskImg, m_gp[2], m_gp[3], m_maskColor, m_lineWidth);
			//计算直线斜率和偏置
			m_dGrad_bj_yz[1] = (m_gp[3].y - m_gp[2].y) / (m_gp[3].x - m_gp[2].x + 10e-8);
			m_dBias_bj_yz[1] = ((m_gp[3].y + m_gp[2].y) - m_dGrad_bj_yz[1] * (m_gp[3].x + m_gp[2].x)) / 2;
			//写入操作
			logInfo log = { 0 };
			log.p[0] = m_gp[2];
			log.p[1] = m_gp[3];
			log.op = DRAW_LINE;
			log.step = m_curStep;
			m_vecLog.push_back(log);
			m_curStep++;
			//m_curDiag_yz = 5;// 当前正在诊断的腰椎
			m_curDiag_xie_yz = 0;
		}
		// 4~ 其他线
		else if (m_curStep > 3)
		{
			if (m_total_lux_yz == 0)
			{
				// 处理完成
				return;
			}
			// 切向楔形判断
			if (m_bLuxs_yz[5] == true && m_curDiag_yz == 5)
			{
				// 第五腰椎
				double l_l = 0, l_r = 0;
				if (m_curDiag_xie_yz == 0)
				{
					m_gp[4] = pt;
					cv::circle(m_maskImg, m_gp[4], m_circleRadius, m_maskColor, -1);
					m_curDiag_xie_yz = 1;
				}
				else if (m_curDiag_xie_yz == 1)
				{
					// p[0~1] 直线两点
					// center[0~1] 直线两关键点
					m_gp[5] = pt;
					// 计算与左右边界直线交点
					cv::Point cl, cr;
					cl = intersect(m_gp[0], m_gp[1], m_gp[4], m_gp[5]);
					cr = intersect(m_gp[2], m_gp[3], m_gp[4], m_gp[5]);
					// 保存直线与边界线的交点
					m_point_cp_l_yz[6] = cl;
					m_point_cp_r_yz[6] = cr;
					// 画出直线
					cv::circle(m_maskImg, m_gp[5], m_circleRadius, m_maskColor, -1);
					cv::line(m_maskImg, cl, cr, m_maskColor, m_lineWidth);
					//写入操作
					m_curDiag_xie_yz = 2;
				}
				// 6、7 第五腰椎
				else if (m_curDiag_xie_yz == 2)
				{
					m_gp[6] = pt;
					cv::circle(m_maskImg, m_gp[6], m_circleRadius, m_maskColor, -1);
					m_curDiag_xie_yz = 3;
				}
				else if (m_curDiag_xie_yz == 3)
				{
					// p[0~1] 直线两点
					// center[0~1] 直线两关键点
					m_gp[7] = pt;
					// 计算与左右边界直线交点
					cv::Point cl, cr;
					cl = intersect(m_gp[0], m_gp[1], m_gp[6], m_gp[7]);
					cr = intersect(m_gp[2], m_gp[3], m_gp[6], m_gp[7]);
					// 保存直线与边界线的交点
					m_point_cp_l_yz[5] = cl;
					m_point_cp_r_yz[5] = cr;
					// 画出直线
					cv::circle(m_maskImg, m_gp[7], m_circleRadius, m_maskColor, -1);
					cv::line(m_maskImg, cl, cr, m_maskColor, m_lineWidth);
					//进行测量和标注
					l_l = m_dheight_scale * std::sqrt(std::pow(m_point_cp_l_yz[5].x - m_point_cp_l_yz[6].x, 2) + std::pow(m_point_cp_l_yz[5].y - m_point_cp_l_yz[6].y, 2));
					l_r = m_dheight_scale * std::sqrt(std::pow(m_point_cp_r_yz[5].x - m_point_cp_r_yz[6].x, 2) + std::pow(m_point_cp_r_yz[5].y - m_point_cp_r_yz[6].y, 2));
					char text_l[20], text_r[20];
					sprintf_s(text_l, "%.1lfmm", l_l);
					sprintf_s(text_r, "%.1lfmm", l_r);
					cv::Point center_l, center_r;
					center_l = cv::Point((m_point_cp_l_yz[5].x + m_point_cp_l_yz[6].x) / 2, (m_point_cp_l_yz[5].y + m_point_cp_l_yz[6].y) / 2);
					int baseline = 0;
					cv::Size sz_wh = cv::getTextSize(text_r, m_font_type_measure, m_dfont_scale_measure, m_font_thick_measure, &baseline);
					center_r = cv::Point((m_point_cp_r_yz[5].x + m_point_cp_r_yz[6].x) / 2, (m_point_cp_r_yz[5].y + m_point_cp_r_yz[6].y) / 2);
					center_r = cv::Point(center_r.x - sz_wh.width, center_r.y);
					cv::putText(m_maskImg, text_l, center_l, m_font_type_measure, m_dfont_scale_measure, m_maskColor, m_font_thick_measure);
					cv::putText(m_maskImg, text_r, center_r, m_font_type_measure, m_dfont_scale_measure, m_maskColor, m_font_thick_measure);
					m_curDiag_xie_yz = 4;
				}
				else if (m_curDiag_xie_yz == 4)
				{
					if (m_bHas_draw_yfc == false)		// 启动旋转判定步骤
					{
						if (m_rotateMethod == 0)
						{
							MessageBox(_T("请选择原发测判定方法。"));
							return;
						}
						drawYfc(pt);
						if (m_bHas_draw_yfc == false)
							return;
					}
					// 诊断
					m_strDiag_yz[5] = _T("5P");
					//1. 旋转判断
					if (m_strYfc == _T("R"))	// 棘突偏向右侧
					{
						m_strDiag_yz[5] = m_strDiag_yz[5] + _T("R");
					}
					else if (m_strYfc == _T("L"))  // 棘突偏向左侧
					{
						m_strDiag_yz[5] = m_strDiag_yz[5] + _T("L");
					}
					else if (m_strYfc == _T(""))	// 没有偏转
					{

					}
					//2. 切向楔形判断,接触点判断
					double lr = std::abs(l_l - l_r);
					if (lr >= m_dThres_xie_yz)		// 有侧向楔形
					{
						if (m_strYfc == _T("R"))
						{
							if (l_l < l_r)	//棘突偏向楔形开口侧
							{
								m_strDiag_yz[5] = m_strDiag_yz[5] + _T("S");
							}
							else
							{
								m_strDiag_yz[5] = m_strDiag_yz[5] + _T("I-M");
							}
						}
						else if (m_strYfc == _T("L"))
						{
							if (l_l > l_r)	//棘突偏向楔形开口侧
							{
								m_strDiag_yz[5] = m_strDiag_yz[5] + _T("S");
							}
							else
							{
								m_strDiag_yz[5] = m_strDiag_yz[5] + _T("I-M");
							}
						}
					}
					else                            // 无侧向楔形
					{
						if (m_strBend_yz == m_strYfc)
						{
							m_strDiag_yz[5] = m_strDiag_yz[5] + _T("-M");
						}
						else
						{
							m_strDiag_yz[5] = m_strDiag_yz[5] + _T("-Sp");
						}
					}
					// 放置诊断
					int baseline = 0;
					cv::Size sz_wh = cv::getTextSize(m_strDiag_yz[5].GetBuffer(), m_font_type_diag, m_font_scale_diag, m_font_thick_diag, &baseline);
					cv::Point center_d;
					center_d = cv::Point((m_gp[6].x + m_gp[7].x) / 2, (m_gp[6].y + m_gp[7].y) / 2);
					center_d = cv::Point(center_d.x - sz_wh.width / 2, center_d.y + sz_wh.height / 2);
					cv::putText(m_maskImg, m_strDiag_yz[5].GetBuffer(), center_d, m_font_type_diag, m_font_scale_diag, m_maskColor, m_font_thick_diag);
					// 进行下一个腰椎判定
					m_curDiag_yz = 0;
					m_curDiag_xie_yz = 0;
					m_total_lux_yz--;
					m_bHas_draw_yfc = false;
					if (m_bLuxs_yz[4] == true)
					{
						m_curDiag_yz = 4;
						m_curDiag_xie_yz = 2;
					}
					else
					{
						for (int i = 3; i > 0; i--)
						{
							if (m_bLuxs_yz[i] == true)
							{
								m_curDiag_yz = i;
								m_curDiag_xie_yz = 0;
								break;
							}
						}
					}
				}
			}

			else if (m_curDiag_yz == 4 && m_bLuxs_yz[4] == true)
			{
				// 第四腰椎
				double l_l = 0, l_r = 0;
				if (m_curDiag_xie_yz == 0)
				{
					m_gp[6] = pt;
					cv::circle(m_maskImg, m_gp[6], m_circleRadius, m_maskColor, -1);
					m_curDiag_xie_yz = 1;
				}
				else if (m_curDiag_xie_yz == 1)
				{
					// p[0~1] 直线两点
					// center[0~1] 直线两关键点
					m_gp[7] = pt;
					// 计算与左右边界直线交点
					cv::Point cl, cr;
					cl = intersect(m_gp[0], m_gp[1], m_gp[6], m_gp[7]);
					cr = intersect(m_gp[2], m_gp[3], m_gp[6], m_gp[7]);
					// 保存直线与边界线的交点
					m_point_cp_l_yz[5] = cl;
					m_point_cp_r_yz[5] = cr;
					// 画出直线
					cv::circle(m_maskImg, m_gp[7], m_circleRadius, m_maskColor, -1);
					cv::line(m_maskImg, cl, cr, m_maskColor, m_lineWidth);
					//写入操作
					m_curDiag_xie_yz = 2;
				}
				//  L4腰椎
				else if (m_curDiag_xie_yz == 2)
				{
					m_gp[8] = pt;
					cv::circle(m_maskImg, m_gp[8], m_circleRadius, m_maskColor, -1);
					m_curDiag_xie_yz = 3;
				}
				else if (m_curDiag_xie_yz == 3)
				{
					// p[0~1] 直线两点
					// center[0~1] 直线两关键点
					m_gp[9] = pt;
					// 计算与左右边界直线交点
					cv::Point cl, cr;
					cl = intersect(m_gp[0], m_gp[1], m_gp[8], m_gp[9]);
					cr = intersect(m_gp[2], m_gp[3], m_gp[8], m_gp[9]);
					// 保存直线与边界线的交点
					m_point_cp_l_yz[4] = cl;
					m_point_cp_r_yz[4] = cr;
					// 画出直线
					cv::circle(m_maskImg, m_gp[9], m_circleRadius, m_maskColor, -1);
					cv::line(m_maskImg, cl, cr, m_maskColor, m_lineWidth);
					//进行测量和标注
					double l_l = 0, l_r = 0;
					l_l = m_dheight_scale * std::sqrt(std::pow(m_point_cp_l_yz[4].x - m_point_cp_l_yz[5].x, 2) + std::pow(m_point_cp_l_yz[4].y - m_point_cp_l_yz[5].y, 2));
					l_r = m_dheight_scale * std::sqrt(std::pow(m_point_cp_r_yz[4].x - m_point_cp_r_yz[5].x, 2) + std::pow(m_point_cp_r_yz[4].y - m_point_cp_r_yz[5].y, 2));
					char text_l[20], text_r[20];
					sprintf_s(text_l, "%.1lfmm", l_l);
					sprintf_s(text_r, "%.1lfmm", l_r);
					cv::Point center_l, center_r;
					center_l = cv::Point((m_point_cp_l_yz[4].x + m_point_cp_l_yz[5].x) / 2, (m_point_cp_l_yz[4].y + m_point_cp_l_yz[5].y) / 2);
					int baseline = 0;
					cv::Size sz_wh = cv::getTextSize(text_r, m_font_type_measure, m_dfont_scale_measure, m_font_thick_measure, &baseline);
					center_r = cv::Point((m_point_cp_r_yz[4].x + m_point_cp_r_yz[5].x) / 2, (m_point_cp_r_yz[4].y + m_point_cp_r_yz[5].y) / 2);
					center_r = cv::Point(center_r.x - sz_wh.width, center_r.y);
					cv::putText(m_maskImg, text_l, center_l, m_font_type_measure, m_dfont_scale_measure, m_maskColor, m_font_thick_measure);
					cv::putText(m_maskImg, text_r, center_r, m_font_type_measure, m_dfont_scale_measure, m_maskColor, m_font_thick_measure);
					m_curDiag_xie_yz = 4;
				}
				else if (m_curDiag_xie_yz == 4)
				{
					if (m_bHas_draw_yfc == false)		// 启动旋转判定步骤
					{
						if (m_rotateMethod == 0)
						{
							MessageBox(_T("请选择原发测判定方法。"));
							return;
						}
						drawYfc(pt);
						if (m_bHas_draw_yfc == false)
							return;
					}
					// 进行诊断
					m_strDiag_yz[4] = _T("4P");
					//1. 旋转判断
					if (m_strYfc == _T("R"))	// 棘突偏向右侧
					{
						m_strDiag_yz[4] = m_strDiag_yz[4] + _T("R");
					}
					else if (m_strYfc == _T("L"))  // 棘突偏向左侧
					{
						m_strDiag_yz[4] = m_strDiag_yz[4] + _T("L");
					}
					else if (m_strYfc == _T(""))	// 没有偏转
					{

					}
					//2. 切向楔形判断,接触点判断
					double lr = std::abs(l_l - l_r);
					if (lr >= m_dThres_xie_yz)		// 有侧向楔形
					{
						if (m_strYfc == _T("R"))
						{
							if (l_l < l_r)	//棘突偏向楔形开口侧
							{
								m_strDiag_yz[4] = m_strDiag_yz[4] + _T("S");
							}
							else
							{
								m_strDiag_yz[4] = m_strDiag_yz[4] + _T("I-M");
							}
						}
						else if (m_strYfc == _T("L"))
						{
							if (l_l > l_r)	//棘突偏向楔形开口侧
							{
								m_strDiag_yz[4] = m_strDiag_yz[4] + _T("S");
							}
							else
							{
								m_strDiag_yz[4] = m_strDiag_yz[4] + _T("I-M");
							}
						}
					}
					else                            // 无侧向楔形
					{
						if (m_strBend_yz == m_strYfc)
						{
							m_strDiag_yz[4] = m_strDiag_yz[4] + _T("-Sp");
						}
						else
						{
							m_strDiag_yz[4] = m_strDiag_yz[4] + _T("-M");
						}
					}
					// 放置诊断
					int baseline = 0;
					cv::Size sz_wh = cv::getTextSize(m_strDiag_yz[4].GetBuffer(), m_font_type_diag, m_font_scale_diag, m_font_thick_diag, &baseline);
					cv::Point center_d;
					center_d = cv::Point((m_gp[8].x + m_gp[9].x) / 2, (m_gp[8].y + m_gp[9].y) / 2);
					center_d = cv::Point(center_d.x - sz_wh.width / 2, center_d.y + sz_wh.height / 2);
					cv::putText(m_maskImg, m_strDiag_yz[4].GetBuffer(), center_d, m_font_type_diag, m_font_scale_diag, m_maskColor, m_font_thick_diag);

					// 进行下一个腰椎判定
					m_curDiag_yz = 0;
					m_curDiag_xie_yz = 0;
					m_total_lux_yz--;
					m_bHas_draw_yfc = false;
					if (m_bLuxs_yz[3] == true)
					{
						m_curDiag_yz = 3;
						m_curDiag_xie_yz = 2;
					}
					else
					{
						for (int i = 2; i > 0; i--)
						{
							if (m_bLuxs_yz[i] == true)
							{
								m_curDiag_yz = i;
								m_curDiag_xie_yz = 0;
								break;
							}
						}
					}
				}
			}
			else if (m_bLuxs_yz[3] == true && m_curDiag_yz == 3)
			{
				// L3腰椎
				double l_l = 0, l_r = 0;
				if (m_curDiag_xie_yz == 0)
				{
					m_gp[8] = pt;
					cv::circle(m_maskImg, m_gp[8], m_circleRadius, m_maskColor, -1);
					m_curDiag_xie_yz = 1;
				}
				else if (m_curDiag_xie_yz == 1)
				{
					// p[0~1] 直线两点
					// center[0~1] 直线两关键点
					m_gp[9] = pt;
					cv::circle(m_maskImg, m_gp[9], m_circleRadius, m_maskColor, -1);
					// 计算与左右边界直线交点
					cv::Point cl, cr;
					cl = intersect(m_gp[0], m_gp[1], m_gp[8], m_gp[9]);
					cr = intersect(m_gp[2], m_gp[3], m_gp[8], m_gp[9]);
					// 保存直线与边界线的交点
					m_point_cp_l_yz[4] = cl;
					m_point_cp_r_yz[4] = cr;
					// 画出直线
					cv::line(m_maskImg, cl, cr, m_maskColor, m_lineWidth);
					//写入操作
					m_curDiag_xie_yz = 2;
				}
				//  L3腰椎
				else if (m_curDiag_xie_yz == 2)
				{
					m_gp[10] = pt;
					cv::circle(m_maskImg, m_gp[10], m_circleRadius, m_maskColor, -1);
					m_curDiag_xie_yz = 3;
				}
				else if (m_curDiag_xie_yz == 3)
				{
					// p[0~1] 直线两点
					// center[0~1] 直线两关键点
					m_gp[11] = pt;
					cv::circle(m_maskImg, m_gp[11], m_circleRadius, m_maskColor, -1);
					// 计算与左右边界直线交点
					cv::Point cl, cr;
					cl = intersect(m_gp[0], m_gp[1], m_gp[10], m_gp[11]);
					cr = intersect(m_gp[2], m_gp[3], m_gp[10], m_gp[11]);
					// 保存直线与边界线的交点
					m_point_cp_l_yz[3] = cl;
					m_point_cp_r_yz[3] = cr;
					// 画出直线
					cv::line(m_maskImg, cl, cr, m_maskColor, m_lineWidth);
					//进行测量和标注
					double l_l = 0, l_r = 0;
					l_l = m_dheight_scale * std::sqrt(std::pow(m_point_cp_l_yz[3].x - m_point_cp_l_yz[4].x, 2) + std::pow(m_point_cp_l_yz[3].y - m_point_cp_l_yz[4].y, 2));
					l_r = m_dheight_scale * std::sqrt(std::pow(m_point_cp_r_yz[3].x - m_point_cp_r_yz[4].x, 2) + std::pow(m_point_cp_r_yz[3].y - m_point_cp_r_yz[4].y, 2));
					char text_l[20], text_r[20];
					sprintf_s(text_l, "%.1lfmm", l_l);
					sprintf_s(text_r, "%.1lfmm", l_r);
					cv::Point center_l, center_r;
					center_l = cv::Point((m_point_cp_l_yz[3].x + m_point_cp_l_yz[4].x) / 2, (m_point_cp_l_yz[3].y + m_point_cp_l_yz[4].y) / 2);
					int baseline = 0;
					cv::Size sz_wh = cv::getTextSize(text_r, m_font_type_measure, m_dfont_scale_measure, m_font_thick_measure, &baseline);
					center_r = cv::Point((m_point_cp_r_yz[3].x + m_point_cp_r_yz[4].x) / 2, (m_point_cp_r_yz[3].y + m_point_cp_r_yz[4].y) / 2);
					center_r = cv::Point(center_r.x - sz_wh.width, center_r.y);
					cv::putText(m_maskImg, text_l, center_l, m_font_type_measure, m_dfont_scale_measure, m_maskColor, m_font_thick_measure);
					cv::putText(m_maskImg, text_r, center_r, m_font_type_measure, m_dfont_scale_measure, m_maskColor, m_font_thick_measure);
					m_curDiag_xie_yz = 4;
				}
				else if (m_curDiag_xie_yz == 4)
				{
					if (m_bHas_draw_yfc == false)		// 启动旋转判定步骤
					{
						if (m_rotateMethod == 0)
						{
							MessageBox(_T("请选择原发测判定方法。"));
							return;
						}
						drawYfc(pt);
						if (m_bHas_draw_yfc == false)
							return;
					}
					// 进行诊断
					m_strDiag_yz[3] = _T("3P");
					//1. 旋转判断
					if (m_strYfc == _T("R"))	// 棘突偏向右侧
					{
						m_strDiag_yz[3] = m_strDiag_yz[3] + _T("R");
					}
					else if (m_strYfc == _T("L"))  // 棘突偏向左侧
					{
						m_strDiag_yz[3] = m_strDiag_yz[3] + _T("L");
					}
					else if (m_strYfc == _T(""))	// 没有偏转
					{

					}
					//2. 切向楔形判断,接触点判断
					double lr = std::abs(l_l - l_r);
					if (lr >= m_dThres_xie_yz)		// 有侧向楔形
					{
						if (m_strYfc == _T("R"))
						{
							if (l_l < l_r)	//棘突偏向楔形开口侧
							{
								m_strDiag_yz[3] = m_strDiag_yz[3] + _T("S");
							}
							else
							{
								m_strDiag_yz[3] = m_strDiag_yz[3] + _T("I-M");
							}
						}
						else if (m_strYfc == _T("L"))
						{
							if (l_l > l_r)	//棘突偏向楔形开口侧
							{
								m_strDiag_yz[3] = m_strDiag_yz[3] + _T("S");
							}
							else
							{
								m_strDiag_yz[3] = m_strDiag_yz[3] + _T("I-M");
							}
						}
					}
					else                            // 无侧向楔形
					{
						if (m_strBend_yz == m_strYfc)
						{
							m_strDiag_yz[3] = m_strDiag_yz[3] + _T("-Sp");
						}
						else
						{
							m_strDiag_yz[3] = m_strDiag_yz[3] + _T("-M");
						}
					}
					// 放置诊断
					int baseline = 0;
					cv::Size sz_wh = cv::getTextSize(m_strDiag_yz[3].GetBuffer(), m_font_type_diag, m_font_scale_diag, m_font_thick_diag, &baseline);
					cv::Point center_d;
					center_d = cv::Point((m_gp[10].x + m_gp[11].x) / 2, (m_gp[10].y + m_gp[11].y) / 2);
					center_d = cv::Point(center_d.x - sz_wh.width / 2, center_d.y + sz_wh.height / 2);
					cv::putText(m_maskImg, m_strDiag_yz[3].GetBuffer(), center_d, m_font_type_diag, m_font_scale_diag, m_maskColor, m_font_thick_diag);
					// 进行下一个腰椎判定
					m_curDiag_xie_yz = 0;
					m_curDiag_yz = 0;
					m_total_lux_yz--;
					m_bHas_draw_yfc = false;
					if (m_bLuxs_yz[2] == true)
					{
						m_curDiag_yz = 2;
						m_curDiag_xie_yz = 2;
					}
					else
					{
						if (m_bLuxs_yz[1] == true)
						{
							m_curDiag_yz = 1;
							m_curDiag_xie_yz = 0;
						}
					}
				}
			}

			else if (m_curDiag_yz == 2 && m_bLuxs_yz[2] == true)
			{
				// L2腰椎
				double l_l = 0, l_r = 0;
				if (m_curDiag_xie_yz == 0)
				{
					m_gp[10] = pt;
					cv::circle(m_maskImg, m_gp[10], m_circleRadius, m_maskColor, -1);
					m_curDiag_xie_yz = 1;
				}
				else if (m_curDiag_xie_yz == 1)
				{
					// p[0~1] 直线两点
					// center[0~1] 直线两关键点
					m_gp[11] = pt;
					cv::circle(m_maskImg, m_gp[11], m_circleRadius, m_maskColor, -1);
					// 计算与左右边界直线交点
					cv::Point cl, cr;
					cl = intersect(m_gp[0], m_gp[1], m_gp[10], m_gp[11]);
					cr = intersect(m_gp[2], m_gp[3], m_gp[10], m_gp[11]);
					// 保存直线与边界线的交点
					m_point_cp_l_yz[3] = cl;
					m_point_cp_r_yz[3] = cr;
					// 画出直线
					cv::line(m_maskImg, cl, cr, m_maskColor, m_lineWidth);
					//写入操作
					m_curDiag_xie_yz = 2;
				}
				//  L3腰椎
				else if (m_curDiag_xie_yz == 2)
				{
					m_gp[12] = pt;
					cv::circle(m_maskImg, m_gp[12], m_circleRadius, m_maskColor, -1);
					m_curDiag_xie_yz = 3;
				}
				else if (m_curDiag_xie_yz == 3)
				{
					// p[0~1] 直线两点
					// center[0~1] 直线两关键点
					m_gp[13] = pt;
					cv::circle(m_maskImg, m_gp[13], m_circleRadius, m_maskColor, -1);
					// 计算与左右边界直线交点
					cv::Point cl, cr;
					cl = intersect(m_gp[0], m_gp[1], m_gp[12], m_gp[13]);
					cr = intersect(m_gp[2], m_gp[3], m_gp[12], m_gp[13]);
					// 保存直线与边界线的交点
					m_point_cp_l_yz[2] = cl;
					m_point_cp_r_yz[2] = cr;
					// 画出直线
					cv::line(m_maskImg, cl, cr, m_maskColor, m_lineWidth);
					//进行测量和标注
					double l_l = 0, l_r = 0;
					l_l = m_dheight_scale * std::sqrt(std::pow(m_point_cp_l_yz[2].x - m_point_cp_l_yz[3].x, 2) + std::pow(m_point_cp_l_yz[2].y - m_point_cp_l_yz[3].y, 2));
					l_r = m_dheight_scale * std::sqrt(std::pow(m_point_cp_r_yz[2].x - m_point_cp_r_yz[3].x, 2) + std::pow(m_point_cp_r_yz[2].y - m_point_cp_r_yz[3].y, 2));
					char text_l[20], text_r[20];
					sprintf_s(text_l, "%.1lfmm", l_l);
					sprintf_s(text_r, "%.1lfmm", l_r);
					cv::Point center_l, center_r;
					center_l = cv::Point((m_point_cp_l_yz[2].x + m_point_cp_l_yz[3].x) / 2, (m_point_cp_l_yz[2].y + m_point_cp_l_yz[3].y) / 2);
					int baseline = 0;
					cv::Size sz_wh = cv::getTextSize(text_r, m_font_type_measure, m_dfont_scale_measure, m_font_thick_measure, &baseline);
					center_r = cv::Point((m_point_cp_r_yz[2].x + m_point_cp_r_yz[3].x) / 2, (m_point_cp_r_yz[2].y + m_point_cp_r_yz[3].y) / 2);
					center_r = cv::Point(center_r.x - sz_wh.width, center_r.y);
					cv::putText(m_maskImg, text_l, center_l, m_font_type_measure, m_dfont_scale_measure, m_maskColor, m_font_thick_measure);
					cv::putText(m_maskImg, text_r, center_r, m_font_type_measure, m_dfont_scale_measure, m_maskColor, m_font_thick_measure);
					m_curDiag_xie_yz = 4;
				}
				else if (m_curDiag_xie_yz == 4)
				{
					if (m_bHas_draw_yfc == false)		// 启动旋转判定步骤
					{
						if (m_rotateMethod == 0)
						{
							MessageBox(_T("请选择原发测判定方法。"));
							return;
						}
						drawYfc(pt);
						if (m_bHas_draw_yfc == false)
							return;
					}
					// 进行诊断
					m_strDiag_yz[2] = _T("2P");
					//1. 旋转判断
					if (m_strYfc == _T("R"))	// 棘突偏向右侧
					{
						m_strDiag_yz[2] = m_strDiag_yz[2] + _T("R");
					}
					else if (m_strYfc == _T("L"))  // 棘突偏向左侧
					{
						m_strDiag_yz[2] = m_strDiag_yz[2] + _T("L");
					}
					else if (m_strYfc == _T(""))	// 没有偏转
					{

					}
					//2. 切向楔形判断,接触点判断
					double lr = std::abs(l_l - l_r);
					if (lr >= m_dThres_xie_yz)		// 有侧向楔形
					{
						if (m_strYfc == _T("R"))
						{
							if (l_l < l_r)	//棘突偏向楔形开口侧
							{
								m_strDiag_yz[2] = m_strDiag_yz[2] + _T("S");
							}
							else
							{
								m_strDiag_yz[2] = m_strDiag_yz[2] + _T("I-M");
							}
						}
						else if (m_strYfc == _T("L"))
						{
							if (l_l > l_r)	//棘突偏向楔形开口侧
							{
								m_strDiag_yz[2] = m_strDiag_yz[2] + _T("S");
							}
							else
							{
								m_strDiag_yz[2] = m_strDiag_yz[2] + _T("I-M");
							}
						}
					}
					else                            // 无侧向楔形
					{
						if (m_strBend_yz == m_strYfc)
						{
							m_strDiag_yz[2] = m_strDiag_yz[2] + _T("-Sp");
						}
						else
						{
							m_strDiag_yz[2] = m_strDiag_yz[2] + _T("-M");
						}
					}
					// 放置诊断
					int baseline = 0;
					cv::Size sz_wh = cv::getTextSize(m_strDiag_yz[2].GetBuffer(), m_font_type_diag, m_font_scale_diag, m_font_thick_diag, &baseline);
					cv::Point center_d;
					center_d = cv::Point((m_gp[12].x + m_gp[13].x) / 2, (m_gp[12].y + m_gp[13].y) / 2);
					center_d = cv::Point(center_d.x - sz_wh.width / 2, center_d.y + sz_wh.height / 2);
					cv::putText(m_maskImg, m_strDiag_yz[2].GetBuffer(), center_d, m_font_type_diag, m_font_scale_diag, m_maskColor, m_font_thick_diag);

					m_curDiag_xie_yz = 0;
					m_curDiag_yz = 0;
					m_total_lux_yz--;
					m_bHas_draw_yfc = false;
					if (m_bLuxs_yz[1] == true)
					{
						m_curDiag_yz = 1;
						m_curDiag_xie_yz = 2;
					}
					else
					{
						m_curDiag_yz = 0;
						m_curDiag_xie_yz = 0;
					}
				}
			}
			else if (m_curDiag_yz == 1 && m_bLuxs_yz[1] == true)
			{
				// L1腰椎
				double l_l = 0, l_r = 0;
				if (m_curDiag_xie_yz == 0)
				{
					m_gp[12] = pt;
					cv::circle(m_maskImg, m_gp[12], m_circleRadius, m_maskColor, -1);
					m_curDiag_xie_yz = 1;
				}
				else if (m_curDiag_xie_yz == 1)
				{
					// p[0~1] 直线两点
					// center[0~1] 直线两关键点
					m_gp[13] = pt;
					cv::circle(m_maskImg, m_gp[13], m_circleRadius, m_maskColor, -1);
					// 计算与左右边界直线交点
					cv::Point cl, cr;
					cl = intersect(m_gp[0], m_gp[1], m_gp[12], m_gp[13]);
					cr = intersect(m_gp[2], m_gp[3], m_gp[12], m_gp[13]);
					// 保存直线与边界线的交点
					m_point_cp_l_yz[2] = cl;
					m_point_cp_r_yz[2] = cr;
					// 画出直线
					cv::line(m_maskImg, cl, cr, m_maskColor, m_lineWidth);
					//写入操作
					m_curDiag_xie_yz = 2;
				}
				//  L1腰椎
				else if (m_curDiag_xie_yz == 2)
				{
					m_gp[14] = pt;
					cv::circle(m_maskImg, m_gp[14], m_circleRadius, m_maskColor, -1);
					m_curDiag_xie_yz = 3;
				}
				else if (m_curDiag_xie_yz == 3)
				{
					// p[0~1] 直线两点
					// center[0~1] 直线两关键点
					m_gp[15] = pt;
					cv::circle(m_maskImg, m_gp[15], m_circleRadius, m_maskColor, -1);
					// 计算与左右边界直线交点
					cv::Point cl, cr;
					cl = intersect(m_gp[0], m_gp[1], m_gp[14], m_gp[15]);
					cr = intersect(m_gp[2], m_gp[3], m_gp[14], m_gp[15]);
					// 保存直线与边界线的交点
					m_point_cp_l_yz[1] = cl;
					m_point_cp_r_yz[1] = cr;
					// 画出直线
					cv::line(m_maskImg, cl, cr, m_maskColor, m_lineWidth);
					//进行测量和标注
					double l_l = 0, l_r = 0;
					l_l = m_dheight_scale * std::sqrt(std::pow(m_point_cp_l_yz[1].x - m_point_cp_l_yz[2].x, 2) + std::pow(m_point_cp_l_yz[1].y - m_point_cp_l_yz[2].y, 2));
					l_r = m_dheight_scale * std::sqrt(std::pow(m_point_cp_r_yz[1].x - m_point_cp_r_yz[2].x, 2) + std::pow(m_point_cp_r_yz[1].y - m_point_cp_r_yz[2].y, 2));
					char text_l[20], text_r[20];
					sprintf_s(text_l, "%.1lfmm", l_l);
					sprintf_s(text_r, "%.1lfmm", l_r);
					cv::Point center_l, center_r;
					center_l = cv::Point((m_point_cp_l_yz[1].x + m_point_cp_l_yz[2].x) / 2, (m_point_cp_l_yz[1].y + m_point_cp_l_yz[2].y) / 2);
					int baseline = 0;
					cv::Size sz_wh = cv::getTextSize(text_r, m_font_type_measure, m_dfont_scale_measure, m_font_thick_measure, &baseline);
					center_r = cv::Point((m_point_cp_r_yz[1].x + m_point_cp_r_yz[2].x) / 2, (m_point_cp_r_yz[1].y + m_point_cp_r_yz[2].y) / 2);
					center_r = cv::Point(center_r.x - sz_wh.width, center_r.y);
					cv::putText(m_maskImg, text_l, center_l, m_font_type_measure, m_dfont_scale_measure, m_maskColor, m_font_thick_measure);
					cv::putText(m_maskImg, text_r, center_r, m_font_type_measure, m_dfont_scale_measure, m_maskColor, m_font_thick_measure);
					m_curDiag_xie_yz = 4;
				}
				else if (m_curDiag_xie_yz == 4)
				{
					if (m_bHas_draw_yfc == false)		// 启动旋转判定步骤
					{
						if (m_rotateMethod == 0)
						{
							MessageBox(_T("请选择原发测判定方法。"));
							return;
						}
						drawYfc(pt);
						if (m_bHas_draw_yfc == false)
							return;
					}
					// 进行诊断
					m_strDiag_yz[1] = _T("1P");
					//1. 旋转判断
					if (m_strYfc == _T("R"))	// 棘突偏向右侧
					{
						m_strDiag_yz[1] = m_strDiag_yz[1] + _T("R");
					}
					else if (m_strYfc == _T("L"))  // 棘突偏向左侧
					{
						m_strDiag_yz[1] = m_strDiag_yz[1] + _T("L");
					}
					else if (m_strYfc == _T(""))	// 没有偏转
					{

					}
					//2. 切向楔形判断,接触点判断
					double lr = std::abs(l_l - l_r);
					if (lr >= m_dThres_xie_yz)		// 有侧向楔形
					{
						if (m_strYfc == _T("R"))
						{
							if (l_l < l_r)	//棘突偏向楔形开口侧
							{
								m_strDiag_yz[1] = m_strDiag_yz[1] + _T("S");
							}
							else
							{
								m_strDiag_yz[1] = m_strDiag_yz[1] + _T("I-M");
							}
						}
						else if (m_strYfc == _T("L"))
						{
							if (l_l > l_r)	//棘突偏向楔形开口侧
							{
								m_strDiag_yz[1] = m_strDiag_yz[1] + _T("S");
							}
							else
							{
								m_strDiag_yz[1] = m_strDiag_yz[1] + _T("I-M");
							}
						}
					}
					else                            // 无侧向楔形
					{
						if (m_strBend_yz == m_strYfc)
						{
							m_strDiag_yz[1] = m_strDiag_yz[1] + _T("-Sp");
						}
						else
						{
							m_strDiag_yz[1] = m_strDiag_yz[1] + _T("-M");
						}
					}
					// 放置诊断
					int baseline = 0;
					cv::Size sz_wh = cv::getTextSize(m_strDiag_yz[1].GetBuffer(), m_font_type_diag, m_font_scale_diag, m_font_thick_diag, &baseline);
					cv::Point center_d;
					center_d = cv::Point((m_gp[14].x + m_gp[15].x) / 2, (m_gp[14].y + m_gp[15].y) / 2);
					center_d = cv::Point(center_d.x - sz_wh.width / 2, center_d.y + sz_wh.height / 2);
					cv::putText(m_maskImg, m_strDiag_yz[1].GetBuffer(), center_d, m_font_type_diag, m_font_scale_diag, m_maskColor, m_font_thick_diag);

					// 结束腰椎判定
					m_curDiag_xie_yz = 0;
					m_curDiag_yz = 0;
					m_total_lux_yz = 0;
					m_bHas_draw_yfc = false;
				}
			}
			//接触点判断
		}
	}
	// 四、 腰骶角诊断
else if (m_opType == DIAG_YZJ && m_curStep < 3)
	{
		// 水平线
		if (m_curStep == 0)
		{
			m_gp[0] = pt;
			// 画出直线
			cv::Point pl, pr;
			pl = cv::Point(m_srcImg.cols / 2, m_gp[0].y);
			pr = cv::Point(m_srcImg.cols, m_gp[0].y);
			cv::circle(m_maskImg, m_gp[0], m_circleRadius, m_maskColor, -1);
			cv::line(m_maskImg, pl, pr, m_maskColor, m_lineWidth);
			// 写入操作
			logInfo log = { 0 };
			log.p[0] = pl;
			log.p[1] = pr;
			log.center[0] = m_gp[0];
			log.op = DRAW_LINE;
			log.step = m_curStep;
			m_vecLog.push_back(log);

		}
		// 0、1 画测量线
		else if (m_curStep == 1)
		{
			m_gp[1] = pt;
			cv::circle(m_maskImg, m_gp[1], m_circleRadius, m_maskColor, -1);
		}
		else if (m_curStep == 2)
		{
			// p[0~1] 为直线两点， center[0~1]为画直线关键点
			// center[2]为测量角度文字放置点
			// text[0] 为测量角度文字
			m_gp[2] = pt;
			cv::circle(m_maskImg, m_gp[2], m_circleRadius, m_maskColor, -1);
			m_grad_yaozhuijiao_x = (m_gp[2].y - m_gp[1].y) / (m_gp[2].x - m_gp[1].x + 10e-8);
			// 画延长线
			cv::Point pl, pr;
			lineExt(m_grad_yaozhuijiao_x, m_gp[1], m_gp[1].x - m_srcImg.cols / 2, 0, m_p1, m_p2);
			pl = m_p1;
			lineExt(m_grad_yaozhuijiao_x, m_gp[2], 0, m_srcImg.rows - m_gp[2].y, m_p1, m_p2);
			pr = m_p2;
			// 画出直线
			cv::line(m_maskImg, pl, pr, m_maskColor, m_lineWidth);
			// 求交点
			cv::Point dot = intersect(m_gp[0], m_gp[1], pl, pr);
			// 求角度
			double theta = std::abs(180 * std::atan(m_grad_yaozhuijiao_x)/3.1415926);
			// 放置测量角度
			cv::Point center = cv::Point((m_srcImg.cols + dot.x) / 2, (dot.y + pr.y) / 2);
			char text[20] = { 0 };
			sprintf_s(text, "%.1f", theta);
			cv::putText(m_maskImg, text, center, m_font_type_measure, m_dfont_scale_measure, m_maskColor, m_font_thick_measure);
			// 保存操作
			logInfo log = { 0 };
			log.p[0] = pl;
			log.p[1] = pr;
			log.center[0] = m_gp[1];
			log.center[1] = m_gp[2];
			log.center[2] = center;
			log.length[0] = theta;
			memcpy(log.text[0], text, 20);
			log.op = DRAW_DIAGNOSE;
			log.step = m_curStep;
			m_vecLog.push_back(log);
		}
		++m_curStep;
		m_bNeedSave = true;
		//有新操作后就不能再返回了
		cv::vector<logInfo>().swap(m_vecDelLog);
		remindColor();
	}
	// 五、胸椎诊断
	// 与腰椎绝大部分相同，不同之处在与右边测量值得放置位置需要调整
else if (m_opType == DIAG_XZ)
{
	// 先确定左右直线边界
	// 0、1左边界
	if (m_curStep == 0)
	{
		m_gp[0] = pt;
		cv::circle(m_maskImg, m_gp[0], m_circleRadius, m_maskColor, -1);
		m_curStep++;
	}
	else if (m_curStep == 1)
	{
		m_gp[1] = pt;
		cv::circle(m_maskImg, m_gp[1], m_circleRadius, m_maskColor, -1);
		cv::line(m_maskImg, m_gp[0], m_gp[1], m_maskColor, m_lineWidth);
		//计算直线斜率和偏置
		m_dGrad_bj_xz[0] = (m_gp[1].y - m_gp[0].y) / (m_gp[1].x - m_gp[0].x + 10e-8);
		m_dBias_bj_xz[0] = ((m_gp[1].y + m_gp[0].y) - m_dGrad_bj_xz[0] * (m_gp[1].x + m_gp[0].x)) / 2;
		//写入操作

		m_curStep++;
	}
	// 2、3右边界
	else if (m_curStep == 2)
	{
		m_gp[2] = pt;
		cv::circle(m_maskImg, m_gp[2], m_circleRadius, m_maskColor, -1);
		m_curStep++;
	}
	else if (m_curStep == 3)
	{
		m_gp[3] = pt;
		cv::circle(m_maskImg, m_gp[3], m_circleRadius, m_maskColor, -1);
		cv::line(m_maskImg, m_gp[3], m_gp[2], m_maskColor, m_lineWidth);
		//计算直线斜率和偏置
		m_dGrad_bj_xz[1] = (m_gp[3].y - m_gp[2].y) / (m_gp[3].x - m_gp[2].x + 10e-8);
		m_dBias_bj_xz[1] = ((m_gp[3].y + m_gp[2].y) - m_dGrad_bj_xz[1] * (m_gp[3].x + m_gp[2].x)) / 2;
		//下一步
		m_curStep++;
		m_curDiag_xie_xz = 0;
	}
	else if ((m_curStep >= 4 && m_curStep <= 3 + 2 * 12 +1) || (m_curStep >= 3 + 2 * 12 + 1 && m_bHas_more_xz_xz == true) || (m_curStep >= 3 + 2 * 12 + 1 && m_bDraw_L1_xz == true))	//正常12胸椎,多有胸椎，L1腰椎
	{
		// T1~T12，提示是否多有腰椎？看情况决定什么时候做做L1。
		if (m_curDiag_xie_xz == 0)		// 胸椎直线点1
		{
			m_gp[m_curStep] = pt;
			cv::circle(m_maskImg, m_gp[m_curStep], m_circleRadius, m_maskColor, -1);
			m_curStep++;
			m_curDiag_xie_xz = 1;
		}
		else if(m_curDiag_xie_xz == 1)  // 胸椎直线点2
		{
			m_gp[m_curStep] = pt;
			// 计算与左右边界直线交点
			cv::Point cl, cr;
			cl = intersect(m_gp[0], m_gp[1], m_gp[m_curStep - 1], m_gp[m_curStep]);
			cr = intersect(m_gp[2], m_gp[3], m_gp[m_curStep - 1], m_gp[m_curStep]);
			// 保存直线与边界线的交点(下缀1~12)
			m_point_cp_l_xz[(m_curStep-3)/2] = cl;
			m_point_cp_r_xz[(m_curStep - 3) / 2] = cr;
			// 画出直线
			cv::circle(m_maskImg, m_gp[m_curStep], m_circleRadius, m_maskColor, -1);
			cv::line(m_maskImg, cl, cr, m_maskColor, m_lineWidth);
			// 测量，保存楔形诊断
			if (m_curStep >= 7)// 大于等于7，证明这条线至少是第二胸椎
			{
				double l_l = 0, l_r = 0;
				l_l = m_dheight_scale * std::sqrt(std::pow(m_point_cp_l_xz[(m_curStep - 5) / 2].x - m_point_cp_l_xz[(m_curStep - 3) / 2].x, 2) + std::pow(m_point_cp_l_xz[(m_curStep - 5) / 2].y - m_point_cp_l_xz[(m_curStep - 3) / 2].y, 2));
				l_r = m_dheight_scale * std::sqrt(std::pow(m_point_cp_r_xz[(m_curStep - 5) / 2].x - m_point_cp_r_xz[(m_curStep - 3) / 2].x, 2) + std::pow(m_point_cp_r_xz[(m_curStep - 5) / 2].y - m_point_cp_r_xz[(m_curStep - 3) / 2].y, 2));
				char text_l[20], text_r[20];
				sprintf_s(text_l, "%.1lfmm", l_l);
				sprintf_s(text_r, "%.1lfmm", l_r);
				cv::Point center_l, center_r;
				center_l = cv::Point((m_point_cp_l_xz[(m_curStep - 5) / 2].x + m_point_cp_l_xz[(m_curStep - 3) / 2].x) / 2, (m_point_cp_l_xz[(m_curStep - 5) / 2].y + m_point_cp_l_xz[(m_curStep - 3) / 2].y) / 2);
				int baseline = 0;
				cv::Size sz_wh = cv::getTextSize(text_r, m_font_type_measure, m_dfont_scale_measure, m_font_thick_measure, &baseline);
				center_r = cv::Point((m_point_cp_r_xz[(m_curStep - 5) / 2].x + m_point_cp_r_xz[(m_curStep - 3) / 2].x) / 2, (m_point_cp_r_xz[(m_curStep - 5) / 2].y + m_point_cp_r_xz[(m_curStep - 3) / 2].y) / 2);
				center_r = cv::Point(center_r.x - sz_wh.width, center_r.y);
				cv::putText(m_maskImg, text_l, center_l, m_font_type_measure, m_dfont_scale_measure, m_maskColor, m_font_thick_measure);
				cv::putText(m_maskImg, text_r, center_r, m_font_type_measure, m_dfont_scale_measure, m_maskColor, m_font_thick_measure);
				// 楔形开口诊断，T1胸椎以T2胸椎为基准，T2以T3为基准，依此类推，直到T12以L1腰椎为基准 
				double delta_xie = std::abs(l_l - l_r);
				if (delta_xie > m_dThres_xie_xz)
				{
					if (l_l < l_r)
						m_strXie_xz[(m_curStep - 5) / 2] = _T("R");
					else
						m_strXie_xz[(m_curStep - 5) / 2] = _T("L");
				}
				else
					m_strXie_xz[(m_curStep - 5) / 2] = _T("");
			}
			// 下一胸椎
			m_curStep++;
			if (m_bDraw_L1_xz == true)	// 是画L1腰椎时，则不用进行原发测判断，并诊断，否则进行原发测判断
			{
				m_curDiag_xie_xz = 0;
				m_bDraw_L1_xz = false;		// 重置，结束划线
				// 进行诊断
				diagXz();

			}
			else m_curDiag_xie_xz = 2;
		}
		// 原发测判断
		else if(m_curDiag_xie_xz == 2)
		{
			// 原发测判断
			if (m_bHas_draw_yfc == false)		// 启动原发测判定步骤
			{
				if (m_rotateMethod == 0)
				{
					MessageBox(_T("请选择原发测判定方法。"));
					return;
				}
				drawYfc(pt);
				if (m_bHas_draw_yfc == false)
					return;
			}
			m_bHas_draw_yfc = false;
			// 当前所画胸椎的原发测
			m_strYfc_xz[(m_curStep - 3) / 2] = m_strYfc;
			m_curDiag_xie_xz = 0;
			m_total_xz++;//总胸椎数
			if (m_curStep >= 3 + 12 * 2 + 1 && m_curStep % 2 == 0 && m_bDraw_L1_xz == false)
			{
				Invalidate();
				INT_PTR ret = MessageBox(_T("12条胸椎已全部画完，如果有超过12条胸椎，请选择是否继续画多出的胸椎？"), _T("提示"), MB_YESNO);
				if (ret == IDYES)
				{
					// 继续执行
					m_bHas_more_xz_xz = true;
				}
				else
				{
					m_bHas_more_xz_xz = false;
					m_bDraw_L1_xz = true;
				}
			}
		} // m_curDiag_xie_xz == 2

		
	}// m_curStep>3

}















	// 六、颈椎
	//*
	else if (m_opType == DIAG_JZ)
	{
		// 先确定左右直线边界
		// 0、1左边界
		if (m_curStep == 0)
		{
			m_gp[19] = pt;
			cv::circle(m_maskImg, m_gp[19], m_circleRadius, m_maskColor, -1);
			m_curStep++;
		}
		else if (m_curStep == 1)
		{
			m_gp[18] = pt;
			cv::circle(m_maskImg, m_gp[18], m_circleRadius, m_maskColor, -1);
			cv::line(m_maskImg, m_gp[19], m_gp[18], m_maskColor, m_lineWidth);
			//计算直线斜率和偏置
			m_dGrad_bj_jz[0] = (m_gp[18].y - m_gp[19].y) / (m_gp[18].x - m_gp[19].x + 10e-8);
			m_dBias_bj_jz[0] = ((m_gp[18].y + m_gp[19].y) - m_dGrad_bj_jz[0] * (m_gp[18].x + m_gp[19].x)) / 2;
			//写入操作
			m_curStep++;
		}
		// 2、3右边界
		else if (m_curStep == 2)
		{
			m_gp[17] = pt;
			cv::circle(m_maskImg, m_gp[17], m_circleRadius, m_maskColor, -1);
			m_curStep++;
		}
		else if (m_curStep == 3)
		{
			m_gp[16] = pt;
			cv::circle(m_maskImg, m_gp[16], m_circleRadius, m_maskColor, -1);
			cv::line(m_maskImg, m_gp[16], m_gp[17], m_maskColor, m_lineWidth);
			//计算直线斜率和偏置
			m_dGrad_bj_jz[1] = (m_gp[16].y - m_gp[17].y) / (m_gp[16].x - m_gp[17].x + 10e-8);
			m_dBias_bj_jz[1] = ((m_gp[16].y + m_gp[17].y) - m_dGrad_bj_jz[1] * (m_gp[16].x + m_gp[17].x)) / 2;
			//写入操作
			m_curStep++;
			m_curDiag_jz = 7;// 当前正在诊断的颈椎
			m_total_lux_jz = 7;
			m_curDiag_step_jz = 0;
		}
		else if (m_curStep > 3)
		{
			if (m_total_lux_jz == 0)
			{
				// 处理完成
				return;
			}
			if (m_curDiag_jz > 0)
			{
				if (m_curDiag_step_jz == 0)
				{
					m_gp[2 * m_curDiag_jz] = pt;
					cv::circle(m_maskImg, m_gp[2 * m_curDiag_jz], m_circleRadius, m_maskColor, -1);
					m_curDiag_step_jz = 1;
				}
				else if (m_curDiag_step_jz == 1)
				{
					// p[0~1] 直线两点
					// center[0~1] 直线两关键点
					m_gp[2 * m_curDiag_jz + 1] = pt;
					// 计算与左右边界直线交点
					cv::Point cl, cr;
					cl = intersect(m_gp[18], m_gp[19], m_gp[2 * m_curDiag_jz], m_gp[2 * m_curDiag_jz + 1]);
					cr = intersect(m_gp[16], m_gp[17], m_gp[2 * m_curDiag_jz], m_gp[2 * m_curDiag_jz + 1]);
					// 保存直线与边界线的交点
					m_point_cp_l_jz[m_curDiag_jz + 1] = cl;
					m_point_cp_r_jz[m_curDiag_jz + 1] = cr;
					// 画出直线
					cv::circle(m_maskImg, m_gp[2 * m_curDiag_jz + 1], m_circleRadius, m_maskColor, -1);
					cv::line(m_maskImg, cl, cr, m_maskColor, m_lineWidth);
					//写入操作
					m_curDiag_step_jz = 2;
				}
				// 颈椎
				else if (m_curDiag_step_jz == 2)
				{
					m_gp[2 * m_curDiag_jz - 2] = pt;
					cv::circle(m_maskImg, m_gp[2 * m_curDiag_jz - 2], m_circleRadius, m_maskColor, -1);
					m_curDiag_step_jz = 3;
				}
				else if (m_curDiag_step_jz == 3)
				{
					m_gp[2 * m_curDiag_jz - 1] = pt;
					// 计算与左右边界直线交点
					cv::Point cl, cr;
					cl = intersect(m_gp[19], m_gp[18], m_gp[2 * m_curDiag_jz - 2], m_gp[2 * m_curDiag_jz - 1]);
					cr = intersect(m_gp[17], m_gp[16], m_gp[2 * m_curDiag_jz - 2], m_gp[2 * m_curDiag_jz - 1]);
					// 保存直线与边界线的交点
					m_point_cp_l_jz[m_curDiag_jz] = cl;
					m_point_cp_r_jz[m_curDiag_jz] = cr;
					// 画出直线
					cv::circle(m_maskImg, m_gp[2 * m_curDiag_jz - 1], m_circleRadius, m_maskColor, -1);
					cv::line(m_maskImg, cl, cr, m_maskColor, m_lineWidth);
					// 诊断和标注
					//进行测量和标注
					double l_l = 0, l_r = 0;
					l_l = m_dheight_scale * std::sqrt(std::pow(m_point_cp_l_jz[m_curDiag_jz].x - m_point_cp_l_jz[m_curDiag_jz + 1].x, 2) + std::pow(m_point_cp_l_jz[m_curDiag_jz].y - m_point_cp_l_jz[m_curDiag_jz + 1].y, 2));
					l_r = m_dheight_scale * std::sqrt(std::pow(m_point_cp_r_jz[m_curDiag_jz].x - m_point_cp_r_jz[m_curDiag_jz + 1].x, 2) + std::pow(m_point_cp_r_jz[m_curDiag_jz].y - m_point_cp_r_jz[m_curDiag_jz + 1].y, 2));
					char text_l[20], text_r[20];
					sprintf_s(text_l, "%.1lfmm", l_l);
					sprintf_s(text_r, "%.1lfmm", l_r);
					cv::Point center_l, center_r;
					center_l = cv::Point((m_point_cp_l_jz[m_curDiag_jz].x + m_point_cp_l_jz[m_curDiag_jz + 1].x) / 2, (m_point_cp_l_jz[m_curDiag_jz].y + m_point_cp_l_jz[m_curDiag_jz + 1].y) / 2);
					int baseline = 0;
					cv::Size sz_wh = cv::getTextSize(text_r, m_font_type_measure, m_dfont_scale_measure, m_font_thick_measure, &baseline);
					center_r = cv::Point((m_point_cp_r_jz[m_curDiag_jz].x + m_point_cp_r_jz[m_curDiag_jz + 1].x) / 2, (m_point_cp_r_jz[m_curDiag_jz].y + m_point_cp_r_jz[m_curDiag_jz + 1].y) / 2);
					center_r = cv::Point(center_r.x - sz_wh.width, center_r.y);
					cv::putText(m_maskImg, text_l, center_l, m_font_type_measure, m_dfont_scale_measure, m_maskColor, m_font_thick_measure);
					cv::putText(m_maskImg, text_r, center_r, m_font_type_measure, m_dfont_scale_measure, m_maskColor, m_font_thick_measure);
					// 进行诊断

					// 开始下一颈椎
					m_curDiag_jz--;
					m_curDiag_step_jz = 2;
					m_bHas_draw_yfc = false;
					m_total_lux_jz--;
				}
			}
		}
	}
	/**/
	// 七、 寰椎
	else if (m_opType == DIAG_HZ && m_curStep < 30)
	{
		// 先确定左右直线边界
		// 0、1左边界
		if (m_curStep == 0)
		{
			m_gp[0] = pt;
			cv::circle(m_maskImg, m_gp[0], m_circleRadius, m_maskColor, -1);
			m_curStep++;
		}
		else if (m_curStep == 1)
		{
			m_gp[1] = pt;
			cv::circle(m_maskImg, m_gp[1], m_circleRadius, m_maskColor, -1);
			cv::line(m_maskImg, m_gp[0], m_gp[1], m_maskColor, m_lineWidth);
			//计算直线斜率和偏置
			m_dGrad_bj_hz[0] = (m_gp[1].y - m_gp[0].y) / (m_gp[1].x - m_gp[0].x + 10e-8);
			m_dBias_bj_hz[0] = ((m_gp[1].y + m_gp[0].y) - m_dGrad_bj_hz[0] * (m_gp[1].x + m_gp[0].x)) / 2;
			//写入操作

			m_curStep++;
		}
		// 2、3右边界
		else if (m_curStep == 2)
		{
			m_gp[2] = pt;
			cv::circle(m_maskImg, m_gp[2], m_circleRadius, m_maskColor, -1);
			m_curStep++;
		}
		else if (m_curStep == 3)
		{
			m_gp[3] = pt;
			cv::circle(m_maskImg, m_gp[3], m_circleRadius, m_maskColor, -1);
			cv::line(m_maskImg, m_gp[3], m_gp[2], m_maskColor, m_lineWidth);
			//计算直线斜率和偏置
			m_dGrad_bj_xz[1] = (m_gp[3].y - m_gp[2].y) / (m_gp[3].x - m_gp[2].x + 10e-8);
			m_dBias_bj_xz[1] = ((m_gp[3].y + m_gp[2].y) - m_dGrad_bj_xz[1] * (m_gp[3].x + m_gp[2].x)) / 2;
			//写入操作
			m_curStep++;
		}
		// 4,5 齿状突线
		else if (m_curStep == 4)
		{
			m_gp[4] = pt;
			cv::circle(m_maskImg, m_gp[4], m_circleRadius, m_maskColor, -1);
			m_curStep++;
		}
		else if (m_curStep == 5)
		{
			m_gp[5] = pt;
			cv::circle(m_maskImg, m_gp[5], m_circleRadius, m_maskColor, -1);
			//计算直线斜率和偏置
			m_dGrad_czt_hz = (m_gp[5].y - m_gp[4].y) / (m_gp[5].x - m_gp[4].x + 10e-8);
			m_dBias_czt_hz = ((m_gp[5].y + m_gp[4].y) - m_dGrad_bj_hz[0] * (m_gp[5].x + m_gp[4].x)) / 2;

			// 齿状突线延长线
			cv::Point pt, pb;
			lineExt(m_dGrad_czt_hz, m_gp[4], abs(m_gp[5].y - m_gp[4].y), 0, m_p1, m_p2);
			pt = m_p1;
			lineExt(m_dGrad_czt_hz, m_gp[5], 0,abs(m_gp[5].y - m_gp[4].y), m_p1, m_p2);
			pb = m_p2;
			cv::line(m_maskImg, pt, pb, m_maskColor, m_lineWidth);
			//写入操作
			m_curStep++;
		}
		// 6. 齿状突垂直线
		else if (m_curStep == 6)
		{
			// m_gp[6]和pd组成齿状突垂直线
			m_gp[6] = pt;
			cv::Point pd;
			pd = lineCrossDot(m_dGrad_czt_hz, m_gp[4], m_gp[6]);
			// 计算与左右边界直线交点
			cv::Point cl, cr;
			cl = intersect(m_gp[0], m_gp[1], m_gp[6], pd);
			cr = intersect(m_gp[2], m_gp[3], m_gp[6], pd);
			m_point_cp_l_hz[0] = cl;
			m_point_cp_r_hz[0] = cr;
			cv::line(m_maskImg, cl, cr, m_maskColor, m_lineWidth);
			m_curStep++;
		}
		// 7,8 寰椎前-后平面线
		else if(m_curStep == 7)
		{
			m_gp[7] = pt;
			cv::circle(m_maskImg, m_gp[7], m_circleRadius, m_maskColor, -1);
			m_curStep++;
		}
		else if (m_curStep == 8)
		{
			if (m_bHas_draw_step8 == false)
			{
				m_gp[8] = pt;
				cv::Point cl, cr;
				cl = intersect(m_gp[0], m_gp[1], m_gp[7], m_gp[8]);
				cr = intersect(m_gp[2], m_gp[3], m_gp[7], m_gp[8]);
				m_point_cp_l_hz[1] = cl;
				m_point_cp_r_hz[1] = cr;
				cv::line(m_maskImg, cl, cr, m_maskColor, m_lineWidth);

				m_bHas_draw_step8 = true;
				// 载入颈椎张口CT
				m_jzzcImg = m_srcImg.clone();
				m_bNeedSave = false;
				Invalidate();
			}
			MessageBox(_T("请载入颈椎张口位片"));
			CFileDialog dlg(
				TRUE, NULL,//_T("*.bmp|*.jpeg"),
				NULL,
				OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
				NULL,//_T("image files (*.bmp; *.jpg;*.png) |*.bmp; *.jpg;*.jpeg;*.jge;*.png; ||"),
				NULL
			);                                        // 选项图片的约定
			dlg.m_ofn.lpstrTitle = _T("Open Image");    // 打开文件对话框的标题名
			if (dlg.DoModal() != IDOK)                    // 判断是否获得图片
				return;
			CString mPath = dlg.GetPathName();            // 获取图片路径
			char *ptxtTemp = mPath.GetBuffer(mPath.GetLength()); //文件完整路径
			CString fileExt = dlg.GetFileExt();// 文件后缀名
			if (fileExt == _T("png") || fileExt == _T("jpg") || fileExt == _T("bmp"))
			{
				m_loadImg = imread(ptxtTemp, CV_LOAD_IMAGE_UNCHANGED);    // 读取图片
			}
			else
			{
				bool ret = dcm2Mat(ptxtTemp, m_loadImg);
				if (!ret)
				{
					MessageBox(_T("载入图像失败，请检查文件的合法性！"));
					return;
				}
			}
			if (m_loadImg.empty())                                    // 判断是否成功载入图片
				return;
			m_srcImg = m_loadImg.clone(); // 为什么这么用，看头文件
			m_zoomImg = m_loadImg.clone();

			m_maskImg.create(m_srcImg.size(), CV_8UC1); // 掩膜图像
			m_maskShowImg.create(m_srcImg.size(), CV_8UC1); // 内部temp掩膜图像
			m_maskImg.setTo(0);
			m_maskShowImg.setTo(0);
			Invalidate();
			// 新边界线
			m_point_jzzk_bj_lt = cv::Point(0, 0);
			m_point_jzzk_bj_lb = cv::Point(0, m_srcImg.rows);
			m_point_jzzk_bj_rt = cv::Point(m_srcImg.cols, 0);
			m_point_jzzk_bj_rb = cv::Point(m_srcImg.cols, m_srcImg.rows);

			// 默认载入17*14图像
			double w, h; //实际尺寸(mm或英寸)
			w = 17 * 25.4;
			h = 14 * 25.4;
			m_dwidth_scale = w / m_srcImg.cols;
			m_dheight_scale = h / m_srcImg.rows;
			// 允许调整尺寸
			GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);
			m_ctrlHint.SetWindowText(_T("请选择操作类型！"));

			// 步骤前进
			m_curStep++;
			m_bHas_draw_step8 = false;// 因可能会用到撤销或重做
		}
		// 9,10寰椎平面线
		else if (m_curStep == 9)
		{
			m_gp[9] = pt;
			cv::circle(m_maskImg, m_gp[9], m_circleRadius, m_maskColor, -1);
			m_curStep++;
		}
		else if (m_curStep == 10)
		{
			m_gp[10] = pt;
			// 计算与左右边界直线交点
			cv::Point cl, cr;
			cl = intersect(m_point_jzzk_bj_lt, m_point_jzzk_bj_lb, m_gp[9], m_gp[10]);
			cr = intersect(m_point_jzzk_bj_rt, m_point_jzzk_bj_rb, m_gp[9], m_gp[10]);
			m_point_cp_l_hz[2] = cl;
			m_point_cp_r_hz[2] = cr;
			cv::line(m_maskImg, cl, cr, m_maskColor, m_lineWidth);
			m_curStep++;
		}
		// 11,12寰椎横贯平面线
		else if (m_curStep == 11)
		{
			m_gp[11] = pt;
			cv::circle(m_maskImg, m_gp[11], m_circleRadius, m_maskColor, -1);
			m_curStep++;
		}
		else if (m_curStep == 12)
		{
			m_gp[12] = pt;
			// 计算与左右边界直线交点
			cv::Point cl, cr;
			cl = intersect(m_point_jzzk_bj_lt, m_point_jzzk_bj_lb, m_gp[11], m_gp[12]);
			cr = intersect(m_point_jzzk_bj_rt, m_point_jzzk_bj_rb, m_gp[11], m_gp[12]);
			m_point_cp_l_hz[3] = cl;
			m_point_cp_r_hz[3] = cr;
			cv::line(m_maskImg, cl, cr, m_maskColor, m_lineWidth);
			m_curStep++;
		}
		// 13,14枕骨髁线
		else if(m_curStep == 13)
		{
			m_gp[13] = pt;
			cv::circle(m_maskImg, m_gp[13], m_circleRadius, m_maskColor, -1);
			m_curStep++;
		}
		else if (m_curStep == 14)
		{
			m_gp[14] = pt;
			// 计算与左右边界直线交点
			cv::Point cl, cr;
			cl = intersect(m_point_jzzk_bj_lt, m_point_jzzk_bj_lb, m_gp[13], m_gp[14]);
			cr = intersect(m_point_jzzk_bj_rt, m_point_jzzk_bj_rb, m_gp[13], m_gp[14]);
			m_point_cp_l_hz[4] = cl;
			m_point_cp_r_hz[4] = cr;
			cv::line(m_maskImg, cl, cr, m_maskColor, m_lineWidth);
			m_curStep++;
		}
		// 旋转判断

	}      
	Invalidate();
	CDialogEx::OnLButtonUp(nFlags, point);
}
// 撤销
void CchiropracticDlg::OnBnClickedButton8()
{
//	// TODO: 在此添加控件通知处理程序代码
//	changeCtrlBtn(IDC_BUTTON8);
//	if (m_vecLog.size() == 0) return;
//	m_maskImg.setTo(0);
//	m_maskShowImg.setTo(0);
//	// 零、手动测量
//	if (m_opType == DRAW_MEASURE)
//	{
//		logInfo log = { 0 };
//		log = m_vecLog.back();
//		m_vecDelLog.push_back(log);
//		m_vecLog.pop_back();
//
//		for (vector<logInfo>::iterator it = m_vecLog.begin(); it != m_vecLog.end(); ++it)
//		{
//			logInfo log = *it;
//			cv::circle(m_maskImg, log.p[0], m_circleRadius, m_maskColor, -1);
//			cv::circle(m_maskImg, log.p[1], m_circleRadius, m_maskColor, -1);
//			cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
//			cv::putText(m_maskImg, log.text[0], log.center[0], m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_maskColor, m_fontThicknessOfMeasure);
//		}
//	}
//	// 一、髂骨诊断
//	else if (m_opType == DIAG_QG)
//	{
//		logInfo log = { 0 };
//		log = m_vecLog.back();
//		m_vecDelLog.push_back(log);
//		m_vecLog.pop_back();
//
//		if (log.step == 1)		// 是股骨头线，撤销这条线，当前操作要回0步
//			m_curStep = 0;
//		else
//			--m_curStep;
//		//重画
//		for (vector<logInfo>::iterator it = m_vecLog.begin(); it != m_vecLog.end(); ++it)
//		{
//			logInfo log = *it;
//			if (log.op == DRAW_DIAGNOSE)
//			{
//				cv::circle(m_maskImg, log.p[0], m_circleRadius, m_circleColor, -1);
//				cv::circle(m_maskImg, log.p[1], m_circleRadius, m_circleColor, -1);
//				cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
//				cv::putText(m_maskImg, log.text[0], log.center[0], m_fontTypeOfDiagnose, m_dFontSizeOfDiagnose, m_maskColor);
//			}
//			else if (log.op == DRAW_LINE)
//			{
//				if (log.step == 1 || log.step == 9)	// 股骨头线、下关节突的关键点与其他不同
//				{
//					cv::circle(m_maskImg, log.p[0], m_circleRadius, m_maskColor, -1);
//					cv::circle(m_maskImg, log.p[1], m_circleRadius, m_maskColor, -1);
//				}
//				else
//					cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
//				cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
//			}
//			else if (log.op == DRAW_LINE_MEASURE)
//			{
//				cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
//				cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
//				cv::line(m_maskImg, log.p[2], log.p[3], m_maskColor, m_lineWidth);
//				cv::putText(m_maskImg, log.text[0], log.center[1], m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_maskColor);
//			}
//			else if (log.op == DRAW_CIRCLE)
//			{
//				cv::circle(m_maskImg, log.center[1], m_circleRadius, m_maskColor, -1);
//			}
//		}
//	}
//	// 二、骶骨诊断
//	else if (m_opType == DIAG_DG)
//	{
//		logInfo log = { 0 };
//		log = m_vecLog.back();
//		m_vecDelLog.push_back(log);
//		m_vecLog.pop_back();
//		if (log.step == 1 || log.step == 4)
//			m_curStep -= 2;
//		else
//			--m_curStep;
//		//重画
//		for (vector<logInfo>::iterator it = m_vecLog.begin(); it != m_vecLog.end(); ++it)
//		{
//			logInfo log = *it;
//			if (log.op == DRAW_DIAGNOSE)
//			{
//				cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
//				cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
//				cv::line(m_maskImg, log.p[2], log.p[3], m_maskColor, m_lineWidth);
//				cv::putText(m_maskImg, log.text[0], log.center[1], m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_maskColor, m_fontThicknessOfMeasure);
//				cv::putText(m_maskImg, log.text[1], log.center[2], m_fontTypeOfDiagnose, m_dFontSizeOfDiagnose, m_maskColor,m_fontThicknessOfDiagnose);
//
//			}
//			else if (log.op == DRAW_LINE_MEASURE)
//			{
//				// 两条垂直线
//				cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
//				cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
//				cv::line(m_maskImg, log.p[2], log.p[3], m_maskColor, m_lineWidth);
//				cv::putText(m_maskImg, log.text[0], log.center[1], m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_maskColor, m_fontThicknessOfMeasure);
//			}
//			else if (log.op == DRAW_DIGU_LINE)
//			{
//				// 画出骶骨水平线和点
//				cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
//				cv::circle(m_maskImg, log.center[1], m_circleRadius, m_maskColor, -1);
//				cv::line(m_maskImg, log.p[0], log.p[1], m_lineColor, m_lineWidth);
//				//画出骶骨水平线的垂直线
//				cv::line(m_maskImg, log.p[2], log.p[3], m_lineColor, m_lineWidth);
//				// 画出股骨头线的平行线
//				cv::line(m_maskImg, log.p[4], log.p[5], m_maskColor, m_lineWidth);
//				// 画出垂直股骨头平行线的垂线
//				cv::line(m_maskImg, log.p[6], log.p[7], m_maskColor, m_lineWidth);
//				// 标注长度
//				cv::putText(m_maskImg, log.text[0], log.center[2], m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_maskColor, m_fontThicknessOfMeasure);
//			}
//			else if (log.op == DRAW_LINE)
//			{
//				if (log.step == 1)
//				{
//					// 股骨头线
//					cv::circle(m_maskImg, log.p[0], m_circleRadius, m_maskColor, -1);
//					cv::circle(m_maskImg, log.p[1], m_circleRadius, m_maskColor, -1);
//					cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
//				}
//				else
//				{
//					// 股骨头线垂直线
//					cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
//					cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
//				}
//			}
//
//			else if (log.op == DRAW_CIRCLE)
//			{
//				cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
//			}
//		}
//	}
//	// 三、 腰椎诊断
//	else if (m_opType == DIAG_YZ)
//	{
//		logInfo log = { 0 };
//		log = m_vecLog.back();
//		m_vecDelLog.push_back(log);
//		m_vecLog.pop_back();
//		// 保存的也需要回滚
//		std::vector<cv::Point> p;
//		std::vector<double> length;
//		if (m_point_cp_l_yz.size() != 0)
//		{
//			p = m_point_cp_l_yz.back();
//			m_vecCpPointDel_yaozhui.push_back(p);
//			m_point_cp_l_yz.pop_back();
//		}
//		if (m_vecMeasure_yaozhui.size() != 0)
//		{
//			length = m_vecMeasure_yaozhui.back();
//			m_vecMeasureDel_yaozhui.push_back(length);
//			m_vecMeasure_yaozhui.pop_back();
//		}	
//		// 当前步骤回滚两步
//		m_curStep -= 2;
//		//重画
//		for (vector<logInfo>::iterator it = m_vecLog.begin(); it != m_vecLog.end(); ++it)
//		{
//			logInfo log = *it;
//			if (log.op == DRAW_LINE)
//			{
//				cv::circle(m_maskImg, log.p[0], m_circleRadius, m_maskColor, -1);
//				cv::circle(m_maskImg, log.p[1], m_circleRadius, m_maskColor, -1);
//				cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
//			}
//			else if (log.op == DRAW_BASE_LINE)
//			{
//				cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
//				cv::circle(m_maskImg, log.center[1], m_circleRadius, m_maskColor, -1);
//				cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
//			}
//			else if (log.op == DRAW_YAOZHUI_MEASURE)
//			{
//				cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
//				cv::circle(m_maskImg, log.center[1], m_circleRadius, m_maskColor, -1);
//				cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
//				cv::putText(m_maskImg, log.text[0], log.center[2], m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_maskColor, m_fontThicknessOfMeasure);
//				cv::putText(m_maskImg, log.text[1], log.center[3], m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_maskColor, m_fontThicknessOfMeasure);
//			}
//		}
//	}
//	// 四、 腰椎角诊断
//	else if (m_opType == DIAG_YZJ)
//	{
//		logInfo log = { 0 };
//		log = m_vecLog.back();
//		m_vecDelLog.push_back(log);
//		m_vecLog.pop_back();
//		if (log.step == 2)
//			m_curStep -= 2;
//		else
//			--m_curStep;
//		//重画
//		for (vector<logInfo>::iterator it = m_vecLog.begin(); it != m_vecLog.end(); ++it)
//		{
//			logInfo log = *it;
//			if (log.op == DRAW_LINE)
//			{
//				cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
//				cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
//			}
//			else if (log.op == DRAW_DIAGNOSE)
//			{
//				cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
//				cv::circle(m_maskImg, log.center[1], m_circleRadius, m_maskColor, -1);
//				cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
//				cv::putText(m_maskImg, log.text[0], log.center[2], m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_maskColor, m_fontThicknessOfMeasure);
//			}
//		}
//
//	}
//	// 五、 胸椎诊断
//	else if (m_opType == DIAG_XZ)
//	{
//		logInfo log = { 0 };
//		log = m_vecLog.back();
//		m_vecDelLog.push_back(log);
//		m_vecLog.pop_back();
//		// 保存的也需要回滚
//		std::vector<cv::Point> p;
//		std::vector<double> length;
//		if (m_vecCpPoint_xiongzhui.size() != 0)
//		{
//			p = m_vecCpPoint_xiongzhui.back();
//			m_vecCpPointDel_xiongzhui.push_back(p);
//			m_vecCpPoint_xiongzhui.pop_back();
//		}
//		if (m_vecMeasure_xiongzhui.size() != 0)
//		{
//			length = m_vecMeasure_xiongzhui.back();
//			m_vecMeasureDel_xiongzhui.push_back(length);
//			m_vecMeasure_xiongzhui.pop_back();
//		}
//		// 当前步骤回滚两步
//		m_curStep -= 2;
//		//重画
//		for (vector<logInfo>::iterator it = m_vecLog.begin(); it != m_vecLog.end(); ++it)
//		{
//			logInfo log = *it;
//			if (log.op == DRAW_LINE)
//			{
//				cv::circle(m_maskImg, log.p[0], m_circleRadius, m_maskColor, -1);
//				cv::circle(m_maskImg, log.p[1], m_circleRadius, m_maskColor, -1);
//				cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
//			}
//			else if (log.op == DRAW_BASE_LINE)
//			{
//				cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
//				cv::circle(m_maskImg, log.center[1], m_circleRadius, m_maskColor, -1);
//				cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
//			}
//			else if (log.op == DRAW_XIONGZHUI_MEASURE)
//			{
//				cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
//				cv::circle(m_maskImg, log.center[1], m_circleRadius, m_maskColor, -1);
//				cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
//				cv::putText(m_maskImg, log.text[0], log.center[2], m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_maskColor, m_fontThicknessOfMeasure);
//				cv::putText(m_maskImg, log.text[1], log.center[3], m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_maskColor, m_fontThicknessOfMeasure);
//			}
//		}
//	}
//	// 六、 颈椎正面
//	else if (m_opType == DIAG_JZ)
//	{
//
//	}
//	// 七、 颈椎张口
//	else if (m_opType == DIAG_HZ)
//	{
//		logInfo log = { 0 };
//		log = m_vecLog.back();
//		m_vecDelLog.push_back(log);
//		m_vecLog.pop_back();
//
//		m_curStep -= 2;
//		// 重画
//		for (vector<logInfo>::iterator it = m_vecLog.begin(); it != m_vecLog.end(); ++it)
//		{
//			log = *it;
//			if (log.op == DRAW_BASE_LINE)
//			{
//				// 画出直线
//				cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
//				cv::circle(m_maskImg, log.center[1], m_circleRadius, m_maskColor, -1);
//				cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
//			}
//			else if (log.op == DRAW_JINGZHUIZHANGKOU_MEASURE)
//			{
//				cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
//				cv::circle(m_maskImg, log.center[1], m_circleRadius, m_maskColor, -1);
//				cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
//				cv::putText(m_maskImg, log.text[0],log.center[2], m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_maskColor, m_fontThicknessOfMeasure);
//				cv::putText(m_maskImg, log.text[1],log.center[3], m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_maskColor, m_fontThicknessOfMeasure);
//			}
//		}
//	}
//	remindColor();
//	Invalidate();
}
// 重做
void CchiropracticDlg::OnBnClickedButton9()
{
//	// TODO: 在此添加控件通知处理程序代码
//	changeCtrlBtn(IDC_BUTTON9);
//	if (m_vecDelLog.size() == 0) return;
//	logInfo log = { 0 };
//	log = m_vecDelLog.back();
//	m_vecLog.push_back(log);
//	m_vecDelLog.pop_back();
//	if (m_opType == DRAW_MEASURE)
//	{
//		cv::circle(m_maskImg, log.p[0], m_circleRadius, m_maskColor, -1);
//		cv::circle(m_maskImg, log.p[1], m_circleRadius, m_maskColor, -1);
//		cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
//		cv::putText(m_maskImg, log.text[0], log.center[0], m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_maskColor, m_fontThicknessOfMeasure);
//	}
//	// 添加回操作
//	else if (m_opType == DIAG_QG)
//	{
//		if (log.step == 1)
//			m_curStep += 2;
//		else
//			++m_curStep;
//
//		if (log.op == DRAW_DIAGNOSE)
//		{
//			cv::circle(m_maskImg, log.p[1], m_circleRadius, m_circleColor, -1);
//			cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
//			cv::putText(m_maskImg, log.text[0], log.center[0], m_fontTypeOfDiagnose, m_dFontSizeOfDiagnose, m_maskColor);
//		}
//		else if (log.op == DRAW_LINE)
//		{
//			if (log.step == 1 || log.step == 9 )	// 股骨头线、下关节突的关键点与其他不同
//			{
//				cv::circle(m_maskImg, log.p[0], m_circleRadius, m_maskColor, -1);
//				cv::circle(m_maskImg, log.p[1], m_circleRadius, m_maskColor, -1);
//			}
//			else
//				cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
//			cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
//			//++m_curStep;
//		}
//		else if (log.op == DRAW_LINE_MEASURE)
//		{
//			cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
//			cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
//			cv::line(m_maskImg, log.p[2], log.p[3], m_maskColor, m_lineWidth);
//			cv::putText(m_maskImg, log.text[0], log.center[1], m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_maskColor);
//			//++m_curStep;
//		}
//		else if (log.op == DRAW_CIRCLE)
//		{
//			cv::circle(m_maskImg, log.center[1], m_circleRadius, m_maskColor, -1);
//			//++m_curStep;
//		}
//	}
//	else if (m_opType == DIAG_DG)
//	{
//		if (log.step == 1 || log.step == 4)
//			m_curStep += 2;
//		else
//			++m_curStep;
//
//		if (log.op == DRAW_DIAGNOSE)
//		{
//			cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
//			cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
//			cv::line(m_maskImg, log.p[2], log.p[3], m_maskColor, m_lineWidth);
//			cv::putText(m_maskImg, log.text[0], log.center[1], m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_maskColor, m_fontThicknessOfMeasure);
//			cv::putText(m_maskImg, log.text[1], log.center[2], m_fontTypeOfDiagnose, m_dFontSizeOfDiagnose, m_maskColor, m_fontThicknessOfDiagnose);
//			//cv::circle(m_maskImg, log.center[0], m_circleRadius, m_circleColor, -1);
//			//cv::putText(m_maskImg, log.text[0], log.center[0], m_fontTypeOfDiagnose, m_dFontSizeOfDiagnose, m_maskColor, m_fontThicknessOfDiagnose);
//		}
//		else if (log.op == DRAW_LINE_MEASURE)
//		{
//			// 两条垂直线
//			cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
//			cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
//			cv::line(m_maskImg, log.p[2], log.p[3], m_maskColor, m_lineWidth);
//			cv::putText(m_maskImg, log.text[0], log.center[1], m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_maskColor, m_fontThicknessOfMeasure);
//			//++m_curStep;
//		}
//		else if (log.op == DRAW_DIGU_LINE)
//		{
//			// 画出骶骨水平线和点
//			cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
//			cv::circle(m_maskImg, log.center[1], m_circleRadius, m_maskColor, -1);
//			cv::line(m_maskImg, log.p[0], log.p[1], m_lineColor, m_lineWidth);
//			//画出骶骨水平线的垂直线
//			cv::line(m_maskImg, log.p[2], log.p[3], m_lineColor, m_lineWidth);
//			// 画出股骨头线的平行线
//			cv::line(m_maskImg, log.p[4], log.p[5], m_maskColor, m_lineWidth);
//			// 画出垂直股骨头平行线的垂线
//			cv::line(m_maskImg, log.p[6], log.p[7], m_maskColor, m_lineWidth);
//			// 标注长度
//			cv::putText(m_maskImg, log.text[0], log.center[2], m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_maskColor, m_fontThicknessOfMeasure);
//			//m_curStep += 2;
//		}
//		else if (log.op == DRAW_LINE)
//		{
//			if (log.step == 1)
//			{
//				// 股骨头线
//				cv::circle(m_maskImg, log.p[0], m_circleRadius, m_maskColor, -1);
//				cv::circle(m_maskImg, log.p[1], m_circleRadius, m_maskColor, -1);
//				cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
//				//m_curStep += 2;
//			}
//			else
//			{
//				// 股骨头线垂直线
//				cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
//				cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
//				//++m_curStep;
//			}
//		}
//
//		else if (log.op == DRAW_CIRCLE)
//		{
//			cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
//			//++m_curStep;
//		}
//	}
//	else if (m_opType == DIAG_YZ)
//	{
//		m_curStep += 2;
//		// 保存数据也要添加回来
//		std::vector<cv::Point> p;
//		std::vector<double> length;
//		if (m_vecCpPointDel_yaozhui.size() != 0)
//		{
//			p = m_vecCpPointDel_yaozhui.back();
//			m_point_cp_l_yz.push_back(p);
//			m_vecCpPointDel_yaozhui.pop_back();
//		}
//		if (m_vecMeasureDel_yaozhui.size() != 0)
//		{
//			length = m_vecMeasureDel_yaozhui.back();
//			m_vecMeasure_yaozhui.push_back(length);
//			m_vecMeasureDel_yaozhui.pop_back();
//		}
//		if (log.op == DRAW_LINE)
//		{
//			cv::circle(m_maskImg, log.p[0], m_circleRadius, m_maskColor, -1);
//			cv::circle(m_maskImg, log.p[1], m_circleRadius, m_maskColor, -1);
//			cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
//		}
//		else if (log.op == DRAW_BASE_LINE)
//		{
//			cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
//			cv::circle(m_maskImg, log.center[1], m_circleRadius, m_maskColor, -1);
//			cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
//		}
//		else if (log.op == DRAW_YAOZHUI_MEASURE)
//		{
//			cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
//			cv::circle(m_maskImg, log.center[1], m_circleRadius, m_maskColor, -1);
//			cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
//			cv::putText(m_maskImg, log.text[0], log.center[2], m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_maskColor, m_fontThicknessOfMeasure);
//			cv::putText(m_maskImg, log.text[1], log.center[3], m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_maskColor, m_fontThicknessOfMeasure);
//		}
//	}
//	else if (m_opType == DIAG_YZJ)
//	{
//		if (log.step == 2)
//			m_curStep += 2;
//		else
//			++m_curStep;
//		if (log.op == DRAW_LINE)
//		{
//			cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
//			cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
//		}
//		else if (log.op == DRAW_DIAGNOSE)
//		{
//			cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
//			cv::circle(m_maskImg, log.center[1], m_circleRadius, m_maskColor, -1);
//			cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
//			cv::putText(m_maskImg, log.text[0], log.center[2], m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_maskColor, m_fontThicknessOfMeasure);
//		}
//	}
//	else if (m_opType == DIAG_XZ)
//	{
//		m_curStep += 2;
//		// 保存数据也要添加回来
//		std::vector<cv::Point> p;
//		std::vector<double> length;
//		if (m_vecCpPointDel_xiongzhui.size() != 0)
//		{
//			p = m_vecCpPointDel_xiongzhui.back();
//			m_vecCpPoint_xiongzhui.push_back(p);
//			m_vecCpPointDel_xiongzhui.pop_back();
//		}
//		if (m_vecMeasureDel_xiongzhui.size() != 0)
//		{
//			length = m_vecMeasureDel_xiongzhui.back();
//			m_vecMeasure_xiongzhui.push_back(length);
//			m_vecMeasureDel_xiongzhui.pop_back();
//		}
//		if (log.op == DRAW_LINE)
//		{
//			cv::circle(m_maskImg, log.p[0], m_circleRadius, m_maskColor, -1);
//			cv::circle(m_maskImg, log.p[1], m_circleRadius, m_maskColor, -1);
//			cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
//		}
//		else if (log.op == DRAW_BASE_LINE)
//		{
//			cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
//			cv::circle(m_maskImg, log.center[1], m_circleRadius, m_maskColor, -1);
//			cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
//		}
//		else if (log.op == DRAW_XIONGZHUI_MEASURE)
//		{
//			cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
//			cv::circle(m_maskImg, log.center[1], m_circleRadius, m_maskColor, -1);
//			cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
//			cv::putText(m_maskImg, log.text[0], log.center[2], m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_maskColor, m_fontThicknessOfMeasure);
//			cv::putText(m_maskImg, log.text[1], log.center[3], m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_maskColor, m_fontThicknessOfMeasure);
//		}
//	}
//	else if (m_opType == DIAG_HZ)
//	{
//		if (log.op == DRAW_BASE_LINE)
//		{
//			// 画出直线
//			cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
//			cv::circle(m_maskImg, log.center[1], m_circleRadius, m_maskColor, -1);
//			cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
//		}
//		else if (log.op == DRAW_JINGZHUIZHANGKOU_MEASURE)
//		{
//			cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
//			cv::circle(m_maskImg, log.center[1], m_circleRadius, m_maskColor, -1);
//			cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
//			cv::putText(m_maskImg, log.text[0], log.center[2], m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_maskColor, m_fontThicknessOfMeasure);
//			cv::putText(m_maskImg, log.text[1], log.center[3], m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_maskColor, m_fontThicknessOfMeasure);
//		}
//		m_curStep += 2;
//	}
//	remindColor();
//	Invalidate();
}
BOOL CchiropracticDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) // 相对于屏幕的左上角
{
	REAL oldzoom = m_zoom; //保存当前的缩放系数，用于计算当前滚动时的坐标
	CPoint ppt = pt;
	CRect rect;
	m_edit = zDelta;
	UpdateData(false);
	if (zDelta == 120)
	{
		m_zoom = 1.1*m_zoom;
	}
	if (zDelta == -120)
	{
		m_zoom = 0.9*m_zoom;
	}
	
	GetDlgItem(IDC_PICTURE)->GetWindowRect(rect); //注意这里的区域是窗口相对于整个屏幕的，因为cpoint pt这个点是相对于屏幕的

	ppt.x -= rect.left; //计算该点在对话框中的位置
	ppt.y -= rect.top;

	int x = ppt.x;// - m_Rect.left;  // 在本程序中无作用
	int y = ppt.y;// - m_Rect.top;

	//assert(ppt.x == x && ppt.y == y);

	REAL oldimagex = (x / oldzoom); //缩放前鼠标在原图中的位置
	REAL oldimagey = (y / oldzoom);

	REAL newimagex = (x / m_zoom); //缩放后鼠标在原图中的位置
	REAL newimagey = (y / m_zoom);

	m_imgX = newimagex - oldimagex + m_imgX; //计算原图应该的偏移
	m_imgY = newimagey - oldimagey + m_imgY;

	Invalidate(); //绘图


	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}
void CchiropracticDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_srcImg.empty())
	{
		MessageBox(_T("请先载入图像！"));
		return;
	}
	int nIndex = m_Combo.GetCurSel();
	CString strText;
	m_Combo.GetLBText(nIndex, strText);
	// 只是为了调整换算比例尺
	if (strText == _T("14x17"))  
	{
		double w, h; //实际尺寸(mm或英寸)
		w = 17*25.4;
		h = 14*25.4;
		m_dwidth_scale = w / m_srcImg.cols;
		m_dheight_scale = h / m_srcImg.rows;
	}
	else if (strText == _T("7x8.5"))
	{
		double w, h; //实际尺寸(mm或英寸)
		w = 8.5*25.4;
		h = 7*25.4;
		m_dwidth_scale = w / m_srcImg.cols;
		m_dheight_scale = h / m_srcImg.rows;
	}
	else if (strText == _T("....."))
	{
		// continue
	}
	else  // default
	{
		// nothing
	}

	// 重绘
	OnPaint();

}
void CchiropracticDlg::Invalidate(BOOL bErase)
{
	CRect rect;
	GetDlgItem(IDC_PICTURE)->GetClientRect(rect);//
	CDC *pDC = GetDlgItem(IDC_PICTURE)->GetDC();
	HDC hdc = pDC->GetSafeHdc();
	//HDC hdc = ::GetDC(m_hWnd);
	CDC dc;
	dc.Attach(hdc);
	CDC memDC;
	CBitmap MemBitmap;
	// 设备描述表初始化
	memDC.CreateCompatibleDC(NULL);
	// 建立与屏幕显示兼容的内存显示设备
	MemBitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	// 选取空白位图
	memDC.SelectObject(MemBitmap);
	memDC.FillSolidRect(0, 0, rect.Width(), rect.Height(), RGB(255, 255, 255));
	//画图
	Draw(&memDC);
	//拷贝到控件DC
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
	MemBitmap.DeleteObject();
	memDC.DeleteDC();
	dc.Detach();
	ReleaseDC(pDC);
}
void CchiropracticDlg::Draw(CDC *pDC)
{
	m_srcImg.copyTo(m_zoomImg);  //	拷贝原图
	m_maskShowImg.setTo(m_maskColor, m_maskImg);
	m_zoomImg.setTo(cv::Scalar(0,0,255), m_maskShowImg);	//绘制
	//m_zoomImg.setTo(m_measureColor, m_maskImg);	//绘制直线
	int width = m_zoomImg.cols;
	int height = m_zoomImg.rows;
	Gdiplus::Bitmap img(m_zoomImg.cols, m_zoomImg.rows, PixelFormat24bppRGB);
	Gdiplus::BitmapData bmpData;
	Gdiplus::Rect rect(0, 0, width, height);
	img.LockBits(&rect, 0x0002, PixelFormat24bppRGB, &bmpData);
	BYTE *pByte = (BYTE*)bmpData.Scan0;
	int widNew = WIDTHBYTES(width * 3 * 8);
	for (int i = 0; i<height; ++i)
	{
		memcpy(pByte + i*widNew, m_zoomImg.data + i*width * 3, width * 3);
	}
	img.UnlockBits(&bmpData);

	Graphics graph(pDC->GetSafeHdc());
	graph.SetInterpolationMode(InterpolationModeHighQualityBilinear); //设置缩放质量
	graph.ScaleTransform(m_zoom, m_zoom);                             //缩放
	graph.DrawImage(&img, m_imgX, m_imgY);                            //m_imgX,m_imgY是原图应该偏移的量
	m_edit = m_curStep;				//调试
	UpdateData(false);	
}

void CchiropracticDlg::OnBnClickedButton11()
{
	changeCtrlBtn(IDC_BUTTON11);
	if (m_srcImg.empty())
	{
		MessageBox(_T("请先载入图像！"));
		return;
	}
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg1(
		FALSE, _T("*.bmp|*.jpeg"),
		NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image files (*.bmp; *.jpg;*.png) |*.bmp; *.jpg;*.jpeg;*.jge;*.png; ||"),
		NULL
	);                                        // 选项图片的约定
	dlg1.m_ofn.lpstrTitle = _T("Save Image");    // 打开文件对话框的标题名
	if (dlg1.DoModal() != IDOK)                    // 判断是否获得图片
		return;

	CString mPath = dlg1.GetPathName();            // 获取图片路径
	/*int len = WideCharToMultiByte(CP_ACP, 0, mPath, -1, NULL, 0, NULL, NULL);
	char *ptxtTemp = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, mPath, -1, ptxtTemp, len, NULL, NULL);*/
	char *ptxtTemp = mPath.GetBuffer(mPath.GetLength());

	cv::Mat saveImg;
	saveImg = m_srcImg.clone();
	saveImg.setTo(cv::Scalar(0, 0, 255), m_maskImg);
	imwrite(ptxtTemp, saveImg);
	//delete[] ptxtTemp;
	m_bNeedSave = false;
}


// 求线的延长线
/*
* grad:线的斜率
* center:延长点坐标
* lenth_l: 偏左延长长度
* lenth_r:偏右延长长度
*/
void  CchiropracticDlg::lineExt(double grad, cv::Point center, double lenth_lt, double lenth_rb, cv::Point &p_lt, cv::Point &p_rb)
{
	double delta_x, delta_y, delta_x1, delta_y1;
	delta_x = std::sqrt(lenth_lt*lenth_lt / (grad*grad + 1));
	delta_y = abs(grad * std::sqrt(lenth_lt*lenth_lt / (grad*grad + 1)));
	delta_x1 = std::sqrt(lenth_rb*lenth_rb / (grad*grad + 1));
	delta_y1 = abs(grad * std::sqrt(lenth_rb*lenth_rb / (grad*grad + 1)));

	if (grad > 0)
	{
		p_lt.x = center.x - delta_x;
		p_lt.y = center.y - delta_y;
		p_rb.x = center.x + delta_x1;
		p_rb.y = center.y + delta_y1;
	}
	else
	{
		p_lt.x = center.x - delta_x;
		p_lt.y = center.y + delta_y;
		p_rb.x = center.x + delta_x1;
		p_rb.y = center.y - delta_y1;
	}
	return;
}

// 求垂线交点
/*
p1 为直线上的点
p2 为直线外的点
grad 为 p1点所在直线斜率
求与跑p1同直线上的交点
*/
cv::Point CchiropracticDlg::lineCrossDot(double grad, cv::Point p1, cv::Point p2)
{
	//grad = 0 - grad;
	double dot_x = (grad*(p2.y - p1.y) + grad*grad*p1.x + p2.x) / (grad*grad + 1);
	double dot_y = p1.y - grad*(p1.x - dot_x);

	return cv::Point(dot_x,dot_y);
}

string CchiropracticDlg::WChar2Ansi(LPSTR pwszSrc)
{
	//pwszSrc.GetBuffer(pwszSrc.GetLenth())
	return pwszSrc;
	
	/*
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);
	if (nLen <= 0) return std::string("");
	char* pszDst = new char[nLen];
	if (NULL == pszDst) return std::string("");
	WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
	pszDst[nLen - 1] = 0;
	std::string strTemp(pszDst);
	delete[] pszDst;
	return strTemp;*/
}

/*
* 功能：返回诊断结果和结果放置位置
* op_type：操作类型
* pose：结果放置位置
*/
CString CchiropracticDlg::diagnose(int op_type, cv::Point &pose)
{
	//CString result = _T("");
	//if (op_type == DIAG_QG)
	//{
	//	// 判断原发侧
	///*	if (m_gp[8].x == m_gp[9].x)
	//	{
	//		MessageBox(_T("无法判断原发侧，请撤销当前操作，并重新执行该步操作!"));
	//		pose = cv::Point(0, 0);
	//		return CString();
	//	}*/
	///*	if (!(m_gp[8].x < m_gp[6].x && m_gp[6].x < m_gp[9].x))
	//	{
	//		MessageBox(_T("无法判断原发侧，请撤销当前操作，并重新执行该步操作!"));
	//		pose = cv::Point(0, 0);
	//		return CString();
	//	}*/
	//	//else
	//	{
	//	/*	double l, r;
	//		l = std::sqrt((m_gp[8].x - m_gp[6].x)*(m_gp[8].x - m_gp[6].x) + (m_gp[8].y - m_gp[6].y)*(m_gp[8].y - m_gp[6].y));
	//		r = std::sqrt((m_gp[9].x - m_gp[6].x)*(m_gp[9].x - m_gp[6].x) + (m_gp[9].y - m_gp[6].y)*(m_gp[9].y - m_gp[6].y));*/
	//		if (m_dLlength_xiaguanjie < m_dRlength_xiaguanjie)	//原发侧在右边，长的为原发侧
	//		{
	//			CString str = _T("");
	//			if (m_dLength_wmg_l_qg < m_dLength_wmg_r_qg)		// 右侧原发侧为PI
	//				str.Format(_T("PI%d"), int(std::round(std::abs(m_dLength_wmg_l_qg - m_dLength_wmg_r_qg))));
	//			else if (m_dLength_wmg_l_qg > m_dLength_wmg_r_qg)		// 右侧原发侧为AS
	//				str.Format(_T("AS%d"), int(std::round(std::abs(m_dLength_wmg_l_qg - m_dLength_wmg_r_qg))));
	//			else if (m_dLength_wmg_l_qg == m_dLength_wmg_r_qg)		// ？？？？？？？？？？？无法判断右侧原发侧为什么
	//				str = _T("");
	//			result += str;

	//			if (m_dLength < 0)		// 右侧原发侧为 Ex
	//				str.Format(_T("Ex%d"), int(std::round(std::abs(m_dLength))));
	//			else if (m_dLength > 0)	// 右侧原发侧为 In
	//				str.Format(_T("In%d"), int(std::round(m_dLength)));
	//			else if(m_dLength == 0)	// ????????????????????? 无法判断
	//				str = _T("");

	//			result += str;
	//			// 调整诊断结果文字放置位置
	//			int baseline = 0;
	//			cv::Size sz_wh = cv::getTextSize(result.GetBuffer(), m_fontTypeOfDiagnose, m_dFontSizeOfDiagnose, m_fontThicknessOfDiagnose, &baseline);
	//			pose = cv::Point(m_srcImg.cols * 7 / 8 - sz_wh.width / 2, m_srcImg.rows / 2 + sz_wh.height / 2);
	//		}
	//		else if (m_dLlength_xiaguanjie > m_dRlength_xiaguanjie)				//左侧为原发侧
	//		{
	//			CString str = _T("");
	//			if (m_dLength_wmg_l_qg > m_dLength_wmg_r_qg)		// 左侧原发侧为PI
	//				str.Format(_T("PI%d"), int(std::round(std::abs(m_dLength_wmg_l_qg - m_dLength_wmg_r_qg))));
	//			else if (m_dLength_wmg_l_qg < m_dLength_wmg_r_qg)		// 左侧原发侧为AS
	//				str.Format(_T("AS%d"), int(std::round(std::abs(m_dLength_wmg_l_qg - m_dLength_wmg_r_qg))));
	//			else if (m_dLength_wmg_l_qg == m_dLength_wmg_r_qg)		// ？？？？？？？？？？？无法判断左侧原发侧为什么
	//				str = _T("");
	//			result += str;

	//			if (m_dLength > 0)		// 左侧原发侧为 Ex
	//				str.Format(_T("Ex%d"), int(std::round(m_dLength)));
	//			else if (m_dLength < 0)	// 左侧原发侧为 In
	//				str.Format(_T("In%d"), int(std::round(std::abs(m_dLength))));
	//			else if (m_dLength == 0)	// ????????????????????? 无法判断
	//				str = _T("");
	//			result += str;
	//			// 调整诊断结果文字放置位置
	//			int baseline = 0;
	//			cv::Size sz_wh = cv::getTextSize(result.GetBuffer(), m_fontTypeOfDiagnose, m_dFontSizeOfDiagnose, m_fontThicknessOfDiagnose, &baseline);
	//			pose = cv::Point(m_srcImg.cols * 1 / 8 - sz_wh.width / 2, m_srcImg.rows / 2 + sz_wh.height / 2);
	//		}
	//		else if (m_dLlength_xiaguanjie == m_dRlength_xiaguanjie)
	//		{
	//			MessageBox(_T("无法判断原发侧，请撤销当前操作，并重新执行该步操作!"));
	//			pose = cv::Point(0, 0);
	//			return CString();
	//		}
	//	}
	//}
	//else if (op_type == DIAG_DG)
	//{
	//	/////
	//	// 判断原发侧
	//	//if (m_gp[7].x == m_gp[8].x)
	//	//{
	//	//	MessageBox(_T("无法判断原发侧，请撤销当前操作，并重新执行该步操作!"));
	//	//	pose = cv::Point(0, 0);
	//	//	return CString();
	//	//}
	//	//if (!(m_gp[7].x < m_gp[2].x && m_gp[2].x < m_gp[8].x))
	//	//{
	//	//	MessageBox(_T("无法判断原发侧，请撤销当前操作，并重新执行该步操作!"));
	//	//	pose = cv::Point(0, 0);
	//	//	return CString();
	//	//}
	//	//else
	//	{
	//		//double l, r;
	//		//l = m_dWidthScale * std::sqrt((m_gp[7].x - m_gp[2].x)*(m_gp[7].x - m_gp[2].x) + (m_gp[7].y - m_gp[2].y)*(m_gp[7].y - m_gp[2].y));
	//		//r = m_dWidthScale * std::sqrt((m_gp[8].x - m_gp[2].x)*(m_gp[8].x - m_gp[2].x) + (m_gp[8].y - m_gp[2].y)*(m_gp[8].y - m_gp[2].y));
	//		// 判断是否有向下偏位
	//		bool bHasDown = false;
	//		double minus = std::abs(m_dLength_l_dg - m_dLength_r_dg);
	//		if (minus >= 7)
	//			bHasDown = true;
	//		else if (minus >= 4 && minus <= 6)
	//		{
	//			CString str;
	//			str.Format(_T("两侧距离之差为%.1fmm, 请判断是否有向下偏位？"), minus);
	//			INT_PTR ret = MessageBox(str, _T("确认"), MB_YESNO);
	//			if (ret == IDYES)
	//				bHasDown = true;
	//			else
	//				bHasDown = false;
	//		}
	//		//判断原发侧
	//		if (m_dLength_l_dg < m_dLength_r_dg)	//原发侧在右边，长的为原发侧
	//		{
	//			CString str = _T("");
	//			if (bHasDown)	// 有向下偏位
	//				result.Format(_T("P%dI%d-R"), int(std::round(std::abs(m_dLength_l_dg - m_dLength_r_dg))), int(std::round(m_dLength_xx_dg)));
	//			else            // 没有向下偏拉
	//				result.Format(_T("P%d-R"), int(std::round(std::abs(m_dLength_l_dg - m_dLength_r_dg))));
	//			// 调整诊断结果文字放置位置
	//			int baseline = 0;
	//			cv::Size sz_wh = cv::getTextSize(result.GetBuffer(), m_fontTypeOfDiagnose, m_dFontSizeOfDiagnose, m_fontThicknessOfDiagnose, &baseline);
	//			pose = cv::Point(m_srcImg.cols * 7 / 8 - sz_wh.width / 2, m_srcImg.rows / 2 + sz_wh.height / 2);
	//		}
	//		else if (m_dLength_l_dg > m_dLength_r_dg)				//左侧为原发侧
	//		{
	//			CString str = _T("");
	//			if (bHasDown)	// 有向下偏位
	//				result.Format(_T("P%dI%d-L"), int(std::round(std::abs(m_dLength_l_dg - m_dLength_r_dg))), int(std::round(m_dLength_xx_dg)));
	//			else            // 没有向下偏拉
	//				result.Format(_T("P%d-L"), int(std::round(std::abs(m_dLength_l_dg - m_dLength_r_dg))));
	//			// 调整诊断结果文字放置位置
	//			int baseline = 0;
	//			cv::Size sz_wh = cv::getTextSize(result.GetBuffer(), m_fontTypeOfDiagnose, m_dFontSizeOfDiagnose, m_fontThicknessOfDiagnose, &baseline);
	//			pose = cv::Point(m_srcImg.cols * 1 / 8 - sz_wh.width / 2, m_srcImg.rows / 2 + sz_wh.height / 2);
	//		}
	//		else if (m_dLength_l_dg == m_dLength_l_dg)
	//		{
	//			MessageBox(_T("无法判断原发侧，请撤销当前操作，并重新执行该步操作!"));
	//			pose = cv::Point(0, 0);
	//			return CString();
	//		}
	//	}

	//}

	return _T("");
}

void CchiropracticDlg::initParam()
{	
	m_recordFirstPoint = 0;
	// debug 变量
	m_edit = 0;
	// 有用变量
	m_bLButtonDown = false;
	m_zoom = 1.0f;
	m_imgX = 0.0f;
	m_imgY = 0.0f;
	m_PtStart.X = 0.0f;
	m_PtStart.Y = 0.0f;

	m_dwidth_scale = 1.0;
	m_dheight_scale = 1.0;
								// 画图相关参数
	m_circleRadius = 3;
	m_lineWidth = 3;													// 线的宽度
	m_maskColor = cv::Scalar(255, 255, 255);							// 蒙版颜色
	m_lineColor = cv::Scalar(255, 255, 255);							// 线的颜色, 白色
	m_circleColor = cv::Scalar(255, 0, 0);								// 小圆点的颜色， 绿色
	m_infoColor = cv::Scalar(0, 255, 0);								// CT片信息的文字颜色，黄色
	m_diagnoseColor = cv::Scalar(255, 0, 0);							// 诊断结果字体颜色，绿色
	m_measureColor = cv::Scalar(0, 0, 255);								// 划片时测量的值的颜色，红色
	m_fontTypeOfInfo = cv::FONT_HERSHEY_COMPLEX;						// CT片信息字体类型
	m_dFontSizeOfInfo = 1;												// CT片信息字体大小
	m_fontThicknessOfInfo = 2;											// CT片信息字体宽度
	m_font_type_measure = cv::FONT_HERSHEY_COMPLEX;						// 划片时测量的值得字体类型
	m_dfont_scale_measure = 1;											// 划片时测量的值得字体大小
	m_font_thick_measure = 2;										// 划片时测量的值得宽度
	m_font_type_diag = cv::FONT_HERSHEY_COMPLEX;					// 诊断结果的字体类型
	m_font_scale_diag = 1;											// 诊断结果的字体大小
	m_font_thick_diag = 3;										// 诊断结果字体宽度

	// 髂骨操作提示语句
	m_strHint_qg[0] = _T("1.1 做股骨头线——选择左侧股骨头的最高点。");
	m_strHint_qg[1] = _T("1.2 做股骨头线——选择右侧股骨头的最高点。");
	m_strHint_qg[2] = _T("2.1 测左无名骨长度——选择左侧髂嵴的最高点。");
	m_strHint_qg[3] = _T("2.2 测左无名骨长度——选择左侧坐骨的最低点。");
	m_strHint_qg[4] = _T("3.1 测右无名骨长度——选择右侧髂嵴的最高点。");
	m_strHint_qg[5] = _T("3.2 测右无名骨长度——选择右侧坐骨的最低点。");
	m_strHint_qg[6] = _T("4. 做骶骨中线——选择第一骶骨棘突顶点。");
	m_strHint_qg[7] = _T("5. 做耻骨联合中线——选择耻骨联合中点。");
	m_strHint_qg[8] = _T("6.1 测量左侧下关节突影长度——选择左侧下关节突影一边的边缘点。");
	m_strHint_qg[9] = _T("6.2 测量左侧下关节突影长度——选择左侧下关节突影另一边的边缘点。");
	m_strHint_qg[10] = _T("7.1 测量右侧下关节突影长度——选择右侧下关节突影一边的边缘点。");
	m_strHint_qg[11] = _T("7.2 测量右侧下关节突影长度——选择右侧下关节突影另一边的边缘点。");
	m_strHint_qg[12] = _T("完成。");
	// 骶骨操作提示语句
	m_strHint_dg[0] = _T("1.1 做股骨头线——选择左侧股骨头的最高点。");
	m_strHint_dg[1] = _T("1.2 做股骨头线——选择右侧股骨头的最高点。");
	m_strHint_dg[2] = _T("2. 做骶骨中线——选择第一骶骨棘突顶点。");
	m_strHint_dg[3] = _T("3.1 做骶骨水平线——选择左侧骶沟点。");
	m_strHint_dg[4] = _T("3.2 做骶骨水平线——选择右侧骶沟点。");
	m_strHint_dg[5] = _T("4. 画左侧骶骨水平线的垂直线——选择左侧骶骨最外侧缘的点。");
	m_strHint_dg[6] = _T("5. 画右侧骶骨水平线的垂直线——选择右侧骶骨最外侧缘的点。");
	m_strHint_dg[7] = _T("完成。");
	// 腰椎操作提示语句
	m_strHint_yz[0] = _T("确定左边界线：选择左边矩形的竖直线的两个点");
	m_strHint_yz[1] = _T("确定右边界线：选择右边矩形的竖直线的两个点");
	m_strHint_yz[2] = _T("测量：选择下一腰椎的两个点");
	m_strHint_yz[3] = _T("测量：选择下一腰椎的两个点");
	m_strHint_yz[4] = _T("测量：选择下一腰椎的两个点");
	m_strHint_yz[5] = _T("测量：选择下一腰椎的两个点");
	m_strHint_yz[6] = _T("测量：选择下一腰椎的两个点");
	m_strHint_yz[7] = _T("测量：选择下一腰椎的两个点");
	m_strHint_yz[8] = _T("测量：选择下一腰椎的两个点");
	m_strHint_yz[9] = _T("测量：选择下一腰椎的两个点");
	m_strHint_yz[10] = _T("测量：选择下一腰椎的两个点");
	m_strHint_yz[11] = _T("测量：选择下一腰椎的两个点");
	m_strHint_yz[12] = _T("测量：选择下一腰椎的两个点");
	m_strHint_yz[13] = _T("测量：选择下一腰椎的两个点");
	m_strHint_yz[14] = _T("测量：选择下一腰椎的两个点");
	m_strHint_yz[15] = _T("测量：选择下一腰椎的两个点");
	// 腰骶角提示






}

// 针对提示语句，对当前步骤的语句进行高亮
void CchiropracticDlg::remindColor()
{
	if (m_opType == -1 || m_opType == DRAW_MEASURE || m_opType == DRAW_RECT)
		return;
	m_ctrlHint.SetWindowText(m_strHint[m_curStep].GetString());
	OnPaint();
}

void CchiropracticDlg::initCtrlBtn(BOOL selBtn0, BOOL selBtn1)
{
	if (selBtn0)
	{
		int height0 = 110;
		m_button2.m_bTransparent = FALSE;
		m_button2.m_bDontUseWinXPTheme = TRUE;
		m_button2.SetTextFont(height0, _T("宋体"));
		m_button2.SetFaceColor(RGB(0xff, 0xff, 0xff));
		m_button2.SetTextColor(RGB(0, 0, 0));

		m_button3.m_bTransparent = FALSE;
		m_button3.m_bDontUseWinXPTheme = TRUE;
		m_button3.SetTextFont(height0, _T("宋体"));
		m_button3.SetFaceColor(RGB(0xff, 0xff, 0xff));
		m_button3.SetTextColor(RGB(0, 0, 0));

		m_button6.m_bTransparent = FALSE;
		m_button6.m_bDontUseWinXPTheme = TRUE;
		m_button6.SetTextFont(height0, _T("宋体"));
		m_button6.SetFaceColor(RGB(0xff, 0xff, 0xff));
		m_button6.SetTextColor(RGB(0, 0, 0));

		m_button8.m_bTransparent = FALSE;
		m_button8.m_bDontUseWinXPTheme = TRUE;
		m_button8.SetTextFont(height0, _T("宋体"));
		m_button8.SetFaceColor(RGB(0xff, 0xff, 0xff));
		m_button8.SetTextColor(RGB(0, 0, 0));

		m_button9.m_bTransparent = FALSE;
		m_button9.m_bDontUseWinXPTheme = TRUE;
		m_button9.SetTextFont(height0, _T("宋体"));
		m_button9.SetFaceColor(RGB(0xff, 0xff, 0xff));
		m_button9.SetTextColor(RGB(0, 0, 0));

		m_button15.m_bTransparent = FALSE;
		m_button15.m_bDontUseWinXPTheme = TRUE;
		m_button15.SetTextFont(height0, _T("宋体"));
		m_button15.SetFaceColor(RGB(0xff, 0xff, 0xff));
		m_button15.SetTextColor(RGB(0, 0, 0));

		m_button14.m_bTransparent = FALSE;
		m_button14.m_bDontUseWinXPTheme = TRUE;
		m_button14.SetTextFont(height0, _T("宋体"));
		m_button14.SetFaceColor(RGB(0xff, 0xff, 0xff));
		m_button14.SetTextColor(RGB(0, 0, 0));

		m_button10.m_bTransparent = FALSE;
		m_button10.m_bDontUseWinXPTheme = TRUE;
		m_button10.SetTextFont(height0, _T("宋体"));
		m_button10.SetFaceColor(RGB(0xff, 0xff, 0xff));
		m_button10.SetTextColor(RGB(0, 0, 0));

		
	}
	//m_logo.cr
	m_button11.m_bTransparent = FALSE;
	m_button11.m_bDontUseWinXPTheme = TRUE;
	m_button11.SetTextFont(110, _T("宋体"));
	m_button11.SetFaceColor(RGB(0x3d, 0xc8, 0x54));
	m_button11.SetTextColor(RGB(0, 0, 0));
	if (selBtn1)
	{
		int height1 = 110;
		m_button_op1.m_bTransparent = FALSE;
		m_button_op1.m_bDontUseWinXPTheme = TRUE;
		m_button_op1.SetTextFont(height1, _T("宋体"));
		m_button_op1.SetFaceColor(RGB(0xff, 0xff, 0xff));
		m_button_op1.SetTextColor(RGB(0, 0, 0));

		m_button_op2.m_bTransparent = FALSE;
		m_button_op2.m_bDontUseWinXPTheme = TRUE;
		m_button_op2.SetTextFont(height1, _T("宋体"));
		m_button_op2.SetFaceColor(RGB(0xff, 0xff, 0xff));
		m_button_op2.SetTextColor(RGB(0, 0, 0));

		m_button_op3.m_bTransparent = FALSE;
		m_button_op3.m_bDontUseWinXPTheme = TRUE;
		m_button_op3.SetTextFont(height1, _T("宋体"));
		m_button_op3.SetFaceColor(RGB(0xff, 0xff, 0xff));
		m_button_op3.SetTextColor(RGB(0, 0, 0));

		m_button_op4.m_bTransparent = FALSE;
		m_button_op4.m_bDontUseWinXPTheme = TRUE;
		m_button_op4.SetTextFont(height1, _T("宋体"));
		m_button_op4.SetFaceColor(RGB(0xff, 0xff, 0xff));
		m_button_op4.SetTextColor(RGB(0, 0, 0));

		m_button_op5.m_bTransparent = FALSE;
		m_button_op5.m_bDontUseWinXPTheme = TRUE;
		m_button_op5.SetTextFont(height1, _T("宋体"));
		m_button_op5.SetFaceColor(RGB(0xff, 0xff, 0xff));
		m_button_op5.SetTextColor(RGB(0, 0, 0));

		m_button_op6.m_bTransparent = FALSE;
		m_button_op6.m_bDontUseWinXPTheme = TRUE;
		m_button_op6.SetTextFont(height1, _T("宋体"));
		m_button_op6.SetFaceColor(RGB(0xff, 0xff, 0xff));
		m_button_op6.SetTextColor(RGB(0, 0, 0));

		m_button_op7.m_bTransparent = FALSE;
		m_button_op7.m_bDontUseWinXPTheme = TRUE;
		m_button_op7.SetTextFont(height1, _T("宋体"));
		m_button_op7.SetFaceColor(RGB(0xff, 0xff, 0xff));
		m_button_op7.SetTextColor(RGB(0, 0, 0));
	}
	
}


// 两组button，一组是顶部操作按钮，另一组是操作类型按钮
// selBtn0 是第一组的， selBtn1 是第二组的
void CchiropracticDlg::changeCtrlBtn(INT selBtn0, INT selBtn1)
{
	// 第一步，初始化按钮组
	initCtrlBtn(selBtn0 != NULL, selBtn1 != NULL);
	// 对获得焦点对的按钮着色
	switch (selBtn0)
	{
	case NULL:
		break;
	case IDC_BUTTON2:
		m_button2.SetFaceColor(RGB(0x3d, 0xc8, 0x54));
		break;
	case IDC_BUTTON3:
		m_button3.SetFaceColor(RGB(0x3d, 0xc8, 0x54));
		break;
	case IDC_BUTTON6:
		m_button6.SetFaceColor(RGB(0x3d, 0xc8, 0x54));
		break;
	case IDC_BUTTON8:
		m_button8.SetFaceColor(RGB(0x3d, 0xc8, 0x54));
		break;
	case IDC_BUTTON9:
		m_button9.SetFaceColor(RGB(0x3d, 0xc8, 0x54));
		break;
	case IDC_BUTTON15:
		m_button15.SetFaceColor(RGB(0x3d, 0xc8, 0x54));
		break;
	case IDC_BUTTON14:
		m_button14.SetFaceColor(RGB(0x3d, 0xc8, 0x54));
		break;
	case IDC_BUTTON10:
		m_button10.SetFaceColor(RGB(0x3d, 0xc8, 0x54));
		break;
	case IDC_BUTTON11:
		m_button11.SetFaceColor(RGB(0x3d, 0xc8, 0x54));
		break;
	default:
		break;
	}
	switch (selBtn1)
	{
	case NULL:
		break;
	case IDC_BUTTON_OP1:
		m_button_op1.SetFaceColor(RGB(0x3d, 0xc8, 0x54));
		break;
	case IDC_BUTTON_OP2:
		m_button_op2.SetFaceColor(RGB(0x3d, 0xc8, 0x54));
		break;
	case IDC_BUTTON_OP3:
		m_button_op3.SetFaceColor(RGB(0x3d, 0xc8, 0x54));
		break;
	case IDC_BUTTON_OP4:
		m_button_op4.SetFaceColor(RGB(0x3d, 0xc8, 0x54));
		break;
	case IDC_BUTTON_OP5:
		m_button_op5.SetFaceColor(RGB(0x3d, 0xc8, 0x54));
		break;
	case IDC_BUTTON_OP6:
		m_button_op6.SetFaceColor(RGB(0x3d, 0xc8, 0x54));
		break;
	case IDC_BUTTON_OP7:
		m_button_op7.SetFaceColor(RGB(0x3d, 0xc8, 0x54));
		break;
	default:
		break;
	}
	OnPaint();
}

bool CchiropracticDlg::dcm2Mat(const char* const fileName, cv::Mat & mat)
{

	DJDecoderRegistration::registerCodecs();								// register JPEG codecs  
	DcmFileFormat fileformat;												//DcmFileFormat fileformat;
	if (!(fileformat.loadFile(fileName).good()))
		return false;

	DcmDataset *dataset = fileformat.getDataset();
	// decompress data set if compressed    
	dataset->chooseRepresentation(EXS_LittleEndianExplicit, NULL);
	// 获取patient信息
	OFString PatientName;								// 病人姓名	PN
	OFString PatientID;									// 病人ID	LO
	OFString PatientSex;								// 病人性别	CS
	OFString PatientBirthDate;							// 病人生日	DA
	OFString PatientAge;								// 病人年龄	AS
	// 获取study 信息
	OFString InstitutionName;							// 拍照医院名称	LO
	//
	// 获取image信息
	//*
	OFintptr_t Rows = 0;								// 图像高度	US
	OFintptr_t Cols = 0;								// 图像宽度	US
	OFintptr_t BitsAllocated;							// 图像数据类型	US
	OFString PhotometricInterpretation;					// 图像类型(黑白或彩色)	CS
	OFString ImagerPixelSpacing;						// 图像分辨率	DS(还有一个叫PixelSpacing)
	OFString PixelSpacing;								// 图像分辨率	DS
	OFString BodyPartExamined;							// 检查部位	CS
	OFString ImageDate;									// 检查时间


	//*/
	dataset->findAndGetOFString(DCM_PatientName, PatientName);
	dataset->findAndGetOFString(DCM_PatientID, PatientID);
	dataset->findAndGetOFString(DCM_PatientSex, PatientSex);
	dataset->findAndGetOFString(DCM_PatientBirthDate, PatientBirthDate);
	dataset->findAndGetOFString(DCM_PatientAge, PatientAge);
	//
	dataset->findAndGetOFString(DCM_InstitutionName, InstitutionName);
	//
	dataset->findAndGetLongInt(DCM_BitsAllocated, BitsAllocated);
	//
	dataset->findAndGetLongInt(DCM_Rows, Rows);
	dataset->findAndGetLongInt(DCM_Columns, Cols);
	dataset->findAndGetOFString(DCM_PhotometricInterpretation, PhotometricInterpretation);
	dataset->findAndGetOFString(DCM_ImagerPixelSpacing, ImagerPixelSpacing);
	dataset->findAndGetOFString(DCM_PixelSpacing, PixelSpacing);


	// 图像读取
	if (Rows == 0 || Cols == 0)
		return false;
	DcmElement* element = NULL;
	OFCondition result = dataset->findAndGetElement(DCM_PixelData, element);
	if (result.bad() || element == NULL)
		return false;

	void *pixData = NULL;
	if (BitsAllocated == 8)
	{
		Uint8* p;
		result = element->getUint8Array(p);
		pixData = p;
	}
	else if (BitsAllocated == 16)
	{
		Uint16* p;
		result = element->getUint16Array(p);
		pixData = p;
	}
	else if (BitsAllocated == 32)
	{
		Uint32* p;
		result = element->getUint32Array(p);
		pixData = p;
	}
	char *pbuf = new char[Rows*Cols*int(BitsAllocated / 8)];		// 分配内存空间
	memcpy(pbuf, pixData, Rows*Cols*int(BitsAllocated / 8));
	Mat xx,xxx;
	if (PhotometricInterpretation == _T("MONOCHROME1") || PhotometricInterpretation == _T("MONOCHROME2"))
	{
		// 黑白图像
		switch (BitsAllocated / 8)
		{
		case 1:
		{
			Mat x(Rows, Cols, CV_8UC1, pbuf);
			xx = x.clone();
			break;
		}	
		case 2:
		{
			Mat x(Rows, Cols, CV_16SC1, pbuf);
			xx = x.clone();
			break;
		}
		case 4:
		{
			Mat x(Rows, Cols, CV_32FC1, pbuf);
			xx = x.clone();
			break;
		}
		default:
			break;
		}
		cv::normalize(xx, xxx, 0, 255, NORM_MINMAX, CV_8UC1);
		Mat afull(xx.rows, xx.cols, CV_8UC1, 255);  // 图像颜色反转，黑变白，白变黑
		xxx = afull - xxx;
		mat = xxx.clone();
		cvtColor(mat, mat, CV_GRAY2RGB);
	}
	else if (PhotometricInterpretation == _T("RGB"))
	{
		// 彩色图像
		switch (BitsAllocated / 8)
		{
		case 1:
		{
			Mat x(Rows, Cols, CV_8UC3, pbuf);
			xx = x.clone();
			break;
		}
		case 2:
		{
			Mat x(Rows, Cols, CV_16SC3, pbuf);
			xx = x.clone();
			break;
		}
		case 4:
		{
			Mat x(Rows, Cols, CV_32FC3, pbuf);
			xx = x.clone();
			break;
		}
		default:
			break;
		}
		cv::normalize(xx, xxx, 0, 255, NORM_MINMAX, CV_8UC3);
	}

	delete[]pbuf;
	DJDecoderRegistration::cleanup(); // deregister JPEG codecs 
	return true;
}

void CchiropracticDlg::OnBnClickedButtonOp1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_srcImg.empty())
	{
		MessageBox(_T("请先载入图像！"));
		return;
	}
	m_curStep = 0;
	m_opType = DIAG_QG;
	m_strHint = m_strHint_qg;		// 指向髂骨
	remindColor();
	changeCtrlBtn(NULL, IDC_BUTTON_OP1);
}
void CchiropracticDlg::OnBnClickedButtonOp2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_srcImg.empty())
	{
		MessageBox(_T("请先载入图像！"));
		return;
	}
	m_curStep = 0;
	m_opType = DIAG_DG;
	m_strHint = m_strHint_dg;		// 指向骶骨
	remindColor();
	changeCtrlBtn(NULL, IDC_BUTTON_OP2);
}


void CchiropracticDlg::OnBnClickedButtonOp3()
{

	// TODO: 在此添加控件通知处理程序代码
	if (m_srcImg.empty())
	{
		MessageBox(_T("请先载入图像！"));
		return;
	}
	// 确定腰椎侧弯侧
	CBend benddlg;
	INT_PTR ret = benddlg.DoModal();
	if (ret != IDOK)
	{
		MessageBox(_T("没有确定腰椎侧弯凸侧！"));
		return;
	}
	m_strBend_yz = benddlg.m_strBend;

	// 目测输入需要诊断的半脱位腰椎
	CInputYZ dlg;
	ret = dlg.DoModal();
	if (ret == IDCANCEL)
	{
		MessageBox(_T("没有确定腰椎半脱位的位置！"));
		return;
	}
	else
	{
		for (int i = 1; i < 6; i++)
		{
			m_bLuxs_yz[i] = dlg.m_bLuxs_yz[i];
		}
		m_total_lux_yz = dlg.m_total_yz;
		for (int i = 5; i > 0; i--)
		{
			if(m_bLuxs_yz[i] == true)
			{
				m_curDiag_yz = i;
				break;
			}				
		}
		m_curDiag_xie_yz = 0;
	}

	m_curStep = 0;
	m_opType = DIAG_YZ;
	m_strHint = m_strHint_yz;
	remindColor();
	changeCtrlBtn(NULL, IDC_BUTTON_OP3);
}


void CchiropracticDlg::OnBnClickedButton13()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CchiropracticDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bNeedSave)
	{
		INT_PTR ret = ::MessageBox(NULL, _T("图像有新操作还没保存，你确定不保存退出？"), _T("提示！"), MB_YESNO);
		if (ret == IDYES)
			CDialogEx::OnCancel();
		else
			return;
	}
	CDialogEx::OnCancel();
}


void CchiropracticDlg::OnBnClickedButton15()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_srcImg.empty())
	{
		MessageBox(_T("请先载入图像！"));
		return;
	}
	m_opType = DRAW_MEASURE;
	changeCtrlBtn(IDC_BUTTON15);
}


void CchiropracticDlg::OnBnClickedButtonOp4()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_srcImg.empty())
	{
		MessageBox(_T("请先载入图像！"));
		return;
	}
	m_curStep = 0;
	m_opType = DIAG_YZJ;
	m_strHint = m_csYaoDiJiao_remind;		// 指向骶骨
	remindColor();
	changeCtrlBtn(NULL, IDC_BUTTON_OP4);
}


void CchiropracticDlg::OnBnClickedButton14()
{
	// TODO: 在此添加控件通知处理程序代码
	changeCtrlBtn(IDC_BUTTON14);
	CInputText dlg;
	INT_PTR ret = dlg.DoModal();
	if (ret == IDOK)
	{
		m_bPutText = true;
		m_strText = dlg.m_strText;
	}
}


void CchiropracticDlg::OnBnClickedButtonOp5()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_srcImg.empty())
	{
		MessageBox(_T("请先载入图像！"));
		return;
	}
	// 确定腰椎侧弯侧
	CBend benddlg;
	INT_PTR ret = benddlg.DoModal();
	if (ret != IDOK)
	{
		MessageBox(_T("没有确定胸椎侧弯凸侧！"));
		return;
	}
	m_strBend_xz = benddlg.m_strBend;

	m_opType = DIAG_XZ;
	m_strHint = m_strHint_xz;		// 指向胸椎
	m_curStep = 0;
	m_bHas_draw_yfc = false;
	m_bHas_more_xz_xz = false;
	m_bDraw_L1_xz = false;
	m_total_xz = 0;
	remindColor();
	changeCtrlBtn(NULL, IDC_BUTTON_OP5);
}


void CchiropracticDlg::OnBnClickedButtonOp6()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_srcImg.empty())
	{
		MessageBox(_T("请先载入图像！"));
		return;
	}
	m_curStep = 0;
	m_opType = DIAG_JZ;
	m_strHint = m_strHint_dg;		// 指向骶骨
	remindColor();
	changeCtrlBtn(NULL, IDC_BUTTON_OP6);
}


void CchiropracticDlg::OnBnClickedButtonOp7()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_srcImg.empty())
	{
		MessageBox(_T("请先载入图像！"));
		return;
	}
	m_curStep = 0;
	m_opType = DIAG_HZ;
	m_strHint = m_strHint_dg;		// 指向骶骨
	remindColor();
	changeCtrlBtn(NULL, IDC_BUTTON_OP7);
}
/*
功能：获取旋转侧
*/

bool CchiropracticDlg::drawYfc(cv::Point pt)
{
	if (m_rotateMethod == 1)
	{
		//m_strRotate 已经有值
		m_bHas_draw_yfc = true;
		m_rotateMethod = 0;
		m_Combo2.SetCurSel(0);
	}
	//棘突中央到椎体边缘的距离
	else if (m_rotateMethod == 2 && m_curRotateStep < 3)  // 三点一条直线，棘突点、左边缘点、右边缘点
	{
		if (m_curRotateStep == 0)
		{
			m_point_rotate[0] = pt;
			cv::circle(m_maskImg, pt, m_circleRadius, m_maskColor, -1);
			m_curRotateStep++;
		}
		else if (m_curRotateStep == 1)
		{
			m_point_rotate[1] = pt;
			cv::circle(m_maskImg, pt, m_circleRadius, m_maskColor, -1);
			m_curRotateStep++;
		}
		else if (m_curRotateStep == 2)
		{
			m_point_rotate[2] = pt;
			double grad_line_rotate = (m_point_rotate[1].y - m_point_rotate[0].y) / (m_point_rotate[1].x - m_point_rotate[0].x + 10e-8);
			m_point_rotate[2].y = grad_line_rotate*(m_point_rotate[2].x - m_point_rotate[0].x) + m_point_rotate[0].y;

			cv::circle(m_maskImg, m_point_rotate[2], m_circleRadius, m_maskColor, -1);
			// 测量
			double l, r;
			l = m_dwidth_scale * std::sqrt(std::pow(m_point_rotate[1].x - m_point_rotate[0].x, 2) + std::pow(m_point_rotate[1].y - m_point_rotate[0].y, 2));
			r = m_dwidth_scale * std::sqrt(std::pow(m_point_rotate[2].x - m_point_rotate[0].x, 2) + std::pow(m_point_rotate[2].y - m_point_rotate[0].y, 2));
			if (l < r)	// 原发侧为右侧
				m_strYfc = _T("R");
			else if (l == r)	//没有脱位
				m_strYfc = _T("");
			else if (l > r)	// 原发侧为左侧
				m_strYfc = _T("L");
			//重置当前进行到的步骤
			m_curRotateStep = 0;
			m_rotateMethod = 0;
			m_Combo2.SetCurSel(0);
			m_bHas_draw_yfc = true;
		}
	}
	// 椎弓根影横经
	else if (m_rotateMethod == 3 && m_curRotateStep < 4)   //四点两条直线，不用共线
	{
		if (m_curRotateStep == 0)
		{
			m_point_rotate[0] = pt;
			cv::circle(m_maskImg, pt, m_circleRadius, m_maskColor, -1);
			m_curRotateStep++;
		}
		else if (m_curRotateStep == 1)
		{
			m_point_rotate[1] = pt;
			cv::circle(m_maskImg, pt, m_circleRadius, m_maskColor, -1);
			m_curRotateStep++;
		}
		else if (m_curRotateStep == 2)
		{
			m_point_rotate[2] = pt;
			cv::circle(m_maskImg, pt, m_circleRadius, m_maskColor, -1);
			m_curRotateStep++;
		}
		else if (m_curRotateStep == 3)
		{
			m_point_rotate[3] = pt;
			cv::circle(m_maskImg, pt, m_circleRadius, m_maskColor, -1);
			// 测量
			double l, r;
			l = m_dwidth_scale * std::sqrt(std::pow(m_point_rotate[1].x - m_point_rotate[0].x, 2) + std::pow(m_point_rotate[1].y - m_point_rotate[0].y, 2));
			r = m_dwidth_scale * std::sqrt(std::pow(m_point_rotate[3].x - m_point_rotate[2].x, 2) + std::pow(m_point_rotate[3].y - m_point_rotate[2].y, 2));
			if (l < r)	// 原发侧为右侧
				m_strYfc = _T("R");
			else if (l = r)	//没有脱位
				m_strYfc = _T("");
			else if (l > r)	// 原发侧为左侧
				m_strYfc = _T("L");
			//重置当前进行到的步骤
			m_curRotateStep = 0;
			m_rotateMethod = 0;
			m_Combo2.SetCurSel(0);
			m_bHas_draw_yfc = true;
		}
	}
	//下关节突影
	else if (m_rotateMethod == 4 && m_curRotateStep < 4)	//四点两条直线，四点共线
	{
		if (m_curRotateStep == 0)
		{
			m_point_rotate[0] = pt;
			cv::circle(m_maskImg, pt, m_circleRadius, m_maskColor, -1);
			m_curRotateStep++;
		}
		else if (m_curRotateStep == 1)
		{
			m_point_rotate[1] = pt;
			cv::circle(m_maskImg, pt, m_circleRadius, m_maskColor, -1);
			m_curRotateStep++;
		}
		else if (m_curRotateStep == 2)
		{
			m_point_rotate[2] = pt;
			double grad_line_rotate = (m_point_rotate[1].y - m_point_rotate[0].y) / (m_point_rotate[1].x - m_point_rotate[0].x + 10e-8);
			m_point_rotate[2].y = grad_line_rotate*(m_point_rotate[2].x - m_point_rotate[0].x) + m_point_rotate[0].y;
			cv::circle(m_maskImg, m_point_rotate[2], m_circleRadius, m_maskColor, -1);
			m_curRotateStep++;
		}
		else if (m_curRotateStep == 3)
		{
			m_point_rotate[3] = pt;
			double grad_line_rotate = (m_point_rotate[1].y - m_point_rotate[0].y) / (m_point_rotate[1].x - m_point_rotate[0].x + 10e-8);
			m_point_rotate[3].y = grad_line_rotate*(m_point_rotate[3].x - m_point_rotate[0].x) + m_point_rotate[0].y;
			cv::circle(m_maskImg, m_point_rotate[3], m_circleRadius, m_maskColor, -1);
			// 测量
			double l, r;
			l = m_dwidth_scale * std::sqrt(std::pow(m_point_rotate[1].x - m_point_rotate[0].x, 2) + std::pow(m_point_rotate[1].y - m_point_rotate[0].y, 2));
			r = m_dwidth_scale * std::sqrt(std::pow(m_point_rotate[3].x - m_point_rotate[2].x, 2) + std::pow(m_point_rotate[3].y - m_point_rotate[2].y, 2));
			if (l < r)	// 原发侧为右侧
				m_strYfc = _T("R");
			else if (l = r)	//没有脱位
				m_strYfc = _T("");
			else if (l > r)	// 原发侧为左侧
				m_strYfc = _T("L");
			//重置当前进行到的步骤
			m_curRotateStep = 0;
			m_rotateMethod = -1;
			m_Combo2.SetCurSel(0);
			m_bHas_draw_yfc = true;
		}
	}
	// 不要往下走了
	return 0;
}

void CchiropracticDlg::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	m_Combo2.GetLBText(m_Combo2.GetCurSel(), str);
	if (str == _T("请选择"))
		m_rotateMethod = -1;
	else if (str == _T("手动输入"))
	{
		CRotateSee dlg;
		INT_PTR ret = dlg.DoModal();
		if (ret == IDCANCEL)
		{
			m_rotateMethod = 0;
			m_Combo2.SetCurSel(0);
		}	
		else
		{
			m_strYfc = dlg.m_strRotate;
			m_rotateMethod = 1;
			drawYfc(cv::Point(0,0));
			OnLButtonUp(0,CPoint(0, 0));
		}
			
	}
	else if (str == _T("测量椎体棘突中央到椎体边缘的距离"))
	{
		m_rotateMethod = 2;
	}
	else if (str == _T("测量椎体椎弓根影横经"))
	{
		m_rotateMethod = 3;
	}
	else if (str == _T("测量椎体下关节突影"))
	{
		m_rotateMethod = 4;
	}
}

void CchiropracticDlg::diagXz()
{
	if (!m_bHas_draw_dd_line_xz)
	{
		MessageBox(_T("请返回骨盆诊断步骤，做出骶骨水平线"), _T("提示"), MB_OK);
		return;
	}
	// ********** 计算各胸椎的斜率，并取其中与骶骨水平线斜率最接近的胸椎作为胸椎的判断基准 ************ //
	// 骶骨水平线的方向向量
	//double eps = 10e-3;
	//if(std::abs(m_dGrad_dg_xz) > eps)		// 认为不
	cv::Point2d e_dg = cv::Point(1.0 / std::sqrt(1 + m_dGrad_dg_xz*m_dGrad_dg_xz), m_dGrad_dg_xz);
	cv::Point2d *e_xz = new cv::Point2d[m_total_xz + 1]; // 索引0废弃
	double *angle_xz = new double[m_total_xz + 1]; // 索引0废弃
	// 求胸椎和腰椎的单位向量
	for (int i = 1; i <= m_total_xz; ++i)
	{
		double delta, delta_x, delta_y;
		delta_x = m_point_cp_r_xz[i].x - m_point_cp_l_xz[i].x;
		delta_y = m_point_cp_r_xz[i].y - m_point_cp_l_xz[i].y;
		delta = std::sqrt(delta_x*delta_x + delta_y*delta_y);

		e_xz[i] = cv::Point2d(delta_x / delta, delta_y / delta);
	}
	// 求胸椎和腰椎与骶骨水平线的夹角 （cos(theta) = (a*b)/(||a||*||b||) = a*b） 因为 a，b已经是单位向量了
	for (int i = 1; i <= m_total_xz; ++i)
	{
		double PI = 3.1415926;
		angle_xz[i] = 180.0/PI* std::acos( (e_xz[i].x * e_dg.x + e_xz[i].y * e_dg.y) );
		// 变换到[-PI/2, PI/2]区域
		if (angle_xz[i] > 90)
			angle_xz[i] = angle_xz[i] - 180;
	}
	// 找到与骶骨水平线斜率最接近的胸椎
	double angle_dg = 180.0 / 3.1415926*std::atan(m_dGrad_dg_xz);
	double min_angle = 90;
	int ref_idx = 0;
	for (int i = 1; i <= m_total_xz; ++i)
	{
		double delta = std::abs(angle_xz[i] - angle_dg);
		if (delta > 90)		//变换到[0,PI/2]
			delta = 180 - delta;
		if ( delta < min_angle)
		{
			min_angle = delta;
			ref_idx = i;
		}
	}
	// **********诊断************ //
	// 往上诊断
	for (int i = ref_idx - 1; i >= 1; --i)
	{
		if (m_strYfc_xz[i] == _T(""))		// 没有半脱位
			continue;

		if (m_strXie_xz[i] == _T(""))		// 没有楔形开口
		{
			m_strDiag_xz[i].Format(_T("%d"),i);
			if (m_strBend_xz == _T(""))		// 没有侧弯
				m_strDiag_xz[i] = m_strDiag_xz[i] + _T("P") + m_strYfc_xz[i] + _T("-SP");
			else if (m_strBend_xz != m_strYfc_xz[i])		// 侧弯侧与原发测不一致，即与棘突旋转向一致，接触点编码为SP
				m_strDiag_xz[i] = m_strDiag_xz[i] + _T("P") + m_strYfc_xz[i] + _T("-SP");
			else if(m_strBend_xz == m_strYfc_xz[i])		// 侧弯侧与原发测一致，即与棘突旋转向不一致，接触点编码为T
				m_strDiag_xz[i] = m_strDiag_xz[i] + _T("P") + m_strYfc_xz[i] + _T("-T");
		}
		else                 // 有楔形开口
		{
			m_strDiag_xz[i].Format(_T("%d"), i);
			if (m_strXie_xz[i] == m_strYfc_xz[i])		// 楔形开口与原发测一致，与棘突偏向侧不一致，楔形编码:"I"，接触点编码：M
			{
				m_strDiag_xz[i] = m_strDiag_xz[i] + _T("P") + m_strYfc_xz[i] + _T("I") +  _T("-M");
			}
			else                                       // 楔形开口与原发测不一致，与棘突偏向侧一致，楔形编码:"S"，接触点编码：SP，无需标注
			{
				m_strDiag_xz[i] = m_strDiag_xz[i] + _T("P") + m_strYfc_xz[i] + _T("S");
			}
		}
		// 放置诊断
		cv::Point center_diag;
		if (m_strYfc_xz[i] == _T("R"))			// 原发测在右，诊断代码放置在右边
		{
			center_diag.x = (m_point_cp_l_xz[i].x + 3 * m_point_cp_r_xz[i].x) / 4;
			center_diag.y = (m_point_cp_l_xz[i].y + 3 * m_point_cp_r_xz[i].y) / 4;
		}
		else                                   // 原发测在左，诊断代码放置在左边
		{
			center_diag.x = (3 * m_point_cp_l_xz[i].x + m_point_cp_r_xz[i].x) / 4;
			center_diag.y = (3 * m_point_cp_l_xz[i].y + m_point_cp_r_xz[i].y) / 4;
		}
		int baseline = 0;
		cv::Size sz_wh = cv::getTextSize(m_strDiag_xz[i].GetBuffer(), m_font_type_diag, m_font_scale_diag, m_font_thick_diag, &baseline);
		center_diag.x = center_diag.x - sz_wh.width / 2;
		center_diag.y = center_diag.y - sz_wh.height / 2;
		cv::putText(m_maskImg, m_strDiag_xz[i].GetBuffer(), center_diag, m_font_type_diag, m_font_scale_diag, m_maskColor, m_font_thick_diag);

	}
	// 往下诊断
	for (int i = ref_idx+1; i <= m_total_xz; ++i)
	{
		if (m_strYfc_xz[i] == _T(""))		// 没有半脱位
			continue;

		if (m_strXie_xz[i] == _T(""))		// 没有楔形开口
		{
			m_strDiag_xz[i].Format(_T("%d"), i);
			if (m_strBend_xz == _T(""))		// 没有侧弯
				m_strDiag_xz[i] = m_strDiag_xz[i] + _T("P") + m_strYfc_xz[i] + _T("-SP");
			else if (m_strBend_xz != m_strYfc_xz[i])		// 侧弯侧与原发测不一致，即与棘突旋转向一致，接触点编码为SP
				m_strDiag_xz[i] = m_strDiag_xz[i] + _T("P") + m_strYfc_xz[i] + _T("-SP");
			else if (m_strBend_xz == m_strYfc_xz[i])		// 侧弯侧与原发测一致，即与棘突旋转向不一致，接触点编码为T
				m_strDiag_xz[i] = m_strDiag_xz[i] + _T("P") + m_strYfc_xz[i] + _T("-T");
		}
		else                 // 有楔形开口
		{
			m_strDiag_xz[i].Format(_T("%d"), i);
			if (m_strXie_xz[i] == m_strYfc_xz[i])		// 楔形开口与原发测一致，与棘突偏向侧不一致，楔形编码:"I"，接触点编码：M
			{
				m_strDiag_xz[i] = m_strDiag_xz[i] + _T("P") + m_strYfc_xz[i] + _T("I") + _T("-M");
			}
			else                                       // 楔形开口与原发测不一致，与棘突偏向侧一致，楔形编码:"S"，接触点编码：SP，无需标注
			{
				m_strDiag_xz[i] = m_strDiag_xz[i] + _T("P") + m_strYfc_xz[i] + _T("S");
			}
		}
		// 放置诊断
		cv::Point center_diag;
		if (m_strYfc_xz[i] == _T("R"))			// 原发测在右，诊断代码放置在右边
		{
			center_diag.x = (m_point_cp_l_xz[i].x + 3 * m_point_cp_r_xz[i].x) / 4;
			center_diag.y = (m_point_cp_l_xz[i].y + 3 * m_point_cp_r_xz[i].y) / 4;
		}
		else                                   // 原发测在左，诊断代码放置在左边
		{
			center_diag.x = (3 * m_point_cp_l_xz[i].x + m_point_cp_r_xz[i].x) / 4;
			center_diag.y = (3 * m_point_cp_l_xz[i].y + m_point_cp_r_xz[i].y) / 4;
		}
		int baseline = 0;
		cv::Size sz_wh = cv::getTextSize(m_strDiag_xz[i].GetBuffer(), m_font_type_diag, m_font_scale_diag, m_font_thick_diag, &baseline);
		center_diag.x = center_diag.x - sz_wh.width / 2;
		center_diag.y = center_diag.y - sz_wh.height / 2;
		cv::putText(m_maskImg, m_strDiag_xz[i].GetBuffer(), center_diag, m_font_type_diag, m_font_scale_diag, m_maskColor, m_font_thick_diag);

	}
	delete[]angle_xz;
	delete[]e_xz;
}
