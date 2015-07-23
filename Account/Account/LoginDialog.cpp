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
	CoUninitialize();//���COM����
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
	//���������ݿ�  ����Ҫע��OnOk
	/*CDialog::OnOK();*/

	//��ʼ��COM����
#if _WIN32_WINNT > 0x500
	//�����֣�����Ϊnull�� �����ط�ʽ COINIT_MULTITHREADED���̵߳ķ�ʽ����
	// �Զ��̷߳�ʽ��comͨ��
	::CoInitializeEx(NULL, COINIT_MULTITHREADED);
#else
	::CoInitialize(NULL);
#endif

	HRESULT hr;
	try                            //�������ݿ�
	{
		hr = theApp.m_pConnection.CreateInstance(__uuidof(Connection)/*"ADODB.Connection"*/);
		if(SUCCEEDED(hr))
		{
			theApp.m_pConnection->ConnectionTimeout = 10;	//���ӳ�ʱ
			theApp.m_pConnection->CursorLocation = adUseClient;//�����ڼ�¼��ָ�룬�ǳ���Ҫ!!!
			theApp.m_pConnection->ConnectionString = _T("File Name=����.udl");
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
			CString sql,passWord;
			sql.Format(_T("select * from login where userName='%s'"),m_userName);
			theApp.m_pRecordset = theApp.m_pConnection->Execute((_bstr_t)sql,NULL,adCmdText);
			if(!theApp.m_pRecordset->EndOfFile)
			{
				passWord=(char*)(_bstr_t)theApp.m_pRecordset->GetCollect("passWord");
				//levelIn=(char*)(_bstr_t)m_rec->GetCollect("level");
				if(passWord!=m_passWord)
				{
					m_alertM.SetWindowText(_T("��ʾ:�������,����������!"));
					GetDlgItem(IDC_EDIT_PASSWORD)->SetFocus();
					m_passWord.Format(_T(""));
					UpdateData(false);
				}
				else
				{
					CLoginDialog::OnOK();
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
		CLoginDialog::OnCancel();
	}
	else if(inCount==3)
	{
		m_alertM.SetWindowText(_T("��ʾ:ֻʣ�����һ�λ�����!"));
		return;
	}
	
}


HBRUSH CLoginDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
