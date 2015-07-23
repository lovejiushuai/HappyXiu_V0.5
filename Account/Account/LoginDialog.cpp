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
	m_password = _T("");
	m_username = _T("");
}

CLoginDialog::~CLoginDialog()
{
}

void CLoginDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_password);
	DDX_CBString(pDX, IDC_EDIT_USERNAME, m_username);
}


BEGIN_MESSAGE_MAP(CLoginDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CLoginDialog::OnBnClickedOk)
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
	
	CDialog::OnOK();

	/*
	UpdateData();
	static int inCount=0;

	++inCount;
	if(m_username.IsEmpty()||m_password.IsEmpty())
	{
		m_ctrlCue.SetWindowText(_T("提示:用户名或密码不能为空!"));
	}
	else
	{
		CString sql,password,levelIn,levelOut;
		sql.Format("select * from login where username='%s'",m_username);
		m_rec=theApp.m_conn->Execute((_bstr_t)sql,NULL,adCmdText);
		if(!m_rec->adoEOF)
		{
			password=(char*)(_bstr_t)m_rec->GetCollect("password");
			levelIn=(char*)(_bstr_t)m_rec->GetCollect("level");
			m_level.GetWindowText(levelOut);
			m_status=levelOut;
			if(password!=m_password)
			{
				m_ctrlCue.SetWindowText(_T("提示:密码错误,请重新输入!"));
				GetDlgItem(IDC_EDIT_PASSWORD)->SetFocus();
				m_password="";
				UpdateData(false);
			}
			else
			{
				if(levelIn==levelOut)
				{
					CDialog::OnOK();
					return;	
					//注意!如果没有return它会继续向下执行如果inCount>=4，就算OnOK了它还是会调用OnCancel函数
				}
				else
				{
					m_ctrlCue.SetWindowText(_T("提示:您不是")+levelOut+_T("!"));
					m_level.SetFocus();
				}
			}
		}
		else
		{
			m_ctrlCue.SetWindowText(_T("提示:对不起,没有此用户!"));
			GetDlgItem(IDC_EDIT_USERNAME)->SetFocus();
			m_username="";
			UpdateData(false);
		}
	}
	if(inCount>=4)	//四次登录失败则退出
	{
		inCount=0;
		CLoginDialog::OnCancel();
	}
	else if(inCount==3)
	{
		m_ctrlCue.SetWindowText(_T("提示:只剩下最后一次机会了!"));
		return;
	}
	*/
}
