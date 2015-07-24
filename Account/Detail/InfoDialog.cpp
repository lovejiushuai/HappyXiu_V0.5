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
	moduleNum.Empty();
	slotNum.Empty();
	boardName.Empty();
	portNum.Empty();
	timeSlot.Empty();
	deviceNum.Empty();	
	portType.Empty();	
	info.Empty();

	m_listName.Empty();
	m_inquerySQL.Empty();
	m_containValue = 0;
	idataID = 0;
	imoduleNum = 0;
	islotNum = 0;
}

CInfoDialog::~CInfoDialog()
{
}

void CInfoDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_list);	
}


BEGIN_MESSAGE_MAP(CInfoDialog, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_LIST, OnClickList)
	ON_BN_CLICKED( IDC_BUTTON_ADD, OnAddData)
	ON_BN_CLICKED( IDC_BUTTON_MODIFY, OnModifyData)
	ON_BN_CLICKED( IDC_BUTTON_DELETE, OnDeleteData)
	ON_BN_CLICKED( IDC_BUTTON_CLEAR, OnClearData)
	ON_MESSAGE(CBN_SELENDOK, UpdataList)
	ON_MESSAGE(WM_UPDATALIST, UpdataList)
END_MESSAGE_MAP()


// CInfoDialog message handlers


BOOL CInfoDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	LoadControl();
	AddToList();
	
	if (theApp.m_bIsAdmin)
	{
		m_addButton.EnableWindow(TRUE);
		m_deleteButton.EnableWindow(TRUE);
		m_modifyButton.EnableWindow(TRUE);
		m_clearButton.EnableWindow(TRUE);
	}
	else
	{
		m_addButton.EnableWindow(FALSE);
		m_deleteButton.EnableWindow(FALSE);
		m_modifyButton.EnableWindow(FALSE);
		m_clearButton.EnableWindow(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CInfoDialog::LoadControl()
{
	// ��ȡ��ǰ��Ļ�ֱ���  -- ��������״̬����С
	/*int screenwidth=GetSystemMetrics(SM_CXFULLSCREEN);
	int screenheight=GetSystemMetrics(SM_CYFULLSCREEN);*/

	int screenwidth=800;
	int screenheight=600;

	CRect m_rcPanel;
	//���õ�ǰ���ڴ�С  �� ��ǰ��Ļ�ֱ��� һ��
	m_rcPanel.SetRect(0,0,screenwidth,screenheight);
	MoveWindow(&m_rcPanel);


	// ������Ļ�ֱ��� & ���ڴ�С���� List ��С
	CWnd *pwnd;
	CRect rect;

	pwnd=(CWnd *)GetDlgItem(IDC_LIST);
	if(pwnd==NULL)
	{
		pwnd = NULL;
	}
	else
	{
		pwnd->GetWindowRect(&rect);
		ScreenToClient(&rect);
		rect.right= 0.99* screenwidth;
		rect.bottom=0.4 * screenheight;
		pwnd->MoveWindow(&rect,TRUE);
		pwnd = NULL;
	}
	
	dataIDText.Create(_T("��ţ�"),WS_CHILD|WS_VISIBLE|SS_LEFT, CRect(0.6 * screenwidth, 0.42 * screenheight, 0.98 * screenwidth, 0.47 * screenheight), this, IDC_TEXT_DATAID);
	moduleNumText.Create(_T("ģ�飺"),WS_CHILD|WS_VISIBLE|SS_LEFT, CRect(0.1 * screenwidth, 0.42* screenheight, 0.2 * screenwidth, 0.47 * screenheight), this, IDC_TEXT_MODNUM);

	//m_modNum.Create(/*ES_MULTILINE |*/ WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_AUTOHSCROLL, CRect(0.22 * screenwidth, 0.42 * screenheight, 0.47 * screenwidth, 0.47 * screenheight), this, IDC_MODNUM);
	// ����ΪCBS_DROPDOWNLIST �����б���ڲ������룬����Ϊ  CBS_DROPDOWN �����б���ڿ�������
	m_cbModNum.Create( WS_CHILD | WS_VISIBLE | WS_TABSTOP |/* CBS_DROPDOWN |*/ CBS_DROPDOWNLIST | CBS_OEMCONVERT | CBS_SORT /*| WS_VSCROLL*/, CRect(0.22 * screenwidth, 0.42 * screenheight, 0.47 * screenwidth, 0.47 * screenheight), this, IDC_MODNUM);
	// Ϊ��Ͽ�ؼ����б������б��� 
	m_cbModNum.InsertString(0,_T("--- ��ѡ�� ---"));
	m_cbModNum.AddString(_T("ģ���"));
	m_cbModNum.AddString(_T("ģ���"));
	m_cbModNum.InsertString(3, _T("ģ���")); 
	m_cbModNum.SetCurSel(0);  // ���õ�ǰѡ����
	
	m_cbSlotNum.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP |/* CBS_DROPDOWN |*/ CBS_DROPDOWNLIST | CBS_OEMCONVERT | CBS_SORT /*| WS_VSCROLL*/, CRect(0.22 * screenwidth, 0.5 * screenheight, 0.47 * screenwidth, 0.55 * screenheight), this, IDC_BNAME);
	// Ϊ��Ͽ�ؼ����б������б��� 	
	CString insertSlotName;
	insertSlotName.Empty();
	for (int i = 0; i < 16; i++)
	{
		insertSlotName.Format(_T("��λ%d"),i);
		m_cbSlotNum.InsertString(i,insertSlotName);
	}	
	m_cbSlotNum.SetCurSel(0);  // ���õ�ǰѡ����

	slotNumText.Create(_T("��λ��"),WS_CHILD|WS_VISIBLE|SS_LEFT, CRect(0.1 * screenwidth, 0.5* screenheight, 0.2 * screenwidth, 0.55 * screenheight), this, IDC_TEXT_SLOTNUM);
	boardNameText.Create(_T("������"),WS_CHILD|WS_VISIBLE|SS_LEFT, CRect(0.6 * screenwidth, 0.5* screenheight, 0.7 * screenwidth, 0.55 * screenheight), this, IDC_TEXT_BNAME);

	//m_slotNum.Create(/*ES_MULTILINE |*/ WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(0.22 * screenwidth, 0.5 * screenheight, 0.47 * screenwidth, 0.55 * screenheight), this, IDC_BNAME);
	m_boardName.Create(/*ES_MULTILINE |*/ WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(0.72 * screenwidth, 0.5 * screenheight, 0.97 * screenwidth, 0.55 * screenheight), this, IDC_BNAME);


	portNumText.Create(_T("�˿ںţ�"),WS_CHILD|WS_VISIBLE|SS_LEFT, CRect(0.1 * screenwidth, 0.59* screenheight, 0.2 * screenwidth, 0.64 * screenheight), this, IDC_TEXT_PORTNUM);
	timeSlotText.Create(_T("ʹ��ʱ϶�ţ�"),WS_CHILD|WS_VISIBLE|SS_LEFT, CRect(0.6 * screenwidth, 0.59* screenheight, 0.7 * screenwidth, 0.64 * screenheight), this, IDC_TEXT_TIMESLOT);

	m_portNum.Create(/*ES_MULTILINE |*/ WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(0.22 * screenwidth, 0.59 * screenheight, 0.47* screenwidth, 0.64 * screenheight), this, IDC_PORTNUM);
	m_timeSlot.Create(/*ES_MULTILINE |*/ WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(0.72 * screenwidth, 0.59 * screenheight, 0.97* screenwidth, 0.64 * screenheight), this, IDC_TIMESLOT);


	deviceNumText.Create(_T("�豸�ţ�"),WS_CHILD|WS_VISIBLE|SS_LEFT, CRect(0.1 * screenwidth, 0.68* screenheight, 0.2 * screenwidth, 0.73 * screenheight), this, IDC_TEXT_DEVICENUM);
	portTypeText.Create(_T("�˿����ͣ�"),WS_CHILD|WS_VISIBLE|SS_LEFT, CRect(0.6 * screenwidth, 0.68* screenheight, 0.7 * screenwidth, 0.73 * screenheight), this, IDC_TEXT_PORTTYPE);

	m_devNum.Create(/*ES_MULTILINE |*/ WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(0.22 * screenwidth, 0.68 * screenheight, 0.47* screenwidth, 0.73 * screenheight), this, IDC_DEVICENUM);
	m_portType.Create(/*ES_MULTILINE |*/ WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_AUTOHSCROLL, CRect(0.72 * screenwidth, 0.68 * screenheight, 0.97* screenwidth, 0.73 * screenheight), this, IDC_PORTTYPE);


	infoText.Create(_T("������"),WS_CHILD|WS_VISIBLE|SS_LEFT, CRect(0.1 * screenwidth, 0.77* screenheight, 0.2 * screenwidth, 0.82 * screenheight), this, IDC_TEXT_INFO);

	m_info.Create(/*ES_MULTILINE |*/ WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_AUTOHSCROLL, CRect(0.22 * screenwidth, 0.77 * screenheight, 0.97* screenwidth, 0.82 * screenheight), this, IDC_INFO);

	//m_modNum.Create(/*ES_MULTILINE |*/ WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_AUTOHSCROLL, CRect(0.1 * screenwidth, 0.7 * screenheight, 0.2* screenwidth, 0.75 * screenheight), this, IDC_MODNUM);
	//m_slotNum.Create(/*ES_MULTILINE |*/ WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(0.35 * screenwidth, 0.7 * screenheight, 0.45* screenwidth, 0.75 * screenheight), this, IDC_BNAME);
	//m_boardName.Create(/*ES_MULTILINE |*/ WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(0.6 * screenwidth, 0.7 * screenheight, 0.7* screenwidth, 0.75 * screenheight), this, IDC_BNAME);
	//m_portNum.Create(/*ES_MULTILINE |*/ WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(0.85 * screenwidth, 0.7 * screenheight, 0.95* screenwidth, 0.75 * screenheight), this, IDC_PORTNUM);
	//m_timeSlot.Create(/*ES_MULTILINE |*/ WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(0.1 * screenwidth, 0.78 * screenheight, 0.2* screenwidth, 0.83 * screenheight), this, IDC_TIMESLOT);
	//m_devNum.Create(/*ES_MULTILINE |*/ WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(0.35 * screenwidth, 0.78 * screenheight, 0.45* screenwidth, 0.83 * screenheight), this, IDC_DEVICENUM);
	//m_portType.Create(/*ES_MULTILINE |*/ WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_AUTOHSCROLL, CRect(0.6 * screenwidth, 0.78 * screenheight, 0.7* screenwidth, 0.83 * screenheight), this, IDC_PORTTYPE);
	//m_info.Create(/*ES_MULTILINE |*/ WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_AUTOHSCROLL, CRect(0.85 * screenwidth, 0.78 * screenheight, 0.95* screenwidth, 0.85 * screenheight), this, IDC_INFO);

	// �����ĸ�����
	m_addButton.Create( _T("���"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, CRect( 0.07 * screenwidth, 0.85 * screenheight, 0.22* screenwidth, 0.95 * screenheight), this, IDC_BUTTON_ADD);
	m_modifyButton.Create(_T("�޸�"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, CRect( 0.32 * screenwidth, 0.85 * screenheight, 0.47 * screenwidth, 0.95 * screenheight), this, IDC_BUTTON_MODIFY);
	m_deleteButton.Create(_T("ɾ��"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, CRect( 0.57 * screenwidth, 0.85 * screenheight, 0.75 * screenwidth, 0.95 * screenheight), this, IDC_BUTTON_DELETE);
	m_clearButton.Create(_T("���"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, CRect( 0.82 * screenwidth, 0.85 * screenheight, 0.97 * screenwidth, 0.95 * screenheight), this, IDC_BUTTON_CLEAR);

	/*m_addButton.EnableWindow(TRUE);
	m_deleteButton.EnableWindow(TRUE);
	m_modifyButton.EnableWindow(TRUE);
	m_clearButton.EnableWindow(TRUE);*/

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

void CInfoDialog::AddToList()
{
	//�������ݿ�
	/*OnInitADOConn();*/

	// ��ȡ��Ļ���
	/*int screenwidth=GetSystemMetrics(SM_CXFULLSCREEN);*/
	int screenwidth=800;
	/*int screenheight=600;*/

	//���� �б� ��ͷ ÿ������ �� ���� ��Ļ�ֱ������ô�С
	m_list.InsertColumn(0,_T("���"),LVCFMT_LEFT,( 0.06 * screenwidth), 0);
	m_list.InsertColumn(1,_T("ģ��"),LVCFMT_LEFT,( 0.09 * screenwidth),1);
	m_list.InsertColumn(2,_T("��λ"),LVCFMT_LEFT,( 0.06 * screenwidth),2);
	m_list.InsertColumn(3,_T("����"),LVCFMT_LEFT,( 0.13 * screenwidth),3);
	m_list.InsertColumn(4,_T("�˿ں�"),LVCFMT_LEFT,( 0.06 * screenwidth),4);
	m_list.InsertColumn(5,_T("ʹ��ʱ϶��"),LVCFMT_LEFT,( 0.1 * screenwidth),5);
	m_list.InsertColumn(6,_T("�豸��"),LVCFMT_LEFT,( 0.12 * screenwidth),6);
	m_list.InsertColumn(7,_T("�˿�����"),LVCFMT_LEFT,( 0.12 * screenwidth),7);
	m_list.InsertColumn(8,_T("����"),LVCFMT_LEFT,( 0.23 * screenwidth),8);
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	CString sql;
	
	m_containValue=0;
	int index = 0;
	int maxDataID = 0;
	try
	{
		//��ģ�顢��λ���˿ںź�������Ϣ��������
		sql.Format(_T("select * from %s order by %s.moduleNum,%s.slotNum,%s.portNum,%s.info asc"), m_inquerySQL, m_listName, m_listName, m_listName, m_listName);
		theApp.m_pRecordset = theApp.m_pConnection->Execute((_bstr_t)sql,NULL,adCmdText);
		_variant_t var;
		while(!theApp.m_pRecordset->adoEOF)
		{
			dataID.Empty();
			moduleNum.Empty();
			slotNum.Empty();
			boardName.Empty();
			portNum.Empty();
			timeSlot.Empty();
			deviceNum.Empty();			
			portType.Empty();
			info.Empty();
			idataID = 0;
			imoduleNum = 0;
			islotNum = 0;

			/*var = theApp.m_pRecordset->GetCollect("dataID");
			if(var.vt != VT_NULL)
			{
				dataID = (char*)(_bstr_t)var;
				m_list.InsertItem(index,dataID);

			}
			else
			{
				m_list.InsertItem(index,dataID);
			}


			maxDataID = _ttoi(dataID);
			if (m_containValue < maxDataID)
			{
				m_containValue = maxDataID;
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
				m_list.SetItemText(index,2,portNum);
			}*/
			
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


			/*maxDataID = _ttoi(dataID);
			if (m_containValue < maxDataID)
			{
				m_containValue = maxDataID;
			}*/

			var = theApp.m_pRecordset->GetCollect("moduleNum");
			if(var.vt != VT_NULL)
			{
				imoduleNum = var;				
				switch( imoduleNum )
				{
				case 1:
					moduleNum.Format(_T("ģ���"));
					break;
				case 2:
					moduleNum.Format(_T("ģ���"));
					break;
				case 3:
					moduleNum.Format(_T("ģ���"));
					break;
				default:
					moduleNum.Format(_T("other"));
				}
				/*moduleNum = (char*)(_bstr_t)var;*/
				m_list.SetItemText(index,1,moduleNum);

			}
			else
			{
				m_list.SetItemText(index,1,moduleNum);
			}

			var =theApp. m_pRecordset->GetCollect("slotNum");			
			if(var.vt != VT_NULL)
			{
				islotNum = var;
				/*slotNum = (char*)(_bstr_t)var;*/
				slotNum.Format(_T("%d"),islotNum);
				m_list.SetItemText(index,2,slotNum);

			}
			else
			{
				m_list.SetItemText(index,2,slotNum);
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
							
			
			theApp.m_pRecordset->MoveNext();
			index ++;			
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

void CInfoDialog::OnClickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int mark = m_list.GetSelectionMark();
	if(mark<0) 
		return;
	
	dataID = m_list.GetItemText(mark,0);
	idataID = _ttoi(dataID);
	CString strShow;
	strShow.Format(_T("��ţ�%s"),dataID);
	dataIDText.SetDlgItemText( IDC_TEXT_DATAID, strShow);
	
	moduleNum = m_list.GetItemText(mark,1);
	/*m_modNum.SetWindowText(moduleNum);*/
	if (moduleNum == _T("ģ���"))
	{
		m_cbModNum.SetCurSel(1);
	}
	else if (moduleNum == _T("ģ���"))
	{
		m_cbModNum.SetCurSel(2);
	}
	else if (moduleNum == _T("ģ���"))
	{
		m_cbModNum.SetCurSel(3);
	}
	
	m_cbModNum.GetLBText(m_cbModNum.GetCurSel(),moduleNum);

	slotNum = m_list.GetItemText(mark,2);
	/*m_slotNum.SetWindowText(slotNum);*/

	islotNum = _ttoi(slotNum);
	m_cbSlotNum.SetCurSel(islotNum);


	boardName = m_list.GetItemText(mark,3);
	m_boardName.SetWindowText(boardName);

	portNum = m_list.GetItemText(mark,4);
	m_portNum.SetWindowText(portNum);

	timeSlot = m_list.GetItemText(mark,5);
	m_timeSlot.SetWindowText(timeSlot);

	deviceNum = m_list.GetItemText(mark,6);
	m_devNum.SetWindowText(deviceNum);

	portType = m_list.GetItemText(mark,7);
	m_portType.SetWindowText(portType);

	info = m_list.GetItemText(mark,8);
	m_info.SetWindowText(info);

	//����������Ļ�ж�Ӧ�ؼ�����ʾ����
	UpdateData(false);


	*pResult = 0;
}

void CInfoDialog::OnAddData()
{	
	//���ڽ���Ļ�Ͽؼ��е����ݽ�����������
	UpdateData(TRUE);


	getEditText();
	if(moduleNum.IsEmpty() || slotNum.IsEmpty() || boardName.IsEmpty() || info.IsEmpty())
	{
		AfxMessageBox(_T("���ȷ����д��Ϣ��!"),MB_ICONEXCLAMATION);
		return;
	}	
	if (m_cbModNum.GetCurSel() == 0)
	{
		AfxMessageBox(_T("��ѡ��Ҫ��ӽ���ģ��!"),MB_ICONEXCLAMATION);
		return;
	}

	/*dataID.Format(_T("%d"), m_containValue + 1);*/

	CString sql,number;	
	try
	{
		//sql.Format("insert into students(stuID,stuName,stuSex,teaID,comeFrom,comeYear,comeMonth,stuYear,stuMonth) \
		//	values(%s,'%s','%s',%s,%s,%s,%s,%s,%s)",m_strNumber,m_strName,m_strSex,m_strTeacher,m_comeYear,m_comeMonth,\
		//	m_stuYear,m_stuMonth);
		/*sql.Format(_T("insert into main(dataID,moduleNum,slotNum,boardName,portNum,timeSlot,deviceNum,portType,info)values(%s,%s,%s,%s,%s,%s,%s,%s,%s)"),+ m_containValue +",'"+moduleNum+"','"+slotNum+"',"+boardName+",'"+portNum+"',"+timeSlot+",\
																																																												  "+deviceNum+","+portType+","+info+"')");*/
		sql.Format(_T("insert into %s(moduleNum,slotNum,boardName,portNum,timeSlot,deviceNum,portType,info)values( %d, %d, '%s', '%s', '%s', '%s', '%s', '%s')"), m_listName, imoduleNum, islotNum, boardName, portNum, timeSlot, deviceNum, portType, info);
		theApp.m_pConnection->Execute((_bstr_t)sql,NULL,adCmdText);
		MessageBox(_T("¼��ɹ�."),_T("��ʾ"));

		//��ģ�顢��λ���˿ںź�������Ϣ��������
		sql.Format(_T("select * from %s order by %s.moduleNum,%s.slotNum,%s.portNum,%s.info asc"), m_inquerySQL, m_listName, m_listName, m_listName, m_listName);
		theApp.m_pRecordset = theApp.m_pConnection->Execute((_bstr_t)sql,NULL,adCmdText);
		DisplayInfo();
	}
	catch(_com_error &e)
	{
		MessageBox(e.Description());
	}
}

void CInfoDialog::OnModifyData()
{	
	//���ڽ���Ļ�Ͽؼ��е����ݽ�����������
	UpdateData(TRUE);


	getEditText();
	if(moduleNum.IsEmpty() || slotNum.IsEmpty() || boardName.IsEmpty() || info.IsEmpty())
	{
		AfxMessageBox(_T("���ȷ����д��Ϣ��!"),MB_ICONEXCLAMATION);
		return;
	}	
	if (m_cbModNum.GetCurSel() == 0)
	{
		AfxMessageBox(_T("��ѡ��Ҫ��ӽ���ģ��!"),MB_ICONEXCLAMATION);
		return;
	}
	if (idataID == 0)
	{
		AfxMessageBox(_T("��ѡ��Ҫ�޸ĵ�����!"),MB_ICONEXCLAMATION);
		return;
	}

	CString sql;
	sql.Format(_T("select * from main where dataID = %d"),idataID);
	theApp.m_pRecordset = theApp.m_pConnection->Execute((_bstr_t)sql,NULL,adCmdText);
	if(theApp.m_pRecordset->adoEOF)
	{
		AfxMessageBox(_T("���ݿ�û����Ҫ�޸ĵ���Ϣ!"),MB_ICONEXCLAMATION);
		return;
	}


	if(AfxMessageBox(_T("ȷ���޸�?"),MB_YESNO)==IDYES)
	{
		sql.Format(_T("update %s set moduleNum = %d,slotNum = %d,boardName = '%s',portNum = '%s',timeSlot = '%s',deviceNum = '%s',portType = '%s',info = '%s' where dataID = %d"), m_listName, imoduleNum, islotNum, boardName, portNum, timeSlot, deviceNum, portType, info, idataID);
		try
		{
			theApp.m_pConnection->Execute((_bstr_t)sql,NULL,adCmdText);
			MessageBox(_T("�޸ĳɹ�."),_T("��ʾ"));

		}
		catch(_com_error &e)
		{
			MessageBox(e.Description());
		}
	}
	UpdataList(0,0);
}

void CInfoDialog::OnDeleteData()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if(idataID == 0)
	{
		AfxMessageBox(_T("Ҫɾ������Ϣ����Ϊ��!"),MB_ICONEXCLAMATION);
		return;
	}
	try
	{
		CString sql;
		sql.Format(_T("select * from %s where dataID = %d"), m_listName,idataID);
		theApp.m_pRecordset = theApp.m_pConnection->Execute((_bstr_t)sql,NULL,adCmdText);
		if(theApp.m_pRecordset->adoEOF)
		{
			AfxMessageBox(_T("���ݿ�û����Ҫɾ������Ϣ!"),MB_ICONEXCLAMATION);
			return;
		}
		if(AfxMessageBox(_T("ȷ��Ҫɾ����������?"),MB_YESNO)==IDYES)
		{
			sql.Format(_T("delete from %s where dataID = %d"), m_listName, idataID);
			theApp.m_pConnection->Execute((_bstr_t)sql,NULL,adCmdText);
			MessageBox(_T("ɾ����Ϣ�ɹ�."));
		}
		sql.Format(_T("select * from %s"), m_listName);
		theApp.m_pRecordset=theApp.m_pConnection->Execute((_bstr_t)sql,NULL,adCmdText);
		DisplayInfo();
	}
	catch(_com_error &e)
	{
		MessageBox(e.Description());
	}
}

void CInfoDialog::OnClearData()
{
	dataID.Empty();
	moduleNum.Empty();
	slotNum.Empty();
	boardName.Empty();
	portNum.Empty();
	timeSlot.Empty();
	deviceNum.Empty();			
	portType.Empty();
	info.Empty();
	idataID = 0;
	imoduleNum = 0;
	islotNum = 0;

	/*m_modNum.SetWindowText(moduleNum);*/	
	m_cbModNum.SetCurSel(1);
	
	/*m_slotNum.SetWindowText(slotNum);*/	
	m_cbSlotNum.SetCurSel(0);
	
	m_boardName.SetWindowText(boardName);
	m_portNum.SetWindowText(portNum);
	m_timeSlot.SetWindowText(timeSlot);
	m_devNum.SetWindowText(deviceNum);
	m_portType.SetWindowText(portType);
	m_info.SetWindowText(info);
	UpdateData(FALSE);
}

void CInfoDialog::DisplayInfo()
{
	m_list.DeleteAllItems();
	
	m_containValue = 0;
	int index = 0;
	int maxDataID;
	_variant_t var;
	while(!theApp.m_pRecordset->adoEOF)
	{
		dataID.Empty();
		moduleNum.Empty();
		slotNum.Empty();
		boardName.Empty();
		portNum.Empty();
		timeSlot.Empty();
		deviceNum.Empty();			
		portType.Empty();
		info.Empty();
		idataID = 0;
		imoduleNum = 0;
		islotNum = 0;

		/*var = theApp.m_pRecordset->GetCollect("dataID");
		if(var.vt != VT_NULL)
		{
			dataID = (char*)(_bstr_t)var;
			m_list.InsertItem(index,dataID);

		}
		else
		{
			m_list.InsertItem(index,dataID);
		}

		maxDataID = _ttoi(dataID);
		if (m_containValue < maxDataID)
		{
			m_containValue = maxDataID;
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
			m_list.SetItemText(index,2,portNum);
		}*/

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


		/*maxDataID = _ttoi(dataID);
		if (m_containValue < maxDataID)
		{
			m_containValue = maxDataID;
		}*/

		var = theApp.m_pRecordset->GetCollect("moduleNum");
		if(var.vt != VT_NULL)
		{
			imoduleNum = var;				
			switch( imoduleNum )
			{
			case 1:
				moduleNum.Format(_T("ģ���"));
				break;
			case 2:
				moduleNum.Format(_T("ģ���"));
				break;
			case 3:
				moduleNum.Format(_T("ģ���"));
				break;
			default:
				moduleNum.Format(_T("other"));
			}
			/*moduleNum = (char*)(_bstr_t)var;*/
			m_list.SetItemText(index,1,moduleNum);

		}
		else
		{
			m_list.SetItemText(index,1,moduleNum);
		}

		var =theApp. m_pRecordset->GetCollect("slotNum");			
		if(var.vt != VT_NULL)
		{
			islotNum = var;
			/*slotNum = (char*)(_bstr_t)var;*/
			slotNum.Format(_T("%d"),islotNum);
			m_list.SetItemText(index,2,slotNum);

		}
		else
		{
			m_list.SetItemText(index,2,portNum);
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


		theApp.m_pRecordset->MoveNext();
		index ++;			
	}
}

void CInfoDialog::getEditText()
{
	/*m_modNum.GetWindowText(moduleNum);
	m_slotNum.GetWindowText(slotNum);*/
	/*m_cbModNum.GetLBText(m_cbModNum.GetCurSel(),moduleNum);	
	m_cbSlotNum.GetLBText(m_cbModNum.GetCurSel(),slotNum);*/
	
	m_cbModNum.GetLBText(m_cbModNum.GetCurSel(),moduleNum);	
	m_cbSlotNum.GetLBText(m_cbModNum.GetCurSel(),slotNum);

	imoduleNum = m_cbModNum.GetCurSel();
	islotNum = m_cbModNum.GetCurSel();

	m_boardName.GetWindowText(boardName);
	m_portNum.GetWindowText(portNum);
	m_timeSlot.GetWindowText(timeSlot);
	m_devNum.GetWindowText(deviceNum);
	m_portType.GetWindowText(portType);
	m_info.GetWindowText(info);		
}

LRESULT CInfoDialog::UpdataList(WPARAM wParam,LPARAM lParam)
{
	//��ģ�顢��λ���˿ںź�������Ϣ��������
	CString sql;
	sql.Format(_T("select * from %s order by %s.moduleNum,%s.slotNum,%s.portNum,%s.info asc"), m_inquerySQL, m_listName, m_listName, m_listName, m_listName);
	theApp.m_pRecordset = theApp.m_pConnection->Execute((_bstr_t)sql,NULL,adCmdText);
	DisplayInfo();
	return 1L;
}

void CInfoDialog::onSetDatabase(CString listName, CString modN, int mod, int bMod)
{
	//���ñ����� & ��Ҫ��ѯģ���
	m_inquerySQL.Empty();
	if (!listName.IsEmpty())
	{
		m_listName.Format(_T("%s"),listName);
	}
	else
	{
		m_listName.Format(_T("%s"),_T("main"));
	}
	
	if (bMod)
	{
		imoduleNum = mod;
		moduleNum.Format(_T("%s"),modN);
		m_inquerySQL.Format(_T("%s where moduleNum = %d"), m_listName, imoduleNum);
	}
	else
	{
		m_inquerySQL.Format(_T("%s"), m_listName);
	}
}