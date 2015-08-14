
// AccountDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Account.h"
#include "AccountDlg.h"
#include "afxdialogex.h"
#include "Global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAccountDlg dialog



// 站点联系对话框 初始化参数
CAccountDlg::CAccountDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAccountDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_buttonCount = 0;
}

// 参数与控件关联
void CAccountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

// 消息映射  消息值、按钮 与响应函数 关联
BEGIN_MESSAGE_MAP(CAccountDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED( IDC_BUTTON_LANZHOUXI, OnButtonClickedLZX)
	ON_BN_CLICKED( IDC_BUTTON_LANXID, OnButtonClickedLXD)
	ON_BN_CLICKED( IDC_BUTTON_CHEN, OnButtonClickedC)
	ON_BN_CLICKED( IDC_BUTTON_MIN, OnButtonClickedM)
	ON_BN_CLICKED( IDC_BUTTON_MAIN, OnButtonClickedMain)
	ON_BN_CLICKED( IDC_BUTTON_SPARE, OnButtonClickedSpare)
	ON_MESSAGE(WM_START_DLL, LaunchDll)

END_MESSAGE_MAP()


// CAccountDlg message handlers
// 初始化窗口
BOOL CAccountDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	// 进行一些按钮 连线的布局
	LoadControl();

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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// 初始化时  屏幕大小 按钮 连线的创建和布局
void CAccountDlg::LoadControl()
{
	// 获取当前屏幕大小
	int screenwidth=GetSystemMetrics(SM_CXFULLSCREEN);
	int screenheight=GetSystemMetrics(SM_CYFULLSCREEN);
	/*int screenwidth=800;
	int screenheight=600;*/
	
	// 设置当前窗口的大小
	m_rcPanel.SetRect(0,0,screenwidth,screenheight);
	MoveWindow(&m_rcPanel);


	
	
	widthRect = m_rcPanel.Width()/13;
	heightRectL = m_rcPanel.Height()*6/10;
	heightRectS = m_rcPanel.Height()*3/10;
	topRect = m_rcPanel.Height()/10;

	// 创建 站点 按键 并进行初始化
	// Create  button.
	m_hMainButton.Create( _T("兰新高铁主用主系统"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, CRect( widthRect - 50, topRect, 2*widthRect, topRect + heightRectL), this, IDC_BUTTON_MAIN);

	m_hLanZhouXiButton.Create(_T("兰州西"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, CRect( 3*widthRect, topRect, 4*widthRect, topRect + heightRectS), this, IDC_BUTTON_LANZHOUXI);

	m_hLanXiDButton.Create(_T("兰西动车所"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, CRect( 5*widthRect, topRect, 6*widthRect, topRect + heightRectS), this, IDC_BUTTON_LANXID);

	m_hChenButton.Create(_T("陈家湾"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, CRect( 7*widthRect, topRect, 8*widthRect, topRect + heightRectS), this, IDC_BUTTON_CHEN);

	m_hMinButton.Create(_T("民和南"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, CRect( 9*widthRect, topRect, 10*widthRect, topRect + heightRectS), this, IDC_BUTTON_MIN);

	m_hSpareButton.Create(_T("兰新高铁备用主系统"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, CRect( 11*widthRect, topRect, 12*widthRect + 50, topRect + heightRectL), this, IDC_BUTTON_SPARE);

	// 把按键设置为屏幕可见   若不设置  则可能在窗口中看不到
	m_hMainButton.EnableWindow(TRUE);
	m_hLanZhouXiButton.EnableWindow(TRUE);
	m_hLanXiDButton.EnableWindow(TRUE);
	m_hChenButton.EnableWindow(TRUE);
	m_hMinButton.EnableWindow(TRUE);
	m_hSpareButton.EnableWindow(TRUE);

	
	lineY_1 = (topRect +  heightRectL/4);
	lineY_2 = (topRect +  heightRectL*3/4);

	//CBitmap bitmap;   
	//bitmap.LoadBitmap(IDB_BITMAP1);//载入图片资源
	//CBrush brush(&bitmap);
	//CClientDC dc(this);
	//dc.FillRect(CRect(m_ptOrigin,point),&brush);

	// Draw  line
	/*CDC *pDC = GetDC();
	pDC->MoveTo( 2*widthRect, lineY_1);
	pDC->LineTo( 3*widthRect, lineY_1);

	pDC->MoveTo( 4*widthRect, lineY_1);
	pDC->LineTo( 5*widthRect, lineY_1);

	pDC->MoveTo( 7*widthRect, lineY_1);
	pDC->LineTo( 8*widthRect, lineY_1);

	pDC->MoveTo( 9*widthRect, lineY_1);
	pDC->LineTo( 10*widthRect, lineY_1);

	pDC->MoveTo( 11*widthRect, lineY_1);
	pDC->LineTo( 12*widthRect, lineY_1);

	pDC->MoveTo( 2*widthRect, lineY_2);
	pDC->LineTo( 10*widthRect, lineY_2);
	ReleaseDC(pDC);*/


	/*CPoint m_ptOrigin;
	m_ptOrigin = (10,10);
	CPoint m_ptOld;
	m_ptOld = (100,100);

	CClientDC dc(this);
	CPen pen(PS_SOLID,1,RGB(255,0,0));
	CPen *oldPen = dc.SelectObject(&pen);

	dc.MoveTo(m_ptOrigin);
	dc.LineTo(m_ptOld);
	dc.MoveTo(m_ptOld);


	dc.SelectObject(oldPen);


	CDC *pDC=GetDC();  
	pDC->MoveTo(m_ptOrigin);  
	pDC->LineTo(m_ptOld);  
	ReleaseDC(pDC); 

	CClientDC mdc(this);
	CPen mpen(PS_SOLID,1,RGB(234,23,53));
	CPen *pOldPen=dc.SelectObject(&mpen);
	CBrush *pBrush=CBrush::FromHandle((HBRUSH)
	GetStockObject(NULL_BRUSH));
	CBrush *pOldBrush=dc.SelectObject(pBrush);
	mdc.Rectangle(CRect(m_ptOrigin,m_ptOld));
	mdc.SelectObject(pOldPen);
	mdc.SelectObject(pOldBrush);*/

}

// 响应系统命令  自动生成  不用管
void CAccountDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

// 每次屏幕移动  或者最小化 然后最大化时  就会调用此函数  在 屏幕上 重新画当前窗口 及 窗口中每个控件
void CAccountDlg::OnPaint()
{
	//if (IsIconic())
	//{
	//	CPaintDC dc(this); // device context for painting

	//	SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

	//	// Center icon in client rectangle
	//	int cxIcon = GetSystemMetrics(SM_CXICON);
	//	int cyIcon = GetSystemMetrics(SM_CYICON);
	//	CRect rect;
	//	GetClientRect(&rect);
	//	int x = (rect.Width() - cxIcon + 1) / 2;
	//	int y = (rect.Height() - cyIcon + 1) / 2;

	//	// Draw the icon
	//	dc.DrawIcon(x, y, m_hIcon);
	//	
	//	dc.MoveTo( 2*widthRect, lineY_1);
	//	dc.LineTo( 3*widthRect, lineY_1);

	//	dc.MoveTo( 4*widthRect, lineY_1);
	//	dc.LineTo( 5*widthRect, lineY_1);

	//	dc.MoveTo( 7*widthRect, lineY_1);
	//	dc.LineTo( 8*widthRect, lineY_1);

	//	dc.MoveTo( 9*widthRect, lineY_1);
	//	dc.LineTo( 10*widthRect, lineY_1);

	//	dc.MoveTo( 11*widthRect, lineY_1);
	//	dc.LineTo( 12*widthRect, lineY_1);

	//	dc.MoveTo( 2*widthRect, lineY_2);
	//	dc.LineTo( 10*widthRect, lineY_2);
	//	
	//}
	//else
	//{
	//	CDialogEx::OnPaint();
	//}

	// 获取画笔 
	CPaintDC dc(this); // device context for painting
		
	// 画笔 移动到点    
	dc.MoveTo( widthRect, lineY_1);
	// 画笔 画到点
	dc.LineTo( 12*widthRect, lineY_1);	
	// 画笔 移动到点
	dc.MoveTo( 2*widthRect, lineY_2);
	// 画笔 画到点
	dc.LineTo( 12*widthRect, lineY_2);

}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAccountDlg::OnQueryDragIcon()
{
	// 自动生成  不用管
	return static_cast<HCURSOR>(m_hIcon);
}

// 点击 main 按键 事件响应
void CAccountDlg::OnButtonClickedMain()
{
	// 发送 启动dll 消息
	/*AfxMessageBox(_T("Main"));*/
	PostMessage(WM_START_DLL, 0, 0);
}

// 点击 备用 按键 事件响应
void CAccountDlg::OnButtonClickedSpare()
{
	/*AfxMessageBox(_T("Spare"));*/
	PostMessage(WM_START_DLL, 0, 0);
}

// 点击 兰州西 按键 事件响应
void CAccountDlg::OnButtonClickedLZX()
{
	/*AfxMessageBox(_T("LanZhouXi"));*/
	PostMessage(WM_START_DLL, 0, 0);
}
// 点击 兰西动车所 按键 事件响应
void CAccountDlg::OnButtonClickedLXD()
{
	/*AfxMessageBox(_T("LanXiDong"));*/
	PostMessage(WM_START_DLL, 0, 0);
}
// 点击 陈家湾 按键 事件响应
void CAccountDlg::OnButtonClickedC()
{
	/*AfxMessageBox(_T("Chen"));*/
	PostMessage(WM_START_DLL, 0, 0);
}
// 点击 民和南 按键 事件响应
void CAccountDlg::OnButtonClickedM()
{
	/*AfxMessageBox(_T("Min"));*/
	PostMessage(WM_START_DLL, 0, 0);
}

// 启动dll 函数执行
LRESULT  CAccountDlg::LaunchDll(WPARAM wParam, LPARAM lParam)
{
	CAccountApp* pApp = (CAccountApp*)AfxGetApp();
	HINSTANCE  hDllLibrary = NULL;
	CString dllStr = _T("Detail.dll");

	// 加载 dll 库
	pApp->m_hApptDllInstance = LoadLibrary(dllStr); 
	hDllLibrary = pApp->m_hApptDllInstance;
	if(!hDllLibrary)
	{
		// 若加载失败 则提示信息
		TRACE(_T("LoadLibrary Failed, Error=%d: %s"), GetLastError(), dllStr);
		return 0;
	}
	//加载成功后  把dll 中 接口 进行初始化  以便后面调用
	LaunchDllFunc = (LaunchDllFuncAPI)GetProcAddress(hDllLibrary, "StartDll");
	SetAdminFunc = (SetAdminFuncAPI)GetProcAddress(hDllLibrary, "SetAdmin");
	ASSERT(LaunchDllFunc);
	if(!LaunchDllFunc)
		return 0;
	ShowWindow(SW_HIDE);
	ASSERT(SetAdminFunc);
	if(!SetAdminFunc)
		return 0;
	if (theApp.adminLevel)
	{
		SetAdminFunc(theApp.m_userID);
	}
	else
	{

	}
	
	// 启动dll 对应函数接口
	// m_hApptDllInstance is HINSTANCE of Account
	LaunchDllFunc(GetSafeHwnd(),
		pApp->m_hApptDllInstance,
		&pDllEntryWinApp);
	
	//释放加载库
	ExitDLLMessage(0,0);
	return 1L;
}

// 退出时  把 加载库进行释放
LRESULT CAccountDlg::ExitDLLMessage(WPARAM wParam,LPARAM lParam)
{
	ShowWindow(SW_SHOW);

	// #endif
	//	CCAMagicMobileApp* pApp = (CCAMagicMobileApp*)AfxGetApp();
	if(theApp.m_hApptDllInstance)
	{
		FreeLibrary(theApp.m_hApptDllInstance);
		theApp.m_hApptDllInstance = NULL;
	}
	return 1L;
}