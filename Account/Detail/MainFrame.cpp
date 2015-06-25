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
	::CoUninitialize();	//�˳�com��
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

		

#if _WIN32_WINNT > 0x500
	//�����֣�����Ϊnull�� �����ط�ʽ COINIT_MULTITHREADED���̵߳ķ�ʽ����
	// �Զ��̷߳�ʽ��comͨ��
	::CoInitializeEx(NULL, COINIT_MULTITHREADED);
#else
	::CoInitialize(NULL);
#endif

	/*CoInitialize(NULL);*/
	HRESULT hr;
	try                            //�������ݿ�
	{
		hr = theApp.m_pConnection.CreateInstance(__uuidof(Connection)/*"ADODB.Connection"*/);
		if(SUCCEEDED(hr))
		{
			theApp.m_pConnection->ConnectionTimeout = 10;	//���ӳ�ʱ
			theApp.m_pConnection->CursorLocation = adUseClient;//�����ڼ�¼��ָ�룬�ǳ���Ҫ!!!
			theApp.m_pConnection->ConnectionString = _T("File Name=HappyXiu.udl");
			theApp.m_pConnection->Open("","","",-1);
		}
	}
	catch(_com_error e)
	{
		CString str;
		str.Format(_T("�������ݿ�ʧ��:%s"),e.ErrorMessage());
		::MessageBox(NULL,str,_T("��ʾ��Ϣ"),NULL);
		//return false;
	}
	
	// ��ȡ��ǰ��Ļ�ֱ���  -- ��������״̬����С
	int screenwidth=GetSystemMetrics(SM_CXFULLSCREEN);
	int screenheight=GetSystemMetrics(SM_CYFULLSCREEN);

	CRect m_rcPanel;
	//���õ�ǰ���ڴ�С  �� ��ǰ��Ļ�ֱ��� һ��
	m_rcPanel.SetRect(0,0,screenwidth,screenheight);
	MoveWindow(&m_rcPanel);


	/////////////��һ�δ��봴�����Ϳؼ�////////////
	if (!m_wndTree.Create(WS_CHILD|WS_VISIBLE|
		TVS_HASLINES|TVS_HASBUTTONS|TVS_LINESATROOT,
		CRect(0, 0, 0, 0), m_pLeft, 100))  ///ע�⣬�����ǽ�m_pLeft��Ϊm_wndTree�ĸ�����
	{
		TRACE0("Failed to create instant bar child\n");
		return -1;
	}
	m_wndTree.ModifyStyleEx(0, WS_EX_CLIENTEDGE);
	//������Ϳؼ�ͼ��
	CImageList* imageList=new CImageList;
	imageList->Create(16,16,ILC_COLOR24,4,4);
	imageList->Add(AfxGetApp()->LoadIcon(IDI_TREE_CLOSE));
	imageList->Add(AfxGetApp()->LoadIcon(IDI_TREE_ROOT));
	imageList->Add(AfxGetApp()->LoadIcon(IDI_TREE_CHILD));
	imageList->Add(AfxGetApp()->LoadIcon(IDI_TREE_OPEN));
	imageList->Add(AfxGetApp()->LoadIcon(IDI_TREE_CHILD2));

	m_wndTree.SetImageList(imageList,TVSIL_NORMAL);
	//�����Ϳؼ���������Լ�ͼ��
	HTREEITEM hti = m_wndTree.InsertItem(_T("���¸�������̨��"),1,1);
	HTREEITEM hti2=m_wndTree.InsertItem(_T("���¸���������ϵͳ"),0,3,hti);
	/*if(theApp.m_status!=_T("��ͨ�û�"))
	{
		m_wndTree.InsertItem(_T("ģ ��  I"),2,4,hti2);
	}*/
	m_wndTree.InsertItem(_T("ģ ��  I"),2,4,hti2);
	m_wndTree.InsertItem(_T("ģ ��  II"),2,4,hti2);	
	m_wndTree.InsertItem(_T("ģ ��  III"),2,4,hti2);

	HTREEITEM hti3=m_wndTree.InsertItem(_T("������"),0,3,hti);
	/*if(theApp.m_status!=_T("��ͨ�û�"))
	{
		m_wndTree.InsertItem(_T(""),2,4,hti3);
	}*/
	m_wndTree.InsertItem(_T("ģ ��  I"),2,4,hti3);

	HTREEITEM hti4=m_wndTree.InsertItem(_T("����������"),0,3,hti);
	/*if(theApp.m_status!=_T("��ͨ�û�"))
	{
		m_wndTree.InsertItem(_T(""),2,4,hti4);
	}*/
	m_wndTree.InsertItem(_T("ģ ��  I"),2,4,hti4);
	
	HTREEITEM hti5=m_wndTree.InsertItem(_T("�¼���"),0,3,hti);
	/*if(theApp.m_status!=_T("��ͨ�û�"))
	{
		m_wndTree.InsertItem(_T(""),2,4,hti5);
	}*/
	m_wndTree.InsertItem(_T("ģ ��  I"),2,4,hti5);
	
	HTREEITEM hti6=m_wndTree.InsertItem(_T("�����"),0,3,hti);
	/*if(theApp.m_status!=_T("��ͨ�û�"))
	{
	m_wndTree.InsertItem(_T(""),2,4,hti6);
	}*/
	m_wndTree.InsertItem(_T("ģ ��  I"),2,4,hti6);	

	HTREEITEM hti7=m_wndTree.InsertItem(_T("���¸���������ϵͳ"),0,3,hti);	
	m_wndTree.InsertItem(_T("ģ ��  I"),2,4,hti7);
	m_wndTree.InsertItem(_T("ģ ��  II"),2,4,hti7);	
	m_wndTree.InsertItem(_T("ģ ��  III"),2,4,hti7);

	HTREEITEM hti8=m_wndTree.InsertItem(_T("������Ϣ"),0,3, hti);
	if(theApp.m_status!=_T("��ͨ�û�"))
	{
		m_wndTree.InsertItem(_T("������Ϣ����"),2,4,hti8);
		HTREEITEM hti9=m_wndTree.InsertItem(_T("���ݿ����"),0,3,hti8);
		m_wndTree.InsertItem(_T("���ݱ���"),2,4,hti9);
		m_wndTree.InsertItem(_T("���ݻ�ԭ"),2,4,hti9);
	}
	//չ�����Ϳؼ��Ľ��
	m_wndTree.Expand(hti,TVE_EXPAND);
	/*m_wndTree.Expand(hti2,TVE_EXPAND);
	m_wndTree.Expand(hti3,TVE_EXPAND);
	m_wndTree.Expand(hti4,TVE_EXPAND);
	m_wndTree.Expand(hti5,TVE_EXPAND);
	m_wndTree.Expand(hti6,TVE_EXPAND);
	m_wndTree.Expand(hti7,TVE_EXPAND);
	m_wndTree.Expand(hti8,TVE_EXPAND);*/

	///�����Ϳؼ����뵽TabCtrl��
	m_pLeft->AddPage(&m_wndTree,_T("Dialog"),IDI_ICON10); //�����Ϳؼ���ӵ���һҳ
	
	m_pLeft->UpdateWindow(); //����TabControl

	return 0;
}


BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle , CWnd* pParentWnd , CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class

	return CFrameWnd::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext);
}


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class

	//Create splitter window by two views
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return -1;

	if (!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CRightView), CSize(100, 100),pContext) ||
		!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CCoolTabCtrl), CSize(100, 100),pContext))
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}
	m_pRight = reinterpret_cast<CRightView*>(m_wndSplitter.GetPane(0,1));
	m_pLeft = reinterpret_cast<CCoolTabCtrl*>(m_wndSplitter.GetPane(0,0));
	m_wndSplitter.SetColumnInfo(0, 200, 100);	

	return CFrameWnd::OnCreateClient(lpcs, pContext);
}

int pos=-100;	//���Կ��ƶԻ���λ���ƶ��ı���
void CMainFrame::OnDblclkTree(NMHDR* pNMHDR, LRESULT* pResult)		//���Ϳؼ���˫���¼�
{

	pos+=20;
	if(pos>0) pos=-70;
	HTREEITEM hm=m_wndTree.GetSelectedItem();
	CString str;
	CRect rect;
	GetClientRect(&rect);
	str=m_wndTree.GetItemText(hm);
	if(str==_T("ģ ��  I"))
	{
		m_wndTree.GetFirstVisibleItem();
		CInfoDialog *infoDialog = new CInfoDialog;
		infoDialog->Create(IDD_INFODIALOG,this);
		infoDialog->ShowWindow(SW_SHOW);	//��ʾ��ģ̬�Ի���

		//�ƶ��Ի����λ��ʹ�䲻�ص�
		//InStuInfoDlg->SetWindowPos(0,rect.right/2+pos,rect.bottom/2+pos,0,0,SWP_NOSIZE | SWP_NOZORDER);

	}
	else if(str==_T("�γ���Ϣ����"))
	{
		
	}
	else if(str==_T("������Ϣ����"))
	{

		
	}
	else if(str==_T("���ݱ���"))
	{

	}
	else if(str==_T("���ݻ�ԭ"))
	{
		
	}

}


void CMainFrame::OnDestroy()
{
	CFrameWnd::OnDestroy();

	// TODO: Add your message handler code here

	//�رռ�¼��������

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
	

	//CoUninitialize();	//�˳�com��
}

