// LoginDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Account.h"
#include "LoginDialog.h"
#include "afxdialogex.h"


// CLoginDialog dialog

IMPLEMENT_DYNAMIC(CLoginDialog, CDialog)

CLoginDialog::CLoginDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDialog::IDD, pParent)
{
	m_passWord = _T("");
	m_userName = _T("");
}

CLoginDialog::~CLoginDialog()
{
	if (theApp.m_pRecordset)
	{
		theApp.m_pRecordset->Close();
		theApp.m_pRecordset = NULL;
	}
	CoUninitialize();//清除COM环境
}

void CLoginDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ALERT, m_alertM);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_passWord);
	DDX_CBString(pDX, IDC_EDIT_USERNAME, m_userName);
}


BEGIN_MESSAGE_MAP(CLoginDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CLoginDialog::OnBnClickedOk)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CLoginDialog message handlers


BOOL CLoginDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CLoginDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//若连接数据库  则需要注释OnOk
	/*CDialog::OnOK();*/

	//初始化COM环境
#if _WIN32_WINNT > 0x500
	//保留字（必须为null） ，加载方式 COINIT_MULTITHREADED多线程的方式加载
	// 以多线程方式打开com通道
	::CoInitializeEx(NULL, COINIT_MULTITHREADED);
#else
	::CoInitialize(NULL);
#endif

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

	UpdateData();
	static int inCount=0;

	++inCount;
	if(m_userName.IsEmpty()||m_passWord.IsEmpty())
	{
		m_alertM.SetWindowText(_T("提示:用户名或密码不能为空!"));
	}
	else
	{	
		try
		{
			CString sql,passWord;
			sql.Format(_T("select * from login where userName='%s'"),m_userName);
			theApp.m_pRecordset = theApp.m_pConnection->Execute((_bstr_t)sql,NULL,adCmdText);
			if(!theApp.m_pRecordset->EndOfFile)
			{
				passWord=(char*)(_bstr_t)theApp.m_pRecordset->GetCollect("passWord");
				//levelIn=(char*)(_bstr_t)m_rec->GetCollect("level");
				if(passWord!=m_passWord)
				{
					m_alertM.SetWindowText(_T("提示:密码错误,请重新输入!"));
					GetDlgItem(IDC_EDIT_PASSWORD)->SetFocus();
					m_passWord.Format(_T(""));
					UpdateData(false);
				}
				else
				{
					//设置用户等级供后面DLL判断修改使用
					theApp.adminLevel = 1;
					CLoginDialog::OnOK();
				}
			}
			else
			{
				m_alertM.SetWindowText(_T("提示:对不起,没有此用户!"));
				GetDlgItem(IDC_EDIT_USERNAME)->SetFocus();
				m_userName.Format(_T(""));
				UpdateData(false);
			}
		}
		catch (_com_error &e)
		{
			MessageBox(e.Description());
		}			
	}

	//四次登录失败则退出
	if(inCount>=4)
	{
		inCount=0;
		theApp.adminLevel = 0;
		CLoginDialog::OnCancel();
	}
	else if(inCount==3)
	{
		m_alertM.SetWindowText(_T("提示:只剩下最后一次机会了!"));
		return;
	}
	
}


HBRUSH CLoginDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here

	//改变对话框背景颜色
	/*if (nCtlColor != CTLCOLOR_EDIT && nCtlColor != CTLCOLOR_LISTBOX) {
		pDC->SetBkMode(TRANSPARENT);
		HBRUSH B = CreateSolidBrush(RGB(128, 184, 223)); 
		return (HBRUSH) B;
	}*/
	//改变提示字体颜色
	if(pWnd->GetDlgCtrlID() == IDC_ALERT)
	{
		pDC->SetTextColor(RGB(255,0,0));
		pDC->SetBkMode(TRANSPARENT);
	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}
