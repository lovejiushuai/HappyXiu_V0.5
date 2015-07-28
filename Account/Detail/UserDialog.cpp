// UserDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Detail.h"
#include "UserDialog.h"
#include "afxdialogex.h"

// CUserDialog dialog

IMPLEMENT_DYNAMIC(CUserDialog, CDialog)

CUserDialog::CUserDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CUserDialog::IDD, pParent)
{
	m_passWord = _T("");
	m_userName = _T("");
}

CUserDialog::~CUserDialog()
{
	
}

void CUserDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	/*DDX_Control(pDX, IDC_ALERT, m_alertM);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_passWord);
	DDX_Text(pDX, IDC_COMFIRM_PASSWORD, m_passWordConfirm);*/
}


BEGIN_MESSAGE_MAP(CUserDialog, CDialog)
	ON_BN_CLICKED( IDC_BUTTON_SUBMIT, OnBnClickedOk)
	ON_BN_CLICKED( IDC_BUTTON_CANCEL, OnBnClickedOk)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CUserDialog message handlers


BOOL CUserDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	
	LoadControl();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CUserDialog::LoadControl()
{
	int screenwidth=GetSystemMetrics(SM_CXFULLSCREEN);
	int screenheight=GetSystemMetrics(SM_CYFULLSCREEN);
	/*int screenwidth=800;
	int screenheight=600;*/
	
	m_Font.CreateFont(30,
		0,
		0,
		0,
		700,
		FALSE,
		FALSE,
		0,
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		FF_SWISS,
		_T("楷体")); 
	
	
	m_rcPanel.SetRect(screenwidth/2 - 340,screenheight/2 - 220,screenwidth/2 + 347,screenheight/2 + 220);
	MoveWindow(&m_rcPanel);

	m_alertM.Create(_T("请输入修改后的密码："),WS_CHILD|WS_VISIBLE|WS_EX_TRANSPARENT,CRect(70,60,500,100),this,IDC_ALERT);	
	GetDlgItem(IDC_ALERT)->SetFont(&m_Font);

	m_editPW.Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER|ES_PASSWORD,CRect(80,180,220,210), this, IDC_EDIT_PASSWORD);
	m_editPWConfirm.Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER|ES_PASSWORD,CRect(450,180,590,210), this, IDC_EDIT_PASSWORD);

	// Create  button.
	m_buttonSubmit.Create( _T("提交"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, CRect( 70, 380, 145, 405), this, IDC_BUTTON_SUBMIT);
	m_buttonCancel.Create( _T("取消"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, CRect( 160, 380, 235, 405), this, IDC_BUTTON_CANCEL);
	return TRUE;
}

void CUserDialog::OnBnClickedOk()
{
	

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
			CString sql,passWord,userID;
			_variant_t var;
			sql.Format(_T("select * from User where userName='%s'"),m_userName);
			theApp.m_pRecordset = theApp.m_pConnection->Execute((_bstr_t)sql,NULL,adCmdText);
			if(!theApp.m_pRecordset->adoEOF)
			{
				passWord=(char*)(_bstr_t)theApp.m_pRecordset->GetCollect("passWord");
				//levelIn=(char*)(_bstr_t)m_rec->GetCollect("level");
				var = theApp.m_pRecordset->GetCollect("id");
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
					CUserDialog::OnOK();
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
		CUserDialog::OnCancel();
	}
	else if(inCount==3)
	{
		m_alertM.SetWindowText(_T("提示:只剩下最后一次机会了!"));
		return;
	}
	
}


HBRUSH CUserDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	if(pWnd->GetDlgCtrlID() == IDC_BUTTON_SUBMIT)
	{		
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	if(pWnd->GetDlgCtrlID() == IDC_BUTTON_CANCEL)
	{
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}