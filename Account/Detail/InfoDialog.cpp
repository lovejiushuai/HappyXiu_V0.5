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
	/*DDX_Text(pDX, IDC_BNAME, boardName);
	DDX_Text(pDX, IDC_DEVICENUM, deviceNum);
	DDX_Text(pDX, IDC_INFO, info);
	DDX_Text(pDX, IDC_MODNUM, moduleNum);
	DDX_Text(pDX, IDC_PORTNUM, portNum);
	DDX_Text(pDX, IDC_PORTTYPE, portType);
	DDX_Text(pDX, IDC_SLOTNUM, slotNum);
	DDX_Text(pDX, IDC_TIMESLOT, timeSlot);*/
	/*DDX_Control(pDX, IDC_BNAME, m_boardName);
	DDX_Control(pDX, IDC_DEVICENUM, m_devNum);
	DDX_Control(pDX, IDC_INFO, m_info);
	DDX_Control(pDX, IDC_MODNUM, m_modNum);
	DDX_Control(pDX, IDC_PORTNUM, m_portNum);
	DDX_Control(pDX, IDC_PORTTYPE, m_portType);
	DDX_Control(pDX, IDC_SLOTNUM, m_slotNum);
	DDX_Control(pDX, IDC_TIMESLOT, m_timeSlot);*/
}


BEGIN_MESSAGE_MAP(CInfoDialog, CDialog)
	/*ON_EN_CHANGE( IDC_BNAME, OnBoardName)
	ON_EN_CHANGE( IDC_DEVICENUM, OnDeviceNum)
	ON_EN_CHANGE( IDC_INFO, OnInfo)
	ON_EN_CHANGE( IDC_MODNUM, OnModuleNum)
	ON_EN_CHANGE( IDC_PORTNUM, OnPortNum)
	ON_EN_CHANGE( IDC_PORTTYPE, OnPortType)
	ON_EN_CHANGE( IDC_SLOTNUM, OnSlotNum)
	ON_EN_CHANGE( IDC_TIMESLOT, OnTimeSlot)*/
	ON_NOTIFY(NM_CLICK, IDC_LIST, OnClickList)
END_MESSAGE_MAP()


// CInfoDialog message handlers


BOOL CInfoDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	LoadControl();
	AddToGrid();


	/*OnInitADOConn();
	m_list.InsertColumn(0,_T("研究生编号"),LVCFMT_CENTER,100,-1);
	m_list.InsertColumn(1,_T("姓名"),LVCFMT_CENTER,80,-1);
	m_list.InsertColumn(2,_T("课程编号"),LVCFMT_CENTER,80,-1);
	m_list.InsertColumn(3,_T("课程名称"),LVCFMT_CENTER,100,-1);
	m_list.InsertColumn(4,_T("时间"),LVCFMT_CENTER,100,-1);
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	CString sql,stuNum,couNum,stuName,couName,time;
	int index=0;
	try
	{
		sql=_T("select * from students,courses,choices where \
			choices.stuID=students.stuID and choices.couID=courses.couID \
			order by students.stuID,choices.couID asc");			//按学号和课程号升序排序
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

void CInfoDialog::LoadControl()
{
	// 获取当前屏幕分辨率  -- 但不包括状态栏大小
	int screenwidth=GetSystemMetrics(SM_CXFULLSCREEN);
	int screenheight=GetSystemMetrics(SM_CYFULLSCREEN);

	CRect m_rcPanel;
	//设置当前窗口大小  与 当前屏幕分辨率 一致
	m_rcPanel.SetRect(0,0,screenwidth,screenheight);
	MoveWindow(&m_rcPanel);


	// 根据屏幕分辨率 & 窗口大小设置 List 大小
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
		rect.bottom=300;
		pwnd->MoveWindow(&rect,TRUE);
		pwnd = NULL;
	}

	CDC *pDC = GetDC();
	pDC->TextOutW(500,500,_T("TEXT"));
	ReleaseDC(pDC);

	m_modNum.Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(0.1 * screenwidth, 0.7 * screenheight, 0.2* screenwidth, 0.75 * screenheight), this, IDC_MODNUM);
	m_slotNum.Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(0.35 * screenwidth, 0.7 * screenheight, 0.45* screenwidth, 0.75 * screenheight), this, IDC_BNAME);
	m_boardName.Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(0.6 * screenwidth, 0.7 * screenheight, 0.7* screenwidth, 0.75 * screenheight), this, IDC_BNAME);
	m_portNum.Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(0.85 * screenwidth, 0.7 * screenheight, 0.95* screenwidth, 0.75 * screenheight), this, IDC_PORTNUM);
	m_timeSlot.Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(0.1 * screenwidth, 0.78 * screenheight, 0.2* screenwidth, 0.83 * screenheight), this, IDC_TIMESLOT);
	m_devNum.Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(0.35 * screenwidth, 0.78 * screenheight, 0.45* screenwidth, 0.83 * screenheight), this, IDC_DEVICENUM);
	m_portType.Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(0.6 * screenwidth, 0.78 * screenheight, 0.7* screenwidth, 0.83 * screenheight), this, IDC_PORTTYPE);
	m_info.Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(0.85 * screenwidth, 0.78 * screenheight, 0.95* screenwidth, 0.83 * screenheight), this, IDC_INFO);

	// 创建四个按键
	m_addButton.Create( _T("添加"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, CRect( 0.07 * screenwidth, 0.85 * screenheight, 0.22* screenwidth, 0.95 * screenheight), this, IDC_BUTTON_ADD);
	m_modifyButton.Create(_T("修改"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, CRect( 0.32 * screenwidth, 0.85 * screenheight, 0.47 * screenwidth, 0.95 * screenheight), this, IDC_BUTTON_MODIFY);
	m_deleteButton.Create(_T("删除"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, CRect( 0.57 * screenwidth, 0.85 * screenheight, 0.75 * screenwidth, 0.95 * screenheight), this, IDC_BUTTON_DELETE);
	m_clearButton.Create(_T("清除"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, CRect( 0.82 * screenwidth, 0.85 * screenheight, 0.97 * screenwidth, 0.95 * screenheight), this, IDC_BUTTON_CLEAR);

	m_addButton.EnableWindow(TRUE);
	m_deleteButton.EnableWindow(TRUE);
	m_modifyButton.EnableWindow(TRUE);
	m_clearButton.EnableWindow(TRUE);

}

void CInfoDialog::OnInitADOConn()
{
	//if(!AfxOleInit())//这就是初始化COM库
	//{
	//	AfxMessageBox(_T("KE初始化出错!"));
	//}

	//CoInitialize(NULL);
	//HRESULT hr;
	//try                            //连接数据库
	//{
	//	hr = m_pConnection.CreateInstance(__uuidof(Connection)/*"ADODB.Connection"*/);
	//	if(SUCCEEDED(hr))
	//	{
	//		m_pConnection->ConnectionTimeout = 10;	//连接超时
	//		m_pConnection->CursorLocation = adUseClient;//作用于记录集指针，非常重要!!!
	//		m_pConnection->ConnectionString = "File Name=happyXiu.udl";
	//		m_pConnection->Open("","","",-1);
	//	}
	//}
	//catch(_com_error e)
	//{
	//	CString str;
	//	str.Format(_T("连接数据库失败:%s"),e.ErrorMessage());
	//	::MessageBox(NULL,str,_T("提示信息"),NULL);
	//	//return false;
	//}
}

void CInfoDialog::ExitConnect()
{
	//关闭记录集和连接

	/*if(m_pRecordset!=NULL)
		m_pRecordset->Close();

	if(m_pConnection!=NULL)
	m_pConnection->Close();*/
	//CoUninitialize();	//退出com库
}

void CInfoDialog::AddToGrid()
{
	//连接数据库
	/*OnInitADOConn();*/

	m_list.InsertColumn(0,_T("编号"),LVCFMT_LEFT,50,0);
	m_list.InsertColumn(1,_T("模块"),LVCFMT_LEFT,80,1);
	m_list.InsertColumn(2,_T("槽位"),LVCFMT_LEFT,50,2);
	m_list.InsertColumn(3,_T("板名"),LVCFMT_LEFT,110,3);
	m_list.InsertColumn(4,_T("端口号"),LVCFMT_LEFT,50,4);
	m_list.InsertColumn(5,_T("使用时隙号"),LVCFMT_LEFT,110,5);
	m_list.InsertColumn(6,_T("设备号"),LVCFMT_LEFT,110,6);
	m_list.InsertColumn(7,_T("端口类型"),LVCFMT_LEFT,110,7);
	m_list.InsertColumn(8,_T("描述"),LVCFMT_LEFT,200,8);
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	CString sql;
	
	int index=0;
	try
	{
		sql=_T("select * from main");			//按学号和课程号升序排序
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
							

			theApp.m_pRecordset->MoveNext();
			index++;
		}

	}
	catch(_com_error &e)
	{
		MessageBox(e.Description());
	}
	//断开数据库连接
	/*ExitConnect();
	CoUninitialize();*/	//退出com库

}


void CInfoDialog::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::OnCancel();
	//断开数据库连接
	ExitConnect();
}

void CInfoDialog::OnClickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int mark = m_list.GetSelectionMark();
	if(mark<0) 
		return;
	
	dataID = m_list.GetItemText(mark,0);
	moduleNum = m_list.GetItemText(mark,1);
	m_modNum.SetWindowText(moduleNum);

	slotNum = m_list.GetItemText(mark,2);
	m_slotNum.SetWindowText(slotNum);

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

	UpdateData(false);
	*pResult = 0;
}

void CInfoDialog::OnModuleNum() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();

	if(boardName.IsEmpty())
	{
		return;
	}
	/*CString sql,sql2;
	sql="select * from students,courses,choices where \
	choices.stuID=students.stuID and choices.couID=courses.couID \
	and choices.stuID="+m_stuID+" order by choices.couID";
	sql2="select * from students where stuID="+m_stuID+"";
	try
	{
	m_rec=theApp.m_conn->Execute((_bstr_t)sql2,NULL,adCmdText);
	if(m_rec->adoEOF)
	{
	m_stuName="无";
	UpdateData(false);
	return;
	}
	m_stuName=(char*)(_bstr_t)m_rec->GetCollect("stuName");
	m_rec=theApp.m_conn->Execute((_bstr_t)sql,NULL,adCmdText);
	DisplayInfo();
	UpdateData(false);
	}
	catch(_com_error &e)
	{
	MessageBox(e.Description());
	}*/	

}
void CInfoDialog::OnSlotNum() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	UpdateData();
	
	if(boardName.IsEmpty())
	{
		return;
	}
	/*CString sql,sql2;
	sql="select * from students,courses,choices where \
	choices.stuID=students.stuID and choices.couID=courses.couID \
	and choices.stuID="+m_stuID+" order by choices.couID";
	sql2="select * from students where stuID="+m_stuID+"";
	try
	{
	m_rec=theApp.m_conn->Execute((_bstr_t)sql2,NULL,adCmdText);
	if(m_rec->adoEOF)
	{
	m_stuName="无";
	UpdateData(false);
	return;
	}
	m_stuName=(char*)(_bstr_t)m_rec->GetCollect("stuName");
	m_rec=theApp.m_conn->Execute((_bstr_t)sql,NULL,adCmdText);
	DisplayInfo();
	UpdateData(false);
	}
	catch(_com_error &e)
	{
	MessageBox(e.Description());
	}*/	

}
void CInfoDialog::OnBoardName() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	UpdateData();

	if(boardName.IsEmpty())
	{
		return;
	}
	/*CString sql,sql2;
	sql="select * from students,courses,choices where \
	choices.stuID=students.stuID and choices.couID=courses.couID \
	and choices.stuID="+m_stuID+" order by choices.couID";
	sql2="select * from students where stuID="+m_stuID+"";
	try
	{
	m_rec=theApp.m_conn->Execute((_bstr_t)sql2,NULL,adCmdText);
	if(m_rec->adoEOF)
	{
	m_stuName="无";
	UpdateData(false);
	return;
	}
	m_stuName=(char*)(_bstr_t)m_rec->GetCollect("stuName");
	m_rec=theApp.m_conn->Execute((_bstr_t)sql,NULL,adCmdText);
	DisplayInfo();
	UpdateData(false);
	}
	catch(_com_error &e)
	{
	MessageBox(e.Description());
	}*/	

}
void CInfoDialog::OnPortNum() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	UpdateData();
	
	if(boardName.IsEmpty())
	{
		return;
	}
	/*CString sql,sql2;
	sql="select * from students,courses,choices where \
	choices.stuID=students.stuID and choices.couID=courses.couID \
	and choices.stuID="+m_stuID+" order by choices.couID";
	sql2="select * from students where stuID="+m_stuID+"";
	try
	{
	m_rec=theApp.m_conn->Execute((_bstr_t)sql2,NULL,adCmdText);
	if(m_rec->adoEOF)
	{
	m_stuName="无";
	UpdateData(false);
	return;
	}
	m_stuName=(char*)(_bstr_t)m_rec->GetCollect("stuName");
	m_rec=theApp.m_conn->Execute((_bstr_t)sql,NULL,adCmdText);
	DisplayInfo();
	UpdateData(false);
	}
	catch(_com_error &e)
	{
	MessageBox(e.Description());
	}*/	

}
void CInfoDialog::OnTimeSlot() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	UpdateData();
	
	if(boardName.IsEmpty())
	{
		return;
	}
	/*CString sql,sql2;
	sql="select * from students,courses,choices where \
	choices.stuID=students.stuID and choices.couID=courses.couID \
	and choices.stuID="+m_stuID+" order by choices.couID";
	sql2="select * from students where stuID="+m_stuID+"";
	try
	{
	m_rec=theApp.m_conn->Execute((_bstr_t)sql2,NULL,adCmdText);
	if(m_rec->adoEOF)
	{
	m_stuName="无";
	UpdateData(false);
	return;
	}
	m_stuName=(char*)(_bstr_t)m_rec->GetCollect("stuName");
	m_rec=theApp.m_conn->Execute((_bstr_t)sql,NULL,adCmdText);
	DisplayInfo();
	UpdateData(false);
	}
	catch(_com_error &e)
	{
	MessageBox(e.Description());
	}*/	

}
void CInfoDialog::OnDeviceNum() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	UpdateData();
	
	if(boardName.IsEmpty())
	{
		return;
	}
	/*CString sql,sql2;
	sql="select * from students,courses,choices where \
	choices.stuID=students.stuID and choices.couID=courses.couID \
	and choices.stuID="+m_stuID+" order by choices.couID";
	sql2="select * from students where stuID="+m_stuID+"";
	try
	{
	m_rec=theApp.m_conn->Execute((_bstr_t)sql2,NULL,adCmdText);
	if(m_rec->adoEOF)
	{
	m_stuName="无";
	UpdateData(false);
	return;
	}
	m_stuName=(char*)(_bstr_t)m_rec->GetCollect("stuName");
	m_rec=theApp.m_conn->Execute((_bstr_t)sql,NULL,adCmdText);
	DisplayInfo();
	UpdateData(false);
	}
	catch(_com_error &e)
	{
	MessageBox(e.Description());
	}*/	

}
void CInfoDialog::OnPortType() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	UpdateData();
	
	if(boardName.IsEmpty())
	{
		return;
	}
	/*CString sql,sql2;
	sql="select * from students,courses,choices where \
	choices.stuID=students.stuID and choices.couID=courses.couID \
	and choices.stuID="+m_stuID+" order by choices.couID";
	sql2="select * from students where stuID="+m_stuID+"";
	try
	{
	m_rec=theApp.m_conn->Execute((_bstr_t)sql2,NULL,adCmdText);
	if(m_rec->adoEOF)
	{
	m_stuName="无";
	UpdateData(false);
	return;
	}
	m_stuName=(char*)(_bstr_t)m_rec->GetCollect("stuName");
	m_rec=theApp.m_conn->Execute((_bstr_t)sql,NULL,adCmdText);
	DisplayInfo();
	UpdateData(false);
	}
	catch(_com_error &e)
	{
	MessageBox(e.Description());
	}*/	

}
void CInfoDialog::OnInfo() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	UpdateData();
	
	if(boardName.IsEmpty())
	{
		return;
	}
	/*CString sql,sql2;
	sql="select * from students,courses,choices where \
	choices.stuID=students.stuID and choices.couID=courses.couID \
	and choices.stuID="+m_stuID+" order by choices.couID";
	sql2="select * from students where stuID="+m_stuID+"";
	try
	{
	m_rec=theApp.m_conn->Execute((_bstr_t)sql2,NULL,adCmdText);
	if(m_rec->adoEOF)
	{
	m_stuName="无";
	UpdateData(false);
	return;
	}
	m_stuName=(char*)(_bstr_t)m_rec->GetCollect("stuName");
	m_rec=theApp.m_conn->Execute((_bstr_t)sql,NULL,adCmdText);
	DisplayInfo();
	UpdateData(false);
	}
	catch(_com_error &e)
	{
	MessageBox(e.Description());
	}*/	

}
