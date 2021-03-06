// LoginDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Account.h"
#include "LoginDialog.h"
#include "afxdialogex.h"


// CLoginDialog dialog

IMPLEMENT_DYNAMIC(CLoginDialog, CDialog)

//初始化参数
CLoginDialog::CLoginDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDialog::IDD, pParent)
{
	m_passWord = _T("");
	m_userName = _T("");
	m_bIsUser = false;
}

//窗口销毁  析构函数
CLoginDialog::~CLoginDialog()
{
	if (theApp.m_pRecordset)
	{
		theApp.m_pRecordset->Close();
		theApp.m_pRecordset = NULL;
	}
	CoUninitialize();//清除COM环境
}

//定义参数 与 控件关联  数据交换
void CLoginDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ALERT, m_alertM);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_passWord);
	DDX_CBString(pDX, IDC_EDIT_USERNAME, m_userName);
}

//消息映射   按钮ID 消息ID 与 响应函数一一对应
BEGIN_MESSAGE_MAP(CLoginDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CLoginDialog::OnBnClickedOk)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDCANCEL, &CLoginDialog::OnBnClickedCancel)
	ON_BN_CLICKED(IDNOMAL, &CLoginDialog::OnBnClickedNomal)
END_MESSAGE_MAP()


// CLoginDialog message handlers

// 窗口初始化
BOOL CLoginDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

// 登录按键  响应
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
		// 若连接失败  就弹出消息框  提示失败消息
		CString str;
		str.Format(_T("连接数据库失败:%s"),e.ErrorMessage());
		::MessageBox(NULL,str,_T("提示信息"),NULL);
		//return false;
	}

	UpdateData();
	static int inCount=0;

	++inCount;
	//检测名字和密码是否为空
	if(m_userName.IsEmpty()||m_passWord.IsEmpty())
	{
		m_alertM.SetWindowText(_T("提示:用户名或密码不能为空!"));
	}
	else
	{	
		try
		{
			// 查询数据库userData 表中  是否存在 指定的 userName
			CString sql,passWord,userID;
			_variant_t var;
			sql.Format(_T("select * from userData where userName='%s'"),m_userName);
			theApp.m_pRecordset = theApp.m_pConnection->Execute((_bstr_t)sql,NULL,adCmdText);
			if(!theApp.m_pRecordset->EndOfFile)
			{
				// 若存在指定 用户名   则取出指定用户名的 密码 uPassword 项
				passWord=(char*)(_bstr_t)theApp.m_pRecordset->GetCollect("uPassword");
				//levelIn=(char*)(_bstr_t)m_rec->GetCollect("uLevel");
				var = theApp.m_pRecordset->GetCollect("userID");
				if(var.vt != VT_NULL)
				{				
					userID = (char*)(_bstr_t)var;
					m_userID = _ttoi(userID);
					if (m_userID > 0)
					{
						theApp.m_userID = m_userID;
					}
					else
					{
						m_alertM.SetWindowText(_T("提示:UserID,小于0!"));
					}
				}
				else
				{
					
				}

				// 进行密码比对 若不一致则进行 静态文本提醒
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

// 若点击对话框 关闭按钮  则相应此函数
void CLoginDialog::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	
	CDialog::OnCancel();
}

// 若点击对话框中  普通登录  则相应此函数
void CLoginDialog::OnBnClickedNomal()
{
	// TODO: Add your control notification handler code here
	m_bIsUser = true;
	CDialog::OnCancel();
}
