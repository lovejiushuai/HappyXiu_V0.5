
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




CAccountDlg::CAccountDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAccountDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_buttonCount = 0;
}

void CAccountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAccountDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED( IDC_BUTTON_LANZHOUXI, OnButtonClickedLZX)
	ON_BN_CLICKED( IDC_BUTTON_LANXID, OnButtonClickedLXD)
	ON_BN_CLICKED( IDC_BUTTON_CHEN, OnButtonClickedC)
	ON_BN_CLICKED( IDC_BUTTON_MIN, OnButtonClickedM)
	ON_BN_CLICKED( IDC_BUTTON_MAIN1, OnButtonClickedMain)
	ON_BN_CLICKED( IDC_BUTTON_MAIN2, OnButtonClickedMain)
	ON_MESSAGE(WM_START_DLL, LaunchDll)

END_MESSAGE_MAP()


// CAccountDlg message handlers

BOOL CAccountDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

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

void CAccountDlg::LoadControl()
{
	int screenwidth=GetSystemMetrics(SM_CXFULLSCREEN);
	int screenheight=GetSystemMetrics(SM_CYFULLSCREEN);
	
	
	m_rcPanel.SetRect(0,0,screenwidth,screenheight);
	MoveWindow(&m_rcPanel);


	
	
	widthRect = m_rcPanel.Width()/13;
	heightRectL = m_rcPanel.Height()*6/10;
	heightRectS = m_rcPanel.Height()*3/10;
	topRect = m_rcPanel.Height()/10;

	
	// Create  button.
	m_hMainButton_1.Create( _T("兰新高铁主用主系统"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, CRect( widthRect, topRect, 2*widthRect, topRect + heightRectL), this, IDC_BUTTON_MAIN1);

	m_hLanZhouXiButton.Create(_T("兰州西"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, CRect( 3*widthRect, topRect, 4*widthRect, topRect + heightRectS), this, IDC_BUTTON_LANZHOUXI);

	m_hLanXiDButton.Create(_T("兰西动车所"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, CRect( 5*widthRect, topRect, 6*widthRect, topRect + heightRectS), this, IDC_BUTTON_LANXID);

	m_hChenButton.Create(_T("陈家湾"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, CRect( 7*widthRect, topRect, 8*widthRect, topRect + heightRectS), this, IDC_BUTTON_CHEN);

	m_hMinButton.Create(_T("民和南"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, CRect( 9*widthRect, topRect, 10*widthRect, topRect + heightRectS), this, IDC_BUTTON_MIN);

	m_hMainButton_2.Create(_T("兰新高铁主用主系统"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, CRect( 11*widthRect, topRect, 12*widthRect, topRect + heightRectL), this, IDC_BUTTON_MAIN2);

	m_hMainButton_1.EnableWindow(TRUE);
	m_hLanZhouXiButton.EnableWindow(TRUE);
	m_hLanXiDButton.EnableWindow(TRUE);
	m_hChenButton.EnableWindow(TRUE);
	m_hMinButton.EnableWindow(TRUE);
	m_hMainButton_2.EnableWindow(TRUE);

	
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

	CPaintDC dc(this); // device context for painting
		
	dc.MoveTo( widthRect, lineY_1);
	dc.LineTo( 12*widthRect, lineY_1);	

	dc.MoveTo( 2*widthRect, lineY_2);
	dc.LineTo( 12*widthRect, lineY_2);

}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAccountDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAccountDlg::OnButtonClickedMain()
{
	/*AfxMessageBox(_T("Main"));*/
	PostMessage(WM_START_DLL, 0, 0);
}

void CAccountDlg::OnButtonClickedLZX()
{
	/*AfxMessageBox(_T("LanZhouXi"));*/
	PostMessage(WM_START_DLL, 0, 0);
}
void CAccountDlg::OnButtonClickedLXD()
{
	/*AfxMessageBox(_T("LanXiDong"));*/
	PostMessage(WM_START_DLL, 0, 0);
}
void CAccountDlg::OnButtonClickedC()
{
	/*AfxMessageBox(_T("Chen"));*/
	PostMessage(WM_START_DLL, 0, 0);
}
void CAccountDlg::OnButtonClickedM()
{
	/*AfxMessageBox(_T("Min"));*/
	PostMessage(WM_START_DLL, 0, 0);
}

LRESULT  CAccountDlg::LaunchDll(WPARAM wParam, LPARAM lParam)
{
	CAccountApp* pApp = (CAccountApp*)AfxGetApp();
	HINSTANCE  hDllLibrary = NULL;
	CString dllStr = _T("Detail.dll");


	pApp->m_hApptDllInstance = LoadLibrary(dllStr); 
	hDllLibrary = pApp->m_hApptDllInstance;
	if(!hDllLibrary)
	{
		TRACE(_T("LoadLibrary Failed, Error=%d: %s"), GetLastError(), dllStr);
		return 0;
	}
	LaunchDllFunc = (LaunchDllFuncAPI)GetProcAddress(hDllLibrary, "StartDll");
	ASSERT(LaunchDllFunc);
	if(!LaunchDllFunc)
		return 0;
	ShowWindow(SW_HIDE);
	// m_hInstPhoneLib is HINSTANCE of AnwMobile
	LaunchDllFunc(GetSafeHwnd(),
		pApp->m_hApptDllInstance,
		&pDllEntryWinApp);
	ExitDLLMessage(0,0);
	return 1L;
}

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