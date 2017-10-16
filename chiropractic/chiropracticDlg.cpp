
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
	, m_edit(0)
	, m_ctrlWidth(1065)
	, m_ctrlHeight(710)

{
	m_dWidthScale = 1.0;
	m_dHeightScale = 1.0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CchiropracticDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_COMBO1, m_Combo);
}

BEGIN_MESSAGE_MAP(CchiropracticDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CchiropracticDlg::OnBnClickedButton2)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON3, &CchiropracticDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CchiropracticDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON9, &CchiropracticDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON8, &CchiropracticDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON10, &CchiropracticDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON5, &CchiropracticDlg::OnBnClickedButton5)
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON7, &CchiropracticDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON1, &CchiropracticDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON6, &CchiropracticDlg::OnBnClickedButton6)
	ON_WM_MOUSEWHEEL()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CchiropracticDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON12, &CchiropracticDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON11, &CchiropracticDlg::OnBnClickedButton11)
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
	m_zoom = 1.0f;

	m_imgX = 0.0f;
	m_imgY = 0.0f;
	m_PtStart.X = 0.0f;
	m_PtStart.Y = 0.0f;

	m_bLButtonDown = false;
	GetDlgItem(IDC_PICTURE)->SetWindowPos(NULL, 0, 0, m_ctrlWidth, m_ctrlHeight, SWP_NOMOVE); //固定大小的窗口
	
	// 尺寸
	m_Combo.AddString(_T("尺寸"));
	m_Combo.AddString(_T("14x17"));
	m_Combo.AddString(_T("7x8.5"));
	int nIndex = m_Combo.FindStringExact(0, _T("尺寸"));
	if(nIndex != CB_ERR)
		m_Combo.SetCurSel(nIndex);

	

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
		TRUE, _T("*.bmp|*.jpeg"),
		NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image files (*.bmp; *.jpg;*.png) |*.bmp; *.jpg;*.jpeg;*.jge;*.png; ||"),
		NULL
	);                                        // 选项图片的约定
	dlg.m_ofn.lpstrTitle = _T("Open Image");    // 打开文件对话框的标题名
	if (dlg.DoModal() != IDOK)                    // 判断是否获得图片
		return;

	CString mPath = dlg.GetPathName();            // 获取图片路径
	int len = WideCharToMultiByte(CP_ACP, 0, mPath, -1, NULL, 0, NULL, NULL);
	char *ptxtTemp = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, mPath, -1, ptxtTemp, len, NULL, NULL);

	m_loadImg = imread(ptxtTemp, CV_LOAD_IMAGE_UNCHANGED);    // 读取图片
	delete[] ptxtTemp;

	if (m_loadImg.empty())                                    // 判断是否成功载入图片
		return;
	m_srcImg = m_loadImg.clone(); // 为什么这么用，看头文件
	m_zoomImg = m_loadImg.clone();
	//m_showImg = m_srcImg.clone();
	

	m_maskImg.create(m_srcImg.size(), CV_8UC1); // 掩膜图像
	m_maskShowImg.create(m_srcImg.size(), CV_8UC1); // 内部temp掩膜图像
	m_maskImg.setTo(0);
	m_maskShowImg.setTo(0);
	Invalidate();
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
	OnRButtonDown(NULL, NULL);
	m_bDrawRect = true;
	return;
}

// 画线
void CchiropracticDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	OnRButtonDown(NULL, NULL);
	m_bDrawLine = true;
	return;
}

// 重做
void CchiropracticDlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_vecDelLog.size() == 0) return;
	logInfo log = m_vecDelLog.back();
	m_vecLog.push_back(log); // 重新添加回操作日志
	m_vecDelLog.pop_back(); // 撤销

							// 读取日志
	if (log.op == DRAW_LINE)
	{
		int r = 1;
		cv::line(m_maskImg, log.p1, log.p2, cvScalar(255), r);
	}

	if (log.op == DRAW_LABEL)
	{
		// to be done
	}
	if (log.op == DRAW_MEASURE)
	{
		if (abs(log.p2.x - log.p1.x) == 0)
		{
			//cv::Point center = cv::Point(log.p1.x, (log.p2.y + log.p1.y) / 2);
			cv::line(m_maskImg, log.p1, log.p2, cv::Scalar(255, 0, 0), 1, 8);
			cv::putText(m_maskImg, log.text, log.center, FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255), 1, 8, false);
		}
		else if(abs(log.p2.y - log.p1.y) == 0)
		{
			//cv::Point center = cv::Point((log.p2.x + log.p1.x) / 2, log.p1.y);
			cv::line(m_maskImg, log.p1, log.p2, cv::Scalar(255, 0, 0), 1, 8);
			cv::putText(m_maskImg, log.text, log.center, FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255), 1, 8, false);
		}
	}
	m_maskImg.copyTo(m_maskShowImg);
	Invalidate();
}

// 撤销
void CchiropracticDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_vecLog.size() == 0) return;
	logInfo log = m_vecLog.back();
	m_vecDelLog.push_back(log);
	m_vecLog.pop_back(); // 撤销
	m_maskImg.setTo(0);
	m_maskShowImg.setTo(0);

	// 重画
	vector<logInfo>::iterator iter;
	for (iter = m_vecLog.begin(); iter != m_vecLog.end(); ++iter)
	{
		logInfo log = *iter;
		// 读取日志
		if (log.op == DRAW_LINE)
		{
			int r = 1;
			cv::line(m_maskImg, log.p1, log.p2, cvScalar(255,0,0), r);
		}
		if (log.op == DRAW_LABEL)
		{
			// to be done
		}
		if (log.op == DRAW_MEASURE)
		{
			if (abs(log.p2.x - log.p1.x) == 0)
			{
				//cv::Point center = cv::Point(log.p1.x, (log.p2.y + log.p1.y) / 2);
				cv::line(m_maskImg, log.p1, log.p2, cv::Scalar(255, 0, 0), 1, 8);
				cv::putText(m_maskImg, log.text, log.center, FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255), 1, 8, false);
			}
			else if (abs(log.p2.y - log.p1.y) == 0)
			{
				//cv::Point center = cv::Point((log.p2.x + log.p1.x) / 2, log.p1.y);
				cv::line(m_maskImg, log.p1, log.p2, cv::Scalar(255, 0, 0), 1, 8);
				cv::putText(m_maskImg, log.text, log.center, FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255), 1, 8, false);
			}
		}
	}
	m_maskImg.copyTo(m_maskShowImg);
	Invalidate();
}

// 清屏
void CchiropracticDlg::OnBnClickedButton10()
{
	//// TODO: 在此添加控件通知处理程序代码
	OnRButtonDown(NULL, NULL);
	m_maskImg.setTo(0);
	m_maskShowImg.setTo(0);
	cv::vector<logInfo>().swap(m_vecLog);
	cv::vector<logInfo>().swap(m_vecDelLog);
	Invalidate();
}

// 删除
void CchiropracticDlg::OnBnClickedButton5()
{
	OnRButtonDown(NULL,NULL);
	m_bDel = true;
	//m_bDrawRect = false;
	//m_bDrawLabel = false;
	// TODO: 在此添加控件通知处理程序代码
}

// 右键取消
void CchiropracticDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bDel = false;
	m_bDrawLine = false;
	m_bDrawRect = false;
	m_bDrawLabel = false;
	m_bMeasure = false;
	CDialogEx::OnRButtonDown(nFlags, point);
}


void CchiropracticDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	OnRButtonDown(NULL, NULL);
	m_bMeasure = true;
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
	m_dWidth = dlg.m_dWidth;
	m_dHeight = dlg.m_dHeight;
	m_dWidthScale = m_dWidth / m_srcImg.cols;
	m_dHeightScale = m_dHeight / m_srcImg.rows;

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
	CRect rect;
	GetDlgItem(IDC_PICTURE)->GetWindowRect(rect);
	ScreenToClient(&rect);

	if (m_bPutText)// 放置测量信息模式
	{
		m_stuLog.center = m_p2;
		cv::putText(m_maskImg, m_stuLog.text, m_stuLog.center, FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255), 1, 8, false);
		m_vecLog.push_back(m_stuLog);

		m_maskImg.copyTo(m_maskShowImg);
		m_bPutText = false;			// 关闭放置测量信息模式
		Invalidate();
	}
	else if (nFlags & MK_LBUTTON && !m_bPutText)
	{
		if (!m_bLButtonDown)
		{
			m_bLButtonDown = true;
			m_mouseDown.X = point.x;
			m_mouseDown.Y = point.y;
			m_PtStart.X = m_imgX;
			m_PtStart.Y = m_imgY;

			m_p1.x = point.x - rect.left;
			m_p1.y = point.y - rect.top;

			m_p1.x = m_p1.x / m_zoom - m_imgX;
			m_p1.y = m_p1.y / m_zoom - m_imgY;
		}
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CchiropracticDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (!m_bLButtonDown && !m_bPutText)		// 鼠标未按下，同时不是putText模式时，返回
		return;
	CRect rect;
	GetDlgItem(IDC_PICTURE)->GetWindowRect(rect);
	ScreenToClient(&rect);

	BOOL bIn = PtInRect(&rect, point);
	if (!bIn) return;

	m_p2.x = point.x - rect.left;
	m_p2.y = point.y - rect.top;

	m_p2.x = m_p2.x / m_zoom - m_imgX;
	m_p2.y = m_p2.y / m_zoom - m_imgY;
	m_maskImg.copyTo(m_maskShowImg);// 将已完成的步骤载入
	//m_maskShowImg.setTo(0);		//清空上一步所画
	if (m_bDrawRect)		//区域选择
	{
		int r = 1;
		cv::rectangle(m_maskShowImg, m_p1, m_p2, cv::Scalar(255), r);
		Invalidate();
	}

	if (m_bDrawLine)	// 画线模式
	{
		int r = 1;
		if (abs(m_p2.x - m_p1.x)< abs(m_p2.y - m_p1.y))
			cv::line(m_maskShowImg, m_p1, cv::Point(m_p1.x, m_p2.y), cv::Scalar(255), r);
		else
			cv::line(m_maskShowImg, m_p1, cv::Point(m_p2.x, m_p1.y), cv::Scalar(255), r);
		Invalidate();
	}
	if ((m_bDel || m_bMeasure) && !m_bPutText)		//删除模式、测量模式
	{
		int r = 1;
		cv::line(m_maskShowImg, m_p1, m_p2, cv::Scalar(255), r);
		Invalidate();
	}
	if (m_bPutText)
	{
		int r = 1;
		cv::Point center = m_p2;
		cv::putText(m_maskShowImg, m_stuLog.text, center, FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255), 1, 8, false);
		Invalidate();
	}

	if (nFlags && MK_LBUTTON && !m_bDrawLine && !m_bDrawRect && !m_bDel &&  !m_bMeasure)	// 移动模式
	{
		REAL deltaX = point.x - m_mouseDown.X; //x轴方向偏移
		REAL deltaY = point.y - m_mouseDown.Y; //y轴方向偏移

		m_imgX = (m_PtStart.X + (deltaX / m_zoom)); //在原始图像中X坐标偏移，这里计算的是在原始图片中的位移，原因在上面已经说明，全局的仿射变换会影响实际的位移
		m_imgY = (m_PtStart.Y + (deltaY / m_zoom)); //在原始图像中Y坐标偏移
		Invalidate();                            //重绘
	}

	CDialogEx::OnMouseMove(nFlags, point);
}

void CchiropracticDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bLButtonDown = false;

	CRect rectBox;
	CWnd *pWnd = GetDlgItem(IDC_PICTURE);
	pWnd->GetWindowRect(&rectBox);  // 得到的是控件相对于左上角的位置
	ScreenToClient(&rectBox);// 得到的是控件相对于程序窗口左上角的位置
	m_p2.x = point.x - rectBox.left;
	m_p2.y = point.y - rectBox.top;
	// 变换到原图坐标
	m_p2.x = m_p2.x / m_zoom - m_imgX;
	m_p2.y = m_p2.y / m_zoom - m_imgY;
	if (m_bDrawRect)			// 选取模式
	{
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

		m_bDrawRect = false;
		Invalidate();
	}

	if (m_bDrawLine)			// 画线模式
	{
		cv::Scalar p = cvScalarAll(255);
		m_maskImg.setTo(p, m_maskShowImg);

		logInfo log = {};    // 写入日志
		// 因为float型有误差，所以m_p2需要修正
		if (abs(m_p2.x - m_p1.x) < abs(m_p2.y - m_p1.y))
			m_p2 = cv::Point(m_p1.x, m_p2.y);
		else
			m_p2 = cv::Point(m_p2.x, m_p1.y);

		log.p1 = m_p1;
		log.p2 = m_p2;
		log.op = DRAW_LINE;
		m_vecLog.push_back(log);
	}

	if (m_bDel) // 删除模式
	{
		logInfo log = {};
		vector<logInfo>::iterator iter;
		vector<logInfo> temp;
		for (iter = m_vecLog.begin(); iter != m_vecLog.end(); ++iter)
		{
			logInfo log = *iter;
			// 读取日志
			if (log.op == DRAW_LINE)
			{
				bool ret = intersect(log.p1, log.p2, m_p1, m_p2);
				if (!ret)
					temp.push_back(log);
				else
					m_vecDelLog.push_back(log);
			}
			if (log.op == DRAW_MEASURE)
			{
				bool ret = intersect(log.p1, log.p2, m_p1, m_p2);
				if (!ret)
					temp.push_back(log);
				else
					m_vecDelLog.push_back(log);
			}


			if (log.op == DRAW_LABEL)
			{
				// to be done
			}
		}
		// 开始重画
		m_maskImg.setTo(0);
		m_maskShowImg.setTo(0);
		m_vecLog = temp;
		for (iter = m_vecLog.begin(); iter != m_vecLog.end(); ++iter)
		{
			logInfo log = *iter;

			// 读取日志
			if (log.op == DRAW_LINE)
			{
				int r = 1;
				cv::line(m_maskImg, log.p1, log.p2, cvScalar(255), r);
			}
			if (log.op == DRAW_MEASURE)
			{
				if (abs(log.p2.x - log.p1.x) == 0)
				{
					//cv::Point center = cv::Point(log.p1.x, (log.p2.y + log.p1.y) / 2);
					cv::line(m_maskImg, log.p1, log.p2, cv::Scalar(255, 0, 0), 1, 8);
					cv::putText(m_maskImg, log.text, log.center, FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255), 1, 8, false);
				}
				else if (abs(log.p2.y - log.p1.y) == 0)
				{
					//cv::Point center = cv::Point((log.p2.x + log.p1.x) / 2, log.p1.y);
					cv::line(m_maskImg, log.p1, log.p2, cv::Scalar(255, 0, 0), 1, 8);
					cv::putText(m_maskImg, log.text, log.center, FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255), 1, 8, false);
				}
			}
			if (log.op == DRAW_LABEL)
			{
				// to be done
			}
		}
		m_maskImg.copyTo(m_maskShowImg);
		Invalidate();
		//return;
	}// 
	if (m_bMeasure && !m_bPutText)			// 测量模式
	{
		logInfo log = {};
		vector<logInfo>::iterator iter;
		vector<logInfo> temp;
		for (iter = m_vecLog.begin(); iter != m_vecLog.end(); ++iter)
		{
			logInfo log = *iter;
			// 读取日志
			if (log.op != DRAW_LINE)
				continue;

			bool ret = intersect(log.p1, log.p2, m_p1, m_p2);
			if (!ret)
				continue;
			m_vecMeasure.push_back(log);
			if (m_vecMeasure.size() == 2)
			{
				int r = 1;
				cv::Point p1, p2;
				//竖线
				if (m_vecMeasure[0].p1.x == m_vecMeasure[0].p2.x && m_vecMeasure[1].p1.x == m_vecMeasure[1].p2.x
					&& m_vecMeasure[0].p1.y != m_vecMeasure[0].p2.y && m_vecMeasure[1].p1.y != m_vecMeasure[1].p2.y)
				{
					p1.x = m_vecMeasure[0].p1.x;
					p1.y = (m_vecMeasure[0].p1.y + m_vecMeasure[0].p2.y) / 2;
					p2.x = m_vecMeasure[1].p1.x;
					p2.y = p1.y;
					cv::line(m_maskImg, p1, p2, cvScalar(255), r);

					int len = abs(p2.x - p1.x);
					//cv::Point center = cv::Point((p2.x + p1.x) / 2, p1.y);
					// 日志记录
					memset(&m_stuLog, 0, sizeof(m_stuLog));
					m_stuLog.op = DRAW_MEASURE;
					m_stuLog.p1 = p1;
					m_stuLog.p2 = p2;
					sprintf_s(m_stuLog.text, "%.1lfmm", len*m_dWidthScale);
					//cv::putText(m_maskImg, log.text, center, FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255), 1, 8, false);

					//m_vecLog.push_back(log);
					
				}
				// 横线
				else if (m_vecMeasure[0].p1.x != m_vecMeasure[0].p2.x && m_vecMeasure[1].p1.x != m_vecMeasure[1].p2.x
					&& m_vecMeasure[0].p1.y == m_vecMeasure[0].p2.y && m_vecMeasure[1].p1.y == m_vecMeasure[1].p2.y)
				{
					p1.x = (m_vecMeasure[0].p1.x + m_vecMeasure[0].p2.x) / 2;
					p1.y = m_vecMeasure[0].p1.y;
					p2.x = p1.x;
					p2.y = m_vecMeasure[1].p1.y;
					cv::line(m_maskImg, p1, p2, cvScalar(255), r);

					int len = abs(p2.y - p1.y);
					//cv::Point center = cv::Point( p1.x, (p2.y + p1.y) / 2);
					memset(&m_stuLog, 0, sizeof(m_stuLog));
					m_stuLog.op = DRAW_MEASURE;
					m_stuLog.p1 = p1;
					m_stuLog.p2 = p2;
					sprintf_s(m_stuLog.text, "%.1lfmm", len*m_dHeightScale);
					//cv::putText(m_maskImg, log.text, center, FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255), 1, 8, false);

					//m_vecLog.push_back(log);
				}
				m_maskImg.copyTo(m_maskShowImg);
				Invalidate();
				cv::vector<logInfo>().swap(m_vecMeasure);
				//break;

				m_bPutText = true;			// 激活放置测量信息模式
			}
		}
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}

BOOL CchiropracticDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) // 屏幕坐标
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

	int x = ppt.x - m_Rect.left;  // 在本程序中无作用
	int y = ppt.y - m_Rect.top;

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
	//// TODO: 在此添加控件通知处理程序代码
	//int nIndex = m_Combo.GetCurSel();
	//CString strText;
	//m_Combo.GetLBText(nIndex, strText);

	//// 只是为了调整换算比例尺
	//if (strText == _T("14x17"))  
	//{
	//	int w, h; //实际尺寸(mm或英寸)
	//	w = 100;
	//	h = 200;
	//	m_dWidthScale = m_dWidth / m_srcImg->width;
	//	m_dHeightScale = m_dHeight / m_srcImg->height;
	//}
	//else if (strText == _T("7x8.5"))
	//{
	//	int w, h; //实际尺寸(mm或英寸)
	//	w = 50;
	//	h = 100;
	//	m_dWidthScale = m_dWidth / m_srcImg->width;
	//	m_dHeightScale = m_dHeight / m_srcImg->height;
	//}
	//else if (strText == _T("....."))
	//{
	//	// continue
	//}
	//else  // default
	//{
	//	// nothing
	//}

	//// 重绘
	//OnPaint();

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
	m_srcImg.copyTo(m_zoomImg);
	m_zoomImg.setTo(cv::Scalar(255, 0, 0), m_maskShowImg);
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
	m_edit = m_imgX;
	UpdateData(false);

	
}

void CchiropracticDlg::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	//CInputName dlg;
	//INT_PTR ret = dlg.DoModal();
	//if (ret != IDOK)
	//	return;
	//CString strName = dlg.m_strName;

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
	int len = WideCharToMultiByte(CP_ACP, 0, mPath, -1, NULL, 0, NULL, NULL);
	char *ptxtTemp = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, mPath, -1, ptxtTemp, len, NULL, NULL);

	cv::Mat saveImg;
	saveImg = m_srcImg.clone();
	saveImg.setTo(cv::Scalar(255, 0, 0), m_maskImg);
	imwrite(ptxtTemp, saveImg);
	delete[] ptxtTemp;
}

// 鼠标，取消一切选取
void CchiropracticDlg::OnBnClickedButton12()
{
	// TODO: 在此添加控件通知处理程序代码
	OnRButtonDown(NULL, NULL);

}