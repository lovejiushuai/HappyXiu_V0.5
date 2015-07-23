// MainFrame.cpp : implementation file
//

#include "stdafx.h"
#include "Detail.h"
#include "MainFrame.h"
#include "InfoDialog.h"

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

CMainFrame::CMainFrame()
{

	EnableAutomation();
}

CMainFrame::~CMainFrame()
{
	::CoUninitialize();	//退出com库
}

void CMainFrame::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CFrameWnd::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_NOTIFY(NM_DBLCLK, 100, OnDblclkTree)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMainFrame, CFrameWnd)
END_DISPATCH_MAP()

// Note: we add support for IID_IMainFrame to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {BF9D1EE8-C74B-432F-A1EF-D02FBE6D60CE}
static const IID IID_IMainFrame =
{ 0xBF9D1EE8, 0xC74B, 0x432F, { 0xA1, 0xEF, 0xD0, 0x2F, 0xBE, 0x6D, 0x60, 0xCE } };

BEGIN_INTERFACE_MAP(CMainFrame, CFrameWnd)
	INTERFACE_PART(CMainFrame, IID_IMainFrame, Dispatch)
END_INTERFACE_MAP()


// CMainFrame message handlers


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	LoadControl();

	return 1L;
}

void CMainFrame::LoadControl()
{
		
	
#if _WIN32_WINNT > 0x500
	//保留字（必须为null） ，加载方式 COINIT_MULTITHREADED多线程的方式加载
	// 以多线程方式打开com通道
	::CoInitializeEx(NULL, COINIT_MULTITHREADED);
#else
	::CoInitialize(NULL);
#endif

	/*CoInitialize(NULL);*/
	HRESULT hr;
	try                            //连接数据库
	{
		hr = theApp.m_pConnection.CreateInstance(__uuidof(Connection)/*"ADODB.Connection"*/);
		if(SUCCEEDED(hr))
		{
			theApp.m_pConnection->ConnectionTimeout = 10;	//连接超时
			theApp.m_pConnection->CursorLocation = adUseClient;//作用于记录集指针，非常重要!!!
			theApp.m_pConnection->ConnectionString = _T("File Name=调度.udl");
			theApp.m_pConnection->Open("","","",-1);
		}
	}
	catch(_com_error e)
	{
		CString str;
		str.Format(_T("连接数据库失败:%s"),e.ErrorMessage());
		::MessageBox(NULL,str,_T("提示信息"),NULL);
		//return false;
	}
	
	// 获取当前屏幕分辨率  -- 但不包括状态栏大小
	int screenwidth=GetSystemMetrics(SM_CXFULLSCREEN);
	int screenheight=GetSystemMetrics(SM_CYFULLSCREEN);
	/*int screenwidth=800;
	int screenheight=600;*/

	CRect m_rcPanel;
	//设置当前窗口大小  与 当前屏幕分辨率 一致
	m_rcPanel.SetRect(0,0,screenwidth,screenheight);
	MoveWindow(&m_rcPanel);


	/////////////这一段代码创建树型控件////////////
	if (!m_wndTree.Create(WS_CHILD|WS_VISIBLE|
		TVS_HASLINES|TVS_HASBUTTONS|TVS_LINESATROOT,
		CRect(0, 0, 0, 0), m_pLeft, 100))  ///注意，这里是将m_pLeft作为m_wndTree的父窗口
	{
		TRACE0("Failed to create instant bar child\n");
		return;
	}
	m_wndTree.ModifyStyleEx(0, WS_EX_CLIENTEDGE);
	//添加树型控件图标
	CImageList* imageList=new CImageList;
	imageList->Create(16,16,ILC_COLOR24,4,4);
	imageList->Add(AfxGetApp()->LoadIcon(IDI_TREE_CLOSE));
	imageList->Add(AfxGetApp()->LoadIcon(IDI_TREE_ROOT));
	imageList->Add(AfxGetApp()->LoadIcon(IDI_TREE_CHILD));
	imageList->Add(AfxGetApp()->LoadIcon(IDI_TREE_OPEN));
	imageList->Add(AfxGetApp()->LoadIcon(IDI_TREE_CHILD2));

	m_wndTree.SetImageList(imageList,TVSIL_NORMAL);
	//往树型控件添加内容以及图标
	HTREEITEM hti = m_wndTree.InsertItem(_T("兰新高铁网管台帐"),1,1);
	HTREEITEM hti2=m_wndTree.InsertItem(_T("兰新高铁主用主系统"),0,3,hti);
	/*if(theApp.m_status!=_T("普通用户"))
	{
		m_wndTree.InsertItem(_T("模 块  I"),2,4,hti2);
	}*/
	m_wndTree.InsertItem(_T("模块Ⅰ"),2,4,hti2);
	m_wndTree.InsertItem(_T("模块Ⅱ"),2,4,hti2);	
	m_wndTree.InsertItem(_T("模块Ⅲ"),2,4,hti2);

	HTREEITEM hti3=m_wndTree.InsertItem(_T("兰州西"),0,3,hti);
	/*if(theApp.m_status!=_T("普通用户"))
	{
		m_wndTree.InsertItem(_T(""),2,4,hti3);
	}*/
	m_wndTree.InsertItem(_T("模块Ⅰ"),2,4,hti3);

	HTREEITEM hti4=m_wndTree.InsertItem(_T("兰西动车所"),0,3,hti);
	/*if(theApp.m_status!=_T("普通用户"))
	{
		m_wndTree.InsertItem(_T(""),2,4,hti4);
	}*/
	m_wndTree.InsertItem(_T("模块Ⅰ"),2,4,hti4);
	
	HTREEITEM hti5=m_wndTree.InsertItem(_T("陈家湾"),0,3,hti);
	/*if(theApp.m_status!=_T("普通用户"))
	{
		m_wndTree.InsertItem(_T(""),2,4,hti5);
	}*/
	m_wndTree.InsertItem(_T("模块Ⅰ"),2,4,hti5);
	
	HTREEITEM hti6=m_wndTree.InsertItem(_T("民和南"),0,3,hti);
	/*if(theApp.m_status!=_T("普通用户"))
	{
	m_wndTree.InsertItem(_T(""),2,4,hti6);
	}*/
	m_wndTree.InsertItem(_T("模块Ⅰ"),2,4,hti6);	

	HTREEITEM hti7=m_wndTree.InsertItem(_T("兰新高铁备用主系统"),0,3,hti);	
	m_wndTree.InsertItem(_T("模块Ⅰ"),2,4,hti7);
	m_wndTree.InsertItem(_T("模块Ⅱ"),2,4,hti7);	
	m_wndTree.InsertItem(_T("模块Ⅲ"),2,4,hti7);

	HTREEITEM hti8=m_wndTree.InsertItem(_T("其它信息"),0,3, hti);
	if(theApp.m_status!=_T("普通用户"))
	{
		m_wndTree.InsertItem(_T("其它信息管理"),2,4,hti8);
		HTREEITEM hti9=m_wndTree.InsertItem(_T("数据库管理"),0,3,hti8);
		m_wndTree.InsertItem(_T("数据备份"),2,4,hti9);
		m_wndTree.InsertItem(_T("数据还原"),2,4,hti9);
	}
	//展开树型控件的结点
	m_wndTree.Expand(hti,TVE_EXPAND);
	/*m_wndTree.Expand(hti2,TVE_EXPAND);
	m_wndTree.Expand(hti3,TVE_EXPAND);
	m_wndTree.Expand(hti4,TVE_EXPAND);
	m_wndTree.Expand(hti5,TVE_EXPAND);
	m_wndTree.Expand(hti6,TVE_EXPAND);
	m_wndTree.Expand(hti7,TVE_EXPAND);
	m_wndTree.Expand(hti8,TVE_EXPAND);*/

	///将树型控件加入到LeftCtrl中
	m_pLeft->AddPage(&m_wndTree,_T("Dialog"),IDI_ICON10); //将树型控件添加到第一页
	
	m_pLeft->UpdateWindow(); //更新LeftControl
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle , CWnd* pParentWnd , CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class

	return CFrameWnd::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext);
}


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class

	//Create splitter window by two views  用 splitter 把 视图 划分为两块
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return -1;

	/*if (!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CRightView), CSize(100, 100),pContext) ||
	!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CLeftCtrl), CSize(100, 100),pContext))
	{
	m_wndSplitter.DestroyWindow();
	return FALSE;
	}*/

	// 若两个都传进 pContext   List会重复画两遍   所以定义 CCreateContext cc  解决重复问题
	if (!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CRightView), CSize(100, 100),&theApp.cc) ||
		!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CLeftCtrl), CSize(100, 100),pContext))
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}
	m_pRight = reinterpret_cast<CRightView*>(m_wndSplitter.GetPane(0,1));
	m_pLeft = reinterpret_cast<CLeftCtrl*>(m_wndSplitter.GetPane(0,0));
	m_wndSplitter.SetColumnInfo(0, 200, 100);	

	return CFrameWnd::OnCreateClient(lpcs, pContext);
}

int pos=-100;	//用以控制对话框位置移动的变量
void CMainFrame::OnDblclkTree(NMHDR* pNMHDR, LRESULT* pResult)		//树型控件的双击事件
{

	pos+=20;
	if(pos>0) pos=-70;
	HTREEITEM hm=m_wndTree.GetSelectedItem();
	HTREEITEM hItemParent;
	CString str;
	CRect rect;
	CString listName;
	CString mNum;
	CString mItemParent;
	int selectModNum;

	listName.Empty();
	mNum.Empty();
	selectModNum = 0;

	GetClientRect(&rect);
	hItemParent = m_wndTree.GetParentItem(hm);
	mItemParent = m_wndTree.GetItemText(hItemParent);
	str=m_wndTree.GetItemText(hm);
	if (mItemParent == _T("兰新高铁主用主系统"))
	{
		listName.Format(_T("main"));
	}
	else if (mItemParent == _T("兰州西"))
	{
		listName.Format(_T("lanzhouxi"));
	}
	else if (mItemParent == _T("兰西动车所"))
	{
		listName.Format(_T("lanxidong"));
	}
	else if (mItemParent == _T("陈家湾"))
	{
		listName.Format(_T("chenjiawan"));
	}
	else if (mItemParent == _T("民和南"))
	{
		listName.Format(_T("minhenan"));
	}
	else if (mItemParent == _T("兰新高铁备用主系统"))
	{
		listName.Format(_T("spare"));
	}
	
	if(str==_T("模块Ⅰ"))
	{
		

		m_wndTree.GetFirstVisibleItem();		
		mNum.Format(str);
		selectModNum = 1;
		CInfoDialog *infoDialog = new CInfoDialog;
		infoDialog->onSetDatabase( listName, mNum, selectModNum, 1);
		infoDialog->Create(IDD_INFODIALOG,this);
		infoDialog->ShowWindow(SW_SHOW);	//显示非模态对话框

		//移动对话框的位置使其不重叠
		//InStuInfoDlg->SetWindowPos(0,rect.right/2+pos,rect.bottom/2+pos,0,0,SWP_NOSIZE | SWP_NOZORDER);

	}
	else if(str==_T("模块Ⅱ"))
	{
		mNum.Format(str);
		selectModNum = 2;
		CInfoDialog *infoDialog = new CInfoDialog;
		infoDialog->onSetDatabase( listName, mNum, selectModNum, 1);
		infoDialog->Create(IDD_INFODIALOG,this);
		infoDialog->ShowWindow(SW_SHOW);	//显示非模态对话框

		//移动对话框的位置使其不重叠
		//InStuInfoDlg->SetWindowPos(0,rect.right/2+pos,rect.bottom/2+pos,0,0,SWP_NOSIZE | SWP_NOZORDER);
	}
	else if(str==_T("模块Ⅲ"))
	{
		mNum.Format(str);
		selectModNum = 3;
		CInfoDialog *infoDialog = new CInfoDialog;
		infoDialog->onSetDatabase( listName, mNum, selectModNum, 1);
		infoDialog->Create(IDD_INFODIALOG,this);
		infoDialog->ShowWindow(SW_SHOW);	//显示非模态对话框

		//移动对话框的位置使其不重叠
		//InStuInfoDlg->SetWindowPos(0,rect.right/2+pos,rect.bottom/2+pos,0,0,SWP_NOSIZE | SWP_NOZORDER);
		
	}
	else if(str==_T("数据备份"))
	{

	}
	else if(str==_T("数据还原"))
	{
		
	}

}


void CMainFrame::OnDestroy()
{
	CFrameWnd::OnDestroy();

	// TODO: Add your message handler code here

	//关闭记录集和连接

	/*if(theApp.m_pRecordset!=NULL)
	{
		theApp.m_pRecordset->Close();
		theApp.m_pRecordset.Release();
	}

	if (theApp.m_pConnection !=NULL )
	{
		theApp.m_pConnection->Close();
		theApp.m_pConnection.Release();
	}*/
	

	//CoUninitialize();	//退出com库
}

