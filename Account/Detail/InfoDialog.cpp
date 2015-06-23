// InfoDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Detail.h"
#include "InfoDialog.h"
#include "afxdialogex.h"


// CInfoDialog dialog

IMPLEMENT_DYNAMIC(CInfoDialog, CDialog)

CInfoDialog::CInfoDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CInfoDialog::IDD, pParent)
{
	dataID.Empty();
	boardName.Empty();
	deviceNum.Empty();
	info.Empty();
	moduleNum.Empty();
	portNum, portType.Empty();
	slotNum.Empty();
	timeSlot.Empty();
}

CInfoDialog::~CInfoDialog()
{
}

void CInfoDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Control(pDX, IDC_BNAME, m_boardName);
	DDX_Control(pDX, IDC_DEVICENUM, m_devNum);
	DDX_Control(pDX, IDC_INFO, m_info);
	DDX_Control(pDX, IDC_MODNUM, m_modNum);
	DDX_Control(pDX, IDC_PORTNUM, m_portNum);
	DDX_Control(pDX, IDC_PORTTYPE, m_portType);
	DDX_Control(pDX, IDC_SLOTNUM, m_slotNum);
	DDX_Control(pDX, IDC_TIMESLOT, m_timeSlot);
}


BEGIN_MESSAGE_MAP(CInfoDialog, CDialog)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CInfoDialog message handlers


BOOL CInfoDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	/*m_Grid.SetExtendedStyle(LVS_EX_FLATSB

		|LVS_EX_FULLROWSELECT

		|LVS_EX_HEADERDRAGDROP

		|LVS_EX_ONECLICKACTIVATE

		|LVS_EX_GRIDLINES);

	m_Grid.InsertColumn(0,_T("���"),LVCFMT_LEFT,50,0);
	m_Grid.InsertColumn(1,_T("ģ��"),LVCFMT_LEFT,80,1);
	m_Grid.InsertColumn(2,_T("��λ"),LVCFMT_LEFT,50,2);
	m_Grid.InsertColumn(3,_T("����"),LVCFMT_LEFT,110,3);
	m_Grid.InsertColumn(4,_T("�˿ں�"),LVCFMT_LEFT,50,4);
	m_Grid.InsertColumn(5,_T("ʹ��ʱ϶��"),LVCFMT_LEFT,110,5);
	m_Grid.InsertColumn(6,_T("�豸��"),LVCFMT_LEFT,110,6);
	m_Grid.InsertColumn(7,_T("�˿�����"),LVCFMT_LEFT,110,7);
	m_Grid.InsertColumn(8,_T("����"),LVCFMT_LEFT,200,8);*/

	/*m_Grid.InsertColumn(0,_T("���"),LVCFMT_LEFT,110,0);

	m_Grid.InsertColumn(1,_T("����"),LVCFMT_LEFT,110,1);

	m_Grid.InsertColumn(2,_T("�Ա�"),LVCFMT_LEFT,110,2);

	m_Grid.InsertColumn(3,_T("ѧ��"),LVCFMT_LEFT,110,3);*/

	AddToGrid();


	/*OnInitADOConn();
	m_list.InsertColumn(0,_T("�о������"),LVCFMT_CENTER,100,-1);
	m_list.InsertColumn(1,_T("����"),LVCFMT_CENTER,80,-1);
	m_list.InsertColumn(2,_T("�γ̱��"),LVCFMT_CENTER,80,-1);
	m_list.InsertColumn(3,_T("�γ�����"),LVCFMT_CENTER,100,-1);
	m_list.InsertColumn(4,_T("ʱ��"),LVCFMT_CENTER,100,-1);
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	CString sql,stuNum,couNum,stuName,couName,time;
	int index=0;
	try
	{
		sql=_T("select * from students,courses,choices where \
			choices.stuID=students.stuID and choices.couID=courses.couID \
			order by students.stuID,choices.couID asc");			//��ѧ�źͿγ̺���������
		m_pRecordset=m_pConnection->Execute((_bstr_t)sql,NULL,adCmdText);
		while(!m_pRecordset->adoEOF)
		{
			stuNum=(char*)(_bstr_t)m_pRecordset->GetCollect("stuID");
			m_list.InsertItem(index,stuNum);

			stuName=(char*)(_bstr_t)m_pRecordset->GetCollect("stuName");
			m_list.SetItemText(index,1,stuName);

			couNum=(char*)(_bstr_t)m_pRecordset->GetCollect("couID");
			m_list.SetItemText(index,2,couNum);

			couName=(char*)(_bstr_t)m_pRecordset->GetCollect("couName");
			m_list.SetItemText(index,3,couName);

			time=(char*)(_bstr_t)m_pRecordset->GetCollect("time");
			m_list.SetItemText(index,4,time);

			m_pRecordset->MoveNext();
			index++;
		}

	}
	catch(_com_error &e)
	{
		MessageBox(e.Description());
	}*/


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CInfoDialog::OnInitADOConn()
{
	//if(!AfxOleInit())//����ǳ�ʼ��COM��
	//{
	//	AfxMessageBox(_T("KE��ʼ������!"));
	//}

	//CoInitialize(NULL);
	//HRESULT hr;
	//try                            //�������ݿ�
	//{
	//	hr = m_pConnection.CreateInstance(__uuidof(Connection)/*"ADODB.Connection"*/);
	//	if(SUCCEEDED(hr))
	//	{
	//		m_pConnection->ConnectionTimeout = 10;	//���ӳ�ʱ
	//		m_pConnection->CursorLocation = adUseClient;//�����ڼ�¼��ָ�룬�ǳ���Ҫ!!!
	//		m_pConnection->ConnectionString = "File Name=happyXiu.udl";
	//		m_pConnection->Open("","","",-1);
	//	}
	//}
	//catch(_com_error e)
	//{
	//	CString str;
	//	str.Format(_T("�������ݿ�ʧ��:%s"),e.ErrorMessage());
	//	::MessageBox(NULL,str,_T("��ʾ��Ϣ"),NULL);
	//	//return false;
	//}
}

void CInfoDialog::ExitConnect()
{
	//�رռ�¼��������

	/*if(m_pRecordset!=NULL)
		m_pRecordset->Close();

	if(m_pConnection!=NULL)
	m_pConnection->Close();*/
	//CoUninitialize();	//�˳�com��
}

void CInfoDialog::AddToGrid()
{
	//�������ݿ�
	/*OnInitADOConn();*/

	m_list.InsertColumn(0,_T("���"),LVCFMT_LEFT,50,0);
	m_list.InsertColumn(1,_T("ģ��"),LVCFMT_LEFT,80,1);
	m_list.InsertColumn(2,_T("��λ"),LVCFMT_LEFT,50,2);
	m_list.InsertColumn(3,_T("����"),LVCFMT_LEFT,110,3);
	m_list.InsertColumn(4,_T("�˿ں�"),LVCFMT_LEFT,50,4);
	m_list.InsertColumn(5,_T("ʹ��ʱ϶��"),LVCFMT_LEFT,110,5);
	m_list.InsertColumn(6,_T("�豸��"),LVCFMT_LEFT,110,6);
	m_list.InsertColumn(7,_T("�˿�����"),LVCFMT_LEFT,110,7);
	m_list.InsertColumn(8,_T("����"),LVCFMT_LEFT,200,8);
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	CString sql;
	
	int index=0;
	try
	{
		sql=_T("select * from main");			//��ѧ�źͿγ̺���������
		theApp.m_pRecordset=theApp.m_pConnection->Execute((_bstr_t)sql,NULL,adCmdText);
		_variant_t var;
		while(!theApp.m_pRecordset->adoEOF)
		{
			dataID.Empty();
			boardName.Empty();
			deviceNum.Empty();
			info.Empty();
			moduleNum.Empty();
			portNum, portType.Empty();
			slotNum.Empty();
			timeSlot.Empty();

			var = theApp.m_pRecordset->GetCollect("dataID");
			if(var.vt != VT_NULL)
			{
				dataID = (char*)(_bstr_t)var;
				m_list.InsertItem(index,dataID);

			}
			else
			{
				m_list.InsertItem(index,dataID);
			}

			var = theApp.m_pRecordset->GetCollect("moduleNum");
			if(var.vt != VT_NULL)
			{
				moduleNum = (char*)(_bstr_t)var;
				m_list.SetItemText(index,1,moduleNum);

			}
			else
			{
				m_list.SetItemText(index,1,moduleNum);
			}

			var =theApp. m_pRecordset->GetCollect("slotNum");			
			if(var.vt != VT_NULL)
			{				
				slotNum = (char*)(_bstr_t)var;
				m_list.SetItemText(index,2,slotNum);

			}
			else
			{
				m_list.SetItemText(index,4,portNum);
			}
			
			var = theApp.m_pRecordset->GetCollect("boardName");			
			if(var.vt != VT_NULL)
			{				
				boardName = (char*)(_bstr_t)var;
				m_list.SetItemText(index,3,boardName);

			}
			else
			{
				m_list.SetItemText(index,3,boardName);
			}

			var = theApp.m_pRecordset->GetCollect("portNum");			
			if(var.vt != VT_NULL)
			{				
				portNum = (char*)(_bstr_t)var;
				m_list.SetItemText(index,4,portNum);
				
			}
			else
			{
				m_list.SetItemText(index,4,portNum);
			}

			var= theApp.m_pRecordset->GetCollect("timeSlot");
			if(var.vt != VT_NULL)
			{				
				timeSlot = (char*)(_bstr_t)var;
				m_list.SetItemText(index,5,timeSlot);

			}
			else
			{
				m_list.SetItemText(index,5,timeSlot);
			}

			var= theApp.m_pRecordset->GetCollect("deviceNum");
			if(var.vt != VT_NULL)
			{
				deviceNum = (char*)(_bstr_t)var;
				m_list.SetItemText(index,6,deviceNum);

			}
			else
			{
				m_list.SetItemText(index,6,timeSlot);
			}

			var= theApp.m_pRecordset->GetCollect("portType");
			if(var.vt != VT_NULL)
			{				
				portType = (char*)(_bstr_t)var;
				m_list.SetItemText(index,7,portType);

			}
			else
			{
				m_list.SetItemText(index,7,portType);
			}

			var= theApp.m_pRecordset->GetCollect("info");
			if(var.vt != VT_NULL)
			{				
				info = (char*)(_bstr_t)var;
				m_list.SetItemText(index,8,info);

			}
			else
			{
				m_list.SetItemText(index,8,info);
			}
					

			/*
			dataID = (char*)(_bstr_t)m_pRecordset->GetCollect(_T("dataID"));			
			m_list.InsertItem(index,dataID);

			moduleNum = (char*)(_bstr_t)m_pRecordset->GetCollect(_T("moduleNum"));
			m_list.SetItemText(index,1,moduleNum);

			slotNum = (char*)(_bstr_t)m_pRecordset->GetCollect(_T("slotNum"));
			m_list.SetItemText( index, 2, slotNum);

			boardName=(char*)(_bstr_t)m_pRecordset->GetCollect(_T("boardName"));
			m_list.SetItemText(index,3,boardName);

			portNum = (char*)(_bstr_t)m_pRecordset->GetCollect(_T("portNum"));	
			if (portNum.IsEmpty())
			{
			portNum.Format(_T(" "));
			}
			m_list.SetItemText(index,4,portNum);

			timeSlot = (char*)(_bstr_t)m_pRecordset->GetCollect(_T("timeSlot"));
			m_list.SetItemText( index, 5, timeSlot);

			deviceNum=(char*)(_bstr_t)m_pRecordset->GetCollect(_T("deviceNum"));
			m_list.SetItemText(index,6,deviceNum);

			portType = (char*)(_bstr_t)m_pRecordset->GetCollect(_T("portType"));
			m_list.SetItemText(index,7,portType);
			
			info = (char*)(_bstr_t)m_pRecordset->GetCollect(_T("info"));
			m_list.SetItemText( index, 8, info);
			*/

			theApp.m_pRecordset->MoveNext();
			index++;
		}

	}
	catch(_com_error &e)
	{
		MessageBox(e.Description());
	}
	//�Ͽ����ݿ�����
	/*ExitConnect();
	CoUninitialize();*/	//�˳�com��

}


void CInfoDialog::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::OnCancel();
	//�Ͽ����ݿ�����
	ExitConnect();
}
