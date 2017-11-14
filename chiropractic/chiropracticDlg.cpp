
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
	DDX_Control(pDX, IDC_REMIND1, m_remind1);
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
	// 更新下尺度变量
	//OnCbnSelchangeCombo1();
	// 操作提示控件
	m_remind1.SetBkColor(RGB(0, 255, 0));
	m_remind1.SetForeColor(RGB(255, 0, 0));
	m_remind1.SetTextFont(200, _T("宋体"));
	m_remind1.SetWindowText(_T("请先加载图像！"));
	// 设置图片控件尺寸
	m_ctrlWidth = 1200;
	m_ctrlHeight = 800;
	GetDlgItem(IDC_PICTURE)->SetWindowPos(NULL, 0, 0, m_ctrlWidth, m_ctrlHeight, SWP_NOMOVE); //固定大小的窗口
	GetDlgItem(IDC_REMIND1)->SetWindowPos(NULL, 0, 800, m_ctrlWidth,32, SWP_NOMOVE);
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
		CDialogEx::OnPaint();

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
	// TODO: 在此添加控件通知处理程序代码

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
	m_dWidthScale = w / m_srcImg.cols;
	m_dHeightScale = h / m_srcImg.rows;
	// 允许调整尺寸
	GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);
	m_remind1.SetWindowText(_T("请选择操作类型！"));

}
bool CchiropracticDlg::intersect(CvPoint aa, CvPoint bb, CvPoint cc, CvPoint dd)
{
	double delta = determinant(bb.x - aa.x, cc.x - dd.x, bb.y - aa.y, cc.y - dd.y);
	if (delta <= (1e-6) && delta >= -(1e-6))  // delta=0，表示两线段重合或平行  
	{
		return false;
	}
	double namenda = determinant(cc.x - aa.x, cc.x - dd.x, cc.y - aa.y, cc.y - dd.y) / delta;
	if (namenda>1 || namenda<0)
	{
		return false;
	}
	double miu = determinant(bb.x - aa.x, cc.x - aa.x, bb.y - aa.y, cc.y - aa.y) / delta;
	if (miu>1 || miu<0)
	{
		return false;
	}
	return true;
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
	//m_bDrawRect = true;
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

	m_dWidthScale = w / m_srcImg.cols;
	m_dHeightScale = h / m_srcImg.rows;
	return;
}
void CchiropracticDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	m_imgX = 0;
	m_imgY = 0;
	m_zoom = 1;
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
	if ((m_opType == DRAW_RECT) && m_bLButtonDown)		//区域选择
	{
		int r = 1;
		cv::rectangle(m_maskShowImg, m_p1, pt, cv::Scalar(255), r);
		Invalidate();
	} 
	else if (m_opType == DIAG_QIAGU)			// 髂骨诊断
	{
		cv::circle(m_maskShowImg, pt, 3, m_maskColor, -1);
		if (m_curStep == 1 )
		{
			cv::line(m_maskShowImg, m_gp[0], pt, m_maskColor, m_lineWidth);
		}
	}	
	else if (m_opType == DIAG_DIGU )		// 骶骨诊断
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
	if (!PtInRect(&rectBox, point))
		return;
	// 不在图片中，则返回
	cv::Point pt;
	pt.x = point.x - rectBox.left; // 求相对于控件的坐标
	pt.y = point.y - rectBox.top;
	pt.x = pt.x / m_zoom - m_imgX;	// 求相对于图像的坐标
	pt.y = pt.y / m_zoom - m_imgY;
	if (pt.x < 0 || pt.y < 0 || pt.x > m_srcImg.cols || pt.y > m_srcImg.rows)
		return;
	// 零、截图操作
	if (m_opType == DRAW_RECT)
	{
		m_p2 = pt;
		// m_p2位于m_p1 左上角
		if (m_p1.x > m_p2.x && m_p1.y > m_p2.y)
		{
			cv::Point t;
			t = m_p1;
			m_p1 = m_p2;
			m_p2 = t;
		}
		// m_p2位于m_p1 左下角
		else if (m_p1.x > m_p2.x && m_p1.y < m_p2.y)
		{
			cv::Point t1,t2;
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
	else if (m_opType == DIAG_QIAGU && m_curStep < 10) // 操作从0到9
	{
		// 0、1 基准线
		if (m_curStep == 0)
		{
			m_gp[0] = pt;
			cv::circle(m_maskImg, pt, m_circleRadius, m_maskColor, -1);
		}
		if (m_curStep == 1)
		{
			m_gp[1] = pt;
			cv::circle(m_maskImg, pt, m_circleRadius, m_maskColor, -1);

			m_grad_gugu_x = double(m_gp[0].y - m_gp[1].y) / (m_gp[0].x - m_gp[1].x + 10e-8); // 求斜率
			m_grad_gugu_y = -1.0f / (m_grad_gugu_x + 10e-8);
			cv::line(m_maskImg, m_gp[0], m_gp[1], m_maskColor, m_lineWidth);

			logInfo log = { 0 };    // 写入日志
			log.p[0] = m_gp[0];
			log.p[1] = m_gp[1];
			log.op = DRAW_LINE;
			log.step = m_curStep;
			m_vecLog.push_back(log);
		}
		// 左高
		if (m_curStep == 2)
		{
			m_gp[2] = pt;
			cv::circle(m_maskImg, pt, m_circleRadius, m_maskColor, -1);

			lineExt(m_grad_gugu_x, pt, pt.x, (m_srcImg.cols/2 - pt.x)/2, m_p1, m_p2);  // 左边
			cv::line(m_maskImg, m_p1, m_p2, m_maskColor, m_lineWidth);

			logInfo log = { 0 };    // 写入日志
			log.p[0] = m_p1;
			log.p[1] = m_p2;
			log.center[0] = m_gp[2]; // 保存关键点
			log.op = DRAW_LINE;
			log.step = m_curStep;
			m_vecLog.push_back(log);
		}
		// 左底
		if (m_curStep == 3)
		{
			m_gp[3] = pt;
			cv::circle(m_maskImg, pt, m_circleRadius, m_maskColor, -1);

			lineExt(m_grad_gugu_x, pt, pt.x, (m_srcImg.cols / 2 - pt.x) / 2, m_p1, m_p2);
			cv::line(m_maskImg, m_p1, m_p2, m_maskColor, m_lineWidth);

			logInfo log = { 0 };    // 写入日志
			// 求交点
			cv::Point dot;
			dot = lineCrossDot(m_grad_gugu_x, pt, m_gp[2]);   // 直线外点与直线的交点
			cv::line(m_maskImg, m_gp[2], dot, m_maskColor, m_lineWidth);
			// 计算测量长度
			double length = m_dHeightScale * std::sqrt((m_gp[2].x - dot.x)*(m_gp[2].x - dot.x) + (m_gp[2].y - dot.y)*(m_gp[2].y - dot.y));
			// 保存测量结果
			sprintf_s(log.text, "%.1fmm", length);
			// 显示测量结果
			cv::Point center = cv::Point(m_gp[2].x, (m_gp[2].y + pt.y) * 2 / 3);
			cv::putText(m_maskImg, log.text, center, m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_maskColor,m_fontThicknessOfMeasure);

			m_dLlength_wuminggu = length;

			// 保存标注信息
			// p[0~1] 正常直线，p[2~3]测量线
			// center[0] 画直线时所取关键点，center[1] 测量线文字放置位置
			log.p[0] = m_p1;
			log.p[1] = m_p2;
			log.p[2] = m_gp[2];
			log.p[3] = dot;
			log.center[0] = m_gp[3]; // 保存关键点
			log.center[1] = center; // 保存关键点
			log.length = length;
			log.op = DRAW_LINE_MEASURE;
			log.step = m_curStep;
			m_vecLog.push_back(log);
		}
		// 右高
		if (m_curStep == 4)
		{
			m_gp[4] = pt;
			cv::circle(m_maskImg, pt, m_circleRadius, m_maskColor, -1);

			lineExt(m_grad_gugu_x, pt, (pt.x - m_srcImg.cols / 2) / 2, m_srcImg.cols - pt.x, m_p1, m_p2);
			cv::line(m_maskImg, m_p1, m_p2, m_maskColor, m_lineWidth);

			logInfo log = { 0 };    // 写入日志
			log.p[0] = m_p1;
			log.p[1] = m_p2;
			log.center[0] = m_gp[4];
			log.op = DRAW_LINE;
			log.step = m_curStep;
			m_vecLog.push_back(log);}
		// 右底
		if (m_curStep == 5)
		{
			m_gp[5] = pt;
			cv::circle(m_maskImg, pt, m_circleRadius, m_maskColor, -1);

			lineExt(m_grad_gugu_x, pt, (pt.x - m_srcImg.cols / 2) / 2, m_srcImg.cols - pt.x, m_p1, m_p2);
			cv::line(m_maskImg, m_p1, m_p2, m_maskColor, m_lineWidth);

			logInfo log = { 0 };    // 写入日志
			// 标注
			cv::Point dot;
			dot = lineCrossDot(m_grad_gugu_x, pt, m_gp[4]);
			cv::line(m_maskImg, m_gp[4], dot, m_maskColor, m_lineWidth);

			double length = m_dHeightScale * std::sqrt((m_gp[4].x - dot.x)*(m_gp[4].x - dot.x) + (m_gp[4].y - dot.y)*(m_gp[4].y - dot.y));
			sprintf_s(log.text, "%.1fmm", length);
			cv::Point center = cv::Point(m_gp[4].x, (m_gp[4].y + pt.y) * 2 / 3);
			cv::putText(m_maskImg, log.text, center, m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_maskColor, m_fontThicknessOfMeasure);
			m_dRlength_wuminggu = length;

			// 保存标注信息
			// p[0~1] 正常直线，p[2~3]测量线
			// center[0] 画直线时所取关键点，center[1] 测量线文字放置位置
			log.p[0] = m_p1;
			log.p[1] = m_p2;
			log.p[2] = m_gp[4];
			log.p[3] = dot;
			log.center[0] = m_gp[5]; // 保存关键点
			log.center[1] = center; // 保存关键点
			log.length = length;
			log.op = DRAW_LINE_MEASURE;
			log.step = m_curStep;
			m_vecLog.push_back(log);
		}
		// 竖1
		if (m_curStep == 6)
		{
			m_gp[6] = pt;
			cv::circle(m_maskImg, pt, m_circleRadius, m_maskColor, -1);

			if (m_grad_gugu_y >0)
				lineExt(m_grad_gugu_y, pt, m_srcImg.rows / 20, m_srcImg.rows - pt.y, m_p1, m_p2);
			else
				lineExt(m_grad_gugu_y, pt, m_srcImg.rows - pt.y, m_srcImg.rows / 20, m_p1, m_p2);
			cv::line(m_maskImg, m_p1, m_p2, m_maskColor, m_lineWidth);

			logInfo log = { 0 };    // 写入日志
			log.p[0] = m_p1;
			log.p[1] = m_p2;
			log.center[0] = m_gp[6];
			log.op = DRAW_LINE;
			log.step = m_curStep;
			m_vecLog.push_back(log);
		}
		// 竖2
		if (m_curStep == 7)
		{
			m_gp[7] = pt;
			cv::circle(m_maskImg, pt, m_circleRadius, m_maskColor, -1);

			if (m_grad_gugu_y >0)
				lineExt(m_grad_gugu_y, pt, m_srcImg.rows/20, m_srcImg.rows - pt.y, m_p1, m_p2);
			else
				lineExt(m_grad_gugu_y, pt, m_srcImg.rows - pt.y, m_srcImg.rows / 20, m_p1, m_p2);
			cv::line(m_maskImg, m_p1, m_p2, m_maskColor, m_lineWidth);

			logInfo log = { 0 };    // 写入日志
			// 标注
			cv::Point dot;
			dot = lineCrossDot(m_grad_gugu_y, m_gp[6], pt);
			double length = m_dHeightScale * std::sqrt((pt.x - dot.x)*(pt.x - dot.x) + (pt.y - dot.y)*(pt.y - dot.y));
			cv::line(m_maskImg, pt, dot, m_maskColor, m_lineWidth);

			sprintf_s(log.text, "%.1fmm", length);
			cv::Point center;
			if(m_gp[7].x < dot.x)		//耻骨联合中线偏左
			{
				int baseline = 0;
				cv::Size sz_wh = cv::getTextSize(log.text, m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_fontThicknessOfMeasure, &baseline);
				center = cv::Point(m_gp[7].x - sz_wh.width, m_gp[7].y + sz_wh.height/2);
			}
			else						//耻骨联合中线偏右,或相等
			{
				center = cv::Point(m_gp[7].x, m_gp[7].y);
			}
			cv::putText(m_maskImg, log.text, center, m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_maskColor, m_fontThicknessOfMeasure);

			if (m_gp[7].x < dot.x)
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
			log.length = length;
			log.op = DRAW_LINE_MEASURE;
			log.step = m_curStep;
			m_vecLog.push_back(log);
		}
		// 8、9 判断原发侧
		if (m_curStep == 8)
		{
			m_gp[8] = pt;
			cv::circle(m_maskImg, pt, m_circleRadius, m_circleColor, -1);
			// 保存操作
			logInfo log = { 0 };
			log.center[1] = m_gp[8];
			log.op = DRAW_CIRCLE;
			log.step = m_curStep;
			m_vecLog.push_back(log);
		}
		if (m_curStep == 9)
		{
			// center[0]，操作关键点，center[1]诊断结果文字放置点
			m_gp[9] = pt;
			cv::circle(m_maskImg, pt, m_circleRadius, m_maskColor, -1);

			// 保存操作
			logInfo log = { 0 };
			log.center[0] = m_gp[9];
			// 进行诊断
			cv::Point pose;
			m_qiagu_diagnose = diagnose(DIAG_QIAGU,pose);
			// 保存诊断结果
			log.center[1] = pose;
			memcpy(log.text, m_qiagu_diagnose.GetBuffer(), m_qiagu_diagnose.GetLength() + 1);
			// 放置诊断结果
			cv::putText(m_maskImg, log.text, pose, m_fontTypeOfDiagnose, m_dFontSizeOfDiagnose, m_maskColor);
			// 写入操作
			log.op = DRAW_DIAGNOSE;
			log.step = m_curStep;
			m_vecLog.push_back(log);
			// 取消所有勾选操作
			//OnRButtonDown(NULL, NULL);
		}

		++m_curStep;
		m_bNeedSave = true;
		//有新操作后就不能再返回了
		cv::vector<logInfo>().swap(m_vecDelLog);
		remindColor();
	} /* 一、髂骨半脱位 */
//===============================================================================================================
	// 二、 骶骨半脱位
	else if (m_opType == DIAG_DIGU && m_curStep < 9)	// 操作从0到8
	{
		// 0、1股骨头线
		if (m_curStep == 0)
		{
			m_gp[0] = pt;
			cv::circle(m_maskImg, pt, m_circleRadius, m_maskColor, -1);
		}
		else if (m_curStep == 1)
		{
			m_gp[1] = pt;
			cv::circle(m_maskImg, pt, m_circleRadius, m_maskColor, -1);

			m_grad_gugu_x = double(m_gp[0].y - m_gp[1].y) / (m_gp[0].x - m_gp[1].x + 10e-8); // 求斜率
			m_grad_gugu_y = -1.0f / (m_grad_gugu_x + 10e-8);
			// 画出股骨头线
			cv::line(m_maskImg, m_gp[0], m_gp[1], m_maskColor, m_lineWidth);
			// 写入操作
			logInfo log = { 0 };   
			log.p[0] = m_gp[0];
			log.p[1] = m_gp[1];
			log.op = DRAW_LINE;
			log.step = m_curStep;
			m_vecLog.push_back(log);
		}
		// 2 股骨头线垂直线
		else if (m_curStep == 2)
		{
			m_gp[2] = pt;
			cv::circle(m_maskImg, pt, m_circleRadius, m_maskColor, -1);
			//求延长线
			if (m_grad_gugu_y >0)
				lineExt(m_grad_gugu_y, pt, m_srcImg.rows / 20, m_srcImg.rows - pt.y, m_p1, m_p2);
			else
				lineExt(m_grad_gugu_y, pt, m_srcImg.rows - pt.y, m_srcImg.rows / 20, m_p1, m_p2);
			// 画出股骨头线垂直线
			cv::line(m_maskImg, m_p1, m_p2, m_maskColor, m_lineWidth);
			//写入操作
			logInfo log = { 0 };
			log.p[0] = m_p1;
			log.p[1] = m_p2;
			log.center[0] = m_gp[2];
			log.op = DRAW_LINE;
			log.step = m_curStep;
			m_vecLog.push_back(log);
		}
		// 3、4骶骨水平线
		else if (m_curStep == 3)
		{
			m_gp[3] = pt;
			cv::circle(m_maskImg, pt, m_circleRadius, m_maskColor, -1);
		}
		else if (m_curStep == 4)   // 此处要画四条线
		{
			// P[0~1]骶骨水平线，p[2~3] 骶骨水平线垂线，p[4~5] 过较高骶沟点做股骨头水平线的平行线， p[6~7] 过较低骶沟点与p[4~5]垂直的线
			// center[0~1] P[0~1]的关键点，center[2] 向下偏拉距离文字放置位置
			logInfo log = { 0 };    
			m_gp[4] = pt;
			m_grad_digu_x = double(m_gp[4].y - m_gp[3].y) / (m_gp[4].x - m_gp[3].x + 10e-8); // 求斜率
			m_grad_digu_y = -1.0f / (m_grad_digu_x + 10e-8);
			// 1. 做骶骨水平线
			cv::Point temp1, temp2;
			lineExt(m_grad_digu_x, m_gp[3], m_gp[3].x / 2, 0, temp1, temp2);
			m_p1 = temp1;
			lineExt(m_grad_digu_x, m_gp[4], 0, (m_srcImg.cols - m_gp[4].x)/2, temp1, temp2);
			m_p2 = temp2;
			// 画出骶骨水平线和点
			cv::circle(m_maskImg, m_gp[3], m_circleRadius, m_maskColor, -1);
			cv::circle(m_maskImg, m_gp[4], m_circleRadius, m_maskColor, -1);
			cv::line(m_maskImg,m_p1, m_p2, m_lineColor, m_lineWidth);
			// 写入操作
			log.p[0] = m_p1;
			log.p[1] = m_p2;
			log.center[0] = m_gp[3];
			log.center[1] = m_gp[4];
			// 2. 过m_gp[2]做骶骨水平线的垂直线
			cv::Point dot = lineCrossDot(m_grad_digu_x, m_gp[3], m_gp[2]);
			if (m_grad_digu_y > 0)	// top 在左边
				lineExt(m_grad_digu_y, dot, 0, m_gp[0].y - dot.y, m_p1, m_p2);
			else                    // top 在右边
				lineExt(m_grad_digu_y, dot, m_gp[0].y - dot.y, 0, m_p1, m_p2);
			//画出骶骨水平线的垂直线
			cv::line(m_maskImg, m_p1, m_p2, m_lineColor, m_lineWidth);
			// 写入操作
			log.p[2] = m_p1;
			log.p[3] = m_p2;
			// 3. 过骶沟较高点做股骨头线的平行线
			if (m_gp[3].y > m_gp[4].y)  //左侧偏下，右侧偏上
			{
				// 过m_gp[4]做股骨头线的平行线
				// 延长线向左延长
				lineExt(m_grad_gugu_x, m_gp[4], m_gp[4].x - (log.p[0].x + m_gp[3].x) / 2, 0, m_p1, m_p2);
			}
			else if (m_gp[3].y < m_gp[4].y)  //左侧偏上，右侧偏下
			{
				// 过m_gp[3]做股骨头线的平行线，
				// 延长线向右延长
				lineExt(m_grad_gugu_x, m_gp[3], 0, (log.p[1].x + m_gp[4].x) / 2-m_gp[3].x, m_p1, m_p2);
			}
			else if (m_gp[3].y == m_gp[4].y)	// ？？？？？？？相等无法判断
			{
				// 两边相等，随便选一个了，此处选向左延长
				// 过m_gp[4]做股骨头线的平行线
				// 延长线向左延长
				lineExt(m_grad_gugu_x, m_gp[4], m_gp[4].x - (log.p[0].x + m_gp[3].x) / 2, 0, m_p1, m_p2);
			}
			// 写入操作
			log.p[4] = m_p1;
			log.p[5] = m_p2;
			// 画出股骨头线的平行线
			cv::line(m_maskImg, log.p[4], log.p[5], m_maskColor, m_lineWidth);
			//4. 过骶沟较低点做股骨头线平行线的垂线
			if (m_gp[3].y > m_gp[4].y)  //左侧偏下，右侧偏上
			{
				// 过m_gp[4]做股骨头线的平行线,过m_gp[3]求与它的垂直点
				dot = lineCrossDot(m_grad_gugu_x, m_gp[4], m_gp[3]);
				//求向下偏拉距离
				m_dDigu_down = m_dHeightScale * std::sqrt((dot.x - m_gp[3].x)*(dot.x - m_gp[3].x) + (dot.y - m_gp[3].y)*(dot.y - m_gp[3].y));
				// 保存直线
				log.p[6] = dot;
				log.p[7] = m_gp[3];
			}
			else if (m_gp[3].y < m_gp[4].y)  //左侧偏上，右侧偏下
			{
				// 过m_gp[3]做股骨头线的平行线,过m_gp[4]求与它的垂直点
				dot = lineCrossDot(m_grad_gugu_x, m_gp[3], m_gp[4]);
				//求向下偏拉距离
				m_dDigu_down = m_dHeightScale * std::sqrt((dot.x - m_gp[4].x)*(dot.x - m_gp[4].x) + (dot.y - m_gp[4].y)*(dot.y - m_gp[4].y));
				// 保存直线
				log.p[6] = dot;
				log.p[7] = m_gp[4];
			}
			else if (m_gp[3].y == m_gp[4].y)	// ？？？？？？？相等无法判断
			{
				// 两边相等，随便选一个了，此处选向左延长
				// 过m_gp[4]做股骨头线的平行线，过m_gp[3]求与它的垂直点
				dot = lineCrossDot(m_grad_gugu_x, m_gp[4], m_gp[3]);
				//求向下偏拉距离,为0
				m_dDigu_down = m_dHeightScale * std::sqrt((dot.x - m_gp[3].x)*(dot.x - m_gp[3].x) + (dot.y - m_gp[3].y)*(dot.y - m_gp[3].y));
				// 保存直线
				log.p[6] = dot;
				log.p[7] = m_gp[3];
			}
			// 画出该直线
			//cv::circle(m_maskImg, log.p[6], m_circleRadius, m_maskColor, -1);
			cv::line(m_maskImg, log.p[6], log.p[7], m_maskColor, m_lineWidth);
			// 写入长度
			log.length = m_dDigu_down;
			log.center[2] = dot;
			sprintf_s(log.text, "%.1fmm", m_dDigu_down);
			// 标注长度
			cv::putText(m_maskImg, log.text, log.center[2], m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_maskColor,m_fontThicknessOfMeasure);
			//写入操作类型和步骤
			log.op = DRAW_DIGU_LINE;
			log.step = m_curStep;
			m_vecLog.push_back(log);
		}
		// 5 左骶骨最外侧缘 做骶骨水平线的垂线
		else if (m_curStep == 5)
		{ 
			// P[0~1] 为垂直线， p[2~3]为测量线
			//center[0]为垂直线关键点，center[1]为测量线文字放置关键点
			logInfo log = { 0 };
			m_gp[5] = pt;
			// 求左垂线与骶骨水平线的垂直点
			cv::Point dot;
			dot = lineCrossDot(m_grad_digu_x, m_gp[3], m_gp[5]);
			//求从dot点延长线
			if (m_grad_digu_y >0)	// top 在左边
				lineExt(m_grad_digu_y, dot, 0, m_gp[0].y - dot.y, m_p1, m_p2);
			else                    // top 在右边
				lineExt(m_grad_digu_y, dot, m_gp[0].y - dot.y, 0, m_p1, m_p2);
			// 画出直线
			cv::circle(m_maskImg, m_gp[5], m_circleRadius, m_maskColor, -1);
			cv::line(m_maskImg, m_p1, m_p2, m_maskColor, m_lineWidth);
			//写入操作
			log.p[0] = m_p1;
			log.p[1] = m_p2;
			log.center[0] = m_gp[5];
			// 求该直线到第一节点m_gp[2]的距离
			dot = lineCrossDot(m_grad_digu_y, m_gp[5], m_gp[2]);
			m_dLlength_digu = m_dWidthScale * std::sqrt((dot.x - m_gp[2].x)*(dot.x - m_gp[2].x) + (dot.y - m_gp[2].y)*(dot.y - m_gp[2].y));
			//画出第一节点m_gp[2]到左边垂直于骶骨水平线的垂直线(距离测量线)
			cv::line(m_maskImg, dot, m_gp[2], m_maskColor, m_lineWidth);
			// 标注距离测量值
			sprintf_s(log.text, "%.1fmm", m_dLlength_digu);
			int baseline = 0;
			cv::Size sz_wh = cv::getTextSize(log.text, m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_fontThicknessOfMeasure, &baseline);
			log.center[1] = cv::Point((dot.x + m_gp[2].x) / 2 - sz_wh.width/2, (dot.y + m_gp[2].y) / 2 + 1.5*sz_wh.height);
			cv::putText(m_maskImg, log.text, log.center[1], m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_maskColor, m_fontThicknessOfMeasure);
			//写入操作
			log.p[2] = dot;
			log.p[3] = m_gp[2];
			log.op = DRAW_LINE_MEASURE;
			log.step = m_curStep;
			m_vecLog.push_back(log);
		}
		// 6 右骶骨最外侧缘 做骶骨水平线的垂线
		else if (m_curStep == 6)
		{
			// P[0~1] 为垂直线， p[2~3]为测量线
			//center[0]为垂直线关键点，center[1]为测量线文字放置关键点
			logInfo log = { 0 };
			m_gp[6] = pt;
			// 求左垂线与骶骨水平线的垂直点
			cv::Point dot;
			dot = lineCrossDot(m_grad_digu_x, m_gp[4], m_gp[6]);
			//求从dot点延长线
			if (m_grad_digu_y >0)	// top 在左边
				lineExt(m_grad_digu_y, dot, 0, m_gp[0].y - dot.y, m_p1, m_p2);
			else                    // top 在右边
				lineExt(m_grad_digu_y, dot, m_gp[0].y - dot.y, 0, m_p1, m_p2);
			// 画出直线
			cv::circle(m_maskImg, m_gp[6], m_circleRadius, m_maskColor, -1);
			cv::line(m_maskImg, m_p1, m_p2, m_maskColor, m_lineWidth);
			//写入操作
			log.p[0] = m_p1;
			log.p[1] = m_p2;
			log.center[0] = m_gp[6];
			// 求该直线到第一节点m_gp[2]的距离
			dot = lineCrossDot(m_grad_digu_y, m_gp[6], m_gp[2]);
			m_dRlength_digu = m_dWidthScale * std::sqrt((dot.x - m_gp[2].x)*(dot.x - m_gp[2].x) + (dot.y - m_gp[2].y)*(dot.y - m_gp[2].y));
			//画出第一节点m_gp[2]到左边垂直于骶骨水平线的垂直线(距离测量线)
			cv::line(m_maskImg, dot, m_gp[2], m_maskColor, m_lineWidth);
			// 标注距离测量值
			sprintf_s(log.text, "%.1fmm", m_dRlength_digu);
			int baseline = 0;
			cv::Size sz_wh = cv::getTextSize(log.text, m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_fontThicknessOfMeasure, &baseline);
			log.center[1] = cv::Point((dot.x + m_gp[2].x) / 2 - sz_wh.width / 2, (dot.y + m_gp[2].y) / 2 + 1.5*sz_wh.height);
			cv::putText(m_maskImg, log.text, log.center[1], m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_maskColor, m_fontThicknessOfMeasure);
			//写入操作
			log.p[2] = dot;
			log.p[3] = m_gp[2];
			log.op = DRAW_LINE_MEASURE;
			log.step = m_curStep;
			m_vecLog.push_back(log);
		}
		// 7,8 判断原发侧
		// 7 左侧点
		else if (m_curStep == 7)
		{
			// center[0] 为关键点
			m_gp[7] = pt;
			cv::circle(m_maskImg, m_gp[7], m_circleRadius, m_maskColor, -1);
			// 保存操作
			logInfo log = { 0 };
			log.center[0] = m_gp[7];
			log.op = DRAW_CIRCLE;
			log.step = m_curStep;
			m_vecLog.push_back(log);
		}
		// 8 右侧点
		else if (m_curStep == 8)
		{
			// center[0] 为关键点，center[1]为诊断结果文字标注位置点
			m_gp[8] = pt;
			cv::circle(m_maskImg, m_gp[8], m_circleRadius, m_maskColor, -1);
			// 保存操作
			logInfo log = { 0 };
			log.center[0] = m_gp[8];
			// 进行诊断
			cv::Point pose;
			m_digu_diagnose = diagnose(DIAG_DIGU, pose);
			// 保存诊断结果
			log.center[1] = pose;
			memcpy(log.text, m_digu_diagnose.GetBuffer(), m_digu_diagnose.GetLength() + 1);
			// 放置诊断结果
			cv::putText(m_maskImg, log.text, pose, m_fontTypeOfDiagnose, m_dFontSizeOfDiagnose, m_maskColor);
			// 写入操作
			log.op = DRAW_DIAGNOSE;
			log.step = m_curStep;
			m_vecLog.push_back(log);
			// 取消所有勾选操作
			//OnRButtonDown(NULL, NULL);
		}
		++m_curStep;
		m_bNeedSave = true;
		//有新操作后就不能再返回了
		cv::vector<logInfo>().swap(m_vecDelLog);
		remindColor();
	}// 二、 骶骨半脱位
	Invalidate();
	CDialogEx::OnLButtonUp(nFlags, point);
}
// 撤销
void CchiropracticDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_vecLog.size() == 0) return;
	m_maskImg.setTo(0);
	m_maskShowImg.setTo(0);

	if (m_opType == DIAG_QIAGU)
	{
		logInfo log = { 0 };
		log = m_vecLog.back();
		m_vecDelLog.push_back(log);
		m_vecLog.pop_back();

		if (log.step == 1)		// 是股骨头线，撤销这条线，当前操作要回0步
			m_curStep = 0;
		else
			--m_curStep;
		//重画
		for (vector<logInfo>::iterator it = m_vecLog.begin(); it != m_vecLog.end(); ++it)
		{
			logInfo log = *it;
			if (log.op == DRAW_DIAGNOSE)
			{
				cv::circle(m_maskImg, log.center[0], m_circleRadius, m_circleColor, -1);
				cv::putText(m_maskImg, log.text, log.center[1], m_fontTypeOfDiagnose, m_dFontSizeOfDiagnose, m_maskColor);
			}
			else if (log.op == DRAW_LINE)
			{
				if (log.step == 1)	// 股骨头线的关键点与其他不同
				{
					cv::circle(m_maskImg, log.p[0], m_circleRadius, m_maskColor, -1);
					cv::circle(m_maskImg, log.p[1], m_circleRadius, m_maskColor, -1);
				}
				else
					cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
				cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
			}
			else if (log.op == DRAW_LINE_MEASURE)
			{
				cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
				cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
				cv::line(m_maskImg, log.p[2], log.p[3], m_maskColor, m_lineWidth);
				cv::putText(m_maskImg, log.text, log.center[1], m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_maskColor);
			}
			else if (log.op == DRAW_CIRCLE)
			{
				cv::circle(m_maskImg, log.center[1], m_circleRadius, m_maskColor, -1);
			}
		}
	}
	else if (m_opType == DIAG_DIGU)
	{
		logInfo log = { 0 };
		log = m_vecLog.back();
		m_vecDelLog.push_back(log);
		m_vecLog.pop_back();
		if (log.step == 1 || log.step == 4)
			m_curStep -= 2;
		else
			--m_curStep;
		//重画
		for (vector<logInfo>::iterator it = m_vecLog.begin(); it != m_vecLog.end(); ++it)
		{
			logInfo log = *it;
			if (log.op == DRAW_DIAGNOSE)
			{
				cv::circle(m_maskImg, log.center[0], m_circleRadius, m_circleColor, -1);
				cv::putText(m_maskImg, log.text, log.center[1], m_fontTypeOfDiagnose, m_dFontSizeOfDiagnose, m_maskColor,m_fontThicknessOfDiagnose);
			}
			else if (log.op == DRAW_LINE_MEASURE)
			{
				// 两条垂直线
				cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
				cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
				cv::line(m_maskImg, log.p[2], log.p[3], m_maskColor, m_lineWidth);
				cv::putText(m_maskImg, log.text, log.center[1], m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_maskColor, m_fontThicknessOfMeasure);
			}
			else if (log.op == DRAW_DIGU_LINE)
			{
				// 画出骶骨水平线和点
				cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
				cv::circle(m_maskImg, log.center[1], m_circleRadius, m_maskColor, -1);
				cv::line(m_maskImg, log.p[0], log.p[1], m_lineColor, m_lineWidth);
				//画出骶骨水平线的垂直线
				cv::line(m_maskImg, log.p[2], log.p[3], m_lineColor, m_lineWidth);
				// 画出股骨头线的平行线
				cv::line(m_maskImg, log.p[4], log.p[5], m_maskColor, m_lineWidth);
				// 画出垂直股骨头平行线的垂线
				cv::line(m_maskImg, log.p[6], log.p[7], m_maskColor, m_lineWidth);
				// 标注长度
				cv::putText(m_maskImg, log.text, log.center[2], m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_maskColor, m_fontThicknessOfMeasure);
			}
			else if (log.op == DRAW_LINE)
			{
				if (log.step == 1)
				{
					// 股骨头线
					cv::circle(m_maskImg, log.p[0], m_circleRadius, m_maskColor, -1);
					cv::circle(m_maskImg, log.p[1], m_circleRadius, m_maskColor, -1);
					cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
				}
				else
				{
					// 股骨头线垂直线
					cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
					cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
				}
			}

			else if (log.op == DRAW_CIRCLE)
			{
				cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
			}
		}
	}
	//m_maskImg.copyTo(m_maskShowImg);
	remindColor();
	Invalidate();
}
// 重做
void CchiropracticDlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_vecDelLog.size() == 0) return;
	logInfo log = { 0 };
	log = m_vecDelLog.back();
	m_vecLog.push_back(log);
	m_vecDelLog.pop_back();

	// 添加回操作
	if (m_opType == DIAG_QIAGU)
	{
		if (log.step == 1)
			m_curStep += 2;
		else
			++m_curStep;

		if (log.op == DRAW_DIAGNOSE)
		{
			cv::circle(m_maskImg, log.center[0], m_circleRadius, m_circleColor, -1);
			cv::putText(m_maskImg, log.text, log.center[1], m_fontTypeOfDiagnose, m_dFontSizeOfDiagnose, m_maskColor);
		}
		else if (log.op == DRAW_LINE)
		{
			if (log.step == 1)	// 股骨头线的关键点与其他不同
			{
				cv::circle(m_maskImg, log.p[0], m_circleRadius, m_maskColor, -1);
				cv::circle(m_maskImg, log.p[1], m_circleRadius, m_maskColor, -1);
			}
			else
				cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
			cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
			//++m_curStep;
		}
		else if (log.op == DRAW_LINE_MEASURE)
		{
			cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
			cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
			cv::line(m_maskImg, log.p[2], log.p[3], m_maskColor, m_lineWidth);
			cv::putText(m_maskImg, log.text, log.center[1], m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_maskColor);
			//++m_curStep;
		}
		else if (log.op == DRAW_CIRCLE)
		{
			cv::circle(m_maskImg, log.center[1], m_circleRadius, m_maskColor, -1);
			//++m_curStep;
		}
	}
	else if (m_opType == DIAG_DIGU)
	{
		if (log.step == 1 || log.step == 4)
			m_curStep += 2;
		else
			++m_curStep;

		if (log.op == DRAW_DIAGNOSE)
		{
			cv::circle(m_maskImg, log.center[0], m_circleRadius, m_circleColor, -1);
			cv::putText(m_maskImg, log.text, log.center[0], m_fontTypeOfDiagnose, m_dFontSizeOfDiagnose, m_maskColor, m_fontThicknessOfDiagnose);
		}
		else if (log.op == DRAW_LINE_MEASURE)
		{
			// 两条垂直线
			cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
			cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
			cv::line(m_maskImg, log.p[2], log.p[3], m_maskColor, m_lineWidth);
			cv::putText(m_maskImg, log.text, log.center[1], m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_maskColor, m_fontThicknessOfMeasure);
			//++m_curStep;
		}
		else if (log.op == DRAW_DIGU_LINE)
		{
			// 画出骶骨水平线和点
			cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
			cv::circle(m_maskImg, log.center[1], m_circleRadius, m_maskColor, -1);
			cv::line(m_maskImg, log.p[0], log.p[1], m_lineColor, m_lineWidth);
			//画出骶骨水平线的垂直线
			cv::line(m_maskImg, log.p[2], log.p[3], m_lineColor, m_lineWidth);
			// 画出股骨头线的平行线
			cv::line(m_maskImg, log.p[4], log.p[5], m_maskColor, m_lineWidth);
			// 画出垂直股骨头平行线的垂线
			cv::line(m_maskImg, log.p[6], log.p[7], m_maskColor, m_lineWidth);
			// 标注长度
			cv::putText(m_maskImg, log.text, log.center[2], m_fontTypeOfMeasure, m_dFontSizeOfMeasure, m_maskColor, m_fontThicknessOfMeasure);
			//m_curStep += 2;
		}
		else if (log.op == DRAW_LINE)
		{
			if (log.step == 1)
			{
				// 股骨头线
				cv::circle(m_maskImg, log.p[0], m_circleRadius, m_maskColor, -1);
				cv::circle(m_maskImg, log.p[1], m_circleRadius, m_maskColor, -1);
				cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
				//m_curStep += 2;
			}
			else
			{
				// 股骨头线垂直线
				cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
				cv::line(m_maskImg, log.p[0], log.p[1], m_maskColor, m_lineWidth);
				//++m_curStep;
			}
		}

		else if (log.op == DRAW_CIRCLE)
		{
			cv::circle(m_maskImg, log.center[0], m_circleRadius, m_maskColor, -1);
			//++m_curStep;
		}
	}

	remindColor();
	Invalidate();
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
		m_dWidthScale = w / m_srcImg.cols;
		m_dHeightScale = h / m_srcImg.rows;
	}
	else if (strText == _T("7x8.5"))
	{
		double w, h; //实际尺寸(mm或英寸)
		w = 8.5*25.4;
		h = 7*25.4;
		m_dWidthScale = w / m_srcImg.cols;
		m_dHeightScale = h / m_srcImg.rows;
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
	m_zoomImg.setTo(m_maskColor, m_maskShowImg);	//绘制
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
	saveImg.setTo(m_lineColor, m_maskImg);
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
void  CchiropracticDlg::lineExt(double grad, cv::Point center, double lenth_l, double lenth_r, cv::Point &p_l, cv::Point &p_r)
{
	double delta_x, delta_y, delta_x1, delta_y1;
	delta_x = std::sqrt(lenth_l*lenth_l / (grad*grad + 1));
	delta_y = abs(grad * std::sqrt(lenth_l*lenth_l / (grad*grad + 1)));
	delta_x1 = std::sqrt(lenth_r*lenth_r / (grad*grad + 1));
	delta_y1 = abs(grad * std::sqrt(lenth_r*lenth_r / (grad*grad + 1)));

	if (grad > 0)
	{
		p_l.x = center.x - delta_x;
		p_l.y = center.y - delta_y;
		p_r.x = center.x + delta_x1;
		p_r.y = center.y + delta_y1;
	}
	else
	{
		p_l.x = center.x - delta_x;
		p_l.y = center.y + delta_y;
		p_r.x = center.x + delta_x1;
		p_r.y = center.y - delta_y1;
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
	CString result = _T("");
	if (op_type == DIAG_QIAGU)
	{
		// 判断原发侧
		if (m_gp[8].x == m_gp[9].x)
		{
			MessageBox(_T("无法判断原发侧，请撤销当前操作，并重新执行该步操作!"));
			pose = cv::Point(0, 0);
			return CString();
		}
		if (!(m_gp[8].x < m_gp[6].x && m_gp[6].x < m_gp[9].x))
		{
			MessageBox(_T("无法判断原发侧，请撤销当前操作，并重新执行该步操作!"));
			pose = cv::Point(0, 0);
			return CString();
		}
		else
		{
			double l, r;
			l = std::sqrt((m_gp[8].x - m_gp[6].x)*(m_gp[8].x - m_gp[6].x) + (m_gp[8].y - m_gp[6].y)*(m_gp[8].y - m_gp[6].y));
			r = std::sqrt((m_gp[9].x - m_gp[6].x)*(m_gp[9].x - m_gp[6].x) + (m_gp[9].y - m_gp[6].y)*(m_gp[9].y - m_gp[6].y));
			if (l < r)	//原发侧在右边，长的为原发侧
			{
				CString str = _T("");
				if (m_dLlength_wuminggu < m_dRlength_wuminggu)		// 右侧原发侧为PI
					str.Format(_T("PI%d"), int(std::round(std::abs(m_dLlength_wuminggu - m_dRlength_wuminggu))));
				else if (m_dLlength_wuminggu > m_dRlength_wuminggu)		// 右侧原发侧为AS
					str.Format(_T("AS%d"), int(std::round(std::abs(m_dLlength_wuminggu - m_dRlength_wuminggu))));
				else if (m_dLlength_wuminggu == m_dRlength_wuminggu)		// ？？？？？？？？？？？无法判断右侧原发侧为什么
					str = _T("");
				result += str;

				if (m_dLength < 0)		// 右侧原发侧为 Ex
					str.Format(_T("Ex%d"), int(std::round(std::abs(m_dLength))));
				else if (m_dLength > 0)	// 右侧原发侧为 In
					str.Format(_T("In%d"), int(std::round(m_dLength)));
				else if(m_dLength == 0)	// ????????????????????? 无法判断
					str = _T("");

				result += str;
				// 调整诊断结果文字放置位置
				int baseline = 0;
				cv::Size sz_wh = cv::getTextSize(result.GetBuffer(), m_fontTypeOfDiagnose, m_dFontSizeOfDiagnose, m_fontThicknessOfDiagnose, &baseline);
				pose = cv::Point(m_srcImg.cols * 7 / 8 - sz_wh.width / 2, m_srcImg.rows / 2 + sz_wh.height / 2);
			}
			else if (l > r)				//左侧为原发侧
			{
				CString str = _T("");
				if (m_dLlength_wuminggu > m_dRlength_wuminggu)		// 左侧原发侧为PI
					str.Format(_T("PI%d"), int(std::round(std::abs(m_dLlength_wuminggu - m_dRlength_wuminggu))));
				else if (m_dLlength_wuminggu < m_dRlength_wuminggu)		// 左侧原发侧为AS
					str.Format(_T("AS%d"), int(std::round(std::abs(m_dLlength_wuminggu - m_dRlength_wuminggu))));
				else if (m_dLlength_wuminggu == m_dRlength_wuminggu)		// ？？？？？？？？？？？无法判断左侧原发侧为什么
					str = _T("");
				result += str;

				if (m_dLength > 0)		// 左侧原发侧为 Ex
					str.Format(_T("Ex%d"), int(std::round(m_dLength)));
				else if (m_dLength < 0)	// 左侧原发侧为 In
					str.Format(_T("In%d"), int(std::round(std::abs(m_dLength))));
				else if (m_dLength == 0)	// ????????????????????? 无法判断
					str = _T("");
				result += str;
				// 调整诊断结果文字放置位置
				int baseline = 0;
				cv::Size sz_wh = cv::getTextSize(result.GetBuffer(), m_fontTypeOfDiagnose, m_dFontSizeOfDiagnose, m_fontThicknessOfDiagnose, &baseline);
				pose = cv::Point(m_srcImg.cols * 1 / 8 - sz_wh.width / 2, m_srcImg.rows / 2 + sz_wh.height / 2);
			}
			else if (l == r)
			{
				MessageBox(_T("无法判断原发侧，请撤销当前操作，并重新执行该步操作!"));
				pose = cv::Point(0, 0);
				return CString();
			}
		}
	}
	else if (op_type == DIAG_DIGU)
	{
		/////
		// 判断原发侧
		if (m_gp[7].x == m_gp[8].x)
		{
			MessageBox(_T("无法判断原发侧，请撤销当前操作，并重新执行该步操作!"));
			pose = cv::Point(0, 0);
			return CString();
		}
		if (!(m_gp[7].x < m_gp[2].x && m_gp[2].x < m_gp[8].x))
		{
			MessageBox(_T("无法判断原发侧，请撤销当前操作，并重新执行该步操作!"));
			pose = cv::Point(0, 0);
			return CString();
		}
		else
		{
			double l, r;
			l = m_dWidthScale * std::sqrt((m_gp[7].x - m_gp[2].x)*(m_gp[7].x - m_gp[2].x) + (m_gp[7].y - m_gp[2].y)*(m_gp[7].y - m_gp[2].y));
			r = m_dWidthScale * std::sqrt((m_gp[8].x - m_gp[2].x)*(m_gp[8].x - m_gp[2].x) + (m_gp[8].y - m_gp[2].y)*(m_gp[8].y - m_gp[2].y));
			// 判断是否有向下偏位
			bool bHasDown = false;
			double minus = std::abs(m_dLlength_digu - m_dRlength_digu);
			if (minus >= 7)
				bHasDown = true;
			else if (minus >= 4 && minus <= 6)
			{
				CString str;
				str.Format(_T("两侧距离之差为%.1fmm, 请判断是否有向下偏位？"), minus);
				INT_PTR ret = MessageBox(str, _T("确认"), MB_YESNO);
				if (ret == IDYES)
					bHasDown = true;
				else
					bHasDown = false;
			}
			//判断原发侧
			if (l < r)	//原发侧在右边，长的为原发侧
			{
				CString str = _T("");
				if (bHasDown)	// 有向下偏位
					result.Format(_T("P%dI%d-R"), int(std::round(std::abs(m_dLlength_digu - m_dRlength_digu))), int(std::round(m_dDigu_down)));
				else            // 没有向下偏拉
					result.Format(_T("P%d-R"), int(std::round(std::abs(m_dLlength_digu - m_dRlength_digu))));
				// 调整诊断结果文字放置位置
				int baseline = 0;
				cv::Size sz_wh = cv::getTextSize(result.GetBuffer(), m_fontTypeOfDiagnose, m_dFontSizeOfDiagnose, m_fontThicknessOfDiagnose, &baseline);
				pose = cv::Point(m_srcImg.cols * 7 / 8 - sz_wh.width / 2, m_srcImg.rows / 2 + sz_wh.height / 2);
			}
			else if (l > r)				//左侧为原发侧
			{
				CString str = _T("");
				if (bHasDown)	// 有向下偏位
					result.Format(_T("P%dI%d-L"), int(std::round(std::abs(m_dLlength_digu - m_dRlength_digu))), int(std::round(m_dDigu_down)));
				else            // 没有向下偏拉
					result.Format(_T("P%d-L"), int(std::round(std::abs(m_dLlength_digu - m_dRlength_digu))));
				// 调整诊断结果文字放置位置
				int baseline = 0;
				cv::Size sz_wh = cv::getTextSize(result.GetBuffer(), m_fontTypeOfDiagnose, m_dFontSizeOfDiagnose, m_fontThicknessOfDiagnose, &baseline);
				pose = cv::Point(m_srcImg.cols * 1 / 8 - sz_wh.width / 2, m_srcImg.rows / 2 + sz_wh.height / 2);
			}
			else if (l == r)
			{
				MessageBox(_T("无法判断原发侧，请撤销当前操作，并重新执行该步操作!"));
				pose = cv::Point(0, 0);
				return CString();
			}
		}

	}

	return result;
}

void CchiropracticDlg::initParam()
{	
	// debug 变量
	m_edit = 0;
	// 有用变量
	m_bLButtonDown = false;
	m_zoom = 1.0f;
	m_imgX = 0.0f;
	m_imgY = 0.0f;
	m_PtStart.X = 0.0f;
	m_PtStart.Y = 0.0f;

	m_dWidthScale = 1.0;
	m_dHeightScale = 1.0;
								// 画图相关参数
	m_circleRadius = 3;
	m_lineWidth = 1;													// 线的宽度
	m_maskColor = cv::Scalar(255, 255, 255);							// 蒙版颜色
	m_lineColor = cv::Scalar(255, 255, 255);							// 线的颜色, 白色
	m_circleColor = cv::Scalar(255, 0, 0);								// 小圆点的颜色， 绿色
	m_infoColor = cv::Scalar(0, 255, 0);								// CT片信息的文字颜色，黄色
	m_diagnoseColor = cv::Scalar(255, 0, 0);							// 诊断结果字体颜色，绿色
	m_measureColor = cv::Scalar(0, 0, 255);								// 划片时测量的值的颜色，红色
	m_fontTypeOfInfo = cv::FONT_HERSHEY_COMPLEX;						// CT片信息字体类型
	m_dFontSizeOfInfo = 1;												// CT片信息字体大小
	m_fontThicknessOfInfo = 2;											// CT片信息字体宽度
	m_fontTypeOfMeasure = cv::FONT_HERSHEY_COMPLEX;						// 划片时测量的值得字体类型
	m_dFontSizeOfMeasure = 1;											// 划片时测量的值得字体大小
	m_fontThicknessOfMeasure = 2;										// 划片时测量的值得宽度
	m_fontTypeOfDiagnose = cv::FONT_HERSHEY_COMPLEX;					// 诊断结果的字体类型
	m_dFontSizeOfDiagnose = 1;											// 诊断结果的字体大小
	m_fontThicknessOfDiagnose = 3;										// 诊断结果字体宽度

	// 髂骨操作提示语句
	m_csQiagu_remind[0] = _T("1.1 做股骨头线——选择左侧股骨头的最高点。");
	m_csQiagu_remind[1] = _T("1.2 做股骨头线——选择右侧股骨头的最高点。");
	m_csQiagu_remind[2] = _T("2.1 测左无名骨长度——选择左侧髂嵴的最高点。");
	m_csQiagu_remind[3] = _T("2.2 测左无名骨长度——选择左侧坐骨的最低点。");
	m_csQiagu_remind[4] = _T("3.1 测右无名骨长度——选择右侧髂嵴的最高点。");
	m_csQiagu_remind[5] = _T("3.2 测右无名骨长度——选择右侧坐骨的最低点。");
	m_csQiagu_remind[6] = _T("4. 做骶骨中线——选择第一骶骨棘突顶点。");
	m_csQiagu_remind[7] = _T("5. 做耻骨联合中线——选择耻骨联合中点。");
	m_csQiagu_remind[8] = _T("6.1 测量棘突中央到左侧椎体边缘的距离——选择左侧椎体边缘点。");
	m_csQiagu_remind[9] = _T("6.2 测量棘突中央到右侧椎体边缘的距离——选择右侧椎体边缘点。");
	m_csQiagu_remind[10] = _T("完成。");
	// 骶骨操作提示语句
	m_csDigu_remind[0] = _T("1.1 做股骨头线——选择左侧股骨头的最高点。");
	m_csDigu_remind[1] = _T("1.2 做股骨头线——选择右侧股骨头的最高点。");
	m_csDigu_remind[2] = _T("2. 做骶骨中线——选择第一骶骨棘突顶点。");
	m_csDigu_remind[3] = _T("3.1 做骶骨水平线——选择左侧骶沟点。");
	m_csDigu_remind[4] = _T("3.2 做骶骨水平线——选择右侧骶沟点。");
	m_csDigu_remind[5] = _T("4. 画左侧骶骨水平线的垂直线——选择左侧骶骨最外侧缘的点。");
	m_csDigu_remind[6] = _T("5. 画右侧骶骨水平线的垂直线——选择右侧骶骨最外侧缘的点。");
	m_csDigu_remind[7] = _T("6.1 测量棘突中央到左侧椎体边缘的距离——选择左侧椎体边缘点。");
	m_csDigu_remind[8] = _T("6.2 测量棘突中央到右侧椎体边缘的距离——选择右侧椎体边缘点。");
	m_csDigu_remind[9] = _T("完成。");
}

// 针对提示语句，对当前步骤的语句进行高亮
void CchiropracticDlg::remindColor()
{
	if (m_opType == -1)
		return;
	m_remind1.SetWindowText(m_csRemind[m_curStep].GetString());
	//if (m_opType == DIAG_QIAGU)
	//{
	//	switch (m_curStep)
	//	{
	//	case 0:
	//		m_remind1.SetWindowText(m_csRemind[0].GetString());
	//	case 1:		// 股骨头线
	//		m_remind1.SetWindowText(m_csRemind[1].GetString());
	//		break;
	//	case 2:
	//		m_remind1.SetWindowText(m_csRemind[2].GetString());
	//	case 3:		// 左侧无名骨
	//		m_remind1.SetWindowText(m_csRemind[3].GetString());
	//		break;
	//	case 4:
	//	case 5:		// 右侧无名骨
	//		m_remind1.SetWindowText(m_csRemind[2].GetString());
	//		break;
	//	case 6:		// 骶骨中线
	//		m_remind1.SetWindowText(m_csRemind[3].GetString());
	//		break;
	//	case 7:		// 耻骨联合中线
	//		m_remind1.SetWindowText(m_csRemind[4].GetString());
	//		break;
	//	case 8:		// 棘突到边缘距离
	//	case 9:
	//		m_remind1.SetWindowText(m_csRemind[5].GetString());
	//		break;
	//	case 10:	// 完成
	//		m_remind1.SetWindowText(m_csRemind[6].GetString());
	//		break;
	//	default:
	//		break;
	//	}
	//}
	//else if (m_opType == DIAG_DIGU)
	//{
	//	switch (m_curStep)
	//	{
	//	case 0:
	//	case 1:		// 股骨头线
	//		m_remind1.SetWindowText(m_csRemind[0].GetString());
	//		break;
	//	case 2:		// 骶骨中线
	//		m_remind1.SetWindowText(m_csRemind[1].GetString());
	//		break;
	//	case 3:		// 骶骨水平线
	//	case 4:
	//		m_remind1.SetWindowText(m_csRemind[2].GetString());
	//		break;
	//	case 5:		// 左垂直
	//		m_remind1.SetWindowText(m_csRemind[3].GetString());
	//		break;
	//	case 6:		// 右垂直
	//		m_remind1.SetWindowText(m_csRemind[4].GetString());
	//		break;		
	//	case 7:		// 棘突到边缘距离
	//	case 8:
	//		m_remind1.SetWindowText(m_csRemind[5].GetString());
	//		break;
	//	case 9:	// 完成
	//		m_remind1.SetWindowText(m_csRemind[6].GetString());
	//		break;
	//	default:
	//		break;
	//	}
	//}
	OnPaint();
}

bool CchiropracticDlg::dcm2Mat(const char* const fileName, cv::Mat & mat)
{

	DJDecoderRegistration::registerCodecs(); // register JPEG codecs  
	DcmFileFormat fileformat;										 //DcmFileFormat fileformat;
	fileformat.loadFile(fileName);
	//if (fileformat.loadFile("ct.1").good())

	DcmDataset *dataset = fileformat.getDataset();
	// decompress data set if compressed    
	dataset->chooseRepresentation(EXS_LittleEndianExplicit, NULL);
	DcmElement* element = NULL;
	OFCondition result = dataset->findAndGetElement(DCM_PixelData, element);
	if (result.bad() || element == NULL)
		return false;
	unsigned short* pixData;
	result = element->getUint16Array(pixData);

	
	OFintptr_t rows = 0;
	OFintptr_t cols = 0;
	dataset->findAndGetLongInt(DCM_Rows, rows);
	dataset->findAndGetLongInt(DCM_Columns, cols);

	if (rows == 0 || cols == 0)
		return false;

	unsigned short *pbuf = new unsigned short[rows*cols];

	memcpy(pbuf, pixData, rows*cols * 2);
	Mat xxx(rows, cols, CV_16SC1, pbuf);
	Mat xx;
	cv::normalize(xxx, xx, 0, 255, NORM_MINMAX, CV_8UC1);

	Mat afull(xx.rows, xx.cols, CV_8UC1, 255);  // 图像颜色反转，黑变白，白变黑
	xx = afull - xx;
	mat = xx.clone();
	
	cvtColor(mat, mat, CV_GRAY2RGB);

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
	m_opType = DIAG_QIAGU;
	m_csRemind = m_csQiagu_remind;		// 指向髂骨
	remindColor();
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
	m_opType = DIAG_DIGU;
	m_csRemind = m_csDigu_remind;		// 指向骶骨
	remindColor();
}


void CchiropracticDlg::OnBnClickedButtonOp3()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_srcImg.empty())
	{
		MessageBox(_T("请先载入图像！"));
		return;
	}
	m_curStep = 0;
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
