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
	DDX_Control(pDX, IDC_ALERT, m_alertM);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_passWord);
	DDX_CBString(pDX, IDC_EDIT_USERNAME, m_userName);
}


BEGIN_MESSAGE_MAP(CUserDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CUserDialog::OnBnClickedOk)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CUserDialog message handlers


BOOL CUserDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CUserDialog::OnBnClickedOk()
{
	

	UpdateData();
	static int inCount=0;

	++inCount;
	if(m_userName.IsEmpty()||m_passWord.IsEmpty())
	{
		m_alertM.SetWindowText(_T("��ʾ:�û��������벻��Ϊ��!"));
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
						m_alertM.SetWindowText(_T("��ʾ:UserID,С��0!"));
					}
				}
				else
				{
					
				}

				if(passWord!=m_passWord)
				{
					m_alertM.SetWindowText(_T("��ʾ:�������,����������!"));
					GetDlgItem(IDC_EDIT_PASSWORD)->SetFocus();
					m_passWord.Format(_T(""));
					UpdateData(false);
				}
				else
				{
					//�����û��ȼ�������DLL�ж��޸�ʹ��
					CUserDialog::OnOK();
				}
			}
			else
			{
				m_alertM.SetWindowText(_T("��ʾ:�Բ���,û�д��û�!"));
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

	//�Ĵε�¼ʧ�����˳�
	if(inCount>=4)
	{
		inCount=0;
		CUserDialog::OnCancel();
	}
	else if(inCount==3)
	{
		m_alertM.SetWindowText(_T("��ʾ:ֻʣ�����һ�λ�����!"));
		return;
	}
	
}


HBRUSH CUserDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here

	//�ı�Ի��򱳾���ɫ
	/*if (nCtlColor != CTLCOLOR_EDIT && nCtlColor != CTLCOLOR_LISTBOX) {
		pDC->SetBkMode(TRANSPARENT);
		HBRUSH B = CreateSolidBrush(RGB(128, 184, 223)); 
		return (HBRUSH) B;
	}*/
	//�ı���ʾ������ɫ
	if(pWnd->GetDlgCtrlID() == IDC_ALERT)
	{
		pDC->SetTextColor(RGB(255,0,0));
		pDC->SetBkMode(TRANSPARENT);
	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}
